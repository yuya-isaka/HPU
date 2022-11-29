
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define HV_DIM 1024
#define HV_NUM HV_DIM / 32

int32_t bound_buff[HV_DIM];

void makeArrayU8(uint8_t ***a, const size_t y, const size_t x)
{
	*a = (uint8_t **)calloc(y, sizeof(uint8_t *));

	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint8_t *)calloc(x, sizeof(uint8_t));
	}
}

void freeArrayU8(uint8_t ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

void makeArrayU32(uint32_t ***a, const size_t y, const size_t x)
{
	*a = (uint32_t **)calloc(y, sizeof(uint32_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint32_t *)calloc(x, sizeof(uint32_t));
	}
}

void freeArrayU32(uint32_t ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

// -----------------------------------------------------------------------

uint32_t xor128(int reset)
{
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

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

void init_hv(void)
{
	memset(bound_buff, 0, sizeof(bound_buff));
}

// -----------------------------------------------------------------------

uint32_t right_perm_31(uint32_t *over_hv, uint32_t perm_num)
{
	uint32_t remain_hv = *over_hv >> perm_num;
	uint32_t mask = (1 << perm_num) - 1;
	*over_hv = (*over_hv & mask) << (32 - perm_num);
	return remain_hv;
}

void right_perm(uint32_t new_hv[HV_NUM], uint32_t base_hv[HV_NUM], uint32_t perm_num)
{
	uint32_t result_hv[HV_NUM];
	memset(result_hv, 0, sizeof(result_hv));

	uint32_t origin_hv = base_hv[0];
	uint32_t origin_hv_perm = right_perm_31(&origin_hv, perm_num);

	result_hv[0] |= origin_hv_perm;
	result_hv[HV_NUM - 1] |= origin_hv;

	for (int i = 1; i < HV_NUM; i++)
	{
		uint32_t origin_hv = base_hv[i];
		uint32_t origin_hv_perm = right_perm_31(&origin_hv, perm_num);

		result_hv[i] |= origin_hv_perm;
		result_hv[i - 1] |= origin_hv;
	}
	for (int i = 0; i < HV_NUM; i++)
	{
		new_hv[i] = result_hv[i];
	}
}

uint32_t left_perm_31(uint32_t *over_hv, uint32_t perm_num)
{
	uint32_t remain_hv = *over_hv << perm_num;
	uint32_t mask = UINT32_MAX << (32 - perm_num);
	*over_hv = (*over_hv & mask) >> (32 - perm_num);
	return remain_hv;
}

void left_perm(uint32_t new_hv[HV_NUM], uint32_t base_hv[HV_NUM], uint32_t perm_num)
{
	uint32_t result_hv[HV_NUM];
	memset(result_hv, 0, sizeof(result_hv));

	uint32_t origin_hv = base_hv[HV_NUM - 1];
	uint32_t origin_hv_perm = left_perm_31(&origin_hv, perm_num);

	result_hv[HV_NUM - 1] |= origin_hv_perm;
	result_hv[0] |= origin_hv;

	for (int i = HV_NUM - 2; i >= 0; i--)
	{
		uint32_t origin_hv = base_hv[i];
		uint32_t origin_hv_perm = left_perm_31(&origin_hv, perm_num);

		result_hv[i] |= origin_hv_perm;
		result_hv[i + 1] |= origin_hv;
	}
	for (int i = 0; i < HV_NUM; i++)
	{
		new_hv[i] = result_hv[i];
	}
}

void perm(uint32_t new[HV_NUM], uint32_t origin[HV_NUM], uint32_t perm_num, void (*perm_func)(uint32_t *, uint32_t *, uint32_t))
{
	uint32_t repeat_perm_num = perm_num / 31;
	uint32_t pre_perm_num;
	if (perm_num % 31 != 0)
	{
		pre_perm_num = perm_num % 31;
	}
	else
	{
		pre_perm_num = 31;
		repeat_perm_num--;
	}

	perm_func(new, origin, pre_perm_num);

	for (int i = 0; i < repeat_perm_num; i++)
	{
		perm_func(new, new, 31);
	}
}

void perm_top(uint32_t new[HV_NUM], uint32_t origin[HV_NUM], uint32_t perm_num)
{
	if (perm_num == 0)
	{
		memcpy(new, origin, sizeof(uint32_t) * HV_NUM);
		return;
	}
	else if (perm_num >= HV_DIM)
	{
		perror("Failed: permutation");
		exit(1);
	}

	if (perm_num > (HV_DIM / 2))
	{
		perm_num = HV_DIM - perm_num;
		perm(new, origin, perm_num, left_perm);
	}
	else
	{
		perm(new, origin, perm_num, right_perm);
	}
}

void bound(uint32_t encoded_hv[HV_NUM])
{
	// reductionを使って並列化する必要性あり
	// https://www.isus.jp/products/c-compilers/32-openmp-traps/
	uint32_t index_assign = HV_NUM - 1;
	for (int i = 0; i < HV_NUM; i++)
	{
		uint32_t hv = encoded_hv[i];
		uint32_t mask = 1;
		for (int j = 0; j < 32; j++)
		{
			uint32_t index = index_assign * 32 + j;
			bound_buff[index] += (mask & hv ? -1 : 1);
			mask <<= 1;
		}
		index_assign--;
	}
}

void bound_extract(uint32_t bound_hv[HV_NUM])
{
	uint32_t mask = 1 << (32 - 1);
	uint32_t index_assign = HV_NUM - 1;
	for (int i = 0; i < HV_NUM; i++)
	{
		uint32_t hv = 0;
		for (int j = 0; j < 32; j++)
		{
			uint32_t index = i * 32 + j;
			uint32_t sign_bit = (bound_buff[index] & mask ? 1 : 0);
			hv += (sign_bit << j);
		}
		bound_hv[index_assign--] = hv;
	}
}

// 現状こっちの方が微妙に早い
// 3.32 -> 3.14 になる
// 並列化するとどうなるかわからん
void bound_batch(uint32_t result_hv[HV_NUM], size_t batch_size, uint32_t **batch_data)
{
	uint32_t hv_buff[HV_DIM];
	memset(hv_buff, 0, sizeof(hv_buff));

	for (int i = 0; i < batch_size; i++)
	{
		uint32_t index_assign = HV_NUM - 1;
		for (int j = 0; j < HV_NUM; j++)
		{
			uint32_t hv = batch_data[i][j];
			uint32_t mask = 1;
			for (int k = 0; k < 32; k++)
			{
				uint32_t index = index_assign * 32 + k;
				hv_buff[index] += (mask & hv ? 1 : 0);
				mask <<= 1;
			}
			index_assign--;
		}
	}

	uint32_t threshold = batch_size / 2;
	uint32_t index = HV_NUM - 1;
	uint32_t counter = 0;
	uint32_t tmp_hv = 0;
	for (int i = 0; i < HV_DIM; i++)
	{
		if (hv_buff[i] > threshold)
		{
			tmp_hv |= 1 << counter;
		}
		counter++;
		if (counter >= 32)
		{
			counter = 0;
			result_hv[index--] = tmp_hv;
			tmp_hv = 0;
		}
	}
	uint32_t result = 0;
	uint32_t mask = (uint32_t)1 << (32 - 1);
}

void bind(uint32_t dst[HV_NUM], uint32_t src1[HV_NUM], uint32_t src2[HV_NUM])
{
	for (int i = 0; i < HV_NUM; i++)
	{
		dst[i] = src1[i] ^ src2[i];
	}
}

// -----------------------------------------------------------------------

int main(int argc, char const *argv[])
{

	// プログラム全体の時間
	clock_t start_program = clock();

	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// 初期化時間
	clock_t start = clock();

	const uint32_t TRAIN_NUM = 2;
	// const char *TRAIN_PATH[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	// const char *TRAIN_PATH[] = {"data/decorate/en", "data/decorate/fr"};
	const char *TRAIN_PATH[] = {"data/decorate/enlong", "data/decorate/frlong"};
	const uint32_t NGRAM = 5;
	const uint32_t RAND_NUM = 27;
	const uint32_t MAJORITY_ADDR = 26;
	uint32_t ALL_NGRAM = 0;
	uint32_t EVEN = 0;

	// ---------------------------------------------

	// ランダム生成の初期化
	xor128(1);

	// ランダムなハイパーベクトルを生成
	uint32_t **item_memory_array;
	makeArrayU32(&item_memory_array, RAND_NUM, HV_NUM);

	for (uint32_t i = 0; i < RAND_NUM; i++)
	{
		for (uint32_t j = 0; j < HV_NUM; j++)
		{
			uint32_t tmp = 0;
			if (i == 0 && j == 0)
			{
				tmp = 88675123;
			}
			else
			{
				tmp = xor128(0);
			}
			item_memory_array[i][j] = tmp;
		}
	}

	clock_t end = clock();
	double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  初期化時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// 英語とフランス語の数だけ繰り返す
	for (uint32_t i = 0; i < TRAIN_NUM; i++)
	{

		// データ準備時間
		start = clock();

		init_hv();

		// ファイル読み込み
		const char *PATH = TRAIN_PATH[i];
		printf("\n------------- %sの学習 -------------\n\n", PATH);
		FILE *file;
		file = fopen(PATH, "r");
		if (file == NULL)
		{
			perror("  Failed: open file");
			exit(1);
		}
		// ---------------------------------------------
		// ファイルから文字列を取得
		uint32_t ch;
		uint32_t num = 0;
		// 与えられたファイルがひと続きの文字列と仮定 (2行になると｛10, 0x0a, LF(改行)｝ が入ってしまいズレる)
		while ((ch = fgetc(file)) != EOF)
		{
			num++;
		}
		printf("EOF: %d\n", EOF); // EOFは全て-1 (Mac, Linux, Petalinux)
		fseek(file, 0, SEEK_SET);
		char *content = (char *)calloc(num, sizeof(char));
		const size_t DONE = fread(content, sizeof(char), num, file);
		if (DONE < num)
		{
			perror("  Failed: fread file");
			exit(1);
		}
		fclose(file);

		ALL_NGRAM = strlen(content) - NGRAM + 1;
		// 偶数なら１こ生やす
		EVEN = ALL_NGRAM % 2 == 0;
		if (EVEN)
		{
			ALL_NGRAM++;
		}

		// 確認
		// printf("content: %s\n", content); // myname...
		printf("ALL_NGRAM: %d\n", ALL_NGRAM);
		printf("EVEN: %d\n", EVEN);

		// ---------------------------------------------

		// 得られた文字列からアドレスを取得
		uint8_t **ascii_array;
		makeArrayU8(&ascii_array, ALL_NGRAM, NGRAM);
		for (uint32_t i = 0; i < ALL_NGRAM; i++)
		{
			for (uint32_t j = 0; j < NGRAM; j++)
			{
				ascii_array[i][j] = (uint8_t)(content[i + j]) - 97;
			}
		}

		// uint32_t **item_memory_array_new;
		// makeArrayU32(&item_memory_array_new, ALL_NGRAM, HV_NUM);

		uint32_t repeat_num = ALL_NGRAM;
		if (EVEN)
		{
			repeat_num--;
		}

		uint32_t result[HV_NUM];
		memset(result, 0, sizeof(result));

		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
		printf("  データ準備時間: %lf[ms]\n", time);

		// -----------------------------------------------------------------------

		// 計算時間
		start = clock();

		// all_ngramの数だけ、shiftとxorのエンコーディングを計算
		for (uint32_t i = 0; i < repeat_num; i++)
		{

			// -----------------------------------------------------
			// シフトしたものをitem_memory_array_reuslt[NGRAM][HV_NUM]に格納
			uint32_t **item_memory_array_result;
			makeArrayU32(&item_memory_array_result, NGRAM, HV_NUM);
			for (uint32_t j = 0; j < NGRAM; j++)
			{
				// shift
				perm_top(item_memory_array_result[j], item_memory_array[ascii_array[i][j]], j);
			}
			// シフト後のデータを各LEGNTHでxorしtmpに格納

			uint32_t bound_tmp[HV_NUM];
			memset(bound_tmp, 0, sizeof(bound_tmp));

			for (uint32_t l = 0; l < NGRAM; l++)
			{
				// bind(item_memory_array_new[i], item_memory_array_new[i], item_memory_array_result[l]);
				bind(bound_tmp, bound_tmp, item_memory_array_result[l]);
			}
			freeArrayU32(&item_memory_array_result, NGRAM);

			bound(bound_tmp);
		}
		// ---------------------------------------------
		if (EVEN)
		{
			// memcpy(item_memory_array_new[ALL_NGRAM - 1], item_memory_array[MAJORITY_ADDR], sizeof(uint32_t) * HV_NUM);
			bound(item_memory_array[MAJORITY_ADDR]);
		}
		// ---------------------------------------------
		// 結果を格納
		// Bounding
		// bound_batch(result, ALL_NGRAM, item_memory_array_new);
		bound_extract(result);

		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
		printf("  計算時間: %lf[ms]\n", time);

		// ---------------------------------------------
		// デバッグ用
		for (uint32_t j = 0; j < HV_NUM; j++)
		{
			printf("%u\n", result[j]);
		}
		// ---------------------------------------------

		// メモリ解放時間
		start = clock();

		// freeArrayU32(&item_memory_array_new, ALL_NGRAM);
		freeArrayU8(&ascii_array, ALL_NGRAM);

		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
		printf("  メモリ解放時間: %lf[ms]\n", time);
	}

	// メモリ解放時間
	start = clock();

	freeArrayU32(&item_memory_array, RAND_NUM);

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  メモリ解放時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	end = clock();
	time = ((double)(end - start_program)) / CLOCKS_PER_SEC * 1000.0;
	printf("  プログラム合計時間: %lf[ms]\n", time);

	return 0;
}