#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "hyper_vector.h"

#ifdef OPENMP
#include <omp.h>
#endif

int main(int argc, char const *argv[])
{
	const int RANNUM = 512;
	hv_t **item_memory = hv_make_imem(RANNUM);

	// 試行回数
	// 100万回
	const int trial_num = 1000000;

	// 実験回数
	int EXP_NUM = 1000;
	for (int nnn = 0; nnn < EXP_NUM; nnn++)
	{
		srand((unsigned int)time(NULL));
		int tmp1 = rand() % RANNUM;
		int tmp2 = rand() % 1024;

		hv_init();

#ifdef OPENMP
#pragma omp parallel for
#endif
		for (int i = 0; i < trial_num; i++)
		{
			int addr = tmp1;
			int perm_num = tmp2;
			hv_bound(hv_perm(item_memory[addr], perm_num));
		}
		hv_t *result = hv_bound_result();
		// hv_print(result);
		hv_free(result);

		hv_finish();
	}

	hv_free_array(item_memory, RANNUM);

	return 0;
}