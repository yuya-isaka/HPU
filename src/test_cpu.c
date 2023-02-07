// include
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hyper_vector.h"

const int RANNUM = 512;
// const int RANNUM = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check()
{
	// HV初期化
	hv_init();

	// アイテムメモリ準備
	hv_t **item_memory = hv_make_imem(RANNUM);

	for (int i = 0; i < 5; i++)
	{
		// Bounding
		hv_bound(item_memory[i]);
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

	check();

	printf("\n ------------------------------- 終了 ------------------------------- \n");
	return 0;
}