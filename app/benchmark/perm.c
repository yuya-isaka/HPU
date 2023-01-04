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
	// seed設定
	srand(10);
	const int RANNUM = 512;

	hv_t **item_memory = hv_make_imem(RANNUM);

	// 試行回数
	const int trial_num = 50000000;
	// const int trial_num = 10000000;

	hv_t **result = hv_make_array(trial_num);

	clock_t START_COMPUTE = clock(); //////////////////////

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < trial_num; i++)
	{
		int addr = atoi(argv[1]);
		int perm_num = atoi(argv[2]);
		result[i] = hv_perm(item_memory[addr], perm_num);
	}

	clock_t END_COMPUTE = clock(); ///////////////////////
	double TIME = ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n  計算時間: %lf[ms]\n", TIME);

	hv_free_array(item_memory, RANNUM);
	hv_free_array(result, trial_num);

	return 0;
}