#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "hyper_vector.h"

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
hv_t **hv_make_imem_new(const uint32_t size, const uint32_t size_2)
{
	// 結果格納
	hv_t **result = hv_make_array(size + size_2);

	for (int i = 0; i < size + size_2; i++)
	{
		if (i <= size)
		{
			for (int j = 0; j < HV_NUM; j++)
			{
#ifdef HV64
				union
				{
					struct
					{
						uint32_t data_0;
						uint32_t data_1;
					};
					hv_t data;
				} conv;
				if (i == 0 && j == 0)
				{
					conv.data_0 = 88675123;
				}
				else
				{
					conv.data_0 = xor128(0);
				}
				conv.data_1 = xor128(0);
				result[i][j] = conv.data;
#else
				uint32_t tmp = 0;
				if (i == 0 && j == 0)
				{
					tmp = 88675123;
				}
				else
				{
					tmp = xor128(0);
				}
				result[i][j] = tmp;
#endif
			}
		}
		else
		{
			int tmp = HV_DIM / (i - size);
			int num = tmp / ELEMENT_SIZE;
			int num_remain = tmp % ELEMENT_SIZE;
			printf("tmp: %d, ", tmp);
			printf("num: %d, ", num);
			printf("num_remain: %d, ", num_remain);
			for (int j = 0; j < num; j++)
			{
				result[i][j] = ~result[size][j];
			}
			if (num_remain != 0)
			{
				uint64_t mask = (2 ^ num_remain - 1);
				result[i][num] = result[size][num] ^ mask;
				for (int j = num + 1; j < HV_NUM; j++)
				{
					result[i][j] = result[size][j];
				}
			}
			else
			{
				for (int j = num; j < HV_NUM; j++)
				{
					result[i][j] = result[size][j];
				}
			}
		}
	}
	return result;
}

// size個のハイパーベクトルを格納したアイテムメモリを生成
hv_t **hv_make_imem_new_2(const uint32_t size, const uint32_t size_2)
{
	// 結果格納
	hv_t **result = hv_make_array(size + size_2);

	for (int i = 0; i < size + size_2; i++)
	{
		if (i <= size)
		{
			for (int j = 0; j < HV_NUM; j++)
			{
#ifdef HV64
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
#else
				uint32_t tmp = 0;
				tmp = xor128(0);
				result[i][j] = tmp;
#endif
			}
		}
		else
		{
			int tmp = HV_DIM / (i - size);
			int num = tmp / ELEMENT_SIZE;
			int num_remain = tmp % ELEMENT_SIZE;
			for (int j = 0; j < num; j++)
			{
				result[i][j] = ~result[size][j];
			}
			if (num_remain != 0)
			{
				uint64_t mask = (2 ^ num_remain - 1);
				result[i][num] = result[size][num] ^ mask;
				for (int j = num + 1; j < HV_NUM; j++)
				{
					result[i][j] = result[size][j];
				}
			}
			else
			{
				for (int j = num; j < HV_NUM; j++)
				{
					result[i][j] = result[size][j];
				}
			}
		}
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

	xor128(1);

	// 637個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM_FIRST = 500;
	const uint32_t RAND_NUM_FIRST_REMAIN = 10;
	hv_t **item_memory_1 = hv_make_imem_new(RAND_NUM_FIRST, RAND_NUM_FIRST_REMAIN);

	const uint32_t RAND_NUM_SECOND = 117;
	const uint32_t RAND_NUM_SECOND_REMAIN = 10;
	hv_t **item_memory_2 = hv_make_imem_new_2(RAND_NUM_SECOND, RAND_NUM_SECOND_REMAIN);

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
				hv_t *bind_result;
				if (k < 500)
				{
					bind_result = hv_bind(item_memory_1[k], item_memory_1[(data_lines[addr_tmp++] - '0') + 500]);
				}
				else
				{
					bind_result = hv_bind(item_memory_2[k - 500], item_memory_2[(data_lines[addr_tmp++] - '0') + 117]);
				}

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

	for (int i = 0; i < ALL_TRAIN_NUM; i++)
	{
		printf("%d:\n", i);
		hv_print(result[i]);
		printf("\n");
	}

	hv_free_array(result, ALL_TRAIN_NUM);
	hv_free_array(item_memory_1, 510);
	hv_free_array(item_memory_2, 127);

	printf("  load時間: %lf[ms]\n", LOAD_TIME);

	return 0;
}