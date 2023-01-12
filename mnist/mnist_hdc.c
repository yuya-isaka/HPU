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
	int *data;
	int cols;
	int rows;
};

static struct tensor *create_tensor(int rows, int cols)
{
	struct tensor *ret;
	ret = malloc(sizeof(struct tensor));
	ret->data = malloc(sizeof(int) * rows * cols);
	memset(ret->data, 0, sizeof(int) * rows * cols);
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

	fseek(fp, 0, SEEK_END);

	int sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	size_t DONE;
	DONE = fread(buf, 1, 4, fp);
	int t = buf2int(buf);

	DONE = fread(buf, 1, 4, fp);
	int n = buf2int(buf);
	DONE = fread(buf, 1, 4, fp);
	int w = buf2int(buf);
	DONE = fread(buf, 1, 4, fp);
	int h = buf2int(buf);

	// printf("%d\n", n); // 60000
	ret = create_tensor(n, 784);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 784; j++)
		{
			DONE = fread(buf, 1, 1, fp);
			if ((int)(buf[0]) == 0)
			{
				ret->data[i * 784 + j] = 0;
			}
			else
			{
				ret->data[i * 784 + j] = 1;
			}
		}
	}

	fclose(fp);

	return ret;
}

static struct tensor *load_label_file(const char *fn)
{
	struct tensor *ret = NULL;
	char buf[4];

	FILE *fp = fopen(fn, "rb");

	fseek(fp, 0, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	size_t DONE;
	DONE = fread(buf, 1, 4, fp);
	int t = buf2int(buf);

	DONE = fread(buf, 1, 4, fp);
	int n = buf2int(buf);
	ret = create_tensor(n, 1);
	for (int i = 0; i < n; i++)
	{
		DONE = fread(buf, 1, 1, fp);
		ret->data[i] = (int)buf[0];
	}

	fclose(fp);
	return ret;
}

static void print_image(int *a)
{
	int w = 28;
	int h = 28;
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			printf("%d", *a);
			a++;
		}
		printf("\n");
	}
	printf("\n");
}

static void print_label(int *a)
{
	printf("%d\n\n", *a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// image->rows = 60000
	// image->cols = 784
	struct tensor *image = load_image_file(TRAIN_IMAGE);
	// struct tensor *label = load_label_file(TRAIN_LABEL);

	// 784個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = image->cols;
	const uint32_t FIRST_RAND_NUM = 490;
	const uint32_t SECOND_RAND_NUM = RAND_NUM - FIRST_RAND_NUM;

	// コア数
	const int CORENUM = 14;

	// メモリセットアップ
	hdc_setup();

	for (int ll = 0; ll < 10; ll++)
	{
		// 490
		hdc_make_imem(FIRST_RAND_NUM);
		hdc_init(0);
		hdc_start();

		char PATH[12];
		snprintf(PATH, 12, "label%d.txt", ll);
		FILE *file;
		file = fopen(PATH, "r");
		char Lines[10];
		while (fgets(Lines, 10, file) != NULL) // 6000回ぐらい？
		{
			int *perm_num = image_pos(image, atoi(Lines));
			int index_num = 0;

			for (int j = 0; j < 7; j++)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array[THREADS_NUM][core_num];
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = index_num;
						index_num++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// permute ---------------------------------------------
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						hdc_permute(*perm_num);
						perm_num++;
					}
					for (int i = 0; i < 2; i++)
					{
						hdc_nop();
					}
				}
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_simd_pstore_thread();
				// ------------------------------------------------------
			}
		}
		fclose(file);

		hdc_last();
		hdc_compute();

		// 294
		hdc_make_imem_2(SECOND_RAND_NUM);
		hdc_init(0);
		snprintf(PATH, 12, "label%d.txt", ll);
		file = fopen(PATH, "r");
		while (fgets(Lines, 10, file) != NULL) // 6000回ぐらい？
		{
			int *perm_num = image_pos(image, atoi(Lines)) + 490;
			int index_num = 0;

			for (int j = 0; j < 4; j++)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array[THREADS_NUM][core_num];
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = index_num;
						index_num++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// permute ---------------------------------------------
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						hdc_permute(*perm_num);
						perm_num++;
					}
					for (int i = 0; i < 2; i++)
					{
						hdc_nop();
					}
				}
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_simd_pstore_thread();
				// ------------------------------------------------------
			}

			// 残り
			uint16_t core_num = CORENUM;
			uint16_t thread_num = 1;

			uint16_t addr_array[thread_num][core_num];
			for (int k = 0; k < thread_num; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = index_num;
					index_num++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(thread_num, core_num, addr_array);
			// ------------------------------------------------------

			// permute ---------------------------------------------
			for (int k = 0; k < thread_num; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					hdc_permute(*perm_num);
					perm_num++;
				}
				for (int i = 0; i < 2; i++)
				{
					hdc_nop();
				}
			}
			for (int k = thread_num; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < 16; i++)
				{
					hdc_nop();
				}
			}
			// ------------------------------------------------------

			// pstore ---------------------------------------------
			hdc_pstore_thread(thread_num, core_num);
			// ------------------------------------------------------
		}
		fclose(file);

		hdc_last();
		hdc_compute();

		// 結果確認
		printf("\n%d:\n", ll);
		for (int j = 0; j < 32; j++)
		{
			printf("  %u\n", dst[j]);
		}

		hdc_finish();
	}

	free_tensor(image);
	// free_tensor(label);

	printf("\n\n\n");
	return 0;
}