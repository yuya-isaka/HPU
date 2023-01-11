#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <fcntl.h>	  // open
#include <unistd.h>	  // read
#include <sys/mman.h> // mmap
#include <time.h>
#include "hdc_processor.h"

#define TRAIN_IMAGE "train-images-idx3-ubyte"
#define TRAIN_LABEL "train-labels-idx1-ubyte"

#define image_pos(a, b) (a->data + b * 784)
#define at(o, a, b) o->data[a * o->cols + b]

#define label_pos(a, b) (a->data + b)

struct tensor
{
	float *data;
	int cols;
	int rows;
};

static struct tensor *create_tensor(int rows, int cols)
{
	struct tensor *ret;
	ret = malloc(sizeof(struct tensor));
	ret->data = malloc(sizeof(float) * rows * cols);
	memset(ret->data, 0, sizeof(float) * rows * cols);
	ret->cols = cols;
	ret->rows = rows;
	return ret;
}

static void free_tensor(struct tensor *t)
{
	if (t && t->data)
		free(t->data);
	if (t)
		free(t);
}

static struct tensor *copy_tensor(struct tensor *a)
{
	struct tensor *ret;
	ret = malloc(sizeof(struct tensor));
	ret->data = malloc(sizeof(float) * a->rows * a->cols);
	memcpy(ret->data, a->data, sizeof(float) * a->rows * a->cols);
	ret->cols = a->cols;
	ret->rows = a->rows;
	return ret;
}

static int buf2int(char *buf_)
{
	int ret;
	unsigned char *buf = (unsigned char *)buf_;

	ret = buf[0];
	ret <<= 8;
	ret |= buf[1];
	ret <<= 8;
	ret |= buf[2];
	ret <<= 8;
	ret |= buf[3];
	return ret;
}

static struct tensor *load_image_file(const char *fn)
{
	struct tensor *ret = NULL;
	char buf[4];

	FILE *fp = fopen(fn, "rb");

	if (fp == NULL)
		goto end;
	fseek(fp, 0, SEEK_END);

	int sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	size_t DONE;
	DONE = fread(buf, 1, 4, fp);
	int t = buf2int(buf);
	if (t != 0x803)
		goto end;

	DONE = fread(buf, 1, 4, fp);
	int n = buf2int(buf);
	DONE = fread(buf, 1, 4, fp);
	int w = buf2int(buf);
	DONE = fread(buf, 1, 4, fp);
	int h = buf2int(buf);
	if (h * w != 784)
		goto end;

	// printf("%d\n", n); // 60000
	ret = create_tensor(n, 784);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 784; j++)
		{
			DONE = fread(buf, 1, 1, fp);
			ret->data[i * 784 + j] = (float)(buf[0] & 255) / 255;
		}
	}

end:
	if (fp)
		fclose(fp);
	return ret;
}

static struct tensor *load_label_file(const char *fn)
{
	struct tensor *ret = NULL;
	char buf[4];

	FILE *fp = fopen(fn, "rb");
	if (fp == NULL)
		goto end;
	fseek(fp, 0, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	size_t DONE;
	DONE = fread(buf, 1, 4, fp);
	int t = buf2int(buf);
	if (t != 0x801)
		goto end;

	DONE = fread(buf, 1, 4, fp);
	int n = buf2int(buf);
	ret = create_tensor(n, 1);
	for (int i = 0; i < n; i++)
	{
		DONE = fread(buf, 1, 1, fp);
		ret->data[i] = (float)buf[0];
	}
end:
	if (fp)
		fclose(fp);
	return ret;
}

static void print_image(float *a)
{
	int w = 28;
	int h = 28;
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			// printf("%s", *a == 0 ? "0" : "1");
			printf("%s", *a == 0 ? "--" : "11");
			a++;
		}
		printf("\n");
	}
	printf("\n");
}

