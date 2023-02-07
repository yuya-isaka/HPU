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

int main(int argc, char const *argv[])
{
	// puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	// 訓練データパス
	// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	// const char *train_path[] = {"data/decorate/enlong", "data/decorate/frlong"};

	// 訓練数
	const int train_num = 2;

	// NGRAM
	const int NGRAM = 3;

	// 命令数
	const int INSTRUCTION_NUM = 2 + ((NGRAM - 2) * 4) + 4;

	// コア数
	const int CORENUM = 2;

	// DMA SEND_MAX
	int SEND_MAX = 33000000;
	const int SEND_TMP = SEND_MAX % (THREADS_NUM * 2 * INSTRUCTION_NUM) * (CORENUM * THREADS_NUM);
	SEND_MAX += SEND_TMP;

	// 偶数の時に使うアドレス
	const int MAJORITY_ADDR = 26;

	// hv -----------------------------
	// メモリセットアップ
	hdc_setup();

	// アイテムメモリ生成
	hdc_com_start();
	hdc_com_gen(88675123);
	for (int i = 0; i < 31; i++)
	{
		hdc_com_gen(xor128(0));
	}
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			hdc_com_gen(xor128(0));
		}
	}
	hdc_compute_only();
	hdc_finish();
	// hv -----------------------------

	double LOAD_TIME = 0.0;
	// double COM_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	// 英語とフランス語
	for (int l = 0; l < train_num; l++)
	{

		// hv -----------------------------

		// SEND_NUM初期化
		hdc_init(0);
		hdc_start();

		START_COMPUTE = clock();
		const char *path = train_path[l];
		FILE *file;
		file = fopen(path, "r");

		int ch;
		size_t num = 0;
		while ((ch = fgetc(file)) != EOF)
		{
			num++;
		}
		fseek(file, 0, SEEK_SET);
		char *content = (char *)calloc(num, sizeof(char));
		size_t done = fread(content, sizeof(char), num, file);
		fclose(file);
		END_COMPUTE = clock();
		LOAD_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// NGRAMの数
		const int ALL_NGRAM = num - NGRAM + 1;

		const int EPOCH = ALL_NGRAM / (CORENUM * THREADS_NUM);

		const int REMAINDAR = ALL_NGRAM % (CORENUM * THREADS_NUM);
		const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;

		const int LAST = EPOCH * CORENUM * THREADS_NUM;
		const int EVEN = ALL_NGRAM % 2 == 0;

		// SEND_MAXまで何個の命令を処理できるか
		// 1回70この命令を、SEND_MAX / 800 回回す必要がある
		// 800 = THREADS_NUM * 16 * INSTRUCTION_NUM
		// 70 = CORENUM * THREADS_NUM
		int ALL_SEND_NUM = SEND_MAX / (THREADS_NUM * 2 * INSTRUCTION_NUM) * (CORENUM * THREADS_NUM);
		// ALL_SEND_EPOCHをLASTまで何回する必要があるか
		const int ALL_SEND_EPOCH = LAST / ALL_SEND_NUM;
		// ALL_SEND_EPOCHをLASTまで何回する必要があるか(あまり)
		const int ALL_SEND_REMAIN = LAST % ALL_SEND_NUM;

		// printf("ALL_SEND_EPOCH: %d\n", ALL_SEND_EPOCH);
		// printf("ALL_SEND_NUM: %d\n", ALL_SEND_NUM);
		// printf("ALL_SEND_REMAIN: %d\n", ALL_SEND_REMAIN);
		// printf("REMAINDAR: %d\n", REMAINDAR);
		// printf("合計命令: %d\n", ALL_SEND_EPOCH * ALL_SEND_NUM + ALL_SEND_REMAIN + REMAINDAR);

		// SEND_NUMのエポック
		for (int ll = 0; ll < ALL_SEND_EPOCH; ll += 1)
		{
			// SEND_NUM繰り返す
			for (int j = 0; j < ALL_SEND_NUM; j += CORENUM * THREADS_NUM)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array[THREADS_NUM][core_num];

				// アドレス
				int nn = ll * ALL_SEND_NUM + j;
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = content[nn] - 97;
						nn++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// move ---------------------------------------------
				// hdc_move_thread(THREADS_NUM, core_num);
				hdc_simd_move_thread();
				// ------------------------------------------------------

				for (int kk = 1; kk < (NGRAM - 2) + 1; kk++)
				{
					// アドレス
					nn = ll * ALL_SEND_NUM + j + kk;
					for (int k = 0; k < THREADS_NUM; k++)
					{
						for (int i = 0; i < core_num; i++)
						{
							addr_array[k][i] = content[nn] - 97;
							nn++;
						}
					}

					// load ---------------------------------------------
					hdc_load_thread(THREADS_NUM, core_num, addr_array);
					// ------------------------------------------------------

					// permute ---------------------------------------------
					// hdc_permute_thread(THREADS_NUM, core_num, 1);
					hdc_simd_permute_thread(kk);
					// ------------------------------------------------------

					// pxor ---------------------------------------------
					// hdc_pxor_thread(THREADS_NUM, core_num);
					hdc_simd_pxor_thread();
					// ------------------------------------------------------

					// move ---------------------------------------------
					// hdc_move_thread(THREADS_NUM, core_num);
					hdc_simd_move_thread();
					// ------------------------------------------------------
				}

				// アドレス
				nn = ll * ALL_SEND_NUM + j + (NGRAM - 1);
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = content[nn] - 97;
						nn++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// permute ---------------------------------------------
				// hdc_permute_thread(THREADS_NUM, core_num, 3);
				hdc_simd_permute_thread(NGRAM - 1);
				// ------------------------------------------------------

				// pxor ---------------------------------------------
				// hdc_pxor_thread(THREADS_NUM, core_num);
				hdc_simd_pxor_thread();
				// ------------------------------------------------------

				// store ---------------------------------------------
				// hdc_store_thread(THREADS_NUM, core_num);
				hdc_simd_store_thread();
				// ------------------------------------------------------
			}
			// hdc_last();

			// START_COMPUTE = clock();
			// hdc_compute();
			// END_COMPUTE = clock();
			// COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

			// hdc_init(0);
		}

		// SEND_NUMエポックのあまり
		for (int j = 0; j < ALL_SEND_REMAIN; j += CORENUM * THREADS_NUM)
		{
			uint16_t core_num = CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];

			// アドレス
			int nn = ALL_SEND_EPOCH * ALL_SEND_NUM + j;
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = content[nn] - 97;
					nn++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// move ---------------------------------------------
			// hdc_move_thread(THREADS_NUM, core_num);
			hdc_simd_move_thread();
			// ------------------------------------------------------

			for (int kk = 1; kk < (NGRAM - 2) + 1; kk++)
			{
				// アドレス
				nn = ALL_SEND_EPOCH * ALL_SEND_NUM + j + kk;
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = content[nn] - 97;
						nn++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// permute ---------------------------------------------
				// hdc_permute_thread(THREADS_NUM, core_num, 1);
				hdc_simd_permute_thread(kk);
				// ------------------------------------------------------

				// pxor ---------------------------------------------
				// hdc_pxor_thread(THREADS_NUM, core_num);
				hdc_simd_pxor_thread();
				// ------------------------------------------------------

				// move ---------------------------------------------
				// hdc_move_thread(THREADS_NUM, core_num);
				hdc_simd_move_thread();
				// ------------------------------------------------------
			}

			// アドレス
			nn = ALL_SEND_EPOCH * ALL_SEND_NUM + j + (NGRAM - 1);
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = content[nn] - 97;
					nn++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// permute ---------------------------------------------
			// hdc_permute_thread(THREADS_NUM, core_num, 3);
			hdc_simd_permute_thread(NGRAM - 1);
			// ------------------------------------------------------

			// pxor ---------------------------------------------
			// hdc_pxor_thread(THREADS_NUM, core_num);
			hdc_simd_pxor_thread();
			// ------------------------------------------------------

			// store ---------------------------------------------
			// hdc_store_thread(THREADS_NUM, core_num);
			hdc_simd_store_thread();
			// ------------------------------------------------------
		}

		// 最後の余り
		if (REMAINDAR != 0)
		{
			uint16_t core_num = REMAINDAR_CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];

			// アドレス
			int nn = LAST;
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = content[nn] - 97;
					nn++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// move ---------------------------------------------
			hdc_move_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			for (int kk = 1; kk < (NGRAM - 2) + 1; kk++)
			{
				// アドレス
				nn = LAST + kk;
				for (int k = 0; k < THREADS_NUM; k++)
				{
					for (int i = 0; i < core_num; i++)
					{
						addr_array[k][i] = content[nn] - 97;
						nn++;
					}
				}

				// load ---------------------------------------------
				hdc_load_thread(THREADS_NUM, core_num, addr_array);
				// ------------------------------------------------------

				// permute ---------------------------------------------
				hdc_permute_thread(THREADS_NUM, core_num, kk);
				// ------------------------------------------------------

				// pxor ---------------------------------------------
				hdc_pxor_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_move_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------
			}

			// アドレス
			nn = LAST + (NGRAM - 1);
			for (int k = 0; k < THREADS_NUM; k++)
			{
				for (int i = 0; i < core_num; i++)
				{
					addr_array[k][i] = content[nn] - 97;
					nn++;
				}
			}

			// load ---------------------------------------------
			hdc_load_thread(THREADS_NUM, core_num, addr_array);
			// ------------------------------------------------------

			// permute ---------------------------------------------
			hdc_permute_thread(THREADS_NUM, core_num, NGRAM - 1);
			// ------------------------------------------------------

			// pxor ---------------------------------------------
			hdc_pxor_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_store_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------
		}

		// 偶数処理
		if (EVEN)
		{
			uint16_t addr_array[1][1] = {{MAJORITY_ADDR}};
			hdc_load_thread(1, 1, addr_array);

			hdc_store_thread(1, 1);
		}

		// hdc_print();

		// ラスト命令
		hdc_last();

		// START_COMPUTE = clock();
		hdc_compute();
		// END_COMPUTE = clock();
		// COM_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

		// // 結果確認
		// for (int j = 0; j < 32; j++)
		// {
		// 	printf("  %u\n", dst[j]);
		// }

		// 終了処理
		hdc_finish();
	}

	// printf("\n  計算時間: %lf[ms]\n", COM_TIME);
	printf("\n  ロード時間: %lf[ms]\n", LOAD_TIME);

	// puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");
	return 0;
}