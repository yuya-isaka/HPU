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
	const int RANNUM = 512;

	hv_t **item_memory = hv_make_imem(RANNUM);

	// 試行回数
	const int trial_num = 50000000;
	// const int trial_num = 10000000;

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < trial_num; i++)
	{
		int addr = atoi(argv[1]);
		int perm_num = atoi(argv[2]);
		hv_bound(hv_perm(item_memory[addr], perm_num));
	}
	hv_t *result = hv_bound_result();

	// hv_print(result);

	hv_free(result);

	hv_free_array(item_memory, RANNUM);
	hv_finish();

	return 0;
}