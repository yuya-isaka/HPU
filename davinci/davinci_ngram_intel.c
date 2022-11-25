#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>
// #include <cstdlib>
// #include <cstdio>
#include <x86intrin.h>

// --------------------- メモリリークチェック、デストラクター -----------------------

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }

// -----------------------------------------------------------------------

// -----------------------------------------------------------------------

#define DIM 1024

#if DIM % 256 == 0
typedef __m256i HV;
#define HV_NUM DIM / 256
#elif DIM % 128 == 0
typedef __m128i HV
#define HV_NUM DIM / 128
#elif DIM % 64 == 0
typedef uint64_t HV;
#define HV_NUM DIM / 64
#elif DIM % 32 == 0
typedef uint32_t HV;
#define HV_NUM DIM % 32
#elif DIM % 16 == 0
typedef uint16_t HV;
#define HV_NUM DIM % 16
#elif DIM % 8 == 0
typedef uint8_t HV;
#define HV_NUM DIM % 8
#endif

// -----------------------------------------------------------------------

// -----------------------------------------------------------------------

__attribute__((overloadable)) void makeArray(__m256i ***a, const size_t y, const size_t x)
{
	*a = (__m256i **)_mm_malloc(sizeof(__m256i *) * y, 32);
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (__m256i *)_mm_malloc(sizeof(__m256i) * x, 32);
		(*a)[i] = _mm256_setzero_si256();
	}
}

__attribute__((overloadable)) void makeArray(__m128i ***a, const size_t y, const size_t x)
{
	*a = (__m128i **)_mm_malloc(sizeof(__m128i *) * y, 16);
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (__m128i *)_mm_malloc(sizeof(__m128i) * x, 16);
		(*a)[i] = _mm128_setzero_si256();
	}
}

__attribute__((overloadable)) void makeArray(uint64_t ***a, const size_t y, const size_t x)
{
	*a = (uint64_t **)calloc(y, sizeof(uint64_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint64_t *)calloc(x, sizeof(uint64_t));
	}
}

__attribute__((overloadable)) void makeArray(uint32_t ***a, const size_t y, const size_t x)
{
	*a = (uint32_t **)calloc(y, sizeof(uint32_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint32_t *)calloc(x, sizeof(uint32_t));
	}
}

__attribute__((overloadable)) void makeArray(uint16_t ***a, const size_t y, const size_t x)
{
	*a = (uint16_t **)calloc(y, sizeof(uint16_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint16_t *)calloc(x, sizeof(uint16_t));
	}
}

__attribute__((overloadable)) void makeArray(uint8_t ***a, const size_t y, const size_t x)
{
	*a = (uint8_t **)calloc(y, sizeof(uint8_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint8_t *)calloc(x, sizeof(uint8_t));
	}
}

// -----------------------------------------------------------------------

// -----------------------------------------------------------------------

__attribute__((overloadable)) void freeArray(__m256i ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		_mm_free((*a)[i]);
	}
	_mm_free(*a);
}

__attribute__((overloadable)) void freeArray(__m128i ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		_mm_free((*a)[i]);
	}
	_mm_free(*a);
}

