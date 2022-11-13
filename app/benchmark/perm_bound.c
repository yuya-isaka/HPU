
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
void shifter_1024(unsigned int new[], unsigned int **original, const unsigned int require_int_num, unsigned int num)
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
		new[i] = result_bind[i];
	}

	free(result_bind);
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
	// -----------------------------------------------------------------------

	// 時間測る
	clock_t start = clock();

	// 1024bitを表現するのに必要なintの数
	const int require_int_num = 32;

	// seed設定
	srand(10);

	// -----------------------------------------------------------------------

	// ランダム生成の初期化
	xor128(1);

	// 生成するランダムなハイパーベクトルの数
	const int item_memory_num = 1024;

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

	// -----------------------------------------------------------------------
	// 実験

	int trial_num = 50000000;

	// 結果を格納
	int result_perm_bound[1024];
	// 初期化しないとバグる
	for (int i = 0; i < 1024; i++)
	{
		result_perm_bound[i] = 0;
	}

	// 試行
	for (int i = 0; i < trial_num; i++) // 5000万
	{
		// アドレス生成
		int addr1 = rand() % 1024;

		// Permutation回数
		int num = rand() % 1024;

		// Perm
		unsigned int result_tmp[require_int_num];
		shifter_1024(result_tmp, &item_memory_array[addr1], require_int_num, num);

		for (int j = 0; j < require_int_num; j++) // 32
		{
			// bound
			unsigned int mask = 1;
			for (int k = 0; k < 32; k++) // 32
			{
				result_perm_bound[j * 32 + k] += (mask & result_tmp[j] ? -1 : 1);
				mask <<= 1;
			}
		}
	}

	// 多数決格納先
	unsigned int result_majority[require_int_num];
	// 初期化しないとバグる
	for (int i = 0; i < require_int_num; i++)
	{
		result_majority[i] = 0;
	}

	// 多数決
	unsigned int main_mask = 1 << (32 - 1);
	for (int i = 0; i < require_int_num; i++) // 32
	{
		for (int j = 0; j < 32; j++) // 32
		{
			// 符号ビットが立ってたら、1 たってなかったら０
			unsigned int result_tmp = (result_perm_bound[i * 32 + j] & main_mask ? 1 : 0);
			result_majority[i] += result_tmp << j;
		}
	}

	// 結果出力
	for (int i = 0; i < require_int_num; i++)
	{
		printf("%u\n", result_majority[i]);
	}

	// 解放
	freeArrayInt(&item_memory_array, item_memory_num);

	// -----------------------------------------------------------------------

	clock_t end = clock();
	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n\nPermu time %lf[ms]\n", time);

	return 0;
}
