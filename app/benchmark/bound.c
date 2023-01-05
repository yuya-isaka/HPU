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
	const int TRIAL_NUM = 1000000;

	double RAN_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	srand(10);

	hv_init();

	for (int nnn = 0; nnn < 10; nnn++)
	{
		/////////////////////////////////////////////////////////////////////////////
		START_COMPUTE = clock();
		int rand_array[TRIAL_NUM];
		for (int i = 0; i < TRIAL_NUM; i++)
		{
			rand_array[i] = rand() % RANNUM;
		}
		int rand_array_num = 0;
		END_COMPUTE = clock();
		RAN_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;
		/////////////////////////////////////////////////////////////////////////////

#ifdef OPENMP
#pragma omp parallel for
#endif
		for (int i = 0; i < TRIAL_NUM; i++)
		{
			int addr = rand_array[rand_array_num++];
			hv_bound(item_memory[addr]);
		}

		hv_t *result = hv_bound_result();
		// hv_print(result);
		hv_free(result);
	}

	hv_finish();

	hv_free_array(item_memory, RANNUM);

	printf("\n  ランダム生成時間: %lf[s]\n", RAN_TIME);

	return 0;
}