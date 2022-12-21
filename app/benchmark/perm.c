
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
	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	clock_t start, end;
	start = clock();

	// seed設定
	srand(10);

	hv_init();

	hv_t **item_memory = hv_make_imem(512);

	// 試行回数
	const int trial_num = 50000000;
	// const int trial_num = 10000000;

	hv_t **result = hv_make_array(trial_num);

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < trial_num; i++)
	{
		int addr = rand() % 512;
		int perm_num = rand() % 1024;
		result[i] = hv_perm(item_memory[addr], perm_num);
	}

	hv_free_array(item_memory, 512);
	hv_free_array(result, trial_num);
	hv_finish();

	end = clock();
	double TIME = (double)(end - start) / CLOCKS_PER_SEC;
#ifdef OPENMP
	TIME = TIME / omp_get_max_threads();
#endif
	printf("  %.3lf秒\n", TIME);

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	return 0;
}