__attribute__((overloadable)) void freeArray(uint64_t ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

__attribute__((overloadable)) void freeArray(uint32_t ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

__attribute__((overloadable)) void freeArray(uint16_t ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

__attribute__((overloadable)) void freeArray(uint8_t ***a, const size_t y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

// -----------------------------------------------------------------------

// -----------------------------------------------------------------------

// ランダム生成（xorshift）
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

// -----------------------------------------------------------------------

// unsigned int 32bitのシフト
// num回右論理シフトしたやつを返す
// 引数のvには、右論理シフトではみだしたやつを（32-num)回論理左シフトして取り出す
unsigned int shifter_32(unsigned int *v, unsigned int num)
{
	// num回 論理右シフト
	unsigned int tmp_v = *v >> num;
	// 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
	unsigned int tmp_num = (1 << num) - 1;
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
void shifter_1024(const unsigned int DIM, unsigned int new[DIM], unsigned int original[DIM], unsigned int num)
{
	// original[DIM] 	... unsigned int のデータが32個格納（1024次元をエミュレート）
	// new[DIM] 		... unsigned int のデータが32個格納（1024次元をエミュレート）
	// original配列に格納されているデータをシフトしたデータをnew配列に格納
	// シフトしたデータを一時的に格納
	unsigned int *result_tmp = (unsigned int *)calloc(DIM, sizeof(unsigned int));
	// 32回繰り返す
	for (int i = 0; i < DIM; i++)
	{
		// tmp		... num回右論理シフトした際にはみ出した部分を（32-num)回左論理シフトしたやつ
		// tmp_v 	... num回右論理シフトしたやつ
		unsigned int tmp = original[i];
		unsigned int tmp_v = shifter_32(&tmp, num);
		// シフト
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
	// 結果を移す
	for (int i = 0; i < DIM; i++)
	{
		new[i] = result_tmp[i];
	}
	free(result_tmp);
}

// -----------------------------------------------------------------------

// 多数決関数　&& 加算
// 32bitの各ビットの立っている数を数えて多数決関数を実行し結果ベクトルを生成
// result_array[train_size] ... すべてのデータの 結果（unsigned int) が入っている。1024次元ならこのbounding関数を32回使う
unsigned int bounding(unsigned int result_array[], size_t train_size)
{
	// Populationカウントをして、その後多数決関数を実行
	unsigned int result = 0;
	// マスクをずらしながら各次元の1が立っている数を調べる
	unsigned int mask = (int)1 << (32 - 1);
	while (mask)
	{
		int buff = 0;
		// 訓練データの数だけ足し算
		for (int i = 0; i < train_size; i++)
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

	const int train_num = 2;
	// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	// const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	const char *train_path[] = {"data/decorate/enlong", "data/decorate/frlong"};
	const int ngram = 3;
	const int DIM = 1024 / 32;
	const int rand_num = 27;
	// 偶数のときにユーザが適当に追加する値のアドレス
	const int majority_tmp = 26;
	int all_ngram = 0;
	int even = 0;

	// ---------------------------------------------

	// ランダム生成の部分をそれぞれ作る ----------------------------
	// ランダム生成の初期化
	xor128(1);

	// ランダムなハイパーベクトルを生成
	uint32_t **item_memory_array;
	makeArray(&item_memory_array, rand_num, DIM);

	for (int i = 0; i < rand_num; i++)
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
		}
	}

	clock_t end = clock();
	double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  初期化時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// 英語とフランス語の数だけ繰り返す
	for (int i = 0; i < train_num; i++)
	{

		// データ準備時間
		start = clock();

		// ファイル読み込み
		const char *path = train_path[i];
		printf("\n------------- %sの学習 -------------\n\n", path);
		FILE *file;
		file = fopen(path, "r");
		if (file == NULL)
		{
			perror("  Failed: open file");
			exit(1);
		}
		// ---------------------------------------------
		// ファイルから文字列を取得
		int ch;
		int num = 0;
		// 与えられたファイルがひと続きの文字列と仮定 (2行になると｛10, 0x0a, LF(改行)｝ が入ってしまいズレる)
		while ((ch = fgetc(file)) != EOF)
		{
			num++;
		}
		printf("EOF: %d\n", EOF); // EOFは全て-1 (Mac, Linux, Petalinux)
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
		// 偶数なら１こ生やす
		even = all_ngram % 2 == 0;
		if (even)
		{
			all_ngram++;
		}

		// 確認
		// printf("content: %s\n", content); // myname...
		printf("all_ngram: %d\n", all_ngram);
		printf("even: %d\n", even);
		// ---------------------------------------------
		// 得られた文字列からアドレスを取得
		uint16_t **ascii_array;
		makeArray(&ascii_array, all_ngram, ngram);
		for (int i = 0; i < all_ngram; i++)
		{
			for (int j = 0; j < ngram; j++)
			{
				ascii_array[i][j] = (unsigned char)(content[i + j]) - 97;
			}
		}

		uint32_t **item_memory_array_new;
		makeArray(&item_memory_array_new, DIM, all_ngram);

		int repeat_num = all_ngram;
		if (even)
		{
			repeat_num--;
		}

		unsigned int result[DIM];

		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
		printf("  データ準備時間: %lf[ms]\n", time);

		// -----------------------------------------------------------------------

		// 計算時間
		start = clock();

		// all_ngramの数だけ、shiftとxorのエンコーディングを計算
		for (int i = 0; i < repeat_num; i++)
		{

			// -----------------------------------------------------
			// シフトしたものをitem_memory_array_reuslt[ngram][DIM]に格納
			uint32_t **item_memory_array_result;
			makeArray(&item_memory_array_result, ngram, DIM);
			for (int j = 0; j < ngram; j++)
			{
				// shift
				shifter_1024(DIM, item_memory_array_result[j], item_memory_array[ascii_array[i][j]], j);
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
				item_memory_array_new[k][i] = tmp[k];
			}
		}
		// ---------------------------------------------
		if (even)
		{
			for (int i = 0; i < DIM; i++)
			{
				item_memory_array_new[i][all_ngram - 1] = item_memory_array[majority_tmp][i];
			}
		}
		// ---------------------------------------------
		// 結果を格納
		// Bounding
		for (int i = 0; i < DIM; i++)
		{
			result[i] = bounding(item_memory_array_new[i], all_ngram);
		}

		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
		printf("  計算時間: %lf[ms]\n", time);

		// ---------------------------------------------
		// デバッグ用
		for (int j = 0; j < DIM; j++)
		{
			printf("%u\n", result[j]);
		}
		// ---------------------------------------------

		// メモリ解放時間
		start = clock();

		freeArrayInt(&item_memory_array_new, DIM);
		freeArray(&ascii_array, all_ngram);

		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
		printf("  メモリ解放時間: %lf[ms]\n", time);
	}

	// メモリ解放時間
	start = clock();

	freeArrayInt(&item_memory_array, rand_num);

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