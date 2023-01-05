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
	const int trial_num = 1000000;

	int EXP_NUM = 1000;

	for (int nnn = 0; nnn < EXP_NUM; nnn++)
	{
		hv_t **result = hv_make_array(trial_num);

		srand((unsigned int)time(NULL));
		int tmp1 = rand() % 512;
		int tmp2 = rand() % 512;

#ifdef OPENMP
#pragma omp parallel for
#endif
		for (int i = 0; i < trial_num; i++)
		{
			int addr1 = tmp1;
			int addr2 = tmp2;
			result[i] = hv_bind(item_memory[addr1], item_memory[addr2]);
		}

		hv_free_array(result, trial_num);
	}

	hv_free_array(item_memory, RANNUM);

	return 0;
}