#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "hyper_vector.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// OpenMP
#ifdef OPENMP
#include <omp.h>
#endif

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ファイル読み込み
char *read_file(const char *PATH, int *num)
{
	FILE *file;
	file = fopen(PATH, "r");
	if (file == NULL)
	{
		perror("  Failed: open file");
		exit(1);
	}

	uint32_t ch;
	// 与えられたファイルがひと続きの文字列と仮定 (2行になると｛10, 0x0a, LF(改行)｝ が入ってしまいズレる)
	// printf("EOF: %d\n", EOF); // EOFは全て-1 (Mac, Linux, Petalinux)
	while ((ch = fgetc(file)) != EOF)
	{
		(*num)++;
	}

	fseek(file, 0, SEEK_SET);
	char *content = (char *)calloc(*num, sizeof(char));
	if (content == NULL)
	{
		perror("  Failed: calloc");
		exit(1);
	}

	const uint32_t DONE = (uint32_t)fread(content, sizeof(char), *num, file);
	if (DONE < *num)
	{
		perror("  Failed: fread file");
		exit(1);
	}

	fclose(file);

	return content;
}

// xor128 RNG
static uint32_t xor128(int reset)
{
	// 初期値
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

	// リセット信号
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
		uint32_t t = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
}

// size個のハイパーベクトルを格納したアイテムメモリを生成
hv_t **hv_make_imem_new(const uint32_t size)
{
	// RNG初期化
	xor128(1);

	// 結果格納
	hv_t **result = hv_make_array(size);

#ifdef HV64
	for (int i = 0; i < 16; i++)
	{
		union
		{
			struct
			{
				uint32_t data_0;
				uint32_t data_1;
			};
			hv_t data;
		} conv;
		if (i == 0)
		{
			conv.data_0 = 88675123;
		}
		else
		{
			conv.data_0 = xor128(0);
		}
		conv.data_1 = xor128(0);
		result[0][i] = conv.data;
	}
#else
	for (int i = 0; i < 32; i++)
	{
		uint32_t tmp = 0;
		if (i == 0)
		{
			tmp = 88675123;
		}
		else
		{
			tmp = xor128(0);
		}
		result[0][i] = tmp;
	}
#endif

	for (int i = 1; i < 10; i++)
	{
#ifdef HV64
		int tmp = 1024 / i;
		int num = tmp / 64;
		int num_remain = tmp % 64;
		hv_copy(result[i], result[0]);
		for (int j = 0; j < num; j++)
		{
			result[i][j] = ~result[0][j];
		}
		if (num_remain != 0)
		{
			union
			{
				struct
				{
					uint32_t data_0;
					uint32_t data_1;
				};
				hv_t data;
			} conv;
			union
			{
				struct
				{
					uint32_t data_0;
					uint32_t data_1;
				};
				hv_t data;
			} conv_result;

			conv.data = result[0][num];

			if (num_remain > 32)
			{
				// ↓ だめ
				// uint32_t mask = 1 << 32 - 1;
				// ↓ これでもいい
				// uint32_t test_mask = -1;
				uint32_t mask = 4294967295;
				conv_result.data_0 = conv.data_0 ^ mask;
				mask = 1 << (num_remain - 32) - 1;
				conv_result.data_1 = conv.data_1 ^ mask;
			}
			else
			{
				uint32_t mask = 1 << num_remain - 1;
				conv_result.data_0 = conv.data_0 ^ mask;
				conv_result.data_1 = conv.data_1;
			}

			result[i][num] = conv_result.data;
			// hv_t mask = 1 << num_remain - 1;
			// result[i][num] = result[0][num] ^ mask;
		}

		// int tmp_num = 0;
		// for (int j = 0; j < 16; j++)
		// {
		// 	union
		// 	{
		// 		struct
		// 		{
		// 			uint32_t data_0;
		// 			uint32_t data_1;
		// 		};
		// 		hv_t data;
		// 	} conv;
		// 	conv.data = result[i][j];
		// 	printf("i:%d j:%d %u\n", i, tmp_num++, conv.data_0);
		// 	printf("i:%d j:%d %u\n", i, tmp_num++, conv.data_1);
		// }
#else
		int tmp = 1024 / i;
		int num = tmp / 32;
		int num_remain = tmp % 32;
		hv_copy(result[i], result[0]);
		for (int j = 0; j < num; j++)
		{
			result[i][j] = ~result[0][j];
			// printf("反転%u:%u\n", result[i][j], result[0][j]);
		}
		if (num_remain != 0)
		{
			hv_t mask = 1 << num_remain - 1;
			result[i][num] = result[0][num] ^ mask;
		}

		// for (int j = 0; j < 32; j++)
		// {
		// 	printf("i:%d j:%d %u\n", i, j, result[i][j]);
		// }
#endif
	}

	for (int i = 10; i < size; i++)
	{
#ifdef HV64
		for (int j = 0; j < 16; j++)
		{
			union
			{
				struct
				{
					uint32_t data_0;
					uint32_t data_1;
				};
				hv_t data;
			} conv;
			conv.data_0 = xor128(0);
			conv.data_1 = xor128(0);
			result[i][j] = conv.data;
		}
#else
		for (int j = 0; j < 32; j++)
		{
			uint32_t tmp = 0;
			tmp = xor128(0);
			result[i][j] = tmp;
		}
#endif
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	double LOAD_TIME = 0.0;
	double COM_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	// 637個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = 627;
	hv_t **item_memory = hv_make_imem_new(RAND_NUM);

	const uint32_t ALL_TRAIN_NUM = 26;

	// 0-9の結果
	hv_t **result = hv_make_array(ALL_TRAIN_NUM);

	for (int i = 0; i < ALL_TRAIN_NUM; i++)
	{
		START_COMPUTE = clock();
		char PATH[12];
		snprintf(PATH, 12, "label%d.txt", i);
		int data_tmp_num = 0;
		char *data_lines = read_file(PATH, &data_tmp_num);
		END_COMPUTE = clock();
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// printf("%d\n", data_tmp_num);
		// for (int j = 0; j < data_tmp_num; j++)
		// {
		// 	printf("%d\n", data_lines[j]);
		// }

		//////////////////////////////////////////////////////////////////////

		hv_init();

// OpenMP
#ifdef OPENMP
#pragma omp parallel for
#endif
		for (int j = 0; j < data_tmp_num; j += 617)
		{
			int addr_tmp = j;

			for (int k = 0; k < 617; k++)
			{
				hv_t *bind_result = hv_bind(item_memory[k + 10], item_memory[(data_lines[addr_tmp++] - '0')]);

				hv_bound(bind_result);
				hv_free(bind_result);
			}
		}

		hv_t *result_tmp = hv_bound_result();
		hv_copy(result[i], result_tmp);
		hv_free(result_tmp);

		hv_finish();

		//////////////////////////////////////////////////////////////////////
	}

	// for (int i = 0; i < ALL_TRAIN_NUM; i++)
	// {
	// 	printf("%d:\n", i);
	// 	hv_print(result[i]);
	// 	printf("\n");
	// }

	hv_free_array(result, ALL_TRAIN_NUM);
	hv_free_array(item_memory, RAND_NUM);

	printf("  load時間: %lf[ms]\n", LOAD_TIME);

	return 0;
}