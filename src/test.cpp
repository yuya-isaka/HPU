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

int main(int argc, char **argv)
{

	unsigned int result_real = 0;
	unsigned int result = 0;
	// 理想の計算
	int tmp = 0;
	for (unsigned int i = 0; i < 24; i++)
	{
		result ^= shifter(i, i);
		tmp += 1;
		if (tmp == 3)
		{
			putb(result);
			result_real += result;
			tmp = 0;
			result = 0;
		}
		// putb(result);
	}

	printf("%d\n", result_real);
	putb(result_real);

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