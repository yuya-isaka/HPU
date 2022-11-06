#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// --------------------------------------- メモリリークチェック、デストラクター -----------------------------------------

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

// -------------------------------------------  パラメータ設定 ---------------------------------------------------

// n-gram
const int NGRAM = 3;

// 次元数
const int LENGTH = 1024;

// 学習対象の個数（英語、フランス語）
int train_num = 2;

// 訓練データ指定
// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"}; // 文字数少なめ
// const char *train_path[] = {"data/decorate/en2", "data/decorate/fr2"}; // 文字数少なめよりは多め
const char *train_path[] = {"data/decorate/en", "data/decorate/fr"}; // 文字数多め

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

// --------------------------------------------------------- エンコード関数 ---------------------------------------------------------------

void encoding(HDC *HDCascii, const char *path, uint8_t *values)
{
	clock_t startEncoding = clock();

	// ファイルオープン
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL)
	{
		perror("  Failed: open file");
		exit(1);
	}

	// 何文字?
	int ch;
	size_t num = 0;
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

	clock_t endEncoding = clock();
	double time_encoding = ((double)(endEncoding - startEncoding)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n    File read time: %lf[ms]\n", time_encoding);

	// ngramの数（パラメータから計算）
	int all_ngram = strlen(content) - NGRAM + 1;

	startEncoding = clock();

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
			ascii_number_n[j] = (unsigned char)(content[i + j]);
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

	endEncoding = clock();
	time_encoding = ((double)(endEncoding - startEncoding)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n    Encoding time: %lf[ms]\n", time_encoding);

	startEncoding = clock();

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

	endEncoding = clock();
	time_encoding = ((double)(endEncoding - startEncoding)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n    Append time: %lf[ms]\n", time_encoding);

	// ------------------------------------------ 最後の加算 -----------------------------------------

	startEncoding = clock();

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

	endEncoding = clock();
	time_encoding = ((double)(endEncoding - startEncoding)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n    Final add time: %lf[ms]\n", time_encoding);

	// 解放
	free(content);
	freeMemoryHDC(&HDCtarget);
	freeMemoryHyperVector(&trained);
}

// --------------------------------------------------------------- main program ----------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	clock_t start = clock();

	// HDCアプリ作成 (ascii)
	HDC HDCascii;
	allocateMemoryHDC(&HDCascii, 127);

	// 127文字生成
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

	// ----------------------------------------- Encoding ---------------------------------------------

	clock_t startEncoding = clock();

	// HDCアプリ作成 (学習後の訓練データを格納)
	HDC HDCtrained;
	allocateMemoryHDC(&HDCtrained, train_num);

	// train_num (英語とフランス語なら２)
	for (int i = 0; i < train_num; i++)
	{
		// HDCtrained.data[i].values の値を更新
		encoding(&HDCascii, train_path[i], HDCtrained.data[i].values);
	}

	clock_t endEncoding = clock();

	const double time_encoding_training = ((double)(endEncoding - startEncoding)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n  Encoding Training Data time: %lf[ms]\n\n", time_encoding_training);

	// ---

	startEncoding = clock();

	// HDCアプリ作成　（学習後のテストデータを格納)
	HDC HDCtested;
	allocateMemoryHDC(&HDCtested, test_num);

	// test_num (英語とフランス語なら２)
	for (int i = 0; i < test_num; i++)
	{
		// HDCtested.data[i].values の値を更新
		encoding(&HDCascii, test_path[i], HDCtested.data[i].values);
	}

	endEncoding = clock();

	const double time_encoding_test = ((double)(endEncoding - startEncoding)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n  Encoding Test Data time: %lf[ms]\n\n", time_encoding_test);

	printf("\n  All Encoding time: %lf[ms]\n\n\n", time_encoding_training + time_encoding_test);

	// ---------------------------------------- 類似度チェック （推論） ---------------------------------------

	clock_t startSimilarity = clock();
	// （cosine類似度チェック）
	// distance = A・B/|A||B|
	// |A| ... Aのnorm
	const char *test_lang[] = {"English", "French"};
	puts("  期待");
	for (int i = 0; i < test_num; i++)
	{
		printf("  test %d → %s\n", i, test_lang[i]);
	}
	puts("");

	puts("  結果");
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

			// norm for train
			int train_sum = 0;
			for (int k = 0; k < LENGTH; k++)
			{
				train_sum += HDCtrained.data[j].values[k];
			}
			double train_norm = (double)sqrt((double)train_sum);

			// norm for test
			int test_sum = 0;
			for (int k = 0; k < LENGTH; k++)
			{
				test_sum += HDCtested.data[i].values[k];
			}
			double test_norm = (double)sqrt((double)test_sum);

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
			puts("  could not find match language");
		}
		else
		{
			printf("  test %d → %s\n", i, train_lang[match]);
		}
	}

	clock_t endSimilarity = clock();

	const double time_similarity = ((double)(endSimilarity - startSimilarity)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n  Similarity time: %lf[ms]\n\n", time_similarity);

	freeMemoryHDC(&HDCascii);
	freeMemoryHDC(&HDCtrained);
	freeMemoryHDC(&HDCtested);

	clock_t end = clock();

	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n\n  time %lf[ms]\n", time);

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	return 0;
}
