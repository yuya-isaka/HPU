
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
	top[0x04 / 4] = 26;
	top[0x00 / 4] = 1;
	while (top[0x00 / 4] & 0x1)
		;

	// ---------------------------------------------
	uint16_t **src_tmp;
	uint16_t **ascii_array;
	const int bus_width = 512;
	const int instruction_bit = 16;
	const int train_num = 2;
	// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	// const char *train_path[] = {"data/decorate/enlong", "data/decorate/frlong"};
	const int ngram = 3;
	const int core_num = 32;
	const int instruction_num = 8;
	const int majority_addr = 26;
	int all_ngram = 0;
	int even = 0;
	// -------------------------------------------

	// 英語とフランス語の数だけ繰り返す
	for (int l = 0; l < train_num; l++)
	{

		// DMAリセット
		dma[0x30 / 4] = 4;
		dma[0x00 / 4] = 4;
		while (dma[0x00 / 4] & 0x4)
			;

		// ファイル読み込み
		const char *path = train_path[l];
		printf("\n------------- %sの学習 -------------\n\n", path);
		FILE *file;
		file = fopen(path, "r");
		if (file == NULL)
		{
			perror("  Failed: open file");
			exit(1);
		}

		// ---------------------------------------------

		// ファイルから文字列を取得
		int ch;
		size_t num = 0;
		// 1行を前提
		while ((ch = fgetc(file)) != EOF)
		{
			num++;
		}
		// printf("EOF: %d\n", EOF); // EOFは全て-1
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

		// 確認
		// printf("content: %s\n", content); // myname...
		printf("all_ngram: %d\n", all_ngram);
		printf("even: %d\n", even);

		// ---------------------------------------------

		// // 何個の命令が必要か算出
		// int all_instruction = all_ngram / core_num;
		// if (all_ngram % core_num != 0)
		// {
		// 	all_instruction++;
		// }
		// all_instruction *= instruction_num;

		// // 確認
		// printf("all_instruction: %d\n\n", all_instruction);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		// 事前にPermしたものをメモリに格納

		// アクセラレータ起動
		top[0x00 / 4] = 2;

		int send_num = 0;

		for (int j = 0; j < 26; j++)
		{
			int ascii_addr = j;

			for (int i = 0; i < core_num; i++)
			{
				uint16_t inst = assemble("load", ascii_addr);
				src[send_num++] = inst;
			}

			for (int i = 0; i < core_num; i++)
			{
				uint16_t inst = assemble("rshift", 0);
				src[send_num++] = inst;
			}

			for (int i = 0; i < core_num; i++)
			{
				uint16_t inst = assemble("wbitem", ascii_addr + 27);
				src[send_num++] = inst;
			}
		}

		for (int j = 0; j < 26; j++)
		{
			int ascii_addr = j + 27;

			for (int i = 0; i < core_num; i++)
			{
				uint16_t inst = assemble("load", ascii_addr);
				src[send_num++] = inst;
			}

			for (int i = 0; i < core_num; i++)
			{
				uint16_t inst = assemble("rshift", 0);
				src[send_num++] = inst;
			}

			for (int i = 0; i < core_num; i++)
			{
				uint16_t inst = assemble("wbitem", ascii_addr + 27);
				src[send_num++] = inst;
			}
		}

		// last命令
		for (int i = 0; i < 1; i++)
		{
			uint16_t inst = assemble("last", 0);
			src[send_num++] = inst;
		}
		for (int i = 1; i < (bus_width / instruction_bit); i++)
		{
			src[send_num++] = 0;
		}

		// 最後の送信
		dma[0x00 / 4] = 1;
		dma[0x18 / 4] = src_phys;
		dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

		dma[0x30 / 4] = 1;
		dma[0x48 / 4] = dst_phys;
		dma[0x58 / 4] = (bus_width / 32) * 2 * 4; // 32個 * 4バイト = 128バイト = 1024ビット

		while ((dma[0x34 / 4] & 0x1000) != 0x1000)
			;

		// アクセラレータ終了
		top[0x00 / 4] = 0;

		dma[0x30 / 4] = 4;
		dma[0x00 / 4] = 4;
		while (dma[0x00 / 4] & 0x4)
			;

		/////////////////////////////////////////////////////////////////////////////////////////////////

		// アクセラレータ起動
		top[0x00 / 4] = 2;

		send_num = 0;

		// 偶数のとき指定した値をsrc配列に入れておく
		if (even)
		{
			// load
			for (int i = 0; i < core_num; i++)
			{
				if (i == 0)
				{
					uint16_t addr = majority_addr;
					uint16_t inst = assemble("load", addr);
					src[send_num] = inst;
				}
				else
				{
					src[send_num] = 0;
				}
				send_num++;
			}

			// store
			for (int i = 0; i < core_num; i++)
			{
				if (i == 0)
				{
					uint16_t inst = assemble("store", 0);
					src[send_num] = inst;
				}
				else
				{
					src[send_num] = 0;
				}
				send_num++;
			}
		}

		// ---------------------------------------------------
		// ↓ コード---------------------------------------------

		int all_instruction = all_ngram / 32;
		int remaind_instruction = all_ngram % 32;

		for (int i = 0; i < all_instruction; i++)
		{
			int flag = 0;
			for (int j = 0; j < core_num; j++)
			{
				uint16_t addr = (unsigned char)(content[i + flag]) - 97;
				src[send_num++] = assemble("load", addr);
				flag++;
			}
			for (int j = 0; j < core_num; j++)
			{
				src[send_num++] = assemble("move", 0);
			}
			flag = 1;
			for (int j = 0; j < core_num; j++)
			{
				uint16_t addr = (unsigned char)(content[i + flag]) - 97 + 27;
				src[send_num++] = assemble("load", addr);
				flag++;
			}
			for (int j = 0; j < core_num; j++)
			{
				src[send_num++] = assemble("xor", 0);
			}
			for (int j = 0; j < core_num; j++)
			{
				src[send_num++] = assemble("move", 0);
			}
			flag = 2;
			for (int j = 0; j < core_num; j++)
			{
				uint16_t addr = (unsigned char)(content[i + flag]) - 97 + 27;
				src[send_num++] = assemble("load", addr);
				flag++;
			}
			for (int j = 0; j < core_num; j++)
			{
				src[send_num++] = assemble("xor", 0);
			}
			for (int j = 0; j < core_num; j++)
			{
				src[send_num++] = assemble("store", 0);
			}

			// 最後じゃないかつ値を超えてたら
			// (2^26-8) / 2 が限界
			if (send_num >= 33000000)
			{

				printf("------------DMA再発行-----------\n");

				// last命令
				for (int i = 0; i < 1; i++)
				{
					uint16_t inst = assemble("last", 0);
					src[send_num] = inst;
					send_num++;
				}

				dma[0x00 / 4] = 1;
				dma[0x18 / 4] = src_phys;
				dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

				dma[0x30 / 4] = 1;
				dma[0x48 / 4] = dst_phys;
				dma[0x58 / 4] = (bus_width / 32) * 2 * 4; // 32個 * 4バイト = 128バイト = 1024ビット

				while ((dma[0x34 / 4] & 0x1000) != 0x1000)
					;

				dma[0x30 / 4] = 4;
				dma[0x00 / 4] = 4;
				while (dma[0x00 / 4] & 0x4)
					;

				send_num = 0;
			}
		}

		int flag = all_instruction * 32;
		for (int j = 0; j < core_num; j++)
		{
			if (j < remaind_instruction)
			{
				uint16_t addr = (unsigned char)(content[flag]) - 97;
				src[send_num++] = assemble("load", addr);
				flag++;
			}
			else
			{
				src[send_num++] = 0;
			}
		}
		for (int j = 0; j < core_num; j++)
		{
			if (j < remaind_instruction)
			{
				src[send_num++] = assemble("move", 0);
			}
			else
			{
				src[send_num++] = 0;
			}
		}
		flag = flag + 1;
		for (int j = 0; j < core_num; j++)
		{
			if (j < remaind_instruction)
			{
				uint16_t addr = (unsigned char)(content[flag]) - 97 + 27;
				src[send_num++] = assemble("load", 0);
				flag++;
			}
			else
			{
				src[send_num++] = 0;
			}
		}
		for (int j = 0; j < core_num; j++)
		{
			if (j < remaind_instruction)
			{
				src[send_num++] = assemble("xor", 0);
			}
			else
			{
				src[send_num++] = 0;
			}
		}
		for (int j = 0; j < core_num; j++)
		{
			if (j < remaind_instruction)
			{
				src[send_num++] = assemble("move", 0);
			}
			else
			{
				src[send_num++] = 0;
			}
		}
		flag = flag + 1;
		for (int j = 0; j < core_num; j++)
		{
			if (j < remaind_instruction)
			{
				uint16_t addr = (unsigned char)(content[flag]) - 97 + 27 + 27;
				src[send_num++] = assemble("load", 0);
				flag++;
			}
			else
			{
				src[send_num++] = 0;
			}
		}
		for (int j = 0; j < core_num; j++)
		{
			if (j < remaind_instruction)
			{
				src[send_num++] = assemble("xor", 0);
			}
			else
			{
				src[send_num++] = 0;
			}
		}
		for (int j = 0; j < core_num; j++)
		{
			if (j < remaind_instruction)
			{
				src[send_num++] = assemble("store", 0);
			}
			else
			{
				src[send_num++] = 0;
			}
		}

		// last命令
		for (int i = 0; i < 1; i++)
		{
			uint16_t inst = assemble("last", 0);
			src[send_num] = inst;
			send_num++;
		}

		// ↑ コード---------------------------------------------
		// ---------------------------------------------------

		// 最後の送信
		dma[0x00 / 4] = 1;
		dma[0x18 / 4] = src_phys;
		dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

		dma[0x30 / 4] = 1;
		dma[0x48 / 4] = dst_phys;
		dma[0x58 / 4] = (bus_width / 32) * 2 * 4; // 32個 * 4バイト = 128バイト = 1024ビット

		while ((dma[0x34 / 4] & 0x1000) != 0x1000)
			;

		// 結果確認
		printf("\n");
		for (int j = 0; j < (1024 / 32); j++)
		{
			printf("%u\n", dst[j]);
		}
		printf("\n");

		// アクセラレータ終了
		top[0x00 / 4] = 0;
	}

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");
	clock_t end = clock();
	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("Ohashi_ngram time %lf[ms]\n", time);

	return 0;
}
