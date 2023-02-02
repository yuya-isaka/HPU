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
	const int INSTRUCTION_NUM = 3;

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
	// hdc_make_imem(RANNUM);
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

	// // 計算時間格納
	// double TIME = 0.0;

	// 実験回数
	const int EXP_NUM = 1000;
	for (int nnn = 0; nnn < EXP_NUM; nnn++)
	{
		// ランダムな値生成
		srand((unsigned int)time(NULL));
		int tmp = rand() % RANNUM;
		int perm_num = rand() % 1024;

		// SEND_NUM初期化
		hdc_init(0);
		hdc_start();

		// SEND_NUMのエポック
		for (int ll = 0; ll < ALL_SEND_EPOCH; ll += 1)
		{
			// SEND_NUM繰り返す
			for (int j = 0; j < ALL_SEND_NUM; j += CORENUM * THREADS_NUM)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array[THREADS_NUM][core_num];

				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = tmp;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// perm ---------------------------------------------
				hdc_simd_permute_thread(perm_num);
				// ------------------------------------------------------

				// store ---------------------------------------------
				// hdc_store_thread(THREADS_NUM, core_num);
				hdc_simd_pstore_thread();
				// ------------------------------------------------------
			}

			// hdc_last();

			// clock_t START_COMPUTE = clock();
			// hdc_compute();
			// clock_t END_COMPUTE = clock();
			// TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC * 1000.0;

			// hdc_init(0);
		}

		// SEND_NUMエポックのあまり
		for (int j = 0; j < ALL_SEND_REMAIN; j += CORENUM * THREADS_NUM)
		{
			uint16_t core_num = CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];

			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = tmp;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// perm ---------------------------------------------
			hdc_simd_permute_thread(perm_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			// hdc_store_thread(THREADS_NUM, core_num);
			hdc_simd_pstore_thread();
			// ------------------------------------------------------
		}

		// 最後の余り
		if (REMAINDAR != 0)
		{
			uint16_t core_num = REMAINDAR_CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];

			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = tmp;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// perm ---------------------------------------------
			hdc_permute_thread(THREADS_NUM, core_num, perm_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_pstore_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------
		}

		// ラスト命令
		hdc_last();

		// clock_t START_COMPUTE = clock();
		hdc_compute();
		// clock_t END_COMPUTE = clock();
		// TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC * 1000.0;

		// 終了処理
		hdc_finish();
	}

	return 0;
}