#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include "hyper_vector.h"

// Mac
#ifdef __MACH__
// Debug
#ifdef DEBUG
// lead error
__attribute__((destructor)) static void destructor()
{
	system("leaks -q mnist");
}
#endif
#endif

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

static struct tensor *copy_tensor(struct tensor *a)
{
	struct tensor *ret;
	ret = malloc(sizeof(struct tensor));
	ret->data = malloc(sizeof(int) * a->rows * a->cols);
	memcpy(ret->data, a->data, sizeof(int) * a->rows * a->cols);
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

	FILE *file = fopen("mnist_image.bin", "wb");
	int save_buf_zero = 0;
	int save_buf_one = 1;

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
				fwrite(&save_buf_zero, 1, 1, file);
			}
			else
			{
				ret->data[i * 784 + j] = 1;
				fwrite(&save_buf_one, 1, 1, file);
			}
		}
	}

	fclose(fp);
	fclose(file);

	return ret;
}

static void load_image_file_2(const char *fn)
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

	for (int ll = 0; ll < 10; ll++)
	{
		char PATH[12];
		snprintf(PATH, 12, "label%d.txt", ll);
		FILE *file;
		file = fopen(PATH, "r");
		char Lines[10];

		char PATH_NEW[12];
		snprintf(PATH_NEW, 12, "image%d.txt", ll);
		FILE *file_new;
		file_new = fopen(PATH_NEW, "w");

		while (fgets(Lines, 10, file) != NULL) // 6000回ぐらい？
		{
			// printf("%d\n", n); // 60000
			for (int i = 0; i < n; i++)
			{
				if (atoi(Lines) == i)
				{
					for (int j = 0; j < 784; j++)
					{
						DONE = fread(buf, 1, 1, fp);
						if ((int)(buf[0]) == 0)
						{
							fprintf(file_new, "%d", 0);
						}
						else
						{
							fprintf(file_new, "%d", 1);
						}
					}
				}
			}
		}
		fclose(file);
	}

	fclose(fp);
	return;
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
			// printf("%s", *a == 0 ? "0" : "1");
			// printf("%s", *a == 0 ? "--" : "11");
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

int read_file(const char *PATH)
{
	FILE *file;
	file = fopen(PATH, "r");
	// fopen_sはfopenのセキュリティ強化版

	char Lines[10];
	uint32_t num = 0;
	//	NULLポインタの終端までファイルから文字を1行ずつ読み込む
	while (fgets(Lines, 10, file) != NULL)
	{
		//	読み込んだ1行を画面に出力する
		// printf("%s", Lines);
		num++;
	}

	fclose(file);

	return num;
}

int main()
{
	// // image->rows = 60000
	// // image->cols = 784

	//////////////////////////////////////////////////////////////////////////////////////////////

	// // mnist_image.bin生成
	// struct tensor *image = load_image_file(TRAIN_IMAGE);
	// struct tensor *label = load_label_file(TRAIN_LABEL);

	// // image0 - image10.txt生成
	load_image_file_2(TRAIN_IMAGE);

	//////////////////////////////////////////////////////////////////////////////////////////////

	// // label0 - label10.txt生成
	// // 0 - 10
	// FILE *fp;
	// fp = fopen("label1.txt", "w");
	// for (int j = 0; j < image->rows; j++) // 60000
	// {
	// 	// 0 - 10
	// 	if (label_pos(label, j) == 1)
	// 	{
	// 		fprintf(fp, "%d\n", j);
	// 	}
	// }
	// fclose(fp);

	//////////////////////////////////////////////////////////////////////////////////////////////

	// // 読み込みチェック
	// int all_num = 0;
	// for (int i = 0; i < 10; i++)
	// {
	// 	char buf[12];
	// 	snprintf(buf, 12, "label%d.txt", i);
	// 	printf("%s\n", buf);

	// 	int num = read_file(buf);
	// 	all_num += num;
	// }
	// printf("\nall_num: %d\n\n", all_num);

	// free_tensor(image);
	// free_tensor(label);

	return 0;
}