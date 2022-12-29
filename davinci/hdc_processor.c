#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdint.h>
#include "hdc_processor.h"

int SEND_NUM = 0;

uint16_t hdc_assemble(const char inst_str[], uint16_t addr)
{
	if (strcmp(inst_str, "load") == 0 || strcmp(inst_str, "permute") == 0 || strcmp(inst_str, "simd_permute") == 0)
	{
		uint16_t result = 0;
		uint16_t inst = 0;

		// load
		if (strcmp(inst_str, "load") == 0)
		{
			inst = 40960;
			result = inst | addr;
		}

		else if (strcmp(inst_str, "permute") == 0)
		{
			inst = 34816;
			result = inst | addr;
		}

		else if (strcmp(inst_str, "simd_permute") == 0)
		{
			inst = 34816 + 1024;
			result = inst | addr;
		}

		return result;
	}

	else
	{
		uint16_t inst = 0;

		// xor
		if (strcmp(inst_str, "xor") == 0)
		{
			inst = 8192;
		}

		else if (strcmp(inst_str, "simd_xor") == 0)
		{
			inst = 8192 + 1024;
		}

		// pxor
		else if (strcmp(inst_str, "pxor") == 0)
		{
			inst = 24576;
		}

		else if (strcmp(inst_str, "simd_pxor") == 0)
		{
			inst = 24576 + 1024;
		}

		// store
		else if (strcmp(inst_str, "store") == 0)
		{
			inst = 4096;
		}

		else if (strcmp(inst_str, "simd_store") == 0)
		{
			inst = 4096 + 1024;
		}

		// pstore
		else if (strcmp(inst_str, "pstore") == 0)
		{
			inst = 20480;
		}

		else if (strcmp(inst_str, "simd_pstore") == 0)
		{
			inst = 20480 + 1024;
		}

		// move
		else if (strcmp(inst_str, "move") == 0)
		{
			inst = 2048;
		}

		else if (strcmp(inst_str, "simd_move") == 0)
		{
			inst = 2048 + 1024;
		}

		// pmove
		else if (strcmp(inst_str, "pmove") == 0)
		{
			inst = 18432;
		}

		else if (strcmp(inst_str, "simd_pmove") == 0)
		{
			inst = 18432 + 1024;
		}

		// last
		else if (strcmp(inst_str, "last") == 0)
		{
			inst = 256;
		}

		// nop
		else if (strcmp(inst_str, "nop") == 0)
		{
			inst = 0;
		}

		else
		{
			printf("error");
		}

		return inst;
	}
}

void hdc_setup(void)
{
	int fd0, fd1, dmaf, topf;

	if ((fd0 = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		ssize_t done = read(fd0, attr, 1024);
		if (done < 0)
		{
			perror("Failed: read /sys/class/u-dma-buf/udmabuf0/phys_addr");
		}
		sscanf(attr, "%lx", &src_phys);
		close(fd0);
	}

	if ((fd0 = open("/sys/class/u-dma-buf/udmabuf1/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		ssize_t done = read(fd0, attr, 1024);
		if (done < 0)
		{
			perror("Failed: read /sys/class/u-dma-buf/udmabuf1/phys_addr");
		}
		sscanf(attr, "%lx", &dst_phys);
		close(fd0);
	}

	if ((fd0 = open("/dev/udmabuf0", O_RDWR)) < 0)
	{
		perror("Failed: open /dev/udmabuf0");
		return;
	}
	if ((fd1 = open("/dev/udmabuf1", O_RDWR)) < 0)
	{
		perror("Failed: open /dev/udmabuf1");
		return;
	}
	if ((dmaf = open("/dev/uio0", O_RDWR | O_SYNC)) < 0)
	{
		perror("Falied: open /dev/uio0");
		return;
	}
	if ((topf = open("/dev/uio1", O_RDWR | O_SYNC)) < 0)
	{
		perror("Failed: open /dev/uio1");
		return;
	}

	top = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, topf, 0);
	if (top == MAP_FAILED)
	{
		perror("mmap top");
		close(topf);
		return;
	}

	dma = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, dmaf, 0);
	if (dma == MAP_FAILED)
	{
		perror("mmap dma");
		close(dmaf);
		return;
	}

	src = (uint16_t *)mmap(NULL, 0x1DCD6500, PROT_READ | PROT_WRITE, MAP_SHARED, fd0, 0);
	if (src == MAP_FAILED)
	{
		perror("mmap src");
		close(fd0);
		return;
	}

	dst = (int *)mmap(NULL, 0x3D0900, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
	if (dst == MAP_FAILED)
	{
		perror("mmap dst");
		close(fd1);
		return;
	}
}

void hdc_print(void)
{
	printf("%d\n", SEND_NUM);
}

void hdc_make_imem(const int RANNUM)
{
	// reset_flag
	top[0x02] = 1;

	// item_memory_num (乱数の数)
	top[0x01] = RANNUM - 1;

	// gen <- 1;
	top[0x00] = 1;

	// 乱数生成終了を待つ
	while (top[0x00] & 0x1)
		;
}

void hdc_dma_reset(void)
{
	// dma reset
	dma[0xc] = 4;
	dma[0x00] = 4;
	while (dma[0x00] & 0x4)
		;
}

void hdc_init(const int N)
{
	SEND_NUM = N;
}

void hdc_start(void)
{
	// run <- 1;
	top[0x00] = 2;
}

void hdc_compute(void)
{
	// AXI DMA 送信の設定（UIO経由）
	dma[0x00] = 1;
	dma[0x6] = src_phys;
	dma[0xa] = SEND_NUM * 2; // 16ビットがsend_num個

	// 受信設定
	// 送信チャネルの設定前に受信チャネルを設定すると変になるっぽい
	dma[0xc] = 1;
	dma[0x12] = dst_phys;
	dma[0x16] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

	// 演算終了を待つ
	while ((dma[0xd] & 0x1000) != 0x1000)
		;

	hdc_dma_reset();
}

void hdc_finish(void)
{
	// run <- 0;
	top[0x00] = 0;

	// reset_flag
	top[0x02] = 0;
}

// =========================================================================================

void hdc_nop(void)
{
	src[SEND_NUM++] = 0;
}

void hdc_nop_core(void)
{
	for (int i = 0; i < 16; i++)
	{
		hdc_nop();
	}
}

// =========================================================================================

void hdc_load(uint16_t addr)
{
	src[SEND_NUM++] = 40960 | addr;
}

void hdc_load_core(uint16_t core_num, uint16_t addr_array[core_num])
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_load(addr_array[i]);
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}

void hdc_load_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num])
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_load_core(core_num, addr_array[k]);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

