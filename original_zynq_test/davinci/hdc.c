#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// メモリりーくチェック、デストラクター
__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

// パラメータ設定

// n-gram
const int NGRAM = 3;
// 次元数
const int LENGTH = 1000;

// ---------------------------------------------------------------

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

// ---------------------------------------------------------------

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

// ---------------------------------------------------------------

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

void encoding(HDC *HDCascii, const char *path, uint8_t *values)
{

	// ファイルオープン
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL)
	{
		perror("Failed to open file");
		exit(1);
	}

	// 何文字か確認
	int ch;
	int num = 0;
	while (((ch = fgetc(file)) != EOF) && ((ch = fgetc(file) != 255))) // ubuntu:EOF == -1,  petalinux:EOF == 255
	{
		num++;
	}
	// printf("%d\n", ch);
	fseek(file, 0, SEEK_SET);
	char *content = (char *)calloc(num, sizeof(char));
	fread(content, sizeof(char), num, file);
	fclose(file);
	// debug
	// printf("%d\n", num);			  // 27
	// printf("%s\n", content);		  // myname...
	// printf("%lu\n", strlen(content)); // 27

	int all_ngram = strlen(content) - NGRAM + 1;
	// printf("%d\n", all_ngram); // 25

	HDC HDCtarget;
	allocateMemoryHDC(&HDCtarget, all_ngram);

	// 先頭から順番にN-gramハイパーベクトルの生成してHDCtargetに格納
	for (int i = 0; i < all_ngram; i++)
	{
		printf("\n---------- %d/%d ----------\n", i, all_ngram);
		// 先頭からngram分のセットを作成
		// mynameis...
		// ↓
		// ascii_number_n = [109, 121, 110] // m, y, n
		int ascii_number_n[NGRAM];
		for (int j = 0; j < NGRAM; j++)
		{
			ascii_number_n[j] = (unsigned char)(content[i + j]);
		}
		// debug
		// for (int j = 0; j < NGRAM; j++)
		// {
		// 	printf("%c:%d, ", content[i + j], ascii_number_n[j]);
		// }
		// printf("\n----------------------------- \n");

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
				int rotatenum = LENGTH - (NGRAM - 1) % LENGTH;
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
		// debug
		// puts("変換前");
		// for (int j = 0; j < LENGTH; j++)
		// {
		// 	printf("%d", HDCascii.data[ascii_number_n[0]].values[j]);
		// }
		// puts("\n変換後");
		// for (int j = 0; j < LENGTH; j++)
		// {
		// 	printf("%d", result.values[j]);
		// }
		// break;

		// resultを格納
		for (int j = 0; j < LENGTH; j++)
		{
			HDCtarget.data[i].values[j] = result.values[j];
		}

		freeMemoryHyperVector(&result);
	}

	// HDCtargetをチェック
	// debug
	// for (int i = 0; i < all_ngram; i++)
	// {
	// 	printf("%2d: ", i);
	// 	for (int j = 0; j < LENGTH; j++)
	// 	{
	// 		printf("%d", HDCtarget.data[i].values[j]);
	// 	}
	// 	puts("");
	// }

	// 偶数だったら多数決できないので、ランダムな値(ハイパーベクトル)を追加
	if ((all_ngram % 2) == 0)
	{
		HyperVector tmp_vector;
		allocateMemoryHyperVector(&tmp_vector);
		srand(128);
		for (int j = 0; j < LENGTH; j++)
		{
			uint8_t value = rand() % 2;
			tmp_vector.values[j] = value;
		}
		append(&HDCtarget, &tmp_vector);
		all_ngram += 1; // 値を一個増やしたので更新
		freeMemoryHyperVector(&tmp_vector);
	}

	// HDCtargetをチェック
	// debug
	// for (int i = 0; i < all_ngram; i++)
	// {
	// 	printf("%2d: ", i);
	// 	for (int j = 0; j < LENGTH; j++)
	// 	{
	// 		printf("%d", HDCtarget.data[i].values[j]);
	// 	}
	// 	puts("");
	// }

	// 最後の加算
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

		// debug
		// printf("%d ", sum);

		if (thr <= sum)
		{
			trained.values[i] = 1;
		}
		else
		{
			trained.values[i] = 0;
		}
	}

	// HDCtrainedをチェック
	// debug
	// puts("");
	// for (int j = 0; j < LENGTH; j++)
	// {
	// 	printf("%d", trained.values[j]);
	// }
	// puts("");

	for (int i = 0; i < LENGTH; i++)
	{
		values[i] = trained.values[i];
	}

	// 解放
	free(content);
	freeMemoryHDC(&HDCtarget);
	freeMemoryHyperVector(&trained);
}

// ---------------------------------------------------------------

