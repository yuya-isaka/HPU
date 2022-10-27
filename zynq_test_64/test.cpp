// include
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 可変パラメータ

const int DIM = 32 / 32;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 変わらん

const int RANNUM = 1024;
const int BUSWIDTH = 1024;
unsigned int item_memory_array[DIM][RANNUM];
unsigned int item_memory_array_new[DIM][RANNUM];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printb(unsigned int v)
{
	unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
	do
		putchar(mask & v ? '1' : '0');
	while (mask >>= 1);
}

void putb(unsigned int v)
{
	printf("  0"), putchar('b'), printb(v), putchar('\n');
}

unsigned int shifter_2(unsigned int *v, unsigned int num)
{
	// num回 論理右シフト
	unsigned int tmp_v = *v >> num;

	// 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
	unsigned int tmp_num = (1 << num) - 1;
	*v = (*v & tmp_num) << (32 - num);

	return tmp_v;
}

void shifter_new(const int NGRAM)
{
	int num = 0;
	for (int i = 0; i < RANNUM; i++)
	{
		unsigned int result_tmp[DIM] = {0};
		for (int j = 0; j < DIM; j++)
		{
			unsigned int tmp = item_memory_array[j][i];
			unsigned int tmp_v = shifter_2(&tmp, num);
			result_tmp[j] |= tmp_v;
			if (j == 0)
			{
				result_tmp[DIM - 1] |= tmp;
			}
			else
			{
				result_tmp[j - 1] |= tmp;
			}
		}

		for (int j = 0; j < DIM; j++)
		{
			item_memory_array_new[j][i] = result_tmp[j];
		}

		num++;
		if (num == NGRAM)
		{
			num = 0;
		}
	}
}

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
		if (tmp > (size / 2))
		{
			result += mask;
		}
		mask >>= 1;
	}
	return result;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check(const int NGRAM, const int CORENUM, const int ADDRNUM)
{

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;
	int ARNUM = ADDRNUM / NGRAM;
	if (EVEN)
	{
		ARNUM++;
	}
	const int LAST = ADDRNUM - 48;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	item_memory_array[0][0] = 88675123;
	for (int j = 0; j < RANNUM; j++)
	{
		for (int i = 0; i < DIM; i++)
		{
			if (i == 0 && j == 0)
				continue;
			item_memory_array[i][j] = xor128(0);
		}
	}

	// あらかじめPermutation
	shifter_new(NGRAM);

	// 1024 / 32bit なら 32回実行
	// 縦は同じハイパーベクトルなので、縦同士を計算させる
	// 横を全てxorすることを縦の数分繰り返す
	// すると縦の数の結果が残る。それが今回求めたい1024次元のハイパーベクトル
	for (int j = 0; j < DIM; j++)
	{
		unsigned int *result_array = (unsigned int *)malloc(sizeof(unsigned int) * ARNUM);
		if (result_array == NULL)
		{
			exit(0);
		}
		unsigned int result = 0;
		int tmp = 0;
		int num = 0;
		for (int i = 0; i < ADDRNUM; i++)
		{
			result ^= item_memory_array_new[j][i];
			// printf("%d:%u\n", i, item_memory_array_new[j][i]);
			tmp += 1;
			if (tmp == NGRAM)
			{
				// printf("%u\n", result);
				// putb(result);
				result_array[num] = result;
				tmp = 0;
				result = 0;
				num += 1;
			}
		}
		// 多数決関数用
		if (EVEN)
		{
			result_array[num] = item_memory_array[j][RANNUM - 1];
			// printf("ランダム：%u\n", result_array[num]);
			// putb(result_array[num]);
		}
		unsigned int result_real = grab_bit(result_array, ARNUM);
		printf("  %u\n", result_real);
		// putb(result_real);
		printf("\n");

		free(result_array);
	}

	return;
}

int main(int argc, char **argv)
{
	printf("\n ------------------------------- 開始 ------------------------------- \n\n\n");

	const int NGRAM = 3;
	const int CORENUM = 16;
	int ADDRNUM = 0;

	for (int i = 48; i < RANNUM; i += 48)
	{
		ADDRNUM = i;

		check(NGRAM, CORENUM, ADDRNUM);
		xor128(1);

		printf(" --------\n\n");
	}

	printf("\n ------------------------------- 終了 ------------------------------- \n");
	return 0;
}