static int get_perm_num(float *a)
{
	if (*a == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

static void print_label(float *a)
{
	printf("%d\n", (int)*a);
	printf("\n");
}

static int get_label(float *a)
{
	return (int)*a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// load
	struct tensor *image = load_image_file(TRAIN_IMAGE);
	struct tensor *label = load_label_file(TRAIN_LABEL);

	// 784個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = image->cols;

	// 512,272に分けて作る

	const int RANNUM = 512;

	const int INSTRUCTION_NUM = 4;

	// DMA SEND_MAX
	int SEND_MAX = 33000000;
	const int SEND_TMP = SEND_MAX % (THREADS_NUM * 16 * INSTRUCTION_NUM);
	SEND_MAX += SEND_TMP;

	// コア数
	const int CORENUM = 14;

	// hv -----------------------------
	// メモリセットアップ
	hdc_setup();

	// アイテムメモリ生成
	hdc_make_imem(RANNUM);
	// hv -----------------------------

	// 試行回数
	// 100万回
	const int TRIAL_NUM = 60000;

	const int EPOCH = TRIAL_NUM / (CORENUM * THREADS_NUM);
	const int REMAINDAR = TRIAL_NUM % (CORENUM * THREADS_NUM);
	const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;
	const int LAST = EPOCH * CORENUM * THREADS_NUM;

	int ALL_SEND_NUM = SEND_MAX / (THREADS_NUM * 16 * INSTRUCTION_NUM) * 70;
	const int ALL_SEND_EPOCH = LAST / ALL_SEND_NUM;
	const int ALL_SEND_REMAIN = LAST % ALL_SEND_NUM;

	// printf("ALL_SEND_EPOCH: %d\n", ALL_SEND_EPOCH);
	// printf("ALL_SEND_NUM: %d\n", ALL_SEND_NUM);
	// printf("ALL_SEND_REMAIN: %d\n", ALL_SEND_REMAIN);
	// printf("REMAINDAR: %d\n", REMAINDAR);
	// printf("合計命令: %d\n", ALL_SEND_EPOCH * ALL_SEND_NUM + ALL_SEND_REMAIN + REMAINDAR);

	double COM_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	hdc_start();

	hdc_init(0);

	// SEND_NUMのエポック
	for (int ll = 0; ll < ALL_SEND_EPOCH; ll += 1)
	{
		// SEND_NUM繰り返す
		for (int j = 0; j < ALL_SEND_NUM; j += CORENUM * THREADS_NUM)
		{
			int tmp = 0;

			uint16_t core_num = CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = tmp;
				}
			}
			tmp++;

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// perm ---------------------------------------------
			hdc__thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// move ---------------------------------------------
			hdc_simd_move_thread();
			// ------------------------------------------------------

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array2);
			// ------------------------------------------------------

			// xor ---------------------------------------------
			hdc_simd_xor_thread();
			// ------------------------------------------------------
		}
	}

	// SEND_NUMエポックのあまり
	for (int j = 0; j < ALL_SEND_REMAIN; j += CORENUM * THREADS_NUM)
	{
		uint16_t core_num = CORENUM;

		uint16_t addr_array1[THREADS_NUM][core_num];
		uint16_t addr_array2[THREADS_NUM][core_num];

		// アドレス
		for (int k = 0; k < THREADS_NUM; k++)
		{
			for (int i = 0; i < core_num; i++)
			{
				addr_array1[k][i] = rand_array[rand_array_num++];
				addr_array2[k][i] = rand_array[rand_array_num++];
			}
		}

		// load ---------------------------------------------
		hdc_load_thread(THREADS_NUM, core_num, addr_array1);
		// ------------------------------------------------------

		// move ---------------------------------------------
		hdc_simd_move_thread();
		// ------------------------------------------------------

		// load ---------------------------------------------
		hdc_load_thread(THREADS_NUM, core_num, addr_array2);
		// ------------------------------------------------------

		// xor ---------------------------------------------
		hdc_simd_xor_thread();
		// ------------------------------------------------------
	}

	// 最後の余り
	if (REMAINDAR != 0)
	{
		uint16_t core_num = REMAINDAR_CORENUM;

		uint16_t addr_array1[THREADS_NUM][core_num];
		uint16_t addr_array2[THREADS_NUM][core_num];

		// アドレス
		for (int k = 0; k < THREADS_NUM; k++)
		{
			for (int i = 0; i < core_num; i++)
			{
				addr_array1[k][i] = rand_array[rand_array_num++];
				addr_array2[k][i] = rand_array[rand_array_num++];
			}
		}

		// load ---------------------------------------------
		hdc_load_thread(THREADS_NUM, core_num, addr_array1);
		// ------------------------------------------------------

		// move ---------------------------------------------
		hdc_move_thread(THREADS_NUM, core_num);
		// ------------------------------------------------------

		// load ---------------------------------------------
		hdc_load_thread(THREADS_NUM, core_num, addr_array2);
		// ------------------------------------------------------

		// xor ---------------------------------------------
		hdc_xor_thread(THREADS_NUM, core_num);
		// ------------------------------------------------------
	}

	// ラスト命令
	hdc_last();

	START_COMPUTE = clock();
	hdc_compute();
	END_COMPUTE = clock();
	COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

	hdc_finish();

	printf("\n  計算時間: %lf[s]\n", COM_TIME);

	free_tensor(image);
	free_tensor(label);

	return 0;
}