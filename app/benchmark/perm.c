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

// 試行回数
// 100万回
#define TRIAL_NUM 1000000

int main(int argc, char const *argv[])
{
	const int RANNUM = 512;
	hv_t **item_memory = hv_make_imem(RANNUM);

	double RAN_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	srand(10);

	/////////////////////////////////////////////////////////////////////////////
	START_COMPUTE = clock();
	int *rand_array = (int *)calloc(TRIAL_NUM, sizeof(int));
	int *perm_array = (int *)calloc(TRIAL_NUM, sizeof(int));
	for (int i = 0; i < TRIAL_NUM; i++)
	{
		rand_array[i] = rand() % RANNUM;
		perm_array[i] = rand() % 1024;
	}
	int rand_array_num = 0;
	int perm_array_num = 0;
	END_COMPUTE = clock();
	RAN_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;
	/////////////////////////////////////////////////////////////////////////////

	hv_t **result = hv_make_array(TRIAL_NUM);

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < TRIAL_NUM; i++)
	{
		int addr = rand_array[rand_array_num++];
		int perm_num = perm_array[perm_array_num++];
		result[i] = hv_perm(item_memory[addr], perm_num);
	}

	hv_free_array(result, TRIAL_NUM);
	hv_free_array(item_memory, RANNUM);

	printf("\n  ランダム生成時間: %lf[s]\n", RAN_TIME);
	return 0;
}