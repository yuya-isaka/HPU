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
	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	// seed設定
	srand(10);
	const int RANNUM = 512;

	// 命令数
	const int INSTRUCTION_NUM = 2;

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

	// hv -----------------------------
	// SEND_NUM初期化
	hdc_init(0);
	hdc_start();

	// 試行回数
	const int TRIAL_NUM = 50000000;
	// const int TRIAL_NUM = 10000000;

	const int EPOCH = TRIAL_NUM / (CORENUM * THREADS_NUM);
	const int REMAINDAR = TRIAL_NUM % (CORENUM * THREADS_NUM);
	const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;
	const int LAST = EPOCH * CORENUM * THREADS_NUM;

	int ALL_SEND_NUM = SEND_MAX / (THREADS_NUM * 16 * INSTRUCTION_NUM) * 70;
	const int ALL_SEND_EPOCH = LAST / ALL_SEND_NUM;
	const int ALL_SEND_REMAIN = LAST % ALL_SEND_NUM;

	// printf("合計命令: %d\n", ALL_SEND_EPOCH * ALL_SEND_NUM + ALL_SEND_REMAIN + REMAINDAR);

	// 計算時間格納
	double TIME = 0.0;

	// SEND_NUMのエポック
	for (int ll = 0; ll < ALL_SEND_EPOCH; ll += 1)
	{
		// SEND_NUM繰り返す
		for (int j = 0; j < ALL_SEND_NUM; j += CORENUM * THREADS_NUM)
		{
			uint16_t core_num = CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];
			uint16_t perm_num[THREADS_NUM][core_num];

			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = rand() % RANNUM;
					perm_num[k][i] = rand() % RANNUM;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// perm ---------------------------------------------
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					hdc_permute(perm_num[k][i]);
				}
				for (int i = core_num; i < 16; i++)
				{
					hdc_nop();
				}
			}
			// ------------------------------------------------------
		}

		hdc_last();

		clock_t START_COMPUTE = clock();
		hdc_compute();
		clock_t END_COMPUTE = clock();
		TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC * 1000.0;

		hdc_init(0);
	}

	// SEND_NUMエポックのあまり
	for (int j = 0; j < ALL_SEND_REMAIN; j += CORENUM * THREADS_NUM)
	{
		uint16_t core_num = CORENUM;

		uint16_t addr_array[THREADS_NUM][core_num];
		uint16_t perm_num[THREADS_NUM][core_num];

		for (int k = 0; k < THREADS_NUM; k++)
		{
			for (int i = 0; i < core_num; i++)
			{
				addr_array[k][i] = rand() % RANNUM;
				perm_num[k][i] = rand() % RANNUM;
			}
		}

		// load ---------------------------------------------
		hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// ------------------------------------------------------

		// perm ---------------------------------------------
		for (int k = 0; k < THREADS_NUM; k++)
		{
			for (int i = 0; i < core_num; i++)
			{
				hdc_permute(perm_num[k][i]);
			}
			for (int i = core_num; i < 16; i++)
			{
				hdc_nop();
			}
		}
		// ------------------------------------------------------
	}

	// 最後の余り
	if (REMAINDAR != 0)
	{
		uint16_t core_num = REMAINDAR_CORENUM;

		uint16_t addr_array[THREADS_NUM][core_num];
		uint16_t perm_num[THREADS_NUM][core_num];

		for (int k = 0; k < THREADS_NUM; k++)
		{
			for (int i = 0; i < core_num; i++)
			{
				addr_array[k][i] = rand() % RANNUM;
				perm_num[k][i] = rand() % RANNUM;
			}
		}

		// load ---------------------------------------------
		hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// ------------------------------------------------------

		// perm ---------------------------------------------
		for (int k = 0; k < THREADS_NUM; k++)
		{
			for (int i = 0; i < core_num; i++)
			{
				hdc_permute(perm_num[k][i]);
			}
			for (int i = core_num; i < 16; i++)
			{
				hdc_nop();
			}
		}
		// ------------------------------------------------------
	}

	// ラスト命令
	hdc_last();

	clock_t START_COMPUTE = clock();
	// 計算開始
	hdc_compute();
	clock_t END_COMPUTE = clock();
	TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC * 1000.0;

	// 終了処理
	hdc_finish();

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");
	return 0;
}