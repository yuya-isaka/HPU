
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>

// --------------------- メモリリークチェック、デストラクター -----------------------

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

// -----------------------------------------------------------------------

void makeArray(uint16_t ***a, const int y, const int x)
{
	*a = (uint16_t **)calloc(y, sizeof(uint16_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint16_t *)calloc(x, sizeof(uint16_t));
	}
}

void freeArray(uint16_t ***a, const int y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

void makeArrayInt(unsigned int ***a, const int y, const int x)
{
	*a = (unsigned int **)calloc(y, sizeof(unsigned int *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (unsigned int *)calloc(x, sizeof(unsigned int));
	}
}

void freeArrayInt(unsigned int ***a, const int y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

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

// 多数決関数　&& 加算
unsigned int grab_bit(unsigned int result_array[], size_t size)
{
	unsigned int result = 0;

	// 次元数可変
	unsigned int mask = (int)1 << (32 - 1);
	while (mask)
	{
		int tmp = 0;
		for (int i = 0; i < size; i++)
		{
			tmp += (mask & result_array[i] ? 1 : 0);
		}
		// 多数決で1の数が過半数なら、resultにmaskを加える（→対象のbit番目が1になる）
		if (tmp > (size / 2))
		{
			result += mask;
		}
		mask >>= 1;
	}
	return result;
}

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

	// 32回繰り返す
	for (int i = 0; i < require_int_num; i++)
	{

		// tmp		... num回右論理シフトした際にはみ出した部分を（32-num)回左論理シフトしたやつ
		// tmp_v 	... num回右論理シフトしたやつ
		unsigned int tmp = (*original)[i];
		unsigned int tmp_v = shifter_32(&tmp, num);

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

	// 結果を移す
	for (int i = 0; i < require_int_num; i++)
	{
		(*new)[i] = result_bind[i];
	}

	free(result_bind);
}

int main(int argc, char const *argv[])
{
	clock_t start = clock();

	const int DIM = 32;
	const int rand_num = 1024;

	srand(10);
	xor128(1);

	// ランダムなハイパーベクトルを生成
	unsigned int **item_memory_array;
	makeArrayInt(&item_memory_array, rand_num, DIM);

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
			// printf("%u\n", tmp);
		}
	}

	int trial_num = 50000000;

	unsigned int **result_tmp;
	makeArrayInt(&result_tmp, trial_num, DIM);

	for (int i = 0; i < trial_num; i++)
	{
		shifter_1024(&result_tmp[i], &item_memory_array[rand() % 1024], DIM, 2);
	}

	// unsigned int result[DIM];
	// for (int i = 0; i < DIM; i++)
	// {
	// 	result[i] = grab_bit(result_tmp[i], trial_num);
	// }

	// for (int i = 0; i < DIM; i++)
	// {
	// 	printf("%u\n", result[i]);
	// }

	clock_t end = clock();
	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n\n  time %lf[ms]\n", time);

	return 0;
}
