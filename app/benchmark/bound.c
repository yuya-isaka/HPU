
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

// 多数決関数　&& 加算
// 32bitの各ビットの立っている数を数えて多数決関数を実行し結果ベクトルを生成
// result_array[train_size] ... すべてのデータの 結果（unsigned int) が入っている。1024次元ならこのbounding関数を32回使う
unsigned int bounding(unsigned int result_array[], size_t train_size)
{
	// Populationカウントをして、その後多数決関数を実行

	unsigned int result_bind_bound = 0;

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
			result_bind_bound += mask;
		}

		mask >>= 1;
	}

	return result_bind_bound;
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
	// const int trial_num = 50000000;
	const int trial_num = 10000000;

	int *addr = (int *)calloc(trial_num, sizeof(int));

	for (int i = 0; i < trial_num; i++)
	{
		addr[i] = rand() % 512;
	}

	// ロードデータ格納
	unsigned int **data;
	makeArrayInt(&data, require_int_num, trial_num);

	unsigned int result[require_int_num];

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  データ準備時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// 計算時間
	start = clock();

	// ロード時間
	clock_t start_load = clock();

	// アイテムメモリからロード
	for (int j = 0; j < require_int_num; j++) // 32
	{
		for (int i = 0; i < trial_num; i++) // 5000万
		{
			data[j][i] = item_memory_array[addr[i]][j];
		}
	}

	end = clock();
	time = ((double)(end - start_load)) / CLOCKS_PER_SEC * 1000.0;
	printf("   (Load計算時間: %lf[ms])\n", time);

	// Bounding時間
	clock_t start_bound = clock();

	// 試行
	for (int i = 0; i < require_int_num; i++)
	{
		// bound
		result[i] = bounding(data[i], trial_num);
	}

	end = clock();
	time = ((double)(end - start_bound)) / CLOCKS_PER_SEC * 1000.0;
	printf("   (Bounding計算時間: %lf[ms])\n", time);

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  計算時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// メモリ解放時間
	start = clock();

	// 解放
	free(addr);
	freeArrayInt(&data, require_int_num);
	freeArrayInt(&item_memory_array, item_memory_num);

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  メモリ解放時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// 結果出力
	for (int i = 0; i < require_int_num; i++)
	{
		printf("%u\n", result[i]);
	}

	// -----------------------------------------------------------------------

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	end = clock();
	time = ((double)(end - start_program)) / CLOCKS_PER_SEC * 1000.0;
	printf("  プログラム合計時間: %lf[ms]\n", time);

	return 0;
}
