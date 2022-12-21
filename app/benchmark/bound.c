
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
	clock_t start, end;
	start = clock();

	hv_init();

	// seed設定
	srand(10);

	hv_t **item_memory = hv_make_imem(512);

	// 試行回数
	const int trial_num = 50000000;
	// const int trial_num = 10000000;

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < trial_num; i++)
	{
		int addr = rand() % 512;
		hv_bound(item_memory[addr]);
	}

	hv_t *result = hv_bound_result();

	hv_print(result);

	hv_free(result);
	hv_free_array(item_memory, 512);
	hv_finish();

	end = clock();
	double TIME = (double)(end - start) / CLOCKS_PER_SEC;
#ifdef OPENMP
	TIME = TIME / omp_get_max_threads();
#endif
	printf("  %.5lf秒\n", TIME);

	return 0;
}
