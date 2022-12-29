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

	const int train_num = 2;

	// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	// const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	const char *train_path[] = {"data/decorate/enlong", "data/decorate/frlong"};

	const int INSTRUCTION_NUM = 14;

	int SEND_MAX = 33000000;

	const int SEND_TMP = SEND_MAX % (THREADS_NUM * 16 * INSTRUCTION_NUM);

	SEND_MAX += SEND_TMP;

	const int CORENUM = 14;

	const int MAJORITY_ADDR = 26;

	const int NGRAM = 4;

	hdc_setup();
	hdc_make_imem(27);

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
			num++;
		}
		fseek(file, 0, SEEK_SET);
		char *content = (char *)calloc(num, sizeof(char));
		size_t done = fread(content, sizeof(char), num, file);
		fclose(file);

		const int ALL_NGRAM = num - NGRAM + 1;
		printf("all_ngram: %d\n", ALL_NGRAM);

		const int EPOCH = ALL_NGRAM / (CORENUM * THREADS_NUM);
		const int REMAINDAR = ALL_NGRAM % (CORENUM * THREADS_NUM);
		printf("remaindar: %d", REMAINDAR);
		const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;
		const int LAST = EPOCH * CORENUM * THREADS_NUM;
		const int EVEN = ALL_NGRAM % 2 == 0;

		// SEND_MAXまで何個の命令を処理できるか
		// 1回70この命令を、SEND_MAX / 800 回回す必要がある
		// 800 = THREADS_NUM * 16 * INSTRUCTION_NUM
		// 70 = CORENUM * THREADS_NUM
		int ALL_SEND_NUM = SEND_MAX / (THREADS_NUM * 16 * INSTRUCTION_NUM) * 70;
		// ALL_SEND_EPOCHをLASTまで何回する必要があるか
		const int ALL_SEND_EPOCH = LAST / ALL_SEND_NUM;
		// ALL_SEND_EPOCHをLASTまで何回する必要があるか(あまり)
		const int ALL_SEND_REMAIN = LAST % ALL_SEND_NUM;

		printf("合計命令: %d\n", ALL_SEND_EPOCH * ALL_SEND_NUM + ALL_SEND_REMAIN + REMAINDAR);

		for (int ll = 0; ll < ALL_SEND_EPOCH; ll += 1)
		{
			for (int j = 0; j < ALL_SEND_NUM; j += CORENUM * THREADS_NUM)
			{
				uint16_t core_num = CORENUM;

				uint16_t addr_array[THREADS_NUM][core_num];

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
				hdc_simd_move_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------

				nn = ll * ALL_SEND_NUM + j + 1;
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

				nn = ll * ALL_SEND_NUM + j + 2;
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

				// move ---------------------------------------------
				hdc_simd_move_thread(THREADS_NUM, core_num);
				// ------------------------------------------------------

				nn = ll * ALL_SEND_NUM + j + 3;
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
				hdc_permute_thread(THREADS_NUM, core_num, 3);
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
			hdc_dma_reset();
			hdc_init(0);
		}

		for (int j = 0; j < ALL_SEND_REMAIN; j += CORENUM * THREADS_NUM)
		{
			uint16_t core_num = CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];

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
			hdc_simd_move_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			nn = ALL_SEND_EPOCH * ALL_SEND_NUM + j + 1;
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

			nn = ALL_SEND_EPOCH * ALL_SEND_NUM + j + 2;
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

			// move ---------------------------------------------
			hdc_simd_move_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			nn = ALL_SEND_EPOCH * ALL_SEND_NUM + j + 3;
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
			hdc_permute_thread(THREADS_NUM, core_num, 3);
			// ------------------------------------------------------

			// pxor ---------------------------------------------
			hdc_pxor_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			// store ---------------------------------------------
			hdc_store_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------
		}

		if (REMAINDAR != 0)
		{
			uint16_t core_num = REMAINDAR_CORENUM;

			uint16_t addr_array[THREADS_NUM][core_num];

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

			// move ---------------------------------------------
			hdc_move_thread(THREADS_NUM, core_num);
			// ------------------------------------------------------

			nn = LAST + 3;
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
			hdc_permute_thread(THREADS_NUM, core_num, 3);
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

		hdc_last_core(1);
		hdc_compute();

		// 結果確認
		printf("\n");
		for (int j = 0; j < 32; j++)
		{
			printf("  %u\n", dst[j]);
		}
		printf("\n");

		hdc_finish();
	}

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");
	return 0;
}