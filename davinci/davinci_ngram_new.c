#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hyper_vector.h"

// SIMD化
// マルチスレッド化
// 無駄な乗算や除算、シーケンシャルアクセスになってない部分を探して直す

__attribute__((destructor)) static void destructor()
{
	system("leaks -q davinci_ngram_new");
}

uint8_t **makeArrayU8(const size_t y, const size_t x)
{
	uint8_t **data = (uint8_t **)calloc(y, sizeof(uint8_t *));

	for (int i = 0; i < y; i++)
	{
		data[i] = (uint8_t *)calloc(x, sizeof(uint8_t));
	}

	return data;
}

void freeArrayU8(uint8_t **data, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		free(data[i]);
	}
	free(data);
}

char *readFile(const char *PATH)
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
	while ((ch = fgetc(file)) != EOF)
	{
		num++;
	}
	// printf("EOF: %d\n", EOF); // EOFは全て-1 (Mac, Linux, Petalinux)
	fseek(file, 0, SEEK_SET);
	char *content = (char *)calloc(num, sizeof(char));
	const size_t DONE = fread(content, sizeof(char), num, file);
	if (DONE < num)
	{
		perror("  Failed: fread file");
		exit(1);
	}
	fclose(file);

	return content;
}

// -----------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	puts("\n  -------------------------------------- HDC Program START ------------------------------------\n");

	const int TRAIN_NUM = 2;
	// const char *TRAIN_PATH[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	const char *TRAIN_PATH[] = {"data/decorate/en", "data/decorate/fr"};
	// const char *TRAIN_PATH[] = {"data/decorate/enlong", "data/decorate/frlong"};

	const int NGRAM = 5;
	const int RAND_NUM = 27;
	const int MAJORITY_ADDR = 26;

	// hv -------------------------------------------------
	hv_t **item_memory = makeItemMemory(RAND_NUM);
	// hv -------------------------------------------------

	// 英語とフランス語の数だけ繰り返す
	for (int i = 0; i < TRAIN_NUM; i++)
	{
		printf("\n------------- %sの学習 -------------\n\n", TRAIN_PATH[i]);

		char *content = readFile(TRAIN_PATH[i]);
		uint32_t ALL_NGRAM = strlen(content) - NGRAM + 1;
		uint32_t EVEN = ALL_NGRAM % 2 == 0;
		printf("ALL_NGRAM: %d\n", ALL_NGRAM);
		printf("EVEN: %d\n", EVEN);

		uint8_t **ascii_array = makeArrayU8(ALL_NGRAM, NGRAM);
		for (uint32_t i = 0; i < ALL_NGRAM; i++)
		{
			for (uint32_t j = 0; j < NGRAM; j++)
			{
				ascii_array[i][j] = (uint8_t)(content[i + j]) - 97;
			}
		}

		clock_t START_COMPUTE = clock();

		// hv -------------------------------------------------
		initHV();

		for (uint32_t i = 0; i < ALL_NGRAM; i++)
		{
			hv_t *bound_tmp = makeHV();
			for (uint32_t j = 0; j < NGRAM; j++)
			{
				hv_t *perm_result = perm(item_memory[ascii_array[i][j]], j);
				hv_t *bind_result = bind(bound_tmp, perm_result);
				copyHV(bound_tmp, bind_result);
				freeHV(bind_result);
				freeHV(perm_result);
			}

			bound(bound_tmp);
			freeHV(bound_tmp);
		}
		if (EVEN)
		{
			bound(item_memory[MAJORITY_ADDR]);
		}
		hv_t *result = bound_extract();
		// hv -------------------------------------------------

		clock_t END_COMPUTE = clock();
		double TIME = ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC * 1000.0;
		printf("  計算時間: %lf[ms]\n", TIME);

		for (uint32_t j = 0; j < HV_NUM; j++)
		{
			printf("%u\n", result[j]);
		}

		freeArrayU8(ascii_array, ALL_NGRAM);
		free(content);

		// hv -------------------------------------------------
		freeHV(result);
		// hv -------------------------------------------------
	}

	// hv -------------------------------------------------
	freeArrayHV(item_memory, RAND_NUM);
	// hv -------------------------------------------------

	puts("\n  --------------------------------------- HDC Program END -------------------------------------\n");

	return 0;
}