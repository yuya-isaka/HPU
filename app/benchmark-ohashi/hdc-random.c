
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

	// ランダム生成
	top[0x04 / 4] = 1023;
	top[0x00 / 4] = 1;
	while (top[0x00 / 4] & 0x1)
		;

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	clock_t end = clock();
	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n\n  time %lf[ms]\n", time);

	return 0;
}
