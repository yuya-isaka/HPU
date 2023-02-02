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

// ファイル読み込み
char *read_file(const char *PATH, int *num)
{
	FILE *file;
	file = fopen(PATH, "r");
	if (file == NULL)
	{
		perror("  Failed: open file");
		exit(1);
	}

	uint32_t ch;
	// 与えられたファイルがひと続きの文字列と仮定 (2行になると｛10, 0x0a, LF(改行)｝ が入ってしまいズレる)
	// printf("EOF: %d\n", EOF); // EOFは全て-1 (Mac, Linux, Petalinux)
	while ((ch = fgetc(file)) != EOF)
	{
		(*num)++;
	}

	fseek(file, 0, SEEK_SET);
	char *content = (char *)calloc(*num, sizeof(char));
	if (content == NULL)
	{
		perror("  Failed: calloc");
		exit(1);
	}

	const uint32_t DONE = (uint32_t)fread(content, sizeof(char), *num, file);
	if (DONE < *num)
	{
		perror("  Failed: fread file");
		exit(1);
	}

	fclose(file);

	return content;
}

uint32_t xor128(int reset)
{
	// 初期値
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

	// リセット信号
	if (reset)
	{
		x = 123456789;
		y = 362436069;
		z = 521288629;
		w = 88675123;
		return 0;
	}
	else
	{
		uint32_t t = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	double LOAD_TIME = 0.0;
	// double COM_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	// 784個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = 784;
	const uint32_t FIRST_RAND_NUM = 500;
	const uint32_t SECOND_RAND_NUM = RAND_NUM - FIRST_RAND_NUM;

	// コア数
	const int CORENUM = 2;

	// メモリセットアップ
	hdc_setup();

	for (int ll = 0; ll < 10; ll++)
	{
		// 500
		// hdc_make_imem(FIRST_RAND_NUM);
		xor128(1);
		hdc_com_start();
		hdc_com_gen(88675123);
		for (int i = 0; i < 31; i++)
		{
			hdc_com_gen(xor128(0));
		}
		for (int i = 0; i < FIRST_RAND_NUM - 1; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				hdc_com_gen(xor128(0));
			}
		}
		hdc_compute_only();
		hdc_finish();

		hdc_init(0);
		hdc_start();

		START_COMPUTE = clock();
		char PATH[12];
		snprintf(PATH, 12, "image%d.txt", ll);
		int data_tmp_num = 0;
		char *data_lines = read_file(PATH, &data_tmp_num);
		END_COMPUTE = clock();
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		for (int dd = 0; dd < data_tmp_num;)
		{
			int index_num = 0;

			for (int j = 0; j < 50; j++)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array[THREADS_NUM][core_num];
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = index_num++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// permute ---------------------------------------------
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						hdc_permute((data_lines[dd++] - '0'));
					}
				}
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_simd_pstore_thread();
				// ------------------------------------------------------
			}
			dd += SECOND_RAND_NUM;
		}

		// hdc_last();
		// START_COMPUTE = clock();
		hdc_compute_only();
		// END_COMPUTE = clock();
		// COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// 284
		hdc_com_start_continue();
		for (int i = 0; i < SECOND_RAND_NUM; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				hdc_com_gen(xor128(0));
			}
		}
		hdc_compute_only();

		hdc_init(0);
		// runだけたった状態に戻す
		hdc_start();

		for (int dd = 0; dd < data_tmp_num;)
		{
			dd += FIRST_RAND_NUM;
			int index_num = 0;

			for (int j = 0; j < 28; j++)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array[THREADS_NUM][core_num];
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = index_num++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// permute ---------------------------------------------
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						hdc_permute((data_lines[dd++] - '0'));
					}
				}
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_simd_pstore_thread();
				// ------------------------------------------------------
			}

			// 残り 4
			uint16_t core_num = CORENUM;
			uint16_t thread_num = 2;

			uint16_t addr_array[thread_num][core_num];
			for (int k = 0; k < thread_num; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = index_num++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(thread_num, core_num, addr_array);
			// ------------------------------------------------------

			// permute ---------------------------------------------
			for (int k = 0; k < thread_num; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					hdc_permute((data_lines[dd++] - '0'));
				}
			}
			for (int k = thread_num; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < 2; i++)
				{
					hdc_nop();
				}
			}
			// ------------------------------------------------------

			// pstore ---------------------------------------------
			hdc_pstore_thread(thread_num, core_num);
			// ------------------------------------------------------
		}

		hdc_last();
		// START_COMPUTE = clock();
		hdc_compute();
		// END_COMPUTE = clock();
		// COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// // 結果確認
		// printf("\n%d:\n", ll);
		// for (int j = 0; j < 32; j++)
		// {
		// 	printf("  %u\n", dst[j]);
		// }

		hdc_finish();

		free(data_lines);
	}

	printf("  load時間: %lf[ms]\n", LOAD_TIME);
	// printf("  計算時間: %lf[ms]", COM_TIME);

	// printf("\n\n");
	return 0;
}