// =========================================================================================

void hdc_store(void)
{
	src[SEND_NUM++] = 4096;
}

void hdc_store_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_store();
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}

void hdc_store_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_store_core(core_num);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

void hdc_simd_store_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM] = 5120;
		SEND_NUM += 16;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		SEND_NUM += 16;
	}
}

// =========================================================================================

void hdc_pstore(void)
{
	src[SEND_NUM++] = 20480;
}

void hdc_pstore_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_pstore();
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}

void hdc_pstore_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_pstore_core(core_num);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

void hdc_simd_pstore_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM] = 21504;
		SEND_NUM += 16;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		SEND_NUM += 16;
	}
}

// =========================================================================================

void hdc_move(void)
{
	src[SEND_NUM++] = 2048;
}

void hdc_move_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_move();
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}

void hdc_move_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_move_core(core_num);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

void hdc_simd_move_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM] = 3072;
		SEND_NUM += 16;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		SEND_NUM += 16;
	}
}

// =========================================================================================

void hdc_pmove(void)
{
	src[SEND_NUM++] = 18432;
}

void hdc_pmove_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_pmove();
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}

void hdc_pmove_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_pmove_core(core_num);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

void hdc_simd_pmove_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM] = 19456;
		SEND_NUM += 16;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		SEND_NUM += 16;
	}
}

// =========================================================================================

void hdc_permute(uint16_t permute_num)
{
	src[SEND_NUM++] = 34816 | permute_num;
}

void hdc_permute_core(uint16_t core_num, uint16_t permute_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_permute(permute_num);
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}

void hdc_permute_thread(uint16_t thread_num, uint16_t core_num, uint16_t permute_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_permute_core(core_num, permute_num);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

void hdc_simd_permute_thread(uint16_t thread_num, uint16_t core_num, uint16_t permute_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM] = 35840 | permute_num;
		SEND_NUM += 16;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		SEND_NUM += 16;
	}
}

// =========================================================================================

void hdc_xor(void)
{
	src[SEND_NUM++] = 8192;
}

void hdc_xor_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_xor();
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}

void hdc_xor_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_xor_core(core_num);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

void hdc_simd_xor_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM] = 9216;
		SEND_NUM += 16;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		SEND_NUM += 16;
	}
}

// =========================================================================================

void hdc_pxor(void)
{
	src[SEND_NUM++] = 24576;
}

void hdc_pxor_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_pxor();
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}

void hdc_pxor_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_pxor_core(core_num);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

void hdc_simd_pxor_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM] = 25600;
		SEND_NUM += 16;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		SEND_NUM += 16;
	}
}

// =========================================================================================

void hdc_last(void)
{
	src[SEND_NUM++] = 256;
}

void hdc_last_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_last();
	}
	for (int i = core_num; i < 16; i++)
	{
		hdc_nop();
	}
}