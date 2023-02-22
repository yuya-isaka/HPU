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

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 784個のハイパーベクトルを生成し格納
	const uint32_t RAND_NUM = 617; // 617 + 10 + 10
	const uint32_t FIRST_RAND_NUM = 500;
	const uint32_t SECOND_RAND_NUM = RAND_NUM - FIRST_RAND_NUM;
	const uint32_t LEVEL_NUM = 10;
	const uint32_t DIM = 32;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hdc_setup();

	xor128(1);
	uint32_t Level[LEVEL_NUM][DIM];
	Level[0][0] = 88675123;
	for (int i = 1; i < DIM; i++)
	{
		Level[0][i] = xor128(0);
	}
	// for (int i = 1; i < 10; i++)
	// {
	// 	int tmp = 1024 / i;
	// 	int num = tmp / 32;
	// 	int num_remain = tmp % 32;
	// 	for (int j = 0; j < num; j++)
	// 	{
	// 		Level[i][j] = ~Level[0][j];
	// 		// printf("%d: 反転%u:%u\n", i, Level[i][j], Level[0][j]);
	// 	}
	// 	if (num_remain != 0)
	// 	{
	// 		uint32_t mask = 1 << num_remain - 1;
	// 		Level[i][num] = Level[0][num] ^ mask;

	// 		for (int j = num + 1; j < 32; j++)
	// 		{
	// 			Level[i][j] = Level[0][j];
	// 		}
	// 	}
	// 	else
	// 	{
	// 		for (int j = num; j < 32; j++)
	// 		{
	// 			Level[i][j] = Level[0][j];
	// 			// printf("%d: そのまま%u:%u\n", i, Level[i][j], Level[0][j]);
	// 		}
	// 	}
	// }
	for (int j = 0; j < DIM; j++)
	{
		Level[1][j] = ~Level[0][j];
	}
	for (int i = 2; i < LEVEL_NUM; i++)
	{
		int tmp = 1024 / i;
		int num = tmp / DIM;
		int num_remain = tmp % DIM;
		for (int j = 0; j < num; j++)
		{
			Level[i][j] = ~Level[0][j];
			// printf("%d: 反転%u:%u\n", i, Level[i][j], Level[0][j]);
		}
		uint32_t mask = 1 << num_remain - 1;
		Level[i][num] = Level[0][num] ^ mask;

		for (int j = num + 1; j < DIM; j++)
		{
			Level[i][j] = Level[0][j];
		}
	}

	for (int ll = 0; ll < 26; ll++)
	{
		// 500

		// 最初はLevelの生成に使用しているからなし
		xor128(1);
		for (int i = 0; i < DIM - 1; i++)
		{
			xor128(0);
		}

		hdc_com_start();

		// ID送信
		for (int i = 0; i < FIRST_RAND_NUM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				hdc_com_gen(xor128(0));
			}
		}
		// Level送信
		for (int i = 0; i < LEVEL_NUM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				hdc_com_gen(Level[i][j]);
			}
		}

		// 計算だけする（結果返さない）
		hdc_compute_only();
		hdc_finish();

		// 計算を再度開始
		hdc_init(0);
		hdc_start();

		START_COMPUTE = clock();
		char PATH[12];
		snprintf(PATH, 12, "label%d.txt", ll);
		int data_tmp_num = 0;
		char *data_lines = read_file(PATH, &data_tmp_num);
		END_COMPUTE = clock();
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// 510
		for (int dd = 0; dd < data_tmp_num;)
		{
			int index_tmp = 0;

			for (int j = 0; j < FIRST_RAND_NUM / THREADS_NUM; j++)
			{
				uint16_t addr_array[THREADS_NUM];

				for (int k = 0; k < THREADS_NUM; k++)
				{
					addr_array[k] = index_tmp++;
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, addr_array);
				// ------------------------------------------------------

				// move --------------------------------------------
				hdc_move_thread(THREADS_NUM);
				// ------------------------------------------------------

				for (int k = 0; k < THREADS_NUM; k++)
				{
					addr_array[k] = (data_lines[dd++] - '0') + FIRST_RAND_NUM;
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, addr_array);
				// ------------------------------------------------------

				// bind ----------------------------------------------
				hdc_xor_thread(THREADS_NUM);
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_store_thread(THREADS_NUM);
				// ------------------------------------------------------
			}
			dd += SECOND_RAND_NUM;
		}

		// hdc_last();
		// START_COMPUTE = clock();
		hdc_compute_only();
		// END_COMPUTE = clock();
		// COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// 127
		hdc_com_start_continue();
		// ID送信
		for (int i = 0; i < SECOND_RAND_NUM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				hdc_com_gen(xor128(0));
			}
		}
		// Level送信
		for (int i = 0; i < LEVEL_NUM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				hdc_com_gen(Level[i][j]);
			}
		}
		hdc_compute_only();

		hdc_init(0);
		// runだけたった状態に戻す
		hdc_start();

		for (int dd = 0; dd < data_tmp_num;)
		{
			dd += FIRST_RAND_NUM;
			int index_tmp = 0;

			// 125
			for (int j = 0; j < 115 / THREADS_NUM; j++)
			{
				uint16_t addr_array[THREADS_NUM];

				// 70
				for (int k = 0; k < THREADS_NUM; k++)
				{
					addr_array[k] = index_tmp++;
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, addr_array);
				// ------------------------------------------------------

				// move --------------------------------------------
				hdc_move_thread(THREADS_NUM);
				// ------------------------------------------------------

				// 70
				for (int k = 0; k < THREADS_NUM; k++)
				{
					addr_array[k] = (data_lines[dd++] - '0') + SECOND_RAND_NUM;
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, addr_array);
				// ------------------------------------------------------

				// bind ----------------------------------------------
				hdc_xor_thread(THREADS_NUM);
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_store_thread(THREADS_NUM);
				// ------------------------------------------------------
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 2
			uint16_t thread_num = 2;
			uint16_t addr_array[thread_num];

			for (int k = 0; k < thread_num; k++)
			{
				addr_array[k] = index_tmp++;
			}

			// load ---------------------------------------------
			hdc_load_thread(thread_num, addr_array);
			// ------------------------------------------------------

			// move --------------------------------------------
			hdc_move_thread(thread_num);
			// ------------------------------------------------------

			// 70
			for (int k = 0; k < thread_num; k++)
			{
				addr_array[k] = (data_lines[dd++] - '0') + SECOND_RAND_NUM;
			}

			// load ---------------------------------------------
			hdc_load_thread(thread_num, addr_array);
			// ------------------------------------------------------

			// bind ----------------------------------------------
			hdc_xor_thread(thread_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_store_thread(thread_num);
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

	// printf("\n\n\n");
	return 0;
}