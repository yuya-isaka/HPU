#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// --------------------------------------- メモリリークチェック、デストラクター -----------------------------------------

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }

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

// -------------------------------------------  パラメータ設定 ---------------------------------------------------

// n-gram
const int NGRAM = 3;

// 次元数
#define LENGTH 1024
const int DIM = LENGTH / 32;

// 学習対象の個数（英語、フランス語）
int train_num = 2;

// 訓練データ指定
const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"}; // 文字数少なめ
// const char *train_path[] = {"data/decorate/en2", "data/decorate/fr2"}; // 文字数少なめよりは多め
// const char *train_path[] = {"data/decorate/en", "data/decorate/fr"}; // 文字数多め

// テストの個数（英語、フランス語）
int test_num = 2;

// テストデータ指定
const char *test_path[] = {"data/decorate/t1", "data/decorate/t2"};

// --------------------------------------------- ハイパーベクトル、メモリアロケート、メモリフリー　---------------------------------------------------------

typedef struct
{
	uint8_t *values;
} HyperVector;

int allocateMemoryHyperVector(HyperVector *v)
{
	v->values = (uint8_t *)calloc(LENGTH, sizeof(uint8_t));
	// 確保できなかったらエラー
	if (v->values == NULL)
	{
		return -1;
	}
	return 0;
}

void freeMemoryHyperVector(HyperVector *v)
{
	free(v->values);
}

// ------------------------------------------------- HDCアプリ, メモリアロケート, メモリフリー, 追加 ----------------------------------------------------

typedef struct
{
	HyperVector *data;
	int size;
} HDC;

int allocateMemoryHDC(HDC *v, int size)
{
	v->data = (HyperVector *)calloc(size, sizeof(HyperVector));
	// 確保できなかったらエラー
	if (v->data == NULL)
	{
		return -1;
	}
	for (int i = 0; i < size; i++)
	{
		allocateMemoryHyperVector(&v->data[i]);
	}
	v->size = size;
	return 0;
}

void freeMemoryHDC(HDC *v)
{
	for (int i = 0; i < v->size; i++)
	{
		freeMemoryHyperVector(&v->data[i]);
	}
	free(v->data);
	v->size = 0;
}

int append(HDC *v, HyperVector *newv)
{
	HDC tmp;
	allocateMemoryHDC(&tmp, v->size);

	// 一時的に格納
	for (int i = 0; i < v->size; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			tmp.data[i].values[j] = v->data[i].values[j];
		}
	}

	freeMemoryHDC(v);

	// 一個増やして再度確保
	v->size = tmp.size + 1;
	v->data = (HyperVector *)calloc(v->size, sizeof(HyperVector));
	// 確保できなかったらエラー
	if (v->data == NULL)
	{
		return -1;
	}

	for (int i = 0; i < v->size; i++)
	{
		allocateMemoryHyperVector(&v->data[i]);
	}

	for (int i = 0; i < v->size - 1; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			v->data[i].values[j] = tmp.data[i].values[j];
		}
	}
	for (int j = 0; j < LENGTH; j++)
	{

		v->data[v->size - 1].values[j] = newv->values[j];
	}

	freeMemoryHDC(&tmp);

	return 0;
}

void printb(HyperVector *v)
{
	const unsigned int mask = 1;
	for (int j = 0; j < LENGTH; j += 32)
	{
		unsigned int result = 0;
		unsigned int n = 31;
		unsigned int l = j;
		do
		{
			uint8_t tmp = v->values[l];
			uint8_t value = (mask & tmp ? 1 : 0);
			result += (value << n);
			l++;
		} while (n--);
		printf("%u\n", result);
	}
	printf("\n");
}

// --------------------------------------------------------- エンコード関数 ---------------------------------------------------------------

