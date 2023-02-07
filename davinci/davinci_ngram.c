// include library
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
	system("leaks -q davinci_ngram");
}
#endif
#endif

// uint8_t two-dimensional array
uint8_t **make_array_u8(const uint32_t y, const uint32_t x)
{
	uint8_t **data = (uint8_t **)calloc(y, sizeof(uint8_t *));
	if (data == NULL)
	{
		perror("  Failed: calloc");
		exit(1);
	}

	for (int i = 0; i < y; i++)
	{
		data[i] = (uint8_t *)calloc(x, sizeof(uint8_t));
		if (data[i] == NULL)
		{
			perror("  Failed: calloc");
			exit(1);
		}
	}

	return data;
}

// uint8_t two-dimensional array
void free_array_u8(uint8_t **data, const uint32_t y)
{
	for (int i = 0; i < y; i++)
	{
		free(data[i]);
	}
	free(data);
}

// ファイル読み込み
char *read_file(const char *PATH)
{
	FILE *file;
	file = fopen(PATH, "r");
	if (file == NULL)
	{
		perror("  Failed: open file");
		exit(1);
	}

	uint32_t ch;
	uint32_t num = 0;
	// 与えられたファイルがひと続きの文字列と仮定 (2行になると｛10, 0x0a, LF(改行)｝ が入ってしまいズレる)
	// printf("EOF: %d\n", EOF); // EOFは全て-1 (Mac, Linux, Petalinux)
	while ((ch = fgetc(file)) != EOF)
	{
		num++;
	}

	fseek(file, 0, SEEK_SET);
	char *content = (char *)calloc(num, sizeof(char));
	if (content == NULL)
	{
		perror("  Failed: calloc");
		exit(1);
	}

	const uint32_t DONE = (uint32_t)fread(content, sizeof(char), num, file);
	if (DONE < num)
	{
		perror("  Failed: fread file");
		exit(1);
	}

	fclose(file);

	return content;
}

int main(int argc, char const *argv[])
{
	// puts("\n  -------------------------------------- HDC Program START ------------------------------------\n");

	// 訓練パス
	// const char *TRAIN_PATH[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	const char *TRAIN_PATH[] = {"data/decorate/en", "data/decorate/fr"};
	// const char *TRAIN_PATH[] = {"data/decorate/enlong", "data/decorate/frlong"};

	// 訓練数
	const uint32_t TRAIN_NUM = 2;

	// NGRAMの数
	const uint32_t NGRAM = 3;

	// 生成するランダム数
	const uint32_t RAND_NUM = 27;

	// 偶数の時に追加するハイパーベクトルのアドレス
	const uint32_t MAJORITY_ADDR = 26;

	// hv -------------------------------------------------
	// アイテムメモリ内にハイパーベクトル生成
	hv_t **item_memory = hv_make_imem(RAND_NUM);
	// hv -------------------------------------------------

	// // 計算時間格納
	double LOAD_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;
	// double TIME = 0.0;

	// 英語とフランス語
	for (uint32_t i = 0; i < TRAIN_NUM; i++)
	{
		// read file
		START_COMPUTE = clock();
		char *content = read_file(TRAIN_PATH[i]);
		END_COMPUTE = clock();
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// NGRAMの数
		uint32_t ALL_NGRAM = strlen(content) - NGRAM + 1;

		// NGRAMの数が偶数か
		uint32_t EVEN = ALL_NGRAM % 2 == 0;

		// 文字列のアドレスを格納
		uint8_t **ascii_array = make_array_u8(ALL_NGRAM, NGRAM);
		for (int i = 0; i < ALL_NGRAM; i++)
		{
			for (int j = 0; j < NGRAM; j++)
			{
				ascii_array[i][j] = (uint8_t)(content[i + j]) - 97;
			}
		}

		// clock_t START_COMPUTE = clock();

		// hv -------------------------------------------------
		// 初期化
		// nobatch
		hv_init();

		// 初期化
		// batch
		// uint32_t TRAIN_SIZE = ALL_NGRAM;
		// if (EVEN)
		// {
		// 	TRAIN_SIZE++;
		// }
		// hv_t **bound_buff = hv_make_array(TRAIN_SIZE);
		// hv -------------------------------------------------

		// hv -------------------------------------------------
// OpenMP
#ifdef OPENMP
#pragma omp parallel for
#endif
		for (uint32_t i = 0; i < ALL_NGRAM; i++)
		{
			// 符号結果を格納
			hv_t *bound_tmp = hv_make();

			// NGRAMの数だけPermutation
			for (uint32_t j = 0; j < NGRAM; j++)
			{
				// Permutation
				hv_t *perm_result = hv_perm(item_memory[ascii_array[i][j]], j);

				// Bind
				hv_t *bind_result = hv_bind(bound_tmp, perm_result);

				// Copy
				hv_copy(bound_tmp, bind_result);

				// Free
				hv_free(bind_result);
				hv_free(perm_result);
			}

			// Bounding
			// nobatch
			hv_bound(bound_tmp);

			// Bounding
			// batch
			// hv_copy(bound_buff[i], bound_tmp);

			// Free
			hv_free(bound_tmp);
		}

		// 偶数の時追加
		// nobatch
		if (EVEN)
		{
			hv_bound(item_memory[MAJORITY_ADDR]);
		}

		// Bounding結果取り出し
		// nobatch
		hv_t *result = hv_bound_result();

		// 偶数の時追加
		// batch
		// if (EVEN)
		// {
		// 	hv_copy(bound_buff[TRAIN_SIZE - 1], item_memory[MAJORITY_ADDR]);
		// }

		// Bounding結果取り出し
		// batch
		// hv_t *result = hv_bound_batch(bound_buff, TRAIN_SIZE);
		// hv_free_array(bound_buff, TRAIN_SIZE);
		// hv -------------------------------------------------

		// 		clock_t END_COMPUTE = clock();
		// 		TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC * 1000.0;
		// #ifdef OPENMP
		// 		TIME += TIME / omp_get_max_threads();
		// #endif

		// hv -------------------------------------------------
		// 結果出力
		hv_print(result);

		// Free
		hv_free(result);

		// 終了処理
		// nobatch
		hv_finish();
		// hv -------------------------------------------------

		// Free 文字列配列
		free_array_u8(ascii_array, ALL_NGRAM);
		free(content);
	}

	// hv -------------------------------------------------
	// Free アイテムメモリ
	hv_free_array(item_memory, RAND_NUM);
	// hv -------------------------------------------------

	// printf("\n  計算時間: %lf[ms]\n", TIME);
	printf("\n  ロード時間: %lf[ms]\n\n", LOAD_TIME);

	// puts("\n  --------------------------------------- HDC Program END -------------------------------------");
	return 0;
}