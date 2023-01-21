// include
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hyper_vector.h"

const int RANNUM = 512;
// const int RANNUM = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    NGRAM   = 1 ~
//    ADDRNUM = NGRAMの倍数 (shifter_newを使ったテストをしているから。また、LASTが０のままになりtb.cppでは止まる。test.cppでは動くけどNGRAMの倍数以外は同じ値が出る)
//    MAJORITY_ADDR = 偶数処理
void check(const int NGRAM, const int ADDRNUM, const int MAJORITY_ADDR)
{
	// HV初期化
	hv_init();

	// アイテムメモリ準備
	hv_t **item_memory = hv_make_imem(RANNUM);

	// 偶数処理
	const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

	for (int i = 0; i < ADDRNUM; i += 3)
	{
		// 格納場所
		hv_t *bound_tmp = hv_make();

		for (int j = 0; j < NGRAM; j++)
		{
			// Permutation
			hv_t *perm_result = hv_perm(item_memory[i + j], j);

			// Binding
			hv_t *bind_result = hv_bind(bound_tmp, perm_result);

			// Copy
			hv_copy(bound_tmp, bind_result);

			// Free
			hv_free(bind_result);
			hv_free(perm_result);
		}

		// Bounding
		hv_bound(bound_tmp);

		// Free
		hv_free(bound_tmp);
	}

	// 偶数処理
	if (EVEN)
	{
		hv_bound(item_memory[MAJORITY_ADDR]);
	}

	// Bounding結果取り出し
	hv_t *result = hv_bound_result();

	// 結果出力
	hv_print(result);

	// Free
	hv_free(result);

	// 終了処理
	hv_finish();

	return;
}

int main(int argc, char **argv)
{
	printf("\n ------------------------------- 開始 ------------------------------- \n\n\n");

	// NGRAM
	const int NGRAM = 3;

	// 偶数処理
	const int MAJORITY_ADDR = RANNUM - 1;

	int ADDRNUM = 0;

	// テスト
	// const int SIMULATION_COUNT = 100;
	// for (int i = 30; i < SIMULATION_COUNT; i += 30)
	// {
	// 	ADDRNUM = i;
	// 	check(NGRAM, ADDRNUM, MAJORITY_ADDR);
	// 	xor128(1);
	// }

	// 単体テスト1
	ADDRNUM = 300;
	check(NGRAM, ADDRNUM, MAJORITY_ADDR);

	// 単体テスト2
	ADDRNUM = 90;
	check(NGRAM, ADDRNUM, MAJORITY_ADDR);

	printf("\n ------------------------------- 終了 ------------------------------- \n");
	return 0;
}