void encoding(HDC *HDCascii, const char *path, uint8_t *values)
{

	// ファイルオープン
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL)
	{
		perror("  Failed to open file");
		exit(1);
	}

	// 何文字?
	int ch;
	int num = 0;
	// while (((ch = fgetc(file)) != EOF)) // ubuntu:EOF == -1,  petalinux:EOF == 255
	// while (((ch = fgetc(file)) != EOF) && ((ch = fgetc(file) != -1))) // ubuntu:EOF == -1,  petalinux:EOF == 255
	while (((ch = fgetc(file)) != EOF) && ((ch = fgetc(file) != 255))) // ubuntu:EOF == -1,  petalinux:EOF == 255
	{
		num++;
	}
	fseek(file, 0, SEEK_SET);
	char *content = (char *)calloc(num, sizeof(char));
	size_t done = fread(content, sizeof(char), num, file);
	if (done < num)
	{
		perror("  Failed: fread file");
	}
	fclose(file);
	// debug
	// printf("%d\n", num);			  		// 27
	// printf("%s\n", content);		  		// myname...
	// printf("%lu\n", strlen(content)); 	// 27

	// ngramの数（パラメータから計算）
	int all_ngram = strlen(content) - NGRAM + 1;
	printf("all_ngram: %d\n", all_ngram);

	// 符号化後の値を入れるHDCアプリ作成
	HDC HDCtarget;
	allocateMemoryHDC(&HDCtarget, all_ngram);

	// 先頭から順番にN-gramハイパーベクトルを生成してHDCtargetに格納
	// 最外ループ
	for (int i = 0; i < all_ngram; i++)
	{
		// debug
		// printf("\n---------- %d/%d ----------\n", i, all_ngram);

		// 先頭からngram分のセットを作成
		// mynameis...
		// ↓
		// ascii_number_n = [109, 121, 110] // m, y, n
		int ascii_number_n[NGRAM];
		for (int j = 0; j < NGRAM; j++)
		{
			ascii_number_n[j] = (unsigned char)(content[i + j] - 97);
		}

		HyperVector result;
		allocateMemoryHyperVector(&result);
		// 毎ループresultを更新
		for (int j = 0; j < NGRAM; j++)
		{
			if (j == 0)
			{
				HyperVector ascii_vector;
				allocateMemoryHyperVector(&ascii_vector);
				for (int k = 0; k < LENGTH; k++)
				{
					// 欲しいasciiを取り出し
					ascii_vector.values[k] = HDCascii->data[ascii_number_n[j]].values[k];
				}
				// Rotate (右シフト)
				HyperVector tmp_vector;
				allocateMemoryHyperVector(&tmp_vector);
				int rotatenum = LENGTH - (NGRAM - 1) % LENGTH;
				int basenum = 0;
				for (int k = rotatenum; k < LENGTH; k++, basenum++)
				{
					tmp_vector.values[basenum] = ascii_vector.values[k];
				}
				for (int k = 0; k < rotatenum; k++, basenum++)
				{
					tmp_vector.values[basenum] = ascii_vector.values[k];
				}
				for (int k = 0; k < LENGTH; k++)
				{
					result.values[k] = tmp_vector.values[k];
				}
				freeMemoryHyperVector(&ascii_vector);
				freeMemoryHyperVector(&tmp_vector);
				continue;
			}

			HyperVector next_ascii_vector;
			allocateMemoryHyperVector(&next_ascii_vector);
			for (int k = 0; k < LENGTH; k++)
			{
				// 欲しいasciiを取り出し
				next_ascii_vector.values[k] = HDCascii->data[ascii_number_n[j]].values[k];
			}
			if (NGRAM - j - 1 != 0)
			{
				// Rotate (右シフト)
				HyperVector tmp_vector;
				allocateMemoryHyperVector(&tmp_vector);
				int rotatenum = (LENGTH - (NGRAM - 1) + j) % LENGTH;
				int basenum = 0;
				for (int k = rotatenum; k < LENGTH; k++, basenum++)
				{
					tmp_vector.values[basenum] = next_ascii_vector.values[k];
				}
				for (int k = 0; k < rotatenum; k++, basenum++)
				{
					tmp_vector.values[basenum] = next_ascii_vector.values[k];
				}
				for (int k = 0; k < LENGTH; k++)
				{
					next_ascii_vector.values[k] = tmp_vector.values[k];
				}
				freeMemoryHyperVector(&tmp_vector);
			}

			// Xor
			for (int k = 0; k < LENGTH; k++)
			{
				result.values[k] = result.values[k] ^ next_ascii_vector.values[k];
			}

			freeMemoryHyperVector(&next_ascii_vector);
		}

		// resultを格納
		for (int j = 0; j < LENGTH; j++)
		{
			HDCtarget.data[i].values[j] = result.values[j];
		}

		freeMemoryHyperVector(&result);
	}

	// 偶数だったら多数決できないので、ランダムな値(ハイパーベクトル)を追加
	if ((all_ngram % 2) == 0)
	{
		HyperVector tmp_vector;
		allocateMemoryHyperVector(&tmp_vector);
		// printf("%ld\n", sizeof(unsigned int)); // 4
		for (int j = 0; j < LENGTH; j++)
		{
			tmp_vector.values[j] = HDCascii->data[26].values[j];
		}
		append(&HDCtarget, &tmp_vector);
		all_ngram += 1; // 値を一個増やしたので更新
		freeMemoryHyperVector(&tmp_vector);
	}

	// ------------------------------------------ 最後の加算 -----------------------------------------

	HyperVector trained;
	allocateMemoryHyperVector(&trained);

	int thr = all_ngram / 2 + 1;
	for (int i = 0; i < LENGTH; i++)
	{
		// all_ngram個のi番目の要素を足し合わせる
		int sum = 0;
		for (int j = 0; j < all_ngram; j++)
		{
			sum += HDCtarget.data[j].values[i];
		}

		if (thr <= sum)
		{
			trained.values[i] = 1;
		}
		else
		{
			trained.values[i] = 0;
		}
	}

	for (int i = 0; i < LENGTH; i++)
	{
		values[i] = trained.values[i];
	}
	// printb(&trained);

	// 解放
	free(content);
	freeMemoryHDC(&HDCtarget);
	freeMemoryHyperVector(&trained);
}

void printbb(unsigned int v)
{
	unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
	do
		putchar(mask & v ? '1' : '0');
	while (mask >>= 1);
}

void putb(unsigned int v)
{
	printf("  0"), putchar('b'), printbb(v), putchar('\n');
}

// --------------------------------------------------------------- main program ----------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	HDC HDCascii;
	allocateMemoryHDC(&HDCascii, 27);

	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < LENGTH; j += 32)
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
			// putb(tmp);
			unsigned int mask = (int)1 << (sizeof(tmp) * 8 - 1);
			unsigned int l = j;
			do
			{
				uint8_t value = (mask & tmp ? 1 : 0);
				// printf("%u", value);
				HDCascii.data[i].values[l] = value;
				l++;
			} while (mask >>= 1);
			// printf("\n");
			// printf("\n");
		}
		// printf("%d\n", i);
		if (i == 0)
		{
			printb(&HDCascii.data[i]);
		}
		// printb(&HDCascii.data[i]);
	}
	// printf("\n");

	puts("\n  -------------------------------------- Encoding ---------------------------------------\n");

	HDC HDCtrained;
	allocateMemoryHDC(&HDCtrained, train_num);

	for (int i = 0; i < train_num; i++)
	{
		encoding(&HDCascii, train_path[i], HDCtrained.data[i].values);
		printb(&HDCtrained.data[i]);
	}

	freeMemoryHDC(&HDCascii);
	freeMemoryHDC(&HDCtrained);

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	return 0;
}
