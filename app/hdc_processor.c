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
	if (strcmp(inst_str, "load") == 0 || strcmp(inst_str, "wbitem") == 0 || strcmp(inst_str, "pwbitem") == 0 || strcmp(inst_str, "permute") == 0 || strcmp(inst_str, "simd_permute") == 0)
	{
		uint16_t result = 0;
		uint16_t inst = 0;

		// load
		if (strcmp(inst_str, "load") == 0)
		{
			inst = 40960;
			result = inst | addr;
		}

		// wb.item
		else if (strcmp(inst_str, "wbitem") == 0)
		{
			inst = 36864;
			result = inst | addr;
		}

		else if (strcmp(inst_str, "pwbitem") == 0)
		{
			inst = 53248;
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
		else if (strcmp(inst_str, "wb") == 0)
		{
			inst = 512;
		}

		// wb
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

// // 簡易アセンブラ
// // 10種類の命令
// uint16_t hdc_assemble(const char inst_str[], uint16_t addr)
// {
// 	if (inst_str[0] == 'l')
// 	{
// 		if (inst_str[1] == 'o')
// 		{
// 			uint16_t inst = 40960;
// 			uint16_t result = inst | addr;
// 			return result;
// 		}
// 		else if (inst_str[1] == 'a')
// 		{
// 			return 512;
// 		}
// 	}
// 	else if (inst_str[0] == 'p')
// 	{
// 		if (inst_str[1] == 'e')
// 		{
// 			uint16_t inst = 34816;
// 			uint16_t result = inst | addr;
// 			return result;
// 		}
// 		else if (inst_str[1] == 'w')
// 		{
// 			uint16_t inst = 53248;
// 			uint16_t result = inst | addr;
// 			return result;
// 		}
// 		else if (inst_str[1] == 'x')
// 		{

// 			return 24576;
// 		}
// 		else if (inst_str[1] == 's')
// 		{

// 			return 20480;
// 		}
// 		else if (inst_str[1] == 'm')
// 		{

// 			return 18432;
// 		}
// 	}
// 	else if (inst_str[0] == 'x')
// 	{
// 		return 8192;
// 	}
// 	else if (inst_str[0] == 's')
// 	{
// 		return 4096;
// 	}
// 	else if (inst_str[0] == 'm')
// 	{
// 		return 2048;
// 	}
// 	else if (strcmp(inst_str, "wb") == 0)
// 	{
// 		return 1024;
// 	}
// 	else if (strcmp(inst_str, "wbitem") == 0)
// 	{

// 		uint16_t inst = 36864;
// 		uint16_t result = inst | addr;
// 		return result;
// 	}
// 	else if (inst_str[0] == 'n')
// 	{
// 		return 0;
// 	}
// 	else
// 	{
// 		printf("error");
// 	}

// 	// if (strcmp(inst_str, "load") == 0 || strcmp(inst_str, "wbitem") == 0 || strcmp(inst_str, "pwbitem") == 0 || strcmp(inst_str, "permute") == 0)
// 	// {
// 	// 	uint16_t result = 0;
// 	// 	uint16_t inst = 0;

// 	// 	// load
// 	// 	if (strcmp(inst_str, "load") == 0)
// 	// 	{
// 	// 		inst = 40960;
// 	// 		result = inst | addr;
// 	// 	}

// 	// 	// wb.item
// 	// 	else if (strcmp(inst_str, "wbitem") == 0)
// 	// 	{
// 	// 		inst = 36864;
// 	// 		result = inst | addr;
// 	// 	}

// 	// 	else if (strcmp(inst_str, "pwbitem") == 0)
// 	// 	{
// 	// 		inst = 53248;
// 	// 		result = inst | addr;
// 	// 	}

// 	// 	else if (strcmp(inst_str, "permute") == 0)
// 	// 	{
// 	// 		inst = 34816;
// 	// 		result = inst | addr;
// 	// 	}

// 	// 	return result;
// 	// }

// 	// else
// 	// {
// 	// 	uint16_t inst = 0;

// 	// 	// xor
// 	// 	if (strcmp(inst_str, "xor") == 0)
// 	// 	{
// 	// 		inst = 8192;
// 	// 	}

// 	// 	// pxor
// 	// 	if (strcmp(inst_str, "pxor") == 0)
// 	// 	{
// 	// 		inst = 24576;
// 	// 	}

// 	// 	// store
// 	// 	else if (strcmp(inst_str, "store") == 0)
// 	// 	{
// 	// 		inst = 4096;
// 	// 	}

// 	// 	// pstore
// 	// 	else if (strcmp(inst_str, "pstore") == 0)
// 	// 	{
// 	// 		inst = 20480;
// 	// 	}

// 	// 	// move
// 	// 	else if (strcmp(inst_str, "move") == 0)
// 	// 	{
// 	// 		inst = 2048;
// 	// 	}

// 	// 	// pmove
// 	// 	else if (strcmp(inst_str, "pmove") == 0)
// 	// 	{
// 	// 		inst = 18432;
// 	// 	}

// 	// 	// wb
// 	// 	else if (strcmp(inst_str, "wb") == 0)
// 	// 	{
// 	// 		inst = 1024;
// 	// 	}

// 	// 	// last
// 	// 	else if (strcmp(inst_str, "last") == 0)
// 	// 	{
// 	// 		inst = 512;
// 	// 	}

// 	// 	// nop
// 	// 	else if (strcmp(inst_str, "nop") == 0)
// 	// 	{
// 	// 		inst = 0;
// 	// 	}

// 	// 	else
// 	// 	{
// 	// 		printf("error");
// 	// 	}

// 	// 	return inst;
// 	// }
// }

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

	src = (uint16_t *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd0, 0);
	if (src == MAP_FAILED)
	{
		perror("mmap src");
		close(fd0);
		return;
	}

	dst = (int *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
	if (dst == MAP_FAILED)
	{
		perror("mmap dst");
		close(fd1);
		return;
	}
}

void hdc_make_imem(const int RANNUM)
{
	// reset_flag
	top[0x08 / 4] = 1;

	// item_memory_num (乱数の数)
	top[0x04 / 4] = RANNUM - 1;

	// gen <- 1;
	top[0x00 / 4] = 1;

	// 乱数生成終了を待つ
	while (top[0x00 / 4] & 0x1)
		;
}

void hdc_dma_reset(void)
{
	// dma reset
	dma[0x30 / 4] = 4;
	dma[0x00 / 4] = 4;
	while (dma[0x00 / 4] & 0x4)
		;
}

void hdc_init(const int N)
{
	SEND_NUM = N;
}

void hdc_start(void)
{
	// run <- 1;
	top[0x00 / 4] = 2;
}

void hdc_compute(void)
{
	// AXI DMA 送信の設定（UIO経由）
	dma[0x00 / 4] = 1;
	dma[0x18 / 4] = src_phys;
	dma[0x28 / 4] = SEND_NUM * 2; // 16ビットがsend_num個

	// 受信設定
	// 送信チャネルの設定前に受信チャネルを設定すると変になるっぽい
	dma[0x30 / 4] = 1;
	dma[0x48 / 4] = dst_phys;
	dma[0x58 / 4] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

	// 演算終了を待つ
	while ((dma[0x34 / 4] & 0x1000) != 0x1000)
		;
}

void hdc_finish(void)
{
	// run <- 0;
	top[0x00 / 4] = 0;

	// reset_flag
	top[0x08 / 4] = 0;
}

// =========================================================================================

void hdc_nop(void)
{
	src[SEND_NUM++] = 0;
}

void hdc_nop_core(void)
{
	for (int i = 0; i < (BUS_WIDTH / 16); i++)
	{
		hdc_nop();
	}
}

// =========================================================================================

void hdc_load(uint16_t addr)
{
	src[SEND_NUM++] = hdc_assemble("load", addr);
}

void hdc_load_core(uint16_t core_num, uint16_t addr_array[core_num])
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_load(addr_array[i]);
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
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

void hdc_wbitem(uint16_t addr)
{
	src[SEND_NUM++] = hdc_assemble("wbitem", addr);
}

void hdc_wbitem_core(uint16_t core_num, uint16_t addr_array[core_num])
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_wbitem(addr_array[i]);
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
	{
		hdc_nop();
	}
}

void hdc_wbitem_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num])
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_wbitem_core(core_num, addr_array[k]);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

