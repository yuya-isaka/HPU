
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint16_t
#include <string.h>
#include <fcntl.h>	  // open
#include <unistd.h>	  // read
#include <sys/mman.h> // mmap
#include <time.h>

// ------------------------------------------------------------------------------------------------

volatile int *top;
volatile int *dma;
volatile uint16_t *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

// ------------------------------------------------------------------------------------------------

// 簡易アセンブラ
// アドレスが必要か、命令コード、アドレス
uint16_t assemble(int addr_flag, unsigned int inst_num, uint16_t addr)
{
	if (addr_flag)
	{
		uint16_t result = 0;
		// load
		if (inst_num == 1)
		{
			uint16_t inst = 3 << 14;
			result = inst | addr;
		}
		// l.rshift
		else if (inst_num == 2)
		{
			uint16_t inst = 5 << 13;
			result = inst | addr;
		}
		// l.lshift
		else if (inst_num == 4)
		{
			uint16_t inst = 9 << 12;
			result = inst | addr;
		}
		// l.xor
		else if (inst_num == 6)
		{
			uint16_t inst = 17 << 11;
			result = inst | addr;
		}
		// wb.item
		else if (inst_num == 12)
		{
			uint16_t inst = 33 << 10;
			result = inst | addr;
		}
		else
		{
			printf("error");
		}
		return result;
	}
	else
	{
		uint16_t inst = 0;
		// rshift
		if (inst_num == 3)
		{
			inst = 1 << 14;
		}
		// lshift
		else if (inst_num == 5)
		{
			inst = 1 << 13;
		}
		// xor
		else if (inst_num == 7)
		{
			inst = 1 << 12;
		}
		// store
		else if (inst_num == 8)
		{
			inst = 1 << 11;
		}
		// last
		else if (inst_num == 9)
		{
			inst = 1 << 10;
		}
		// move
		else if (inst_num == 10)
		{
			inst = 1 << 9;
		}
		// wb
		else if (inst_num == 11)
		{
			inst = 1 << 8;
		}
		else
		{
			printf("error");
		}
		return inst;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	clock_t start = clock();
	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	int fd0, fd1, dmaf, topf;

	if ((fd0 = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		ssize_t done = read(fd0, attr, 1024);
		if (done < 0)
		{
			perror("  Failed: read /sys/class/u-dma-buf/udmabuf0/phys_addr");
			exit(1);
		}
		sscanf(attr, "%lx", &src_phys);
		close(fd0);
	}
	// printf("src_phys: %lx\n", src_phys);

	if ((fd0 = open("/sys/class/u-dma-buf/udmabuf1/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		ssize_t done = read(fd0, attr, 1024);
		if (done < 0)
		{
			perror("  Failed: read /sys/class/u-dma-buf/udmabuf1/phys_addr");
			exit(1);
		}
		sscanf(attr, "%lx", &dst_phys);
		close(fd0);
	}
	// printf("dst_phys: %lx\n", dst_phys);

	if ((fd0 = open("/dev/udmabuf0", O_RDWR)) < 0)
	{
		perror("  Failed: open /dev/udmabuf0");
		return 0;
	}
	if ((fd1 = open("/dev/udmabuf1", O_RDWR)) < 0)
	{
		perror("  Failed: open /dev/udmabuf1");
		return 0;
	}
	if ((dmaf = open("/dev/uio0", O_RDWR | O_SYNC)) < 0)
	{
		perror("  Falied: open /dev/uio0");
		return 0;
	}
	if ((topf = open("/dev/uio1", O_RDWR | O_SYNC)) < 0)
	{
		perror("  Failed: open /dev/uio1");
		return 0;
	}

	top = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, topf, 0);
	if (top == MAP_FAILED)
	{
		perror("  mmap top");
		close(topf);
		return 0;
	}
	dma = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, dmaf, 0);
	if (dma == MAP_FAILED)
	{
		perror("  mmap dma");
		close(dmaf);
		return 0;
	}
	// 500MB
	// もしかしたら8MBでいいのか。。。
	src = (uint16_t *)mmap(NULL, 0x1DCD6500, PROT_READ | PROT_WRITE, MAP_SHARED, fd0, 0);
	if (src == MAP_FAILED)
	{
		perror("  mmap src");
		close(fd0);
		return 0;
	}
	// 4MB
	dst = (int *)mmap(NULL, 0x3D0900, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
	if (dst == MAP_FAILED)
	{
		perror("  mmap dst");
		close(fd1);
		return 0;
	}

	// // ランダム生成
	// top[0x04 / 4] = 1023;
	// top[0x00 / 4] = 1;
	// while (top[0x00 / 4] & 0x1)
	// 	;

	// const int core_num = 16;

	// DMAリセット
	dma[0x30 / 4] = 4;
	dma[0x00 / 4] = 4;
	while (dma[0x00 / 4] & 0x4)
		;

	top[0x00 / 4] = 2;

	srand(10);

	int send_num = 0;
	const int trial_num = 50000000;

	// 一度流れる命令を決めて、それがひたすら実行される

	for (int i = 0; i < trial_num; i += 16)
	{

		for (int j = 0; j < 16; j++)
		{
			src[send_num++] = assemble(1, 2, rand() % 1024);
		}
		for (int j = 16; j < 64; j++)
		{
			src[send_num++] = 0;
		}

		for (int j = 0; j < 16; j++)
		{
			src[send_num++] = assemble(1, 6, rand() % 1024);
		}
		for (int j = 16; j < 64; j++)
		{
			src[send_num++] = 0;
		}

		// for (int j = 0; j < 16; j++)
		// {
		// 	src[send_num++] = assemble(0, 8, 0);
		// }
		// for (int j = 16; j < 64; j++)
		// {
		// 	src[send_num++] = 0;
		// }

		// if (num > 512)
		// {
		// 	uint16_t inst = assemble(1, 4, addr);
		// 	src[send_num++] = inst;
		// 	for (int j = 0; j < (1024 - num - 1); j++)
		// 	{
		// 		inst = assemble(0, 5, 0);
		// 		src[send_num++] = inst;
		// 	}
		// }
		// else
		// {
		// 	uint16_t inst = assemble(1, 2, addr);
		// 	src[send_num++] = inst;
		// 	for (int j = 0; j < (num - 1); j++)
		// 	{
		// 		inst = assemble(0, 3, 0);
		// 		src[send_num++] = inst;
		// 	}
		// }

		if (send_num >= 33000000)
		{
			// last命令
			for (int j = 0; j < 1; j++)
			{
				uint16_t inst = assemble(0, 9, 0);
				src[send_num++] = inst;
			}
			for (int i = 1; i < 64; i++)
			{
				src[send_num++] = 0;
			}

			dma[0x00 / 4] = 1;
			dma[0x18 / 4] = src_phys;
			dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

			dma[0x30 / 4] = 1;
			dma[0x48 / 4] = dst_phys;
			dma[0x58 / 4] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

			while ((dma[0x34 / 4] & 0x1000) != 0x1000)
				;

			dma[0x30 / 4] = 4;
			dma[0x00 / 4] = 4;
			while (dma[0x00 / 4] & 0x4)
				;

			send_num = 0;
		}
	}

	// last命令
	for (int j = 0; j < 1; j++)
	{
		uint16_t inst = assemble(0, 9, 0);
		src[send_num++] = inst;
	}
	for (int i = 1; i < 64; i++)
	{
		src[send_num++] = 0;
	}

	dma[0x00 / 4] = 1;
	dma[0x18 / 4] = src_phys;
	dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

	dma[0x30 / 4] = 1;
	dma[0x48 / 4] = dst_phys;
	dma[0x58 / 4] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

	while ((dma[0x34 / 4] & 0x1000) != 0x1000)
		;

	for (int j = 0; j < 32; j++)
	{
		printf("%u\n", dst[j]);
	}

	top[0x00 / 4] = 0;

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");
	clock_t end = clock();
	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n\n  time %lf[ms]\n", time);

	return 0;
}
