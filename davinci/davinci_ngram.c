#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define HV_DIM 1024
#define HV_NUM HV_DIM / 32

// -------------------- メモリリークチェック、デストラクター -----------------

// M1のみ使用
__attribute__((destructor)) static void destructor()
{
	system("leaks -q davinci_ngram");
}

// -----------------------------------------------------------------------

// y列x行のuint8_t２次元配列を確保
void makeArrayU8(uint8_t ***a, const size_t y, const size_t x)
{
	// ポインタの配列準備
	*a = (uint8_t **)calloc(y, sizeof(uint8_t *));

	// ポインタの配列の各要素に『配列』を格納
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint8_t *)calloc(x, sizeof(uint8_t));
	}
}

// y列x行のuint8_t２次元配列を解放
void freeArrayU8(uint8_t ***a, const size_t y)
{
	// ポインタの配列の各要素（配列）を解放
	for (int i = 0; i < y; i++)
	{
		// (*a)[i]に配列が格納されている
		free((*a)[i]);
	}
	// ポインタの配列を解放
	free(*a);
}

// -----------------------------------------------------------------------

// y列x行のuint32_tの２次元配列を確保
void makeArrayU32(uint32_t ***a, const size_t y, const size_t x)
{
	*a = (uint32_t **)calloc(y, sizeof(uint32_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint32_t *)calloc(x, sizeof(uint32_t));
	}
}

