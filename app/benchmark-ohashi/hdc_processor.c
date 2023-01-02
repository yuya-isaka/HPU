// include
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdint.h>
#include "hdc_processor.h"

// DMAで送るバイト数
int SEND_NUM = 0;

// UIO, DMA メモリマップドIO設定
void hdc_setup(void)
{
	int udmabuf0, udmabuf1, uio0, uio1;

	// src_physにアドレス格納
	if ((udmabuf0 = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		ssize_t done = read(udmabuf0, attr, 1024);
		if (done < 0)
		{
			perror("Failed: read /sys/class/u-dma-buf/udmabuf0/phys_addr");
		}
		sscanf(attr, "%lx", &src_phys);
		close(udmabuf0);
	}

	// dst_physにアドレス格納
	if ((udmabuf1 = open("/sys/class/u-dma-buf/udmabuf1/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		ssize_t done = read(udmabuf1, attr, 1024);
		if (done < 0)
		{
			perror("Failed: read /sys/class/u-dma-buf/udmabuf1/phys_addr");
		}
		sscanf(attr, "%lx", &dst_phys);
		close(udmabuf1);
	}

	// ファイルオープン
	if ((udmabuf0 = open("/dev/udmabuf0", O_RDWR)) < 0)
	{
		perror("Failed: open /dev/udmabuf0");
		return;
	}
	if ((udmabuf1 = open("/dev/udmabuf1", O_RDWR)) < 0)
	{
		perror("Failed: open /dev/udmabuf1");
		return;
	}
	if ((uio0 = open("/dev/uio0", O_RDWR | O_SYNC)) < 0)
	{
		perror("Falied: open /dev/uio0");
		return;
	}
	if ((uio1 = open("/dev/uio1", O_RDWR | O_SYNC)) < 0)
	{
		perror("Failed: open /dev/uio1");
		return;
	}

	// mmap
	dma = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, uio0, 0);
	if (dma == MAP_FAILED)
	{
		perror("mmap dma");
		close(uio0);
		return;
	}
	top = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, uio1, 0);
	if (top == MAP_FAILED)
	{
		perror("mmap top");
		close(uio1);
		return;
	}
	src = (uint16_t *)mmap(NULL, 0x1DCD6500, PROT_READ | PROT_WRITE, MAP_SHARED, udmabuf0, 0);
	if (src == MAP_FAILED)
	{
		perror("mmap src");
		close(udmabuf0);
		return;
	}
	dst = (int *)mmap(NULL, 0x3D0900, PROT_READ | PROT_WRITE, MAP_SHARED, udmabuf1, 0);
	if (dst == MAP_FAILED)
	{
		perror("mmap dst");
		close(udmabuf1);
		return;
	}
}

// RANNUM数　アイテムメモリ生成
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

// DMAリセット
void hdc_dma_reset(void)
{
	dma[0xc] = 4;
	dma[0x00] = 4;
	while (dma[0x00] & 0x4)
		;
}

// SEND_NUM初期化 & DMAリセット
void hdc_init(const int N)
{
	SEND_NUM = N;
	hdc_dma_reset();
}

// HDCプロセッサ起動
void hdc_start(void)
{
	// run <- 1;
	top[0x00] = 2;
}

// DMA送信開始 & 計算開始
void hdc_compute(void)
{
	// AXI DMA 送信設定（UIO経由）
	dma[0x00] = 1;
	dma[0x6] = src_phys;
	dma[0xa] = SEND_NUM * 2; // 16ビット命令の数 * 2 = バイト数

	// AXI DMA 受信設定 (UIO経由)
	dma[0xc] = 1;
	dma[0x12] = dst_phys;
	dma[0x16] = 128; // 128バイト = 1024ビット

	// 演算終了を待つ
	while ((dma[0xd] & 0x1000) != 0x1000)
		;
}

// HDCプロセッサ停止 & アイテムメモリ初期化
void hdc_finish(void)
{
	// run <- 0;
	top[0x00] = 0;

	// reset_flag
	top[0x02] = 0;
}

// Nop =========================================================================================

void hdc_nop(void)
{
	src[SEND_NUM++] = 0;
}

// Load =========================================================================================

void hdc_load_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num])
{
	for (int k = 0; k < thread_num; k++)
	{
		for (int i = 0; i < core_num; i++)
		{
			src[SEND_NUM++] = 40960 | addr_array[k][i];
		}
		for (int i = core_num; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
}

// Store =========================================================================================

void hdc_store_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		for (int i = 0; i < core_num; i++)
		{
			src[SEND_NUM++] = 4096;
		}
		for (int i = core_num; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
}

void hdc_simd_store_thread(void)
{
	for (int k = 0; k < THREADS_NUM; k++)
	{
		src[SEND_NUM] = 5120;
		SEND_NUM += 16;
	}
}

// pstore =========================================================================================

void hdc_pstore_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		for (int i = 0; i < core_num; i++)
		{
			src[SEND_NUM++] = 20480;
		}
		for (int i = core_num; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
}

void hdc_simd_pstore_thread(void)
{
	for (int k = 0; k < THREADS_NUM; k++)
	{
		src[SEND_NUM] = 21504;
		SEND_NUM += 16;
	}
}

// move =========================================================================================

void hdc_move_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		for (int i = 0; i < core_num; i++)
		{
			src[SEND_NUM++] = 2048;
		}
		for (int i = core_num; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
}

void hdc_simd_move_thread(void)
{
	for (int k = 0; k < THREADS_NUM; k++)
	{
		src[SEND_NUM] = 3072;
		SEND_NUM += 16;
	}
}

// pmove =========================================================================================

void hdc_pmove_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		for (int i = 0; i < core_num; i++)
		{
			src[SEND_NUM++] = 18432;
		}
		for (int i = core_num; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
}

void hdc_simd_pmove_thread(void)
{
	for (int k = 0; k < THREADS_NUM; k++)
	{
		src[SEND_NUM] = 19456;
		SEND_NUM += 16;
	}
}

// permute =========================================================================================

void hdc_permute(uint16_t permute_num)
{
	src[SEND_NUM++] = 34816 | permute_num;
}

void hdc_permute_thread(uint16_t thread_num, uint16_t core_num, uint16_t permute_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		for (int i = 0; i < core_num; i++)
		{
			src[SEND_NUM++] = 34816 | permute_num;
		}
		for (int i = core_num; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
}

void hdc_simd_permute_thread(uint16_t permute_num)
{
	for (int k = 0; k < THREADS_NUM; k++)
	{
		src[SEND_NUM] = 35840 | permute_num;
		SEND_NUM += 16;
	}
}

// xor =========================================================================================

void hdc_xor_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		for (int i = 0; i < core_num; i++)
		{
			src[SEND_NUM++] = 8192;
		}
		for (int i = core_num; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
}

void hdc_simd_xor_thread(void)
{
	for (int k = 0; k < THREADS_NUM; k++)
	{
		src[SEND_NUM] = 9216;
		SEND_NUM += 16;
	}
}

// pxor =========================================================================================

void hdc_pxor_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		for (int i = 0; i < core_num; i++)
		{
			src[SEND_NUM++] = 24576;
		}
		for (int i = core_num; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			src[SEND_NUM++] = 0;
		}
	}
}

void hdc_simd_pxor_thread(void)
{
	for (int k = 0; k < THREADS_NUM; k++)
	{
		src[SEND_NUM] = 25600;
		SEND_NUM += 16;
	}
}

// last =========================================================================================

void hdc_last(void)
{
	src[SEND_NUM++] = 256;
	for (int i = 1; i < 16; i++)
	{
		src[SEND_NUM++] = 0;
	}
}