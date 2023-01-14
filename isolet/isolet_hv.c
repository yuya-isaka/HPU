#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "hyper_vector.h"

// OpenMP
#ifdef OPENMP
#include <omp.h>
#endif

// Mac
#ifdef __MACH__
// Debug
#ifdef DEBUG
// lead error
__attribute__((destructor)) static void destructor()
{
	system("leaks -q mnist");
}
#endif
#endif

int main(void)
{
	double LOAD_TIME = 0.0;
	double COM_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	// 637個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = 637;
	hv_t **item_memory = hv_make_imem(RAND_NUM);

	// 0-9の結果
	hv_t **result = hv_make_array(10);

	for (int i = 0; i < 10; i++)
	{
		clock_t START_COMPUTE;
		char PATH[12];
		snprintf(PATH, 12, "label%d.txt", i);
		FILE *file;
		file = fopen(PATH, "r");
		char lines[3];

		int data_tmp_num = 0;
		int data_lines[150000];
		while (fgets(lines, 3, file) != NULL)
		{
			data_lines[data_tmp_num++] = atoi(lines);
		}
		fclose(file);
		clock_t END_COMPUTE;
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// printf("%d\n", data_tmp_num);
		// for (int j = 0; j < data_tmp_num; j++)
		// {
		// 	printf("%d\n", data_lines[j]);
		// }

		//////////////////////////////////////////////////////////////////////

		hv_init();

// OpenMP
#ifdef OPENMP
#pragma omp parallel for
#endif
		for (int j = 0; j < data_tmp_num; j++)
		{
			for (int k = 0; k < 617; k++)
			{
				hv_t *bind_result = hv_bind(item_memory[k], item_memory[data_lines[j] + 617]);
				j++;

				hv_bound(bind_result);
				hv_free(bind_result);
			}
			j--;
		}

		hv_t *result_tmp = hv_bound_result();
		hv_copy(result[i], result_tmp);
		hv_free(result_tmp);

		hv_finish();

		//////////////////////////////////////////////////////////////////////
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d:\n", i);
		hv_print(result[i]);
		printf("\n");
	}

	hv_free_array(result, 10);
	hv_free_array(item_memory, 637);

	printf("  load時間: %lf[ms]\n", LOAD_TIME);

	return 0;
}