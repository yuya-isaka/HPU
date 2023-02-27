// include
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdint.h>
#include "hdc_processor.h"

unsigned long src_phys;
unsigned long dst_phys;

volatile int *top;
volatile int *dma;
uint32_t *src;
int *dst;

// DMAで送るバイト数
int SEND_NUM = 0;

void hdc_print(void)
{
	printf("SEND_NUM: %d\n", SEND_NUM);
}

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
	// 64MB
	src = (uint32_t *)mmap(NULL, 0x4000000, PROT_READ | PROT_WRITE, MAP_SHARED, udmabuf0, 0);
	if (src == MAP_FAILED)
	{
		perror("mmap src");
		close(udmabuf0);
		return;
	}
	// 512KB
	dst = (int *)mmap(NULL, 0x80000, PROT_READ | PROT_WRITE, MAP_SHARED, udmabuf1, 0);
	if (dst == MAP_FAILED)
	{
		perror("mmap dst");
		close(udmabuf1);
		return;
	}
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
	top[0x00] = 1;
}

// DMA送信開始 & 計算開始 & 受信完了
void hdc_compute(void)
{
	// AXI DMA 送信設定（UIO経由）
	dma[0x00] = 1;
	dma[0x6] = src_phys;
	dma[0xa] = SEND_NUM * 4; // 32ビット命令の数がSEND_NUMなので、バイト数は * 4する

	// AXI DMA 受信設定 (UIO経由)
	dma[0xc] = 1;
	dma[0x12] = dst_phys;
	dma[0x16] = 128; // 128バイト = 1024ビット

	// 演算終了を待つ
	while ((dma[0xd] & 0x1000) != 0x1000)
		;
}

// DMA送信開始 & 計算開始
void hdc_compute_only(void)
{
	// AXI DMA 送信設定（UIO経由）
	dma[0x00] = 1;
	dma[0x6] = src_phys;
	dma[0xa] = SEND_NUM * 4;

	// 送信終了
	while ((dma[0x1] & 0x1000) != 0x1000)
		;
}

// HDCプロセッサ停止 & アイテムメモリ初期化
void hdc_finish(void)
{
	// run <- 0;
	top[0x00] = 0;
}

// COM =========================================================================================

void hdc_com_start(void)
{
	hdc_init(0);

	// com <- 1;
	top[0x00] = 2;
}

void hdc_com_start_continue(void)
{
	hdc_init(0);

	// com <- 2;
	// run <- 1;
	top[0x00] = 3;
}

void hdc_com_gen(uint32_t num)
{
	src[SEND_NUM++] = num;
}

// Nop =========================================================================================

void hdc_nop(void)
{
	src[SEND_NUM++] = 0;
}

// load.1 =========================================================================================

void hdc_load_1(uint32_t addr_array[THREADS_NUM])
{
	src[SEND_NUM++] = 2147487744 | addr_array[0];
	src[SEND_NUM++] = 2147487744 | addr_array[1];
	src[SEND_NUM++] = 2147487744 | addr_array[2];
	src[SEND_NUM++] = 2147487744 | addr_array[3];
	src[SEND_NUM++] = 2147487744 | addr_array[4];
}

void hdc_load_1_thread(uint32_t thread_num, uint32_t addr_array[thread_num])
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 2147487744 | addr_array[k];
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// xor.121 =========================================================================================

void hdc_bind_121(void)
{
	src[SEND_NUM++] = 2147491840;
	src[SEND_NUM++] = 2147491840;
	src[SEND_NUM++] = 2147491840;
	src[SEND_NUM++] = 2147491840;
	src[SEND_NUM++] = 2147491840;
}

void hdc_bind_121_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 2147491840;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// xor.p21 =========================================================================================

void hdc_bind_p21(void)
{
	src[SEND_NUM++] = 2147500032;
	src[SEND_NUM++] = 2147500032;
	src[SEND_NUM++] = 2147500032;
	src[SEND_NUM++] = 2147500032;
	src[SEND_NUM++] = 2147500032;
}

void hdc_bind_p21_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 2147500032;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// xor.p11 =========================================================================================

void hdc_bind_p11(void)
{
	src[SEND_NUM++] = 2147516416;
	src[SEND_NUM++] = 2147516416;
	src[SEND_NUM++] = 2147516416;
	src[SEND_NUM++] = 2147516416;
	src[SEND_NUM++] = 2147516416;
}

void hdc_bind_p11_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 2147516416;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// move.21 =========================================================================================

void hdc_move_21(void)
{
	src[SEND_NUM++] = 2147549184;
	src[SEND_NUM++] = 2147549184;
	src[SEND_NUM++] = 2147549184;
	src[SEND_NUM++] = 2147549184;
	src[SEND_NUM++] = 2147549184;
}

void hdc_move_21_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 2147549184;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// move.p1 =========================================================================================

void hdc_move_p1(void)
{
	src[SEND_NUM++] = 2147614720;
	src[SEND_NUM++] = 2147614720;
	src[SEND_NUM++] = 2147614720;
	src[SEND_NUM++] = 2147614720;
	src[SEND_NUM++] = 2147614720;
}

void hdc_move_p1_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 2147614720;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// load.2 =========================================================================================

