#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>

// --------------------- メモリリークチェック、デストラクター -----------------------

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

// -----------------------------------------------------------------------

void makeArray(uint16_t ***a, const int y, const int x)
{
	*a = (uint16_t **)calloc(y, sizeof(uint16_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint16_t *)calloc(x, sizeof(uint16_t));
	}
}

void freeArray(uint16_t ***a, const int y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

void makeArrayInt(unsigned int ***a, const int y, const int x)
{
	*a = (unsigned int **)calloc(y, sizeof(unsigned int *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (unsigned int *)calloc(x, sizeof(unsigned int));
	}
}

void freeArrayInt(unsigned int ***a, const int y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

unsigned int xor128(int reset)
{
	// 内部で値を保持（seed） パターン１
	// static unsigned int x = 2380889285;
	// static unsigned int y = 1631889387;
	// static unsigned int z = 1698655726;
	// static unsigned int w = 2336862850;

	// 内部で値を保持（seed） パターン２
	static unsigned int x = 123456789;
	static unsigned int y = 362436069;
	static unsigned int z = 521288629;
	static unsigned int w = 88675123;

	if (reset)
	{
		x = 123456789;
		y = 362436069;
		z = 521288629;
		w = 88675123;
		return 0;
	}
	else
	{

		// 前回のxを使う
		unsigned int t = x ^ (x << 11);
		// 更新
		x = y;
		y = z;
		z = w;

		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
}

unsigned int shifter(unsigned int *v, unsigned int num)
{
	// num回 論理右シフト
	unsigned int tmp_v = *v >> num;

	// 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
	unsigned int tmp_num = (1 << num) - 1;
	*v = (*v & tmp_num) << (32 - num);

	return tmp_v;
}

// 多数決関数　&& 加算
unsigned int grab_bit(unsigned int result_array[], size_t size)
{
	unsigned int result = 0;

	// 次元数可変
	unsigned int mask = (int)1 << (32 - 1);
	while (mask)
	{
		int tmp = 0;
		for (int i = 0; i < size; i++)
		{
			tmp += (mask & result_array[i] ? 1 : 0);
		}
		// 多数決で1の数が過半数なら、resultにmaskを加える（→対象のbit番目が1になる）
		if (tmp > (size / 2))
		{
			result += mask;
		}
		mask >>= 1;
	}
	return result;
}

void shifter_new(unsigned int **new, unsigned int **original, const unsigned int DIM, unsigned int num)
{
	unsigned int *result_tmp = (unsigned int *)calloc(DIM, sizeof(unsigned int));
	for (int i = 0; i < DIM; i++)
	{
		unsigned int tmp = (*original)[i];
		unsigned int tmp_v = shifter(&tmp, num);
		result_tmp[i] |= tmp_v;
		if (i == 0)
		{
			result_tmp[DIM - 1] |= tmp;
		}
		else
		{
			result_tmp[i - 1] |= tmp;
		}
	}

	for (int i = 0; i < DIM; i++)
	{
		(*new)[i] = result_tmp[i];
	}
	free(result_tmp);
}

int main(int argc, char const *argv[])
{
	clock_t start = clock();
	printf("\n\n");
	// ---------------------------------------------
	const int train_num = 2;
	// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	const int ngram = 3;
	const int DIM = 1024 / 32;

	int all_ngram = 0;
	int even = 0;
	// ---------------------------------------------
	for (int i = 0; i < train_num; i++)
	{
		const char *path = train_path[i];
		printf("\n------------- %sの学習 -------------\n\n", path);
		FILE *file;
		file = fopen(path, "r");
		if (file == NULL)
		{
			perror("  Failed: open file");
			exit(1);
		}
		int ch;
		int num = 0;
		// while (((ch = fgetc(file)) != EOF) && ((ch = fgetc(file) != 255))) // ubuntu:EOF == -1,  petalinux:EOF == 255
		while ((ch = fgetc(file)) != EOF) // ubuntu:EOF == -1,  petalinux:EOF == 255
		{
			num++;
		}
		fseek(file, 0, SEEK_SET);
		char *content = (char *)calloc(num, sizeof(char));
		size_t done = fread(content, sizeof(char), num, file);
		if (done < num)
		{
			perror("  Failed: fread file");
			exit(1);
		}
		fclose(file);
		all_ngram = strlen(content) - ngram + 1;
		even = all_ngram % 2 == 0;
		// printf("content: %s\n", content); // myname...
		printf("all_ngram: %d\n", all_ngram);
		printf("even: %d\n", even);

		uint16_t **ascii_array;
		makeArray(&ascii_array, all_ngram, ngram);
		for (int i = 0; i < all_ngram; i++)
		{
			for (int j = 0; j < ngram; j++)
			{
				ascii_array[i][j] = (unsigned char)(content[i + j]) - 97;
				// printf("%d ", ascii_array[i][j]);
			}
		}

		xor128(1);

		// コード ----------------------------------------

		unsigned int **item_memory_array;
		makeArrayInt(&item_memory_array, 27, DIM);

		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				unsigned int tmp = 0;
				if (i == 0 && j == 0)
				{
					tmp = 88675123;
				}
				else
				{
					tmp = xor128(0);
				}
				item_memory_array[i][j] = tmp;
				// printf("%u\n", tmp);
			}
		}

		unsigned int **item_memory_array_new;
		makeArrayInt(&item_memory_array_new, all_ngram, DIM);

		// all_ngramの数だけ、shiftとxorのエンコーディングを計算
		for (int i = 0; i < all_ngram; i++)
		{
			// -----------------------------------------------------
			// シフトしたものをitem_memory_array_reuslt[ngram][DIM]に格納
			unsigned int **item_memory_array_result;
			makeArrayInt(&item_memory_array_result, ngram, DIM);
			for (int j = 0; j < ngram; j++)
			{
				// shift
				shifter_new(&item_memory_array_result[j], &item_memory_array[ascii_array[i][j]], DIM, j);
			}
			// シフト後のデータを各LEGNTHでxorしtmpに格納
			unsigned int tmp[DIM];
			for (int j = 0; j < DIM; j++)
			{
				tmp[j] = 0;
			}
			for (int k = 0; k < DIM; k++)
			{
				for (int l = 0; l < ngram; l++)
				{
					// xor
					tmp[k] ^= item_memory_array_result[l][k];
				}
			}
			freeArrayInt(&item_memory_array_result, ngram);
			// ------------------------------------------------------

			// tmpに入ったエンコーディング結果でitem_memory_array_new[all_ngram][DIM]を更新
			for (int k = 0; k < DIM; k++)
			{
				item_memory_array_new[i][k] = tmp[k];
			}
		}

		// grab_bit使うために転置
		// item_memory_array_new_t[DIM][all_ngram]
		unsigned int **item_memory_array_new_t;
		makeArrayInt(&item_memory_array_new_t, DIM, all_ngram);

		for (int i = 0; i < all_ngram; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				item_memory_array_new_t[j][i] = item_memory_array_new[i][j];
			}
		}

		unsigned int result[DIM];

		for (int i = 0; i < DIM; i++)
		{
			result[i] = grab_bit(item_memory_array_new_t[i], all_ngram);
		}

		// デバッグ用
		for (int j = 0; j < DIM; j++)
		{
			printf("%u\n", result[j]);
		}

		// ---------------------------------------------

		freeArrayInt(&item_memory_array_new, all_ngram);
		freeArrayInt(&item_memory_array_new_t, DIM);
		freeArrayInt(&item_memory_array, 27);
		freeArray(&ascii_array, all_ngram);
	}
	printf("\n");
	printf("---------------------------------------------------------\n\n");
	clock_t end = clock();
	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n\n  time %lf[ms]\n", time);

	return 0;
}
