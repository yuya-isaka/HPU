// include
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 次元数可変
const int DIM = 32 / 32;
// const int DIM = 1024 / 32;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 変わらん
// 追加されるランダムな値はRANNUM-1番目
const int RANNUM = 512;
unsigned int item_memory_array[DIM][RANNUM];
unsigned int item_memory_array_new[DIM][RANNUM];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 渡された32ビットのvを、バイナリでコマンドライン出力
void printb(unsigned int v)
{
	unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
	do
		putchar(mask & v ? '1' : '0');
	while (mask >>= 1);
}

// printbを使いつつ整形して、バイナリをコマンドライン出力
void putb(unsigned int v)
{
	printf("  0"), putchar('b'), printb(v), putchar('\n');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 2個の値を返す
// 1. 右にnum回シフトしたやつを返す
// 2. 第一引数にm右にシフトしたやつを取り出して、左に(32-num)回論理左シフトしたやつを格納し更新
unsigned int shifter_32(unsigned int *v, unsigned int num)
{
	// num回 論理右シフト
	unsigned int tmp_v = *v >> num;

	// 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
	unsigned int tmp_num = (1 << num) - 1;
	*v = (*v & tmp_num) << (32 - num);

	return tmp_v;
}

// N-gram用のシフト関数
void shifter_ngram(const int NGRAM)
{
	int num = 0;
	for (int i = 0; i < RANNUM; i++)
	{
		unsigned int result_tmp[DIM] = {0};
		for (int j = 0; j < DIM; j++)
		{
			unsigned int tmp = item_memory_array[j][i];
			// はみ出たやつを論理左シフトしたやつ (tmp)
			// 右論理シフトしたやつ (tmp_v)
			unsigned int tmp_v = shifter_32(&tmp, num);
			// 右にシフトしたやつを0, 1, 2 ... と順番に格納
			// つまり、右から昇順の配列があったら、右から左に向かって順番に更新していく
			result_tmp[j] |= tmp_v;
			// 最初だけ、最後のセクタにtmpを格納
			if (j == 0)
			{
				result_tmp[DIM - 1] |= tmp;
			}
			// 最初以外は一個前（右隣）のセクタに、tmpを格納
			else
			{
				result_tmp[j - 1] |= tmp;
			}
		}

		// 新しく作った32個の配列を、更新
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 多数決関数　&& 加算
unsigned int bounding(unsigned int result_array[], size_t size)
{
	unsigned int result = 0;

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// xorshiftのランダム生成関数（32bitごとに出力）
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

	// リセット信号
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

// N-gram専用check関数
// 簡易アセンブラを使って、直接アセンブラを記述 (関数使ったやつに書き直す)
//    NGRAM   = 1 ~
//    ADDRNUM = NGRAMの倍数 (shifter_newを使ったテストをしているから。また、LASTが０のままになりtb.cppでは止まる。test.cppでは動くけどNGRAMの倍数以外は同じ値が出る)
void check(const int NGRAM, const int ADDRNUM, const int MAJORITY_ADDR)
{

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ADDRNUM(計算する個数)が偶数か否かを設定(後で変えるかも)
	const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

	// 実際に計算する回数
	int ARNUM = ADDRNUM / NGRAM;
	if (EVEN)
	{
		ARNUM++;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 0 ~ RANNUM分のハイパーベクトルをランダム生成
	// 次元数が1024の場合は、その次元は最初の0-32のランダム生成された整数を使う
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

	// simple_en, simple_fr ... aaa のテスト　（hdc.c と　 hdc_pl.cのどっちが正しいかわからなくなった時に使用したテスト、一応残す）
	// 具体的には、aaaの文字をテストするようで、i==0の時にもう一度最初からランダム生成することで、RANNUMの数分のaを用意した。
	// for (int j = 0; j < RANNUM; j++)
	// {
	// 	for (int i = 0; i < DIM; i++)
	// 	{
	// 		if (i == 0)
	// 		{
	// 			item_memory_array[i][j] = 88675123;
	// 			continue;
	// 		}
	// 		item_memory_array[i][j] = xor128(0);
	// 	}
	// 	xor128(1);
	// }

	// あらかじめPermutation
	// item_memoryに格納されている順番に、行ごとにPermutationを実行する
	// item_memoryは[32][1024]で格納されており、縦の32の右シフトの演算を実現してくれている
	// ただ、Nーgramに特化しており、NGRAMで指定された数分を順番にシフトする形式にしてある。なので、どこを何ビットシフトするかちゃんと指定する形にするには別の関数が必要。
	shifter_ngram(NGRAM);

	// 1024 / 32bit なら 32回実行
	// 縦は同じハイパーベクトル. 横同士を計算させる
	// 横をNGRAMの数分xorして、加算していく
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
		// 計算したい数が偶数の時１つ足し合わせる
		if (EVEN)
		{
			// RANNUM-1を追加するランダム値に使う
			result_array[num] = item_memory_array[j][MAJORITY_ADDR];
			// printf("ランダム：%u\n", result_array[num]);
			// putb(result_array[num]);
		}
		unsigned int result_real = bounding(result_array, ARNUM);
		printf("  %u\n", result_real);
		// putb(result_real);

		free(result_array);
	}

	return;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	printf("\n ------------------------------- 開始 ------------------------------- \n\n\n");

	const int NGRAM = 3;
	const int MAJORITY_ADDR = 511;
	int ADDRNUM = 0;

	// const int SIMULATION_COUNT = 100;
	// for (int i = 3; i < SIMULATION_COUNT; i += 3)
	// {
	// 	ADDRNUM = i;

	// 	check(NGRAM, ADDRNUM, MAJORITY_ADDR);
	// 	xor128(1);

	// 	printf(" -------------------\n\n");
	// }

	ADDRNUM = 240;
	check(NGRAM, ADDRNUM, MAJORITY_ADDR);
	// xor128(1);
	// printf(" --------\n\n");
	// ADDRNUM = 54;
	// check(NGRAM, ADDRNUM, MAJORITY_ADDR);
	// xor128(1);

	printf("\n ------------------------------- 終了 ------------------------------- \n");
	return 0;
}
