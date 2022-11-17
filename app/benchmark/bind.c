
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>

// // --------------------- メモリリークチェック、デストラクター -----------------------

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }

// -----------------------------------------------------------------------

// y列x行のunsigned int２次元配列を確保
void makeArrayInt(unsigned int ***a, const int y, const int x)
{
	*a = (unsigned int **)calloc(y, sizeof(unsigned int *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (unsigned int *)calloc(x, sizeof(unsigned int));
	}
}

// y列x行のunsigned int２次元配列を解放
void freeArrayInt(unsigned int ***a, const int y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

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

int main(int argc, char const *argv[])
{
	// プログラム全体の時間
	clock_t start_program = clock();

	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// 初期化時間
	clock_t start = clock();

	// seed設定
	srand(10);

	// ランダム生成の初期化
	xor128(1);

	// 生成するランダムなハイパーベクトルの数
	const int item_memory_num = 512;

	// 1024bitを表現するのに必要なintの数
	const int require_int_num = 32;

	// ランダムなハイパーベクトルを格納
	unsigned int **item_memory_array;
	makeArrayInt(&item_memory_array, item_memory_num, require_int_num);

	// 生成
	for (int i = 0; i < item_memory_num; i++) // 1024
	{
		for (int j = 0; j < require_int_num; j++) // 32
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

	// データ準備時間
	start = clock();

	// 試行回数
	const int trial_num = 50000000;

	int *addr1 = (int *)calloc(trial_num, sizeof(int));
	int *addr2 = (int *)calloc(trial_num, sizeof(int));

	for (int i = 0; i < trial_num; i++)
	{
		addr1[i] = rand() % 512;
		addr2[i] = rand() % 512;
	}

	// 結果を格納
	unsigned int **result_bind;
	makeArrayInt(&result_bind, require_int_num, trial_num);

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  データ準備時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// 計算時間
	start = clock();

	// 試行
	for (int j = 0; j < require_int_num; j++) // 32
	{
		for (int i = 0; i < trial_num; i++) // 5000万
		{
			result_bind[j][i] = item_memory_array[addr1[i]][j] ^ item_memory_array[addr2[i]][j];
		}
	}

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  計算時間(Load+Binding): %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// メモリ解放時間
	start = clock();

	// 解放
	free(addr1);
	free(addr2);
	freeArrayInt(&result_bind, require_int_num);
	freeArrayInt(&item_memory_array, item_memory_num);

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  メモリ解放時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	// タイム確認
	end = clock();
	time = ((double)(end - start_program)) / CLOCKS_PER_SEC * 1000.0;
	printf("  プログラム合計時間: %lf[ms]\n", time);

	return 0;
}
