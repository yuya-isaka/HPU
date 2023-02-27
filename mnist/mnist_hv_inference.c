#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
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

// 32bitの時だけ
uint32_t HammingDistance(uint32_t n)
{
	n = (n & 0x55555555) + (n >> 1 & 0x55555555);
	n = (n & 0x33333333) + (n >> 2 & 0x33333333);
	n = (n & 0x0f0f0f0f) + (n >> 4 & 0x0f0f0f0f);
	n = (n & 0x00ff00ff) + (n >> 8 & 0x00ff00ff);
	return (n & 0x0000ffff) + (n >> 16 & 0x0000ffff);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	double LOAD_TIME = 0.0;
	double INFERENCE_TIME = 0.0;
	double COM_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;
	clock_t INFERENCE_START_COMPUTE;
	clock_t INFERENCE_END_COMPUTE;

	// 784個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = 784;
	hv_t **item_memory = hv_make_imem(RAND_NUM);

	// 0-9の結果
	hv_t **result = hv_make_array(10);

	for (int i = 0; i < 10; i++)
	{
		hv_init();

		START_COMPUTE = clock();
		char PATH[12];
		snprintf(PATH, 12, "image%d.txt", i);
		int data_tmp_num = 0;
		char *data_lines = read_file(PATH, &data_tmp_num);
		END_COMPUTE = clock();
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

// OpenMP
#ifdef OPENMP
#pragma omp parallel for
#endif
		for (int j = 0; j < data_tmp_num; j += 784)
		{
			int index_num = 0;
			int perm_num = j;

			for (int k = 0; k < 784; k++)
			{
				hv_t *perm_result = hv_perm(item_memory[index_num++], (data_lines[perm_num++] - '0'));

				// bound
				hv_bound(perm_result);
				hv_free(perm_result);
			}
		}

		hv_t *result_tmp = hv_bound_result();
		hv_copy(result[i], result_tmp);
		hv_free(result_tmp);

		hv_finish();

		free(data_lines);
	}

	INFERENCE_START_COMPUTE = clock();
	int correct = 0;
	for (int i = 0; i < 10; i++)
	{
		// printf("%d:\n", i);
		// hv_print(result[i]);
		// printf("\n");

		START_COMPUTE = clock();
		char PATH[16];
		snprintf(PATH, 16, "testimage%d.txt", i);
		int data_tmp_num = 0;
		char *data_lines = read_file(PATH, &data_tmp_num);
		END_COMPUTE = clock();
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		for (int j = 0; j < data_tmp_num; j += 784)
		{
			hv_init_inference();
			int index_num = 0;
			int perm_num = j;

			for (int k = 0; k < 784; k++)
			{
				hv_t *perm_result = hv_perm(item_memory[index_num++], (data_lines[perm_num++] - '0'));

				// bound
				hv_bound_inference(perm_result);
				hv_free(perm_result);
			}

			hv_t *result_tmp = hv_bound_result_inference();

			// ここでresult_tmpとresult[0]-result[10]とのハミング距離を計測して、どこに分類されるか判定
			int hamming[10];
			for (int k = 0; k < 10; k++)
			{
				hamming[k] = 0;
				// for (int l = 0; l < 64; l++)
				// for (int l = 0; l < 128; l++)
				// for (int l = 0; l < 256; l++)
				for (int l = 0; l < 32; l++)
				{
					hamming[k] += HammingDistance(result[k][l] ^ result_tmp[l]);
				}
			}

			int test_result = 0;
			int min_result = hamming[0];
			for (int k = 1; k < 10; k++)
			{
				if (min_result > hamming[k])
				{
					min_result = hamming[k];
					test_result = k;
				}
			}

			// 判定後、iと比較して正しかったらcorrectに足し算
			// printf("%d:%d ", i, test_result);
			if (i == test_result)
			{
				correct++;
			}

			hv_free(result_tmp);
			hv_finish_inference();
		}
		free(data_lines);
	}
	INFERENCE_END_COMPUTE = clock();
	INFERENCE_TIME = ((double)(INFERENCE_END_COMPUTE - INFERENCE_START_COMPUTE)) / CLOCKS_PER_SEC;

	// correct / 10000 = 正解率を出力
	printf("Correct: %d\n", correct);
	printf("Accuracy: %f\n", correct / 10000.0);

	hv_free_array(result, 10);
	hv_free_array(item_memory, RAND_NUM);

	printf("  load時間: %lf[ms]\n", LOAD_TIME);
	printf("  推論時間: %lf[ms]\n", INFERENCE_TIME);

	return 0;
}