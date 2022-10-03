#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void printb(unsigned int v)
{
	unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
	// printf("%lu\n", sizeof(v));
	do
		putchar(mask & v ? '1' : '0');
	while (mask >>= 1);
}

void putb(unsigned int v)
{
	putchar('0'), putchar('b'), printb(v), putchar('\n');
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

uint32_t xor128(void)
{
	// 内部で値を保持（seed） パターン１
	static uint32_t x = 2380889285;
	static uint32_t y = 1631889387;
	static uint32_t z = 1698655726;
	static uint32_t w = 2336862850;

	// 内部で値を保持（seed） パターン２
	// static uint32_t x = 123456789;
	// static uint32_t y = 362436069;
	// static uint32_t z = 521288629;
	// static uint32_t w = 88675123;

	// 前回のxを使う
	uint32_t t = x ^ (x << 11);
	// 更新
	x = y;
	y = z;
	z = w;

	return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

//////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{

	printf("\n ------------------------------- 開始 ------------------------------- \n\n");

	// randomテスト
	for (int i = 0; i < 10; i++)
	{
		printf("   %d:  %10u\n", i, xor128());
	}

	// hdcテスト
	// unsigned int sample_array[24];
	// unsigned int sample = 33215360;
	// for (int i = 0; i < 24; i++)
	// {
	// 	sample_array[i] = sample;
	// 	sample += 180038;
	// }

	// unsigned int item_memory_array[100];
	// unsigned int item_memory_value = 33215360;
	// for (unsigned int i = 0; i < 100; i++)
	// {
	// 	item_memory_array[i] = item_memory_value;
	// 	item_memory_value += 18360;
	// }

	// unsigned int result_array[8];
	// unsigned int result = 0;
	// int tmp = 0;
	// int num = 0;
	// for (unsigned int i = 0; i < 24; i++)
	// {
	// 	result ^= shifter(item_memory_array[i], tmp);
	// 	tmp += 1;
	// 	if (tmp == 3)
	// 	{
	// 		putb(result);
	// 		result_array[num] = result;
	// 		tmp = 0;
	// 		result = 0;
	// 		num += 1;
	// 	}
	// }

	// unsigned int result_real = grab_bit(result_array, sizeof(result_array) / sizeof(result_array[0]));
	// printf("%d\n", result_real);
	// putb(result_real);

	printf("\n ------------------------------- 終了 ------------------------------- \n");

	// n-gramテスト
	// // const int NGRAM = 3;

	// int ascii[26];
	// for (int i = 0; i < 26; i++)
	// {
	// 	ascii[i] = rand() & 0x000000ff;
	// 	printf("%c:%d, ", i + 97, ascii[i]);
	// }
	// printf("\n");

	// const char *hello = "helloworld";

	// // CGRAを４列と仮定
	// // int *sample[4];
	// // for (i = 0; i < 4; i++)
	// // {
	// //   sample[i] = (int *)calloc(((strlen(hello) - 2) / 4) * NGRAM, sizeof(int)); // また変える必要あり
	// // }
	// int sample[4][6];
	// for (int i = 0; i < (strlen(hello) - 2) / 2; i++) // 4でいい
	// {
	// 	for (int k = 0; k < 3; k++)
	// 	{
	// 		const char tmp = hello[i + k];
	// 		const int addr = tmp - 97; // 'a' = 97
	// 		sample[i][k] = ascii[addr];
	// 		printf("%c:%3d ", tmp, sample[i % 4][k]);
	// 	}
	// 	printf(" | ");
	// 	for (int k = 0; k < 3; k++)
	// 	{
	// 		const char tmp = hello[i + 4 + k];			  // ここが変わってる
	// 		const int addr = tmp - 97;					  // 'a' = 97
	// 		sample[i][k + 3] = ascii[addr];				  // ここが変わってる
	// 		printf("%c:%3d ", tmp, sample[i % 4][k + 3]); // ここが変わってる
	// 	}
	// 	printf("\n");
	// }
}