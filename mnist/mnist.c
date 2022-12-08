#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define TRAIN_IMAGE "train-images-idx3-ubyte"
#define TRAIN_LABEL "train-labels-idx1-ubyte"

#define image_pos(a, b) (a->data + b * 784)
#define label_pos(a, b) (a->data + b * 10)
#define at(o, a, b) o->data[a * o->cols + b]

#define max_(a, b) (((a) > (b)) ? (a) : (b))
#define min_(a, b) (((a) < (b)) ? (a) : (b))

// struct
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
	FILE *fp;
	int sz, t, w, h, n, i, j;
	char buf[4];

	fp = fopen(fn, "rb");
	if (fp == NULL)
		goto end;
	fseek(fp, 0, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	fread(buf, 1, 4, fp);
	t = buf2int(buf);
	if (t != 0x803)
		goto end;

	fread(buf, 1, 4, fp);
	n = buf2int(buf);
	fread(buf, 1, 4, fp);
	w = buf2int(buf);
	fread(buf, 1, 4, fp);
	h = buf2int(buf);
	if (h * w != 784)
		goto end;

	printf("%d\n", n);
	ret = create_tensor(n, 784);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 784; j++)
		{
			fread(buf, 1, 1, fp);
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
	FILE *fp;
	int sz, t, n, i, j;
	char buf[4];

	fp = fopen(fn, "rb");
	if (fp == NULL)
		goto end;
	fseek(fp, 0, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	fread(buf, 1, 4, fp);
	t = buf2int(buf);
	if (t != 0x801)
		goto end;

	fread(buf, 1, 4, fp);
	n = buf2int(buf);
	ret = create_tensor(n, 10);
	for (i = 0; i < n; i++)
	{
		fread(buf, 1, 1, fp);
		for (j = 0; j < 10; j++)
		{
			ret->data[i * 10 + j] = (float)((j == buf[0]) ? 1 : 0);
		}
	}
end:
	if (fp)
		fclose(fp);
	return ret;
}

static void print_image(float *a)
{
	int w = 28, h = 28, i, j;
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			printf("%s", *a == 0 ? "--" : "11");
			a++;
		}
		printf("\n");
	}
	printf("\n");
}

static void print_label(float *a)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		printf("%d: %f\n", i, a[i]);
	}
	printf("\n");
}

int main()
{
	int input = 28 * 28;

	struct tensor *a, *b;

	a = load_image_file(TRAIN_IMAGE);
	b = load_label_file(TRAIN_LABEL);

	free_tensor(a);
	free_tensor(b);

	return 0;
}
