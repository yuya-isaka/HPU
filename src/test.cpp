#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

	// const int NGRAM = 3;

	int ascii[26];
	for (int i = 0; i < 26; i++)
	{
		ascii[i] = rand() & 0x000000ff;
		printf("%c:%d, ", i + 97, ascii[i]);
	}
	printf("\n");

	const char *hello = "helloworld";

	// CGRAを４列と仮定
	// int *sample[4];
	// for (i = 0; i < 4; i++)
	// {
	//   sample[i] = (int *)calloc(((strlen(hello) - 2) / 4) * NGRAM, sizeof(int)); // また変える必要あり
	// }
	int sample[4][6];
	for (int i = 0; i < (strlen(hello) - 2) / 2; i++) // 4でいい
	{
		for (int k = 0; k < 3; k++)
		{
			const char tmp = hello[i + k];
			const int addr = tmp - 97; // 'a' = 97
			sample[i][k] = ascii[addr];
			printf("%c:%3d ", tmp, sample[i % 4][k]);
		}
		printf(" | ");
		for (int k = 0; k < 3; k++)
		{
			const char tmp = hello[i + 4 + k];			  // ここが変わってる
			const int addr = tmp - 97;					  // 'a' = 97
			sample[i][k + 3] = ascii[addr];				  // ここが変わってる
			printf("%c:%3d ", tmp, sample[i % 4][k + 3]); // ここが変わってる
		}
		printf("\n");
	}
}