// include
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hyper_vector.h"

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

// N-gram専用check関数
// 簡易アセンブラを使って、直接アセンブラを記述 (関数使ったやつに書き直す)
//    NGRAM   = 1 ~
//    ADDRNUM = NGRAMの倍数 (shifter_newを使ったテストをしているから。また、LASTが０のままになりtb.cppでは止まる。test.cppでは動くけどNGRAMの倍数以外は同じ値が出る)
void check(const int NGRAM, const int ADDRNUM, const int MAJORITY_ADDR)
{

	hv_init();

	hv_t **item_memory = hv_make_imem(512);

	const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

	for (int i = 0; i < ADDRNUM; i += 3)
	{
		hv_t *bound_tmp = hv_make();
		for (int j = 0; j < NGRAM; j++)
		{
			hv_t *perm_result = hv_perm(item_memory[i + j], j);
			hv_t *bind_result = hv_bind(bound_tmp, perm_result);
			hv_copy(bound_tmp, bind_result);

			hv_free(bind_result);
			hv_free(perm_result);
		}

		hv_bound(bound_tmp);

		hv_free(bound_tmp);
	}

	if (EVEN)
	{
		hv_bound(item_memory[MAJORITY_ADDR]);
	}
	hv_t *result = hv_bound_result();

	hv_print(result);

	hv_free(result);
	hv_finish();

	return;
}

// hv_init
// hv_make_imem

// hv_make
// hv_free
// hv_print

// hv_perm
// hv_bind
// hv_bound
// hv_bound_result

// hv_finish

// ----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	printf("\n ------------------------------- 開始 ------------------------------- \n\n\n");

	const int NGRAM = 3;
	const int MAJORITY_ADDR = 511;
	int ADDRNUM = 0;

	// const int SIMULATION_COUNT = 100;
	// for (int i = 30; i < SIMULATION_COUNT; i += 30)
	// {
	// 	ADDRNUM = i;

	// 	check(NGRAM, ADDRNUM, MAJORITY_ADDR);
	// 	xor128(1);

	// 	printf(" -------------------\n\n");
	// }

	// const int SIMULATION_COUNT = 500;
	// for (int i = 120; i < SIMULATION_COUNT; i += 120)
	// {
	// 	ADDRNUM = i;

	// 	check(NGRAM, ADDRNUM, MAJORITY_ADDR);
	// 	xor128(1);

	// 	printf(" -------------------\n\n");
	// }

	ADDRNUM = 420;
	check(NGRAM, ADDRNUM, MAJORITY_ADDR);
	// printf(" --------\n\n");
	// ADDRNUM = 54;
	// check(NGRAM, ADDRNUM, MAJORITY_ADDR);
	// xor128(1);

	printf("\n ------------------------------- 終了 ------------------------------- \n");
	return 0;
}
