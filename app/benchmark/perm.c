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
	// const int trial_num = 50000000;
	// const int trial_num = 10000000;
	const int trial_num = 5000000;

	hv_t **result = hv_make_array(trial_num);

	int tmp1 = atoi(argv[1]);
	int tmp2 = atoi(argv[2]);

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < trial_num; i++)
	{
		int addr = tmp1;
		int perm_num = tmp2;
		result[i] = hv_perm(item_memory[addr], perm_num);
	}

	hv_free_array(item_memory, RANNUM);
	hv_free_array(result, trial_num);

	return 0;
}