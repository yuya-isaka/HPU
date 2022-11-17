
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
// 10種類の命令
uint16_t assemble(const char inst_str[], uint16_t addr)
{
	if (strcmp(inst_str, "load") == 0 || strcmp(inst_str, "wbitem") == 0)
	{
		uint16_t result = 0;

		// load
		if (strcmp(inst_str, "load") == 0)
		{
			uint16_t inst = 49152;
			result = inst | addr;
		}

		// wb.item
		else if (strcmp(inst_str, "wbitem") == 0)
		{
			uint16_t inst = 40960;
			result = inst | addr;
		}

		return result;
	}

	else
	{
		uint16_t inst = 0;

		// rshift
		if (strcmp(inst_str, "rshift") == 0)
		{
			inst = 16384;
		}

		// lshift
		else if (strcmp(inst_str, "lshift") == 0)
		{
			inst = 8192;
		}

		// xor
		else if (strcmp(inst_str, "xor") == 0)
		{
			inst = 4096;
		}

		// store
		else if (strcmp(inst_str, "store") == 0)
		{
			inst = 2048;
		}

		// last
		else if (strcmp(inst_str, "last") == 0)
		{
			inst = 1024;
		}

		// move
		else if (strcmp(inst_str, "move") == 0)
		{
			inst = 512;
		}

		// wb
		else if (strcmp(inst_str, "wb") == 0)
		{
			inst = 256;
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
	// プログラム全体の時間
	clock_t start_program = clock();

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// 初期化の時間
	clock_t start = clock();

	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

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

	// ----------------------------------------------------------------------------------------------------------------------------------------------

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

	if ((dmaf = open("/dev/uio0", O_RDWR | O_SYNC)) < 0)
	{
		perror("  Falied: open /dev/uio0");
		return 0;
	}
	dma = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, dmaf, 0);
	if (dma == MAP_FAILED)
	{
		perror("  mmap dma");
		close(dmaf);
		return 0;
	}

	if ((fd0 = open("/dev/udmabuf0", O_RDWR)) < 0)
	{
		perror("  Failed: open /dev/udmabuf0");
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

	if ((fd1 = open("/dev/udmabuf1", O_RDWR)) < 0)
	{
		perror("  Failed: open /dev/udmabuf1");
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

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// ランダム生成
	top[0x04 / 4] = 511;
	top[0x00 / 4] = 1;
	while (top[0x00 / 4] & 0x1)
		;

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// DMAリセット
	dma[0x30 / 4] = 4;
	dma[0x00 / 4] = 4;
	while (dma[0x00 / 4] & 0x4)
		;

	srand(10);

	clock_t end = clock();
	double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("初期化時間（CPU）: %lf[ms]\n", time);

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// データ準備時間
	start = clock();

	const int core_num = 32;
	const int trial_num = 50000000;
	const int send_num_max = 33000000;

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	int addr1[core_num];
	int addr2[core_num];

	int send_num = 0;
	int send_num_array[100];
	int send_num_count = 0;
	int count = 0;

	for (int i = 0; i < trial_num; i += core_num)
	{

		for (int j = 0; j < core_num; j++)
		{
			addr1[j] = rand() % 512;
			addr2[j] = rand() % 512;
		}

		// ----------------------------------------------------------------------------------------------------------------------------------------------

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("load", addr1[j]);
			count++;
		}

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("move", 0);
			count++;
		}

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("load", addr2[j]);
			count++;
		}

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("xor", 0);
			count++;
		}

		// ----------------------------------------------------------------------------------------------------------------------------------------------

		if (count >= send_num_max)
		{
			// last命令
			for (int j = 0; j < core_num; j++)
			{
				uint16_t inst = assemble("last", 0);
				src[send_num++] = inst;
				count++;
			}
			send_num_array[send_num_count++] = count;
			count = 0;
		}
	}

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// last命令
	for (int j = 0; j < core_num; j++)
	{
		uint16_t inst = assemble("last", 0);
		src[send_num++] = inst;
		count++;
	}
	send_num_array[send_num_count++] = count;

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("データ準備時間（CPU）: %lf[ms]\n", time);

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// 計算時間（アクセラレータ）
	start = clock();

	top[0x00 / 4] = 2;

	for (int i = 0; i < send_num_count; i++)
	{
		int send_num_tmp = send_num_array[i];

		dma[0x00 / 4] = 1;
		dma[0x18 / 4] = src_phys;
		dma[0x28 / 4] = send_num_tmp * 2; // 16ビットがsend_num個

		dma[0x30 / 4] = 1;
		dma[0x48 / 4] = dst_phys;
		dma[0x58 / 4] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

		while ((dma[0x34 / 4] & 0x1000) != 0x1000)
			;

		dma[0x30 / 4] = 4;
		dma[0x00 / 4] = 4;
		while (dma[0x00 / 4] & 0x4)
			;

		src_phys += send_num_tmp * 2;
	}

	top[0x00 / 4] = 0;

	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("計算時間（アクセラレータ）: %lf[ms]\n", time);

	for (int j = 0; j < 32; j++)
	{
		printf("%u\n", dst[j]);
	}

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	end = clock();
	time = ((double)(end - start_program)) / CLOCKS_PER_SEC * 1000.0;
	printf("プログラム時間（CPU＋アクセラレータ）: %lf[ms]\n", time);

	return 0;
}
