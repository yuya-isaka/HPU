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

	clock_t START_COMPUTE = clock();
	srand((unsigned int)time(NULL));
	int rand_array[TRIAL_NUM * 2];
	for (int i = 0; i < TRIAL_NUM; i++)
	{
		rand_array[i] = rand() % RANNUM;
	}
	int rand_array_num = 0;
	clock_t END_COMPUTE = clock();
	double TIME = ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;
	// printf("\n  ランダム生成時間: %lf[ms]\n", TIME);

	hv_t **result = hv_make_array(TRIAL_NUM);

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < TRIAL_NUM; i++)
	{
		int addr1 = rand_array[rand_array_num++];
		int addr2 = rand_array[rand_array_num++];
		result[i] = hv_bind(item_memory[addr1], item_memory[addr2]);
	}

	hv_free_array(result, TRIAL_NUM);

	hv_free_array(item_memory, RANNUM);

	return 0;
}