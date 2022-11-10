
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint16_t
#include <string.h>
#include <fcntl.h>	  // open
#include <unistd.h>	  // read
#include <sys/mman.h> // mmap
#include <time.h>

volatile int *top;
volatile int *dma;
volatile uint16_t *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

// --------------------------------------- メモリリークチェック、デストラクター -------------------------

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }

// ------------------------------------------------------------------------------------------------

// 2次元配列生成
void makeArray(uint16_t ***a, const int y, const int x)
{
	*a = (uint16_t **)calloc(y, sizeof(uint16_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint16_t *)calloc(x, sizeof(uint16_t));
	}
}

// 2次元配列解放
void freeArray(uint16_t ***a, const int y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

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
	top[0x04 / 4] = 26;
	top[0x00 / 4] = 1;
	while (top[0x00 / 4] & 0x1)
		;

	// ---------------------------------------------
	uint16_t **src_tmp;
	uint16_t **ascii_array;
	const int bus_width = 1024;
	const int instruction_bit = 16;
	const int train_num = 2;
	// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	const int ngram = 3;
	const int core_num = 2;
	const int instruction_num = 9;
	const int majority_addr = 26;
	int all_ngram = 0;
	int even = 0;
	// -------------------------------------------

	// DMAリセット
	for (int l = 0; l < train_num; l++)
	{

		dma[0x30 / 4] = 4;
		dma[0x00 / 4] = 4;
		while (dma[0x00 / 4] & 0x4)
			;

		const char *path = train_path[l];
		FILE *file;
		file = fopen(path, "r");
		if (file == NULL)
		{
			perror("  Failed: open file");
			exit(1);
		}
		int ch;
		size_t num = 0;
		// 1行を前提
		while ((ch = fgetc(file)) != EOF)
		{
			num++;
		}
		printf("EOF: %d\n", EOF); // EOFは全て-1
		fseek(file, 0, SEEK_SET);
		char *content = (char *)calloc(num, sizeof(char));
		size_t done = fread(content, sizeof(char), num, file);
		if (done < num)
		{
			perror("  Failed: fread file");
			exit(1);
		}
		fclose(file);
		all_ngram = strlen(content) - ngram + 1;
		even = all_ngram % 2 == 0;
		// printf("content: %s\n", content); // myname...
		printf("all_ngram: %d\n", all_ngram);
		printf("even: %d\n", even);

		int all_instruction = all_ngram / core_num;
		if (all_ngram % core_num != 0)
		{
			all_instruction++;
		}
		all_instruction *= instruction_num;
		printf("all_instruction: %d\n", all_instruction);

		makeArray(&src_tmp, core_num, all_instruction);
		makeArray(&ascii_array, all_ngram, ngram);
		for (int i = 0; i < core_num; i++)
		{
			for (int j = 0; j < all_instruction; j++)
			{
				src_tmp[i][j] = 0;
			}
		}
		for (int i = 0; i < all_ngram; i++)
		{
			for (int j = 0; j < ngram; j++)
			{
				ascii_array[i][j] = (unsigned char)(content[i + j]) - 97;
			}
		}

		top[0x00 / 4] = 2;

		// ---------------------------------------------------
		// ↓ コード---------------------------------------------

		int instruction = 0;
		int core = 0;
		for (int i = 0; i < all_ngram; i++)
		{
			// 1 load
			uint16_t addr = ascii_array[i][0];
			uint16_t inst = assemble(1, 1, addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 10 move
			inst = assemble(0, 10, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 2 l.rshift
			addr = ascii_array[i][1];
			inst = assemble(1, 2, addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 7 xor
			inst = assemble(0, 7, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 10 move
			inst = assemble(0, 10, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 2 l.rshift
			addr = ascii_array[i][2];
			inst = assemble(1, 2, addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 3 rshift
			inst = assemble(0, 3, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 7 xor
			inst = assemble(0, 7, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 8 store
			inst = assemble(0, 8, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			if (core != (core_num - 1))
			{
				instruction -= instruction_num;
			}

			core = (core + 1) % core_num;
		}

		int send_num = 0;

		if (even)
		{
			// load
			for (int i = 0; i < (bus_width / instruction_bit); i++)
			{
				if (i == 0)
				{
					uint16_t addr = majority_addr;
					uint16_t inst = assemble(1, 1, addr);
					src[send_num] = inst;
				}
				else
				{
					src[send_num] = 0;
				}
				send_num++;
			}

			// store
			for (int i = 0; i < (bus_width / instruction_bit); i++)
			{
				if (i == 0)
				{
					uint16_t inst = assemble(0, 8, 0);
					src[send_num] = inst;
				}
				else
				{
					src[send_num] = 0;
				}
				send_num++;
			}
		}

		// デバッグ
		// int debug_flag = 0;
		// int debug_mass = 1;
		// for (int j = 0; j < all_instruction; j++)
		// {
		// 	if (debug_flag == 0)
		// 	{
		// 		printf("命令の塊%d\n", debug_mass);
		// 		debug_mass++;
		// 	}
		// 	for (int i = 0; i < core_num; i++)
		// 	{
		// 		printf("%7d ", src_tmp[i][j]);
		// 	}
		// 	debug_flag++;
		// 	if (debug_flag == instruction_num)
		// 	{
		// 		printf("\n");
		// 		debug_flag = 0;
		// 	}
		// 	printf("\n");
		// }

		for (int j = 0; j < all_instruction; j++)
		{

			for (int i = 0; i < core_num; i++)
			{
				src[send_num] = src_tmp[i][j];
				send_num++;
			}
			for (int i = core_num; i < (bus_width / instruction_bit); i++)
			{
				src[send_num] = 0;
				send_num++;
			}
			// printf("%d\n", send_num);

			// 最後じゃないかつ値を超えてたら
			// 2億5000万が限界
			if (j != (all_instruction - 1) && send_num >= 30000000)
			{

				printf("------------DMA再発行-----------\n");

				// last命令
				for (int i = 0; i < 1; i++)
				{
					uint16_t inst = assemble(0, 9, 0);
					src[send_num] = inst;
					send_num++;
				}
				for (int i = 1; i < (bus_width / instruction_bit); i++)
				{
					src[send_num] = 0;
					send_num++;
				}

				dma[0x00 / 4] = 1;
				dma[0x18 / 4] = src_phys;
				dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

				dma[0x30 / 4] = 1;
				dma[0x48 / 4] = dst_phys;
				dma[0x58 / 4] = (bus_width / 32) * 4; // 32個 * 4バイト = 128バイト = 1024ビット

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
		for (int i = 0; i < 1; i++)
		{
			uint16_t inst = assemble(0, 9, 0);
			src[send_num] = inst;
			send_num++;
		}
		for (int i = 1; i < (bus_width / instruction_bit); i++)
		{
			src[send_num] = 0;
			send_num++;
		}

		// ↑ コード---------------------------------------------
		// ---------------------------------------------------

		dma[0x00 / 4] = 1;
		dma[0x18 / 4] = src_phys;
		dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

		dma[0x30 / 4] = 1;
		dma[0x48 / 4] = dst_phys;
		dma[0x58 / 4] = (bus_width / 32) * 4; // 32個 * 4バイト = 128バイト = 1024ビット

		while ((dma[0x34 / 4] & 0x1000) != 0x1000)
			;

		for (int j = 0; j < (1024 / 32); j++)
		{
			printf("%u\n", dst[j]);
		}

		top[0x00 / 4] = 0;

		freeArray(&ascii_array, ngram);
		freeArray(&src_tmp, core_num);

		printf("\n");
	}

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");
	clock_t end = clock();
	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("\n\n  time %lf[ms]\n", time);

	return 0;
}
