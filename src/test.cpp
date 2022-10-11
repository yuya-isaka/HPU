// include
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

unsigned int shifter(unsigned int v, unsigned int num)
{
	// num回 論理右シフト
	unsigned int tmp = v >> num;

	// 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
	unsigned int tmp_num = (1 << num) - 1;
	unsigned int tmp_v = (v & tmp_num) << ((sizeof(v) * 8) - num);

	tmp_v = tmp_v | tmp;
	return tmp_v;
}

unsigned int grab_bit(unsigned int result_array[], size_t size)
{
	unsigned int result = 0;

	unsigned int mask = (int)1 << (sizeof(result_array[0]) * 8 - 1);
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

// 周期が2^128
// 32bitごとに結果（LFSRは１bitごと）
unsigned int xor128(void)
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

	// 前回のxを使う
	unsigned int t = x ^ (x << 11);
	// 更新
	x = y;
	y = z;
	z = w;

	return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// item_memoryの数（top.vの設定値より１つ大きくする）
const int RANNUM = 1001;

// 偶数 ... ADDRNUM/NGRAM/2-1をtop.vに設定  (例：900 ... 900/NGRAM/2-1=149)
// 奇数 ... ADDRNUM/NGRAM/2をtop.vに設定	(例:903 ... 903/NGRAM/2=150）
// tb.cppのADDRNUMとは一緒
const int ADDRNUM = 900;

// N-gram
const int NGRAM = 3;

// ADDRNUM / NGRAM + 1を設定
const int ARNUM = ADDRNUM / NGRAM + 1;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{

	printf("\n ------------------------------- 開始 ------------------------------- \n\n");

	// hdcテスト
	unsigned int item_memory_array[RANNUM];
	item_memory_array[0] = 88675123;
	for (unsigned int i = 1; i < RANNUM; i++)
	{
		item_memory_array[i] = xor128();
		// printf("   %d:  %10u\n", i, item_memory_array[i]);
	}

	unsigned int result_array[ARNUM] = {0};
	unsigned int result = 0;
	int tmp = 0;
	int num = 0;
	for (unsigned int i = 0; i < ADDRNUM; i++)
	{
		result ^= shifter(item_memory_array[i], tmp);
		tmp += 1;
		if (tmp == NGRAM)
		{
			// putb(result);
			// printf("%u\n", result);
			result_array[num] = result;
			tmp = 0;
			result = 0;
			num += 1;
		}
	}

	// 多数決関数用
	if ((ADDRNUM / NGRAM) < ARNUM)
	{
		result_array[num] = item_memory_array[RANNUM - 1];
		// printf("%u", item_memory_array[RANNUM - 1]);
	}

	unsigned int result_real = grab_bit(result_array, sizeof(result_array) / sizeof(result_array[0]));

	printf("  %u\n\n", result_real);
	putb(result_real);

	printf("\n ------------------------------- 終了 ------------------------------- \n");
}
