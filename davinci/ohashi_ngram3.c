
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

	hdc_setup();

	hdc_make_imem(27);

	const int train_num = 2;
	const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	// const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	// const char *train_path[] = {"data/decorate/enlong", "data/decorate/frlong"};

	const int SEND_MAX = 33000000 + 30;
	const int CORENUM = 14;
	const int MAJORITY_ADDR = 26;
	const int NGRAM = 3;
	const unsigned long SRC_PHYS = src_phys;

	// 英語とフランス語の数だけ繰り返す
	for (int l = 0; l < train_num; l++)
	{

		hdc_init(0);

		hdc_dma_reset();

		hdc_start();

		const char *path = train_path[l];
		printf("\n------------- %sの学習 -------------\n\n", path);
		FILE *file;
		file = fopen(path, "r");

		int ch;
		size_t num = 0;
		while ((ch = fgetc(file)) != EOF)
		{
			// printf("%c", ch);
			num++;
		}
		printf("num: %d\n", num);
		fseek(file, 0, SEEK_SET);
		char *content = (char *)calloc(num, sizeof(char));
		size_t done = fread(content, sizeof(char), num, file);
		fclose(file);

		printf("content: %d\n", strlen(content));
		// const int ALL_NGRAM = strlen(content) - NGRAM + 1;
		const int ALL_NGRAM = num - NGRAM + 1;
		printf("all_ngram: %d\n", ALL_NGRAM);
		// const int EPOCH = ALL_NGRAM / SEND_MAX; // SEND_MAXがちょうど80で割り切れて良い
		// printf("epoch: %d\n", EPOCH);
		// const int EPOCH_AMARI = ALL_NGRAM % SEND_MAX;
		// printf("epoch_amari: %d\n", EPOCH_AMARI);

		// const int LAST = EPOCH_AMARI / (CORENUM * THREADS_NUM);
		// printf("last: %d\n", LAST);
		// const int REMAINDAR = EPOCH_AMARI % (CORENUM * THREADS_NUM);
		// printf("remaindar: %d\n", REMAINDAR);
		// const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;
		// printf("remaindar_corenum: %d\n", REMAINDAR_CORENUM);

		const int EPOCH = ALL_NGRAM / (CORENUM * THREADS_NUM);
		printf("epoch: %d\n", EPOCH);
		const int REMAINDAR = ALL_NGRAM % (CORENUM * THREADS_NUM);
		printf("remaindar: %d\n", REMAINDAR);
		const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;
		printf("remaindar_corenum: %d\n", REMAINDAR_CORENUM);
		const int LAST = EPOCH * CORENUM * THREADS_NUM;
		printf("last: %d\n", LAST);
		const int EVEN = ALL_NGRAM % 2 == 0;
		printf("even: %d\n", EVEN);

		uint16_t core_num = CORENUM;

		int aaa = SEND_MAX / 800 * 70;
		printf("aaa: %d\n", aaa);
		const int bbb = LAST / aaa;
		printf("bbb: %d\n", bbb);
		const int ccc = LAST % aaa;
		printf("ccc: %d\n", ccc);

		for (int ll = 0; ll < bbb; ll += 1)
		{
			for (int j = 0; j < aaa; j += CORENUM * THREADS_NUM)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array[THREADS_NUM][core_num];

				// 0, 3, 6, ...
				int nn = ll * aaa + j;
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
				hdc_simd_move_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------

				nn = ll * aaa + j + 1;
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
				hdc_permute_thread(THREADS_NUM, core_num, 1);
				// ------------------------------------------------------

				// pxor ---------------------------------------------
				hdc_pxor_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------

				// move ---------------------------------------------
				hdc_simd_move_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------

				nn = ll * aaa + j + 2;
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
				hdc_permute_thread(THREADS_NUM, core_num, 2);
				// ------------------------------------------------------

				// pxor ---------------------------------------------
				hdc_pxor_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------

				// store ---------------------------------------------
				hdc_store_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------

				// hdc_print();
			}
			hdc_last_core(1);
			hdc_compute();
			hdc_init(0);
		}

		for (int j = 0; j < ccc; j += CORENUM * THREADS_NUM)
		{
			uint16_t core_num = CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];

			// 0, 3, 6, ...
			int nn = bbb * aaa + j;
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
			hdc_simd_move_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			nn = bbb * aaa + j + 1;
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
			hdc_permute_thread(THREADS_NUM, core_num, 1);
			// ------------------------------------------------------

			// pxor ---------------------------------------------
			hdc_pxor_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			// move ---------------------------------------------
			hdc_simd_move_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			nn = bbb * aaa + j + 2;
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
			hdc_permute_thread(THREADS_NUM, core_num, 2);
			// ------------------------------------------------------

			// pxor ---------------------------------------------
			hdc_pxor_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_store_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------
		}
		hdc_last_core(1);
		hdc_compute();
		hdc_init(0);

		if (REMAINDAR != 0)
		{
			uint16_t core_num = REMAINDAR_CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];

			// 1190,1193, 1196, 1199
			// 1202, 1205, 1208, 1211
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

			nn = LAST + 1;
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
			hdc_permute_thread(THREADS_NUM, core_num, 1);
			// ------------------------------------------------------

			// pxor ---------------------------------------------
			hdc_pxor_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			// move ---------------------------------------------
			hdc_move_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			nn = LAST + 2;
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
			hdc_permute_thread(THREADS_NUM, core_num, 2);
			// ------------------------------------------------------

			// pxor ---------------------------------------------
			hdc_pxor_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_store_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------
		}

		if (EVEN)
		{
			uint16_t addr_array[1][1] = {{MAJORITY_ADDR}};
			hdc_load_thread(1, 1, addr_array);

			hdc_store_thread(1, 1);
		}

		// LAST命令
		// 1024bit ---------------------------------------------
		hdc_last_core(1);
		// ------------------------------------------------------

		// for (int ee = 0; ee < EPOCH; ee++)
		// {
		// 	for (int j = ee * SEND_MAX; j < ((ee + 1) * SEND_MAX); j += CORENUM * THREADS_NUM)
		// 	{
		// 		uint16_t addr_array[THREADS_NUM][core_num];

		// 		int nn = j;
		// 		for (int k = 0; k < THREADS_NUM; k++)
		// 		{
		// 			for (int i = 0; i < core_num; i++)
		// 			{
		// 				addr_array[k][i] = content[nn];
		// 				nn += NGRAM;
		// 			}
		// 		}
		// 		// load ---------------------------------------------
		// 		hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 		// ------------------------------------------------------
		// 		// move ---------------------------------------------
		// 		hdc_move_thread(THREADS_NUM, core_num);
		// 		// ------------------------------------------------------

		// 		nn = j + 1;
		// 		for (int k = 0; k < THREADS_NUM; k++)
		// 		{
		// 			for (int i = 0; i < core_num; i++)
		// 			{
		// 				addr_array[k][i] = content[nn];
		// 				nn += NGRAM;
		// 			}
		// 		}
		// 		// load ---------------------------------------------
		// 		hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 		// ------------------------------------------------------

		// 		// permute ---------------------------------------------
		// 		hdc_permute_thread(THREADS_NUM, core_num, 1);
		// 		// ------------------------------------------------------

		// 		// pxor ---------------------------------------------
		// 		hdc_pxor_thread(THREADS_NUM, core_num);
		// 		// ------------------------------------------------------

		// 		// move ---------------------------------------------
		// 		hdc_move_thread(THREADS_NUM, core_num);
		// 		// ------------------------------------------------------

		// 		nn = j + 2;
		// 		for (int k = 0; k < THREADS_NUM; k++)
		// 		{
		// 			for (int i = 0; i < core_num; i++)
		// 			{
		// 				addr_array[k][i] = content[nn];
		// 				nn += NGRAM;
		// 			}
		// 		}

		// 		// load ---------------------------------------------
		// 		hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 		// ------------------------------------------------------

		// 		// permute ---------------------------------------------
		// 		hdc_permute_thread(THREADS_NUM, core_num, 2);
		// 		// ------------------------------------------------------

		// 		// pxor ---------------------------------------------
		// 		hdc_pxor_thread(THREADS_NUM, core_num);
		// 		// ------------------------------------------------------

		// 		// store ---------------------------------------------
		// 		hdc_store_thread(THREADS_NUM, core_num);
		// 		// ------------------------------------------------------
		// 	}
		// 	// LAST命令
		// 	// 1024bit ---------------------------------------------
		// 	hdc_last_core(1);
		// 	// ------------------------------------------------------
		// }

		// core_num = CORENUM;
		// for (int j = EPOCH * SEND_MAX; j < LAST; j += CORENUM * THREADS_NUM)
		// {
		// 	uint16_t addr_array[THREADS_NUM][core_num];

		// 	int nn = j;
		// 	for (int k = 0; k < THREADS_NUM; k++)
		// 	{
		// 		for (int i = 0; i < core_num; i++)
		// 		{
		// 			addr_array[k][i] = content[nn];
		// 			nn += NGRAM;
		// 		}
		// 	}
		// 	// load ---------------------------------------------
		// 	hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 	// ------------------------------------------------------
		// 	// move ---------------------------------------------
		// 	hdc_move_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------

		// 	nn = j + 1;
		// 	for (int k = 0; k < THREADS_NUM; k++)
		// 	{
		// 		for (int i = 0; i < core_num; i++)
		// 		{
		// 			addr_array[k][i] = content[nn];
		// 			nn += NGRAM;
		// 		}
		// 	}
		// 	// load ---------------------------------------------
		// 	hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 	// ------------------------------------------------------

		// 	// permute ---------------------------------------------
		// 	hdc_permute_thread(THREADS_NUM, core_num, 1);
		// 	// ------------------------------------------------------

		// 	// pxor ---------------------------------------------
		// 	hdc_pxor_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------

		// 	// move ---------------------------------------------
		// 	hdc_move_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------

		// 	nn = j + 2;
		// 	for (int k = 0; k < THREADS_NUM; k++)
		// 	{
		// 		for (int i = 0; i < core_num; i++)
		// 		{
		// 			addr_array[k][i] = content[nn];
		// 			nn += NGRAM;
		// 		}
		// 	}

		// 	// load ---------------------------------------------
		// 	hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 	// ------------------------------------------------------

		// 	// permute ---------------------------------------------
		// 	hdc_permute_thread(THREADS_NUM, core_num, 2);
		// 	// ------------------------------------------------------

		// 	// pxor ---------------------------------------------
		// 	hdc_pxor_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------

		// 	// store ---------------------------------------------
		// 	hdc_store_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------
		// }

		// core_num = REMAINDAR_CORENUM;
		// for (int j = LAST; j < EPOCH_AMARI; j += CORENUM * THREADS_NUM)
		// {
		// 	uint16_t addr_array[THREADS_NUM][core_num];

		// 	int nn = j;
		// 	for (int k = 0; k < THREADS_NUM; k++)
		// 	{
		// 		for (int i = 0; i < core_num; i++)
		// 		{
		// 			addr_array[k][i] = content[nn];
		// 			nn += NGRAM;
		// 		}
		// 	}
		// 	// load ---------------------------------------------
		// 	hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 	// ------------------------------------------------------
		// 	// move ---------------------------------------------
		// 	hdc_move_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------

		// 	nn = j + 1;
		// 	for (int k = 0; k < THREADS_NUM; k++)
		// 	{
		// 		for (int i = 0; i < core_num; i++)
		// 		{
		// 			addr_array[k][i] = content[nn];
		// 			nn += NGRAM;
		// 		}
		// 	}
		// 	// load ---------------------------------------------
		// 	hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 	// ------------------------------------------------------

		// 	// permute ---------------------------------------------
		// 	hdc_permute_thread(THREADS_NUM, core_num, 1);
		// 	// ------------------------------------------------------

		// 	// pxor ---------------------------------------------
		// 	hdc_pxor_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------

		// 	// move ---------------------------------------------
		// 	hdc_move_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------

		// 	nn = j + 2;
		// 	for (int k = 0; k < THREADS_NUM; k++)
		// 	{
		// 		for (int i = 0; i < core_num; i++)
		// 		{
		// 			addr_array[k][i] = content[nn];
		// 			nn += NGRAM;
		// 		}
		// 	}

		// 	// load ---------------------------------------------
		// 	hdc_load_thread(THREADS_NUM, core_num, addr_array);
		// 	// ------------------------------------------------------

		// 	// permute ---------------------------------------------
		// 	hdc_permute_thread(THREADS_NUM, core_num, 2);
		// 	// ------------------------------------------------------

		// 	// pxor ---------------------------------------------
		// 	hdc_pxor_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------

		// 	// store ---------------------------------------------
		// 	hdc_store_thread(THREADS_NUM, core_num);
		// 	// ------------------------------------------------------
		// }
		// // LAST命令
		// // 1024bit ---------------------------------------------
		// hdc_last_core(1);
		// // ------------------------------------------------------

		hdc_compute();

		// for (int i = 0; i < EPOCH; i++)
		// {
		// 	hdc_dma_reset();

		// 	dma[0x00 / 4] = 1;
		// 	dma[0x18 / 4] = src_phys;
		// 	dma[0x28 / 4] = SEND_MAX * 2; // 16ビットがsend_num個

		// 	dma[0x30 / 4] = 1;
		// 	dma[0x48 / 4] = dst_phys;
		// 	dma[0x58 / 4] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

		// 	while ((dma[0x34 / 4] & 0x1000) != 0x1000)
		// 		;

		// 	src_phys += SEND_MAX * 2;
		// }

		// hdc_dma_reset();

		// dma[0x00 / 4] = 1;
		// dma[0x18 / 4] = src_phys;
		// dma[0x28 / 4] = EPOCH_AMARI * 2; // 16ビットがsend_num個

		// dma[0x30 / 4] = 1;
		// dma[0x48 / 4] = dst_phys;
		// dma[0x58 / 4] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

		// while ((dma[0x34 / 4] & 0x1000) != 0x1000)
		// 	;

		// hdc_finish();

		// 結果確認
		printf("\n");
		for (int j = 0; j < 32; j++)
		{
			printf("  %u\n", dst[j]);
		}
		printf("\n");

		hdc_finish();

		// src_phys = SRC_PHYS;
	}

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	return 0;
}