// =========================================================================================

void hdc_pwbitem(uint16_t addr)
{
	src[SEND_NUM++] = hdc_assemble("pwbitem", addr);
}

void hdc_pwbitem_core(uint16_t core_num, uint16_t addr_array[core_num])
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_pwbitem(addr_array[i]);
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
	{
		hdc_nop();
	}
}

void hdc_pwbitem_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num])
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_pwbitem_core(core_num, addr_array[k]);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

// =========================================================================================

void hdc_store(void)
{
	src[SEND_NUM++] = hdc_assemble("store", 0);
}

void hdc_store_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_store();
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
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

// =========================================================================================

void hdc_pstore(void)
{
	src[SEND_NUM++] = hdc_assemble("pstore", 0);
}

void hdc_pstore_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_pstore();
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
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

// =========================================================================================

void hdc_move(void)
{
	src[SEND_NUM++] = hdc_assemble("move", 0);
}

void hdc_move_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_move();
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
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

// =========================================================================================

void hdc_pmove(void)
{
	src[SEND_NUM++] = hdc_assemble("pmove", 0);
}

void hdc_pmove_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_pmove();
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
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

// =========================================================================================

void hdc_permute(uint16_t permute_num)
{
	src[SEND_NUM++] = hdc_assemble("permute", permute_num);
}

void hdc_permute_core(uint16_t core_num, uint16_t permute_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_permute(permute_num);
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
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

// =========================================================================================

void hdc_xor(void)
{
	src[SEND_NUM++] = hdc_assemble("xor", 0);
}

void hdc_xor_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_xor();
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
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

// =========================================================================================

void hdc_pxor(void)
{
	src[SEND_NUM++] = hdc_assemble("pxor", 0);
}

void hdc_pxor_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_pxor();
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
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

// =========================================================================================

void hdc_wb(void)
{
	src[SEND_NUM++] = hdc_assemble("wb", 0);
}

void hdc_wb_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_wb();
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
	{
		hdc_nop();
	}
}

void hdc_wb_thread(uint16_t thread_num, uint16_t core_num)
{
	for (int k = 0; k < thread_num; k++)
	{
		hdc_wb_core(core_num);
	}
	for (int k = thread_num; k < THREADS_NUM; k++)
	{
		hdc_nop_core();
	}
}

// =========================================================================================

void hdc_last(void)
{
	src[SEND_NUM++] = hdc_assemble("last", 0);
}

void hdc_last_core(uint16_t core_num)
{
	for (int i = 0; i < core_num; i++)
	{
		hdc_last();
	}
	for (int i = core_num; i < (BUS_WIDTH / 16); i++)
	{
		hdc_nop();
	}
}