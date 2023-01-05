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

int main(int argc, char const *argv[])
{
	const int RANNUM = 512;

	// 命令数
	const int INSTRUCTION_NUM = 4;

	// DMA SEND_MAX
	int SEND_MAX = 33000000;
	const int SEND_TMP = SEND_MAX % (THREADS_NUM * 16 * INSTRUCTION_NUM);
	SEND_MAX += SEND_TMP;

	// コア数
	const int CORENUM = 14;

	// hv -----------------------------
	// メモリセットアップ
	hdc_setup();

	// アイテムメモリ生成
	hdc_make_imem(RANNUM);
	// hv -----------------------------

	// 試行回数
	// 100万回
	const int TRIAL_NUM = 1000000;

	const int EPOCH = TRIAL_NUM / (CORENUM * THREADS_NUM);
	const int REMAINDAR = TRIAL_NUM % (CORENUM * THREADS_NUM);
	const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;
	const int LAST = EPOCH * CORENUM * THREADS_NUM;

	int ALL_SEND_NUM = SEND_MAX / (THREADS_NUM * 16 * INSTRUCTION_NUM) * 70;
	const int ALL_SEND_EPOCH = LAST / ALL_SEND_NUM;
	const int ALL_SEND_REMAIN = LAST % ALL_SEND_NUM;

	// printf("ALL_SEND_EPOCH: %d\n", ALL_SEND_EPOCH);
	// printf("ALL_SEND_NUM: %d\n", ALL_SEND_NUM);
	// printf("ALL_SEND_REMAIN: %d\n", ALL_SEND_REMAIN);
	// printf("REMAINDAR: %d\n", REMAINDAR);
	// printf("合計命令: %d\n", ALL_SEND_EPOCH * ALL_SEND_NUM + ALL_SEND_REMAIN + REMAINDAR);

	double RAN_TIME = 0.0;
	double COM_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	hdc_start();

	for (int nnn = 0; nnn < 10; nnn)
	{
		START_COMPUTE = clock();
		srand((unsigned int)time(NULL));
		int rand_array[TRIAL_NUM * 2];
		for (int i = 0; i < TRIAL_NUM; i++)
		{
			rand_array[i] = rand() % RANNUM;
		}
		int rand_array_num = 0;
		END_COMPUTE = clock();
		RAN_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// hv -----------------------------
		// SEND_NUM初期化
		hdc_init(0);

		// SEND_NUMのエポック
		for (int ll = 0; ll < ALL_SEND_EPOCH; ll += 1)
		{
			// SEND_NUM繰り返す
			for (int j = 0; j < ALL_SEND_NUM; j += CORENUM * THREADS_NUM)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array1[THREADS_NUM][core_num];
				uint16_t addr_array2[THREADS_NUM][core_num];

				// アドレス
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array1[k][i] = rand_array[rand_array_num++];
						addr_array2[k][i] = rand_array[rand_array_num++];
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
		}

		// SEND_NUMエポックのあまり
		for (int j = 0; j < ALL_SEND_REMAIN; j += CORENUM * THREADS_NUM)
		{
			uint16_t core_num = CORENUM;

			uint16_t addr_array1[THREADS_NUM][core_num];
			uint16_t addr_array2[THREADS_NUM][core_num];

			// アドレス
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array1[k][i] = rand_array[rand_array_num++];
					addr_array2[k][i] = rand_array[rand_array_num++];
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

		// 最後の余り
		if (REMAINDAR != 0)
		{
			uint16_t core_num = REMAINDAR_CORENUM;

			uint16_t addr_array1[THREADS_NUM][core_num];
			uint16_t addr_array2[THREADS_NUM][core_num];

			// アドレス
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array1[k][i] = rand_array[rand_array_num++];
					addr_array2[k][i] = rand_array[rand_array_num++];
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array1);
			// ------------------------------------------------------

			// move ---------------------------------------------
			hdc_move_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array2);
			// ------------------------------------------------------

			// xor ---------------------------------------------
			hdc_xor_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------
		}

		// ラスト命令
		hdc_last();

		START_COMPUTE = clock();
		hdc_compute();
		END_COMPUTE = clock();
		COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;
	}

	hdc_finish();

	printf("\n  ランダム生成時間: %lf[s]\n", RAN_TIME);
	printf("\n  計算時間: %lf[s]\n", COM_TIME);

	return 0;
}