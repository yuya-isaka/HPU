#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

	fread(buf, 1, 4, fp);
	int t = buf2int(buf);
	if (t != 0x803)
		goto end;

	fread(buf, 1, 4, fp);
	int n = buf2int(buf);
	fread(buf, 1, 4, fp);
	int w = buf2int(buf);
	fread(buf, 1, 4, fp);
	int h = buf2int(buf);
	if (h * w != 784)
		goto end;

	// printf("%d\n", n); // 60000
	ret = create_tensor(n, 784);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 784; j++)
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
	ret = create_tensor(n, 1);
	for (i = 0; i < n; i++)
	{
		fread(buf, 1, 1, fp);
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

static void print_label(float *a)
{
	printf("%d\n", (int)*a);
	printf("\n");
}

int main()
{
	struct tensor *a = load_image_file(TRAIN_IMAGE);
	struct tensor *b = load_label_file(TRAIN_LABEL);
	// printf("%d\n", a->cols); // 60000
	// printf("%d\n", a->rows); // 784

	for (int i = 0; i < a->cols; i++)
	{
		print_image(image_pos(a, i));
		print_label(label_pos(b, i));
	}

	free_tensor(a);
	free_tensor(b);

	return 0;
}