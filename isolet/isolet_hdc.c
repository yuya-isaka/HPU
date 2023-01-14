#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <fcntl.h>	  // open
#include <unistd.h>	  // read
#include <sys/mman.h> // mmap
#include <time.h>
#include "hdc_processor.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	double LOAD_TIME = 0.0;
	double COM_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 784個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = 637;
	const uint32_t FIRST_RAND_NUM = 500;
	const uint32_t SECOND_RAND_NUM = RAND_NUM - FIRST_RAND_NUM;

	// コア数
	const int CORENUM = 14;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hdc_setup();

	for (int ll = 0; ll < 10; ll++)
	{
		// 490
		hdc_make_imem(FIRST_RAND_NUM);
		hdc_init(0);
		hdc_start();

		START_COMPUTE;
		char PATH[12];
		snprintf(PATH, 12, "label%d.txt", ll);
		FILE *file;
		file = fopen(PATH, "r");
		char Lines[3];
		// ↓
		int data_tmp_num = 0;
		int data_lines[150000];
		while (fgets(Lines, 3, file) != NULL)
		{
			data_lines[data_tmp_num++] = atoi(Lines);
		}
		fclose(file);
		END_COMPUTE;
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		for (int dd = 0; dd < data_tmp_num;)
		{
			int index_tmp = 0;

			for (int j = 0; j < 7; j++)
			{
				uint16_t core_num = CORENUM;
				uint16_t addr_array[THREADS_NUM][core_num];

				// 70
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = index_tmp++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// move --------------------------------------------
				hdc_simd_move_thread();
				// ------------------------------------------------------

				// 70
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = data_lines[dd++] + 490;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// bind ----------------------------------------------
				hdc_simd_xor_thread();
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_simd_store_thread();
				// ------------------------------------------------------
			}
			dd += 127;
		}

		hdc_last();
		START_COMPUTE = clock();
		hdc_compute();
		END_COMPUTE = clock();
		COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// 137
		hdc_make_imem_2(SECOND_RAND_NUM);
		hdc_init(0);
		for (int dd = 0; dd < data_tmp_num;)
		{
			dd += 490;
			int index_tmp = 0;

			uint16_t core_num = CORENUM;
			uint16_t addr_array[THREADS_NUM][core_num];

			// 70
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = index_tmp++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// move --------------------------------------------
			hdc_simd_move_thread();
			// ------------------------------------------------------

			// 70
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = data_lines[dd++] + 127;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// bind ----------------------------------------------
			hdc_simd_xor_thread();
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_simd_store_thread();
			// ------------------------------------------------------

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 残り
			core_num = CORENUM;
			uint16_t thread_num = 4;

			for (int k = 0; k < thread_num; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = index_tmp++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(thread_num, core_num, addr_array);
			// ------------------------------------------------------

			// move --------------------------------------------
			hdc_move_thread(thread_num, core_num);
			// ------------------------------------------------------

			// 70
			for (int k = 0; k < thread_num; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = data_lines[dd++] + 127;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(thread_num, core_num, addr_array);
			// ------------------------------------------------------

			// bind ----------------------------------------------
			hdc_xor_thread(thread_num, core_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_store_thread(thread_num, core_num);
			// ------------------------------------------------------

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 残り
			core_num = 1;
			thread_num = 1;

			for (int k = 0; k < thread_num; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = index_tmp++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(thread_num, core_num, addr_array);
			// ------------------------------------------------------

			// move --------------------------------------------
			hdc_move_thread(thread_num, core_num);
			// ------------------------------------------------------

			// 70
			for (int k = 0; k < thread_num; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = data_lines[dd++] + 127;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(thread_num, core_num, addr_array);
			// ------------------------------------------------------

			// bind ----------------------------------------------
			hdc_xor_thread(thread_num, core_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_store_thread(thread_num, core_num);
			// ------------------------------------------------------
		}

		hdc_last();
		START_COMPUTE = clock();
		hdc_compute();
		END_COMPUTE = clock();
		COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// // 結果確認
		// printf("\n%d:\n", ll);
		// for (int j = 0; j < 32; j++)
		// {
		// 	printf("  %u\n", dst[j]);
		// }

		hdc_finish();
	}

	printf("  load時間: %lf[ms]\n", LOAD_TIME);
	printf("  計算時間: %lf[ms]", COM_TIME);

	printf("\n\n\n");
	return 0;
}