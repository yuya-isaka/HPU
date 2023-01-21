// include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint16_t
#include <string.h>
#include <fcntl.h>	  // open
#include <unistd.h>	  // read
#include <sys/mman.h> // mmap
#include <time.h>
#include "hdc_processor.h"

// 試行回数
// 100万回
#define TRIAL_NUM 1000000

int main(int argc, char const *argv[])
{
	const int RANNUM = 512;

	// コア数
	const int CORENUM = 2;

	// hv -----------------------------
	// メモリセットアップ
	hdc_setup();

	// アイテムメモリ生成
	hdc_make_imem(RANNUM);
	// hv -----------------------------

	double RAN_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	srand(10);

	hdc_start();

	/////////////////////////////////////////////////////////////////////////////
	START_COMPUTE = clock();
	int *rand_array_1 = (int *)calloc(TRIAL_NUM, sizeof(int));
	int *rand_array_2 = (int *)calloc(TRIAL_NUM, sizeof(int));
	for (int i = 0; i < TRIAL_NUM; i++)
	{
		rand_array_1[i] = rand() % RANNUM;
		rand_array_2[i] = rand() % RANNUM;
	}
	END_COMPUTE = clock();
	RAN_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;
	/////////////////////////////////////////////////////////////////////////////

	// SEND_NUM初期化
	hdc_init(0);

	uint16_t core_num = CORENUM;

	uint16_t addr_array1[THREADS_NUM][core_num];
	uint16_t addr_array2[THREADS_NUM][core_num];

	for (int ll = 0; ll < TRIAL_NUM; ll += 10)
	{
		int tmp = ll;

		// アドレス
		for (int k = 0; k < THREADS_NUM; k++)
		{
			for (int i = 0; i < core_num; i++)
			{
				addr_array1[k][i] = rand_array_1[tmp];
				addr_array2[k][i] = rand_array_2[tmp];
				tmp++;
			}
		}

		// load ---------------------------------------------
		hdc_load_thread(THREADS_NUM, core_num, addr_array1);
		// ------------------------------------------------------

		// move ---------------------------------------------
		hdc_simd_move_thread();
		// ------------------------------------------------------

		// load ---------------------------------------------
		hdc_load_thread(THREADS_NUM, core_num, addr_array2);
		// ------------------------------------------------------

		// xor ---------------------------------------------
		hdc_simd_xor_thread();
		// ------------------------------------------------------
	}

	// ラスト命令
	hdc_last();

	hdc_compute();

	hdc_finish();

	printf("\n  ランダム生成時間: %lf[s]\n", RAN_TIME);

	return 0;
}