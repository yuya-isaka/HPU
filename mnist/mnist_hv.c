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
	struct tensor *label = load_label_file(TRAIN_LABEL);

	// 784個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = image->cols;
	hv_t **item_memory = hv_make_imem(RAND_NUM);

	// 0-9の結果
	hv_t **result = hv_make_array(10);

	for (int i = 0; i < 10; i++)
	{
		hv_init();

		char PATH[12];
		snprintf(PATH, 12, "label%d.txt", i);
		FILE *file;
		file = fopen(PATH, "r");
		char Lines[10];
		// ここで作業
		while (fgets(Lines, 10, file) != NULL)
		{
			int *perm_num = image_pos(image, atoi(Lines));
			for (int k = 0; k < 28; k++)
			{
				for (int l = 0; l < 28; l++)
				{
					// printf("perm_num: %d\n", *perm_num);
					hv_t *perm_result = hv_perm(item_memory[k + l], *perm_num);
					perm_num++;

					// bound
					hv_bound(perm_result);

					hv_free(perm_result);
				}
			}
		}
		fclose(file);

		hv_t *result_tmp = hv_bound_result();
		hv_copy(result[i], result_tmp);

		hv_free(result_tmp);
		hv_finish();
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d:\n", i);
		hv_print(result[i]);
		printf("\n");
	}

	hv_free_array(result, 10);
	hv_free_array(item_memory, RAND_NUM);

	free_tensor(image);
	free_tensor(label);

	return 0;
}