int main(int argc, char const *argv[])
{
	puts("\n---------- HDC Program start ----------\n");

	HDC HDCascii;
	allocateMemoryHDC(&HDCascii, 127);

	for (int i = 0; i < 127; i++)
	{
		// Random生成
		srand(i);
		for (int j = 0; j < LENGTH; j++)
		{
			uint8_t value = rand() % 2;
			HDCascii.data[i].values[j] = value;
		}
	}

	// Debug
	// for (int i = 0; i < HDCascii.size; i++)
	// {
	// 	printf("%d: ", i);
	// 	for (int j = 0; j < LENGTH; j++)
	// 	{
	// 		printf("%d", HDCascii.data[i].values[j]);
	// 	}
	// 	printf("\n");
	// }

	// appendテスト
	// HyperVector newv;
	// allocateMemoryHyperVector(&newv);
	// srand(128);
	// for (int j = 0; j < LENGTH; j++)
	// {
	// 	uint8_t value = rand() % 2;
	// 	newv.values[j] = value;
	// }
	// append(&HDCascii, &newv);
	// freeMemoryHyperVector(&newv);

	// ↓ appendをしたことでデバッグ結果が変わってる。成功。

	// Debug
	// for (int i = 0; i < HDCascii.size; i++)
	// {
	// 	printf("%d: ", i);
	// 	for (int j = 0; j < LENGTH; j++)
	// 	{
	// 		printf("%d", HDCascii.data[i].values[j]);
	// 	}
	// 	printf("\n");
	// }

	// パラメータ設定 ---------------------------------------------------------------------------------------

	// 学習対象の個数（英語、フランス語）
	int train_num = 2;

	// 訓練データ指定
	// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"}; // 文字数少なめ
	// const char *train_path[] = {"data/decorate/en", "data/decorate/fr"}; // 文字数多め
	const char *train_path[] = {"data/decorate/en2", "data/decorate/fr2"}; // 文字数多め

	// テストの個数（英語、フランス語）
	int test_num = 2;

	// テストデータ指定
	const char *test_path[] = {"data/decorate/t1", "data/decorate/t2"};

	// ---------------------------------------------------------------------------------------------------

	// 学習後のデータを格納
	HDC HDCtrained;
	allocateMemoryHDC(&HDCtrained, train_num);

	for (int i = 0; i < train_num; i++)
	{
		// HDCtrained.data[i].values の値を更新
		encoding(&HDCascii, train_path[i], HDCtrained.data[i].values);
	}

	// debug
	// puts("trained");
	// for (int i = 0; i < train_num; i++)
	// {
	// 	printf("%d: ", i);
	// 	for (int j = 0; j < LENGTH; j++)
	// 	{
	// 		printf("%d", HDCtrained.data[i].values[j]);
	// 	}
	// 	puts("");
	// }

	// 学習後のデータを格納
	HDC HDCtested;
	allocateMemoryHDC(&HDCtested, test_num);

	for (int i = 0; i < test_num; i++)
	{
		// HDCtested.data[i].values の値を更新
		encoding(&HDCascii, test_path[i], HDCtested.data[i].values);
	}

	// debug
	// puts("tested");
	// for (int i = 0; i < test_num; i++)
	// {
	// 	printf("%d: ", i);
	// 	for (int j = 0; j < LENGTH; j++)
	// 	{
	// 		printf("%d", HDCtested.data[i].values[j]);
	// 	}
	// 	puts("");
	// }

	// 類似度チェック （推論）
	// （cosine類似度チェック）
	// distance = A・B/|A||B|
	// |A| ... Aのnorm
	const char *test_lang[] = {"English", "French"};
	puts("期待");
	for (int i = 0; i < test_num; i++)
	{
		printf("test %d → %s\n", i, test_lang[i]);
	}
	puts("");

	puts("結果");
	const char *train_lang[] = {"English", "French"};
	for (int i = 0; i < test_num; i++)
	{
		int match = -1; // 最終的にマッチした番号が入る
		double max_cosine = -2.0;
		for (int j = 0; j < train_num; j++)
		{

			// 内積
			int dot_result = 0;
			for (int k = 0; k < LENGTH; k++)
			{
				dot_result += HDCtested.data[i].values[k] & HDCtrained.data[j].values[k];
			}
			// debug
			// printf("%d\n", dot_result);

			// norm for test
			int test_sum = 0;
			for (int k = 0; k < LENGTH; k++)
			{
				test_sum += HDCtested.data[i].values[k];
			}
			double test_norm = (double)sqrt((double)test_sum);

			// norm for train
			int train_sum = 0;
			for (int k = 0; k < LENGTH; k++)
			{
				train_sum += HDCtrained.data[j].values[k];
			}
			double train_norm = (double)sqrt((double)train_sum);

			// cosineチェック
			double cosine = (double)dot_result / (test_norm * train_norm);
			if (cosine > max_cosine)
			{
				max_cosine = cosine;
				match = j; // 更新
			}
		}
		if (match == -1)
		{
			puts("could not find match language");
		}
		else
		{
			printf("test %d → %s\n", i, train_lang[match]);
		}
	}

	freeMemoryHDC(&HDCascii);
	freeMemoryHDC(&HDCtrained);
	freeMemoryHDC(&HDCtested);

	puts("\n---------- HDC Program end ----------\n");

	return 0;
}
