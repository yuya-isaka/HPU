
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hyper_vector.h"

#ifdef OPENMP
#include <omp.h>
#endif

// hardwareでpermutationを駆使したやつやと早くなるかも
// Permutatoinはvshrq_n_u64とかを使って128のシフトを実現可能
// populationカウントは統治戦略によって並列に実行可能

#ifdef DEBUG
__attribute__((destructor)) static void destructor()
{
	system("leaks -q davinci_ngram");
}
#endif

uint8_t **make_array_u8(const uint32_t y, const uint32_t x)
{
	uint8_t **data = (uint8_t **)calloc(y, sizeof(uint8_t *));
	if (data == NULL)
	{
		perror("  Failed: calloc");
		exit(1);
	}

	for (uint32_t i = 0; i < y; i++)
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

void free_array_u8(uint8_t **data, const uint32_t y)
{
	for (uint32_t i = 0; i < y; i++)
	{
		free(data[i]);
	}
	free(data);
}

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
	while ((ch = fgetc(file)) != EOF)
	{
		num++;
	}
	// printf("EOF: %d\n", EOF); // EOFは全て-1 (Mac, Linux, Petalinux)
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

// -----------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	puts("\n  -------------------------------------- HDC Program START ------------------------------------\n");

	const uint32_t TRAIN_NUM = 2;
	// const char *TRAIN_PATH[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	// const char *TRAIN_PATH[] = {"data/decorate/en", "data/decorate/fr"};
	const char *TRAIN_PATH[] = {"data/decorate/enlong", "data/decorate/frlong"};

	const uint32_t NGRAM = 100;
	const uint32_t RAND_NUM = 27;
	const uint32_t MAJORITY_ADDR = 26;

	// hv -------------------------------------------------
	hv_t **item_memory = hv_make_imem(RAND_NUM);
	// hv -------------------------------------------------

	// 英語とフランス語の数だけ繰り返す
	for (uint32_t i = 0; i < TRAIN_NUM; i++)
	{
		printf("\n------------- %sの学習 -------------\n\n", TRAIN_PATH[i]);

		char *content = read_file(TRAIN_PATH[i]);
		uint32_t ALL_NGRAM = strlen(content) - NGRAM + 1;
		uint32_t EVEN = ALL_NGRAM % 2 == 0;
		printf("ALL_NGRAM: %d\n", ALL_NGRAM);
		printf("EVEN: %d\n", EVEN);

		uint8_t **ascii_array = make_array_u8(ALL_NGRAM, NGRAM);
		for (uint32_t i = 0; i < ALL_NGRAM; i++)
		{
			for (uint32_t j = 0; j < NGRAM; j++)
			{
				ascii_array[i][j] = (uint8_t)(content[i + j]) - 97;
			}
		}

		clock_t START_COMPUTE = clock();

		// hv -------------------------------------------------

		// nobatch
		hv_init();
		// batch
		// uint32_t TRAIN_SIZE = ALL_NGRAM;
		// if (EVEN)
		// {
		// 	TRAIN_SIZE++;
		// }
		// hv_t **bound_buff = hv_make_array(TRAIN_SIZE);

#ifdef OPENMP
#pragma omp parallel for
#endif
		for (uint32_t i = 0; i < ALL_NGRAM; i++)
		{
			hv_t *bound_tmp = hv_make();
			for (uint32_t j = 0; j < NGRAM; j++)
			{
				hv_t *perm_result = hv_perm(item_memory[ascii_array[i][j]], j);
				hv_t *bind_result = hv_bind(bound_tmp, perm_result);
				hv_copy(bound_tmp, bind_result);

				hv_free(bind_result);
				hv_free(perm_result);
			}

			// nobatch
			hv_bound(bound_tmp);
			// batch
			// hv_copy(bound_buff[i], bound_tmp);

			hv_free(bound_tmp);
		}

		// nobatch
		if (EVEN)
		{
			hv_bound(item_memory[MAJORITY_ADDR]);
		}
		hv_t *result = hv_bound_result();
		// batch
		// if (EVEN)
		// {
		// 	hv_copy(bound_buff[TRAIN_SIZE - 1], item_memory[MAJORITY_ADDR]);
		// }
		// hv_t *result = hv_bound_batch(bound_buff, TRAIN_SIZE);
		// hv_free_array(bound_buff, TRAIN_SIZE);

		// hv -------------------------------------------------

		clock_t END_COMPUTE = clock();

		double TIME = ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC * 1000.0;
#ifdef OPENMP
		TIME = TIME / omp_get_max_threads();
#endif
		printf("  計算時間: %lf[ms]\n", TIME);

		for (uint32_t j = 0; j < HV_NUM; j++)
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
			conv.data = result[j];
			printf("%u\n", conv.data_0);
			printf("%u\n", conv.data_1);
#else
			printf("%u\n", result[j]);
#endif
		}

		free_array_u8(ascii_array, ALL_NGRAM);
		free(content);

		// hv -------------------------------------------------
		hv_free(result);

		// nobatch
		hv_finish();
		// hv -------------------------------------------------
	}

	// hv -------------------------------------------------
	hv_free_array(item_memory, RAND_NUM);
	// hv -------------------------------------------------

	puts("\n  --------------------------------------- HDC Program END -------------------------------------\n");

	return 0;
}