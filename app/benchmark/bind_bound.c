#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "hyper_vector.h"

#ifdef OPENMP
#include <omp.h>
#endif

int main(int argc, char const *argv[])
{
	hv_init();

	// seed設定
	srand(10);

	hv_t **item_memory = hv_make_imem(1024);

	// 試行回数
	const int trial_num = 50000000;
	// const int trial_num = 10000000;

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < trial_num; i++)
	{
		int addr1 = rand() % 1024;
		int addr2 = rand() % 1024;
		hv_bound(hv_bind(item_memory[addr1], item_memory[addr2]));
	}

	// Bound結果出力
	hv_t *result = hv_bound_result();

	// 結果出力
	hv_print(result);

	// Free
	hv_free(result);
	hv_free_array(item_memory, 1024);

	// 終了
	hv_finish();

	return 0;
}