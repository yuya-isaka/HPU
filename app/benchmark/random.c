

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "hyper_vector.h"

int main(int argc, char const *argv[])
{
	clock_t start, end;
	start = clock();

	hv_t **item_memory = hv_make_imem(512);

	hv_free_array(item_memory, 512);

	end = clock();
	double TIME = (double)(end - start) / CLOCKS_PER_SEC;
#ifdef OPENMP
	TIME = TIME / omp_get_max_threads();
#endif
	printf("  %.5lf秒\n", TIME);

	return 0;
}