void hdc_load_2(uint32_t addr_array[THREADS_NUM])
{
	src[SEND_NUM++] = 1073745920 | addr_array[0];
	src[SEND_NUM++] = 1073745920 | addr_array[1];
	src[SEND_NUM++] = 1073745920 | addr_array[2];
	src[SEND_NUM++] = 1073745920 | addr_array[3];
	src[SEND_NUM++] = 1073745920 | addr_array[4];
}

void hdc_load_2_thread(uint32_t thread_num, uint32_t addr_array[thread_num])
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 1073745920 | addr_array[k];
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// xor.122 =========================================================================================

void hdc_bind_122(void)
{
	src[SEND_NUM++] = 1073750016;
	src[SEND_NUM++] = 1073750016;
	src[SEND_NUM++] = 1073750016;
	src[SEND_NUM++] = 1073750016;
	src[SEND_NUM++] = 1073750016;
}

void hdc_bind_122_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 1073750016;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// xor.p22 =========================================================================================

void hdc_bind_p22(void)
{
	src[SEND_NUM++] = 1073758208;
	src[SEND_NUM++] = 1073758208;
	src[SEND_NUM++] = 1073758208;
	src[SEND_NUM++] = 1073758208;
	src[SEND_NUM++] = 1073758208;
}

void hdc_bind_p22_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 1073758208;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// xor.p12 =========================================================================================

void hdc_bind_p12(void)
{
	src[SEND_NUM++] = 1073774592;
	src[SEND_NUM++] = 1073774592;
	src[SEND_NUM++] = 1073774592;
	src[SEND_NUM++] = 1073774592;
	src[SEND_NUM++] = 1073774592;
}

void hdc_bind_p12_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 1073774592;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// move.12 =========================================================================================

void hdc_move_12(void)
{
	src[SEND_NUM++] = 1073807360;
	src[SEND_NUM++] = 1073807360;
	src[SEND_NUM++] = 1073807360;
	src[SEND_NUM++] = 1073807360;
	src[SEND_NUM++] = 1073807360;
}

void hdc_move_12_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 1073807360;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// move.p2 =========================================================================================

void hdc_move_p2(void)
{
	src[SEND_NUM++] = 1073872896;
	src[SEND_NUM++] = 1073872896;
	src[SEND_NUM++] = 1073872896;
	src[SEND_NUM++] = 1073872896;
	src[SEND_NUM++] = 1073872896;
}

void hdc_move_p2_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 1073872896;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// permute_2 =========================================================================================

void hdc_permute_2(uint32_t permute_num)
{
	src[SEND_NUM++] = 536875008 | permute_num;
	src[SEND_NUM++] = 536875008 | permute_num;
	src[SEND_NUM++] = 536875008 | permute_num;
	src[SEND_NUM++] = 536875008 | permute_num;
	src[SEND_NUM++] = 536875008 | permute_num;
}

void hdc_permute_2_thread(uint32_t thread_num, uint32_t permute_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 536875008 | permute_num;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// permute_1 =========================================================================================

void hdc_permute_1(uint32_t permute_num)
{
	src[SEND_NUM++] = 536870912 | permute_num;
	src[SEND_NUM++] = 536870912 | permute_num;
	src[SEND_NUM++] = 536870912 | permute_num;
	src[SEND_NUM++] = 536870912 | permute_num;
	src[SEND_NUM++] = 536870912 | permute_num;
}

void hdc_permute_1_thread(uint32_t thread_num, uint32_t permute_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 536870912 | permute_num;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// permute_2_単体 =========================================================================================

void hdc_permute_2_unit(uint32_t permute_num)
{
	src[SEND_NUM++] = 536875008 | permute_num;
}

// permute_1_単体 =========================================================================================

void hdc_permute_1_unit(uint32_t permute_num)
{
	src[SEND_NUM++] = 536870912 | permute_num;
}

// bound.2 =========================================================================================

void hdc_bound_2(void)
{
	src[SEND_NUM++] = 268439552;
	src[SEND_NUM++] = 268439552;
	src[SEND_NUM++] = 268439552;
	src[SEND_NUM++] = 268439552;
	src[SEND_NUM++] = 268439552;
}

void hdc_bound_2_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 268439552;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// bound.1 =========================================================================================

void hdc_bound_1(void)
{
	src[SEND_NUM++] = 268443648;
	src[SEND_NUM++] = 268443648;
	src[SEND_NUM++] = 268443648;
	src[SEND_NUM++] = 268443648;
	src[SEND_NUM++] = 268443648;
}

void hdc_bound_1_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 268443648;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// bound.p =========================================================================================

void hdc_bound_p(void)
{
	src[SEND_NUM++] = 268451840;
	src[SEND_NUM++] = 268451840;
	src[SEND_NUM++] = 268451840;
	src[SEND_NUM++] = 268451840;
	src[SEND_NUM++] = 268451840;
}

void hdc_bound_p_thread(uint32_t thread_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		src[SEND_NUM++] = 268451840;
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		src[SEND_NUM++] = 0;
	}
}

// last =========================================================================================

void hdc_last(void)
{
	src[SEND_NUM++] = 268468224;
}
