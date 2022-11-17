
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
void shifter_1024(unsigned int **new, unsigned int **original, const unsigned int require_int_num, unsigned int num)
{
	// original[require_int_num] 	... unsigned int のデータが32個格納（1024次元をエミュレート）
	// new[require_int_num] 		... unsigned int のデータが32個格納（1024次元をエミュレート）

	// original配列に格納されているデータをシフトしたデータをnew配列に格納

	// シフトしたデータを一時的に格納
	unsigned int *result_bind = (unsigned int *)calloc(require_int_num, sizeof(unsigned int));

	unsigned int perm = 0;
	while (num)
	{

		// あと何回かチェック
		if (num > 31)
		{
			perm = 31;
			num -= 31;
		}
		else
		{
			perm = num;
			num = 0;
		}

		// 32回繰り返す
		for (int i = 0; i < require_int_num; i++)
		{

			// tmp		... num回右論理シフトした際にはみ出した部分を（32-num)回左論理シフトしたやつ
			// tmp_v 	... num回右論理シフトしたやつ
			unsigned int tmp = (*original)[i];
			unsigned int tmp_v = shifter_32(&tmp, perm);

			// シフト
			result_bind[i] |= tmp_v;
			if (i == 0)
			{
				result_bind[require_int_num - 1] |= tmp;
			}
			else
			{
				result_bind[i - 1] |= tmp;
			}
		}
	}

	// 結果を移す
	for (int i = 0; i < require_int_num; i++)
	{
		(*new)[i] = result_bind[i];
	}

	free(result_bind);
}

// -----------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	// プログラム全体の時間
	clock_t start_program = clock();

	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	// -----------------------------------------------------------------------

	// 初期化時間
	clock_t start = clock();

	// seed設定
	srand(10);

	// ランダム生成の初期化
	xor128(1);

	// 生成するランダムなハイパーベクトルの数
	const int item_memory_num = 1024;

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

	const int trial_num = 50000000;
	const int perm_num = 3;

	int *addr = (int *)calloc(trial_num, sizeof(int));

	for (int i = 0; i < trial_num; i++)
	{
		addr[i] = rand() % 512;
	}

	// Permutation結果を格納
	unsigned int **result;
	makeArrayInt(&result, trial_num, require_int_num);

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  データ準備時間: %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// 計算時間
	start = clock();

	// 試行
	for (int i = 0; i < trial_num; i++)
	{
		// Perm
		shifter_1024(&result[i], &item_memory_array[addr[i]], require_int_num, perm_num);
	}

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("  計算時間(Load+Permutation): %lf[ms]\n", time);

	// -----------------------------------------------------------------------

	// メモリ解放時間
	start = clock();

	// 解放
	free(addr);
	freeArrayInt(&result, trial_num);
	freeArrayInt(&item_memory_array, item_memory_num);

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