// y列x行のuint32_tの２次元配列を解放
void freeArrayU32(uint32_t ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

// -----------------------------------------------------------------------

// ランダム生成（xorshift）
uint32_t xor128(int reset)
{
	// 内部で値を保持（seed） パターン１
	// static uint32_t x = 2380889285;
	// static uint32_t y = 1631889387;
	// static uint32_t z = 1698655726;
	// static uint32_t w = 2336862850;

	// 内部で値を保持（seed） パターン２
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
		// 前回のxを使う
		uint32_t t = x ^ (x << 11);
		// 更新
		x = y;
		y = z;
		z = w;

		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
}

// -----------------------------------------------------------------------

// unsigned int 32bitのシフト
// num回右論理シフトしたやつを返す
// 引数のvには、右論理シフトではみだしたやつを（32-num)回論理左シフトして取り出す
uint32_t shifter_32(uint32_t *v, uint32_t num)
{
	// num回 論理右シフト
	uint32_t tmp_v = *v >> num;
	// 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
	uint32_t tmp_num = (1 << num) - 1;
	*v = (*v & tmp_num) << (32 - num);
	return tmp_v;
}

// unsigned int 1024bitのシフト
// 32bitのシフトを繰り返すことでエミュレート（現状31シフトが限界）
// 第一引数 ... uint32_t型の配列 (格納先)

// 第二引数 ... uint32_t型の配列
// 第三引数 ... 配列の個数
// 第四引数 ... 右シフトする数
// 8 - 128で割り切れる最大の数を型として使う
// initila関数に次元設定→型が自動的に決まって

// shifterとbindのインタフェースを揃える
// perm ... 対象ハイパーベクトル、Peramutationする数 -> ハイパーベクトル（返り値）
// bind ... 対象ハイパーベクトル、対象ハイパーベクトル -> ハイパーベクトル（返り値）
// bound ...ハイパーベクトルの配列　->  ハイパーベクトル（返り値）
// void shifter_1024(uint32_t new[HV_NUM], uint32_t original[HV_NUM], uint32_t perm_num)
// {
// 	if (perm_num == 0)
// 	{
// 		memcpy(new, original, sizeof(uint32_t) * HV_NUM);
// 		return;
// 	}
// 	// original[HV_NUM] 	... unsigned int のデータが32個格納（1024次元をエミュレート）
// 	// new[HV_NUM] 		... unsigned int のデータが32個格納（1024次元をエミュレート）
// 	// original配列に格納されているデータをシフトしたデータをnew配列に格納
// 	// シフトしたデータを一時的に格納
// 	uint32_t *result_tmp = (uint32_t *)calloc(HV_NUM, sizeof(uint32_t));
// 	// 32回繰り返す
// 	for (uint32_t i = 0; i < HV_NUM; i++)
// 	{
// 		// tmp		... num回右論理シフトした際にはみ出した部分を（32-num)回左論理シフトしたやつ
// 		// tmp_v 	... num回右論理シフトしたやつ
// 		uint32_t tmp = original[i];
// 		uint32_t tmp_v = shifter_32(&tmp, perm_num);
// 		// シフト
// 		result_tmp[i] |= tmp_v;
// 		if (i == 0)
// 		{
// 			result_tmp[HV_NUM - 1] |= tmp;
// 		}
// 		else
// 		{
// 			result_tmp[i - 1] |= tmp;
// 		}
// 	}
// 	// 結果を移す
// 	for (uint32_t i = 0; i < HV_NUM; i++)
// 	{
// 		new[i] = result_tmp[i];
// 	}
// 	free(result_tmp);
// }

void shifter_1024(uint32_t new[HV_NUM], uint32_t original[HV_NUM], uint32_t perm_num)
{
	// original[require_int_num] 	... unsigned int のデータが32個格納（1024次元をエミュレート）
	// new[require_int_num] 		... unsigned int のデータが32個格納（1024次元をエミュレート）

	// original配列に格納されているデータをシフトしたデータをnew配列に格納
	if (perm_num == 0)
	{
		memcpy(new, original, sizeof(uint32_t) * HV_NUM);
		return;
	}

	int flag = 1;
	unsigned int perm = 0;
	uint32_t result_hv[HV_NUM];
	memset(result_hv, 0, sizeof(result_hv));

	while (perm_num)
	{
		// あと何回かチェック
		if (perm_num > 31)
		{
			perm = 31;
			perm_num -= 31;
		}
		else
		{
			perm = perm_num;
			perm_num = 0;
		}

		if (flag)
		{
			// 32回繰り返す
			for (int i = 0; i < HV_NUM; i++)
			{
				// tmp		... num回右論理シフトした際にはみ出した部分を（32-num)回左論理シフトしたやつ
				// tmp_v 	... num回右論理シフトしたやつ
				unsigned int tmp = original[i];
				unsigned int tmp_v = shifter_32(&tmp, perm);

				// シフト
				result_hv[i] |= tmp_v;
				if (i == 0)
				{
					result_hv[HV_NUM - 1] |= tmp;
				}
				else
				{
					result_hv[i - 1] |= tmp;
				}
			}
			for (int i = 0; i < HV_NUM; i++)
			{
				new[i] = result_hv[i];
				result_hv[i] = 0;
			}
			flag = 0;
		}
		else
		{
			// 32回繰り返す
			for (int i = 0; i < HV_NUM; i++)
			{

				// tmp		... num回右論理シフトした際にはみ出した部分を（32-num)回左論理シフトしたやつ
				// tmp_v 	... num回右論理シフトしたやつ
				unsigned int tmp = new[i];
				unsigned int tmp_v = shifter_32(&tmp, perm);

				// シフト
				result_hv[i] |= tmp_v;
				if (i == 0)
				{
					result_hv[HV_NUM - 1] |= tmp;
				}
				else
				{
					result_hv[i - 1] |= tmp;
				}
			}
			for (int i = 0; i < HV_NUM; i++)
			{
				new[i] = result_hv[i];
				result_hv[i] = 0;
			}
		}
	}
}

// -----------------------------------------------------------------------

// 多数決関数　&& 加算
// 32bitの各ビットの立っている数を数えて多数決関数を実行し結果ベクトルを生成
// result_array[train_size] ... すべてのデータの 結果（unsigned int) が入っている。1024次元ならこのbounding関数を32回使う
uint32_t bounding(uint32_t result_array[], size_t train_size)
{
	// Populationカウントをして、その後多数決関数を実行
	uint32_t result = 0;
	// マスクをずらしながら各次元の1が立っている数を調べる
	uint32_t mask = (uint32_t)1 << (32 - 1);

	while (mask)
	{
		uint32_t buff = 0;
		// 訓練データの数だけ足し算
		for (uint32_t i = 0; i < train_size; i++)
		{
			buff += (mask & result_array[i] ? 1 : 0);
		}
		// 多数決で1の数が過半数なら、resultにmaskを加える（→対象のbit番目が1になる）
		if (buff > (train_size / 2))
		{
			// 多数決で1が優位だったら、該当ビットを立たせる
			result += mask;
		}
		mask >>= 1;
	}
	return result;
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
	const char *TRAIN_PATH[] = {"data/decorate/en", "data/decorate/fr"};
	// const char *TRAIN_PATH[] = {"data/decorate/enlong", "data/decorate/frlong"};
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
				ascii_array[i][j] = (unsigned char)(content[i + j]) - 97;
			}
		}

		uint32_t **item_memory_array_new;
		makeArrayU32(&item_memory_array_new, HV_NUM, ALL_NGRAM);

		uint32_t repeat_num = ALL_NGRAM;
		if (EVEN)
		{
			repeat_num--;
		}

		u_int32_t result[HV_NUM];

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
				shifter_1024(item_memory_array_result[j], item_memory_array[ascii_array[i][j]], j);
			}
			// シフト後のデータを各LEGNTHでxorしtmpに格納
			uint32_t tmp[HV_NUM];
			for (uint32_t j = 0; j < HV_NUM; j++)
			{
				tmp[j] = 0;
			}
			for (uint32_t k = 0; k < HV_NUM; k++)
			{
				for (uint32_t l = 0; l < NGRAM; l++)
				{
					// xor
					tmp[k] ^= item_memory_array_result[l][k];
				}
			}
			freeArrayU32(&item_memory_array_result, NGRAM);
			// ------------------------------------------------------
			// tmpに入ったエンコーディング結果でitem_memory_array_new[ALL_NGRAM][HV_NUM]を更新
			for (uint32_t k = 0; k < HV_NUM; k++)
			{
				item_memory_array_new[k][i] = tmp[k];
			}
		}
		// ---------------------------------------------
		if (EVEN)
		{
			for (uint32_t i = 0; i < HV_NUM; i++)
			{
				item_memory_array_new[i][ALL_NGRAM - 1] = item_memory_array[MAJORITY_ADDR][i];
			}
		}
		// ---------------------------------------------
		// 結果を格納
		// Bounding
		for (uint32_t i = 0; i < HV_NUM; i++)
		{
			result[i] = bounding(item_memory_array_new[i], ALL_NGRAM);
		}

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

		freeArrayU32(&item_memory_array_new, HV_NUM);
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