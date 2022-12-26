
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

// y列x行のuint16_t２次元配列を確保
void makeArray(uint16_t ***a, const int y, const int x)
{
	*a = (uint16_t **)calloc(y, sizeof(uint16_t *));
	if (*a == NULL)
	{
		perror("  Failed: calloc");
		exit(1);
	}
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint16_t *)calloc(x, sizeof(uint16_t));
		if ((*a)[i] == NULL)
		{
			perror("  Failed: calloc");
			exit(1);
		}
	}
}

// y列x行のuint16_t２次元配列を解放
void freeArray(uint16_t ***a, const int y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

// ------------------------------------------------------------------------------------------------

uint16_t assemble(const char inst_str[], uint16_t addr)
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

// ----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char const *argv[])
{

	// プログラム全体の時間
	clock_t start_program = clock();

	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// 初期化の時間
	clock_t start = clock();

	// initialの抽象化は後回し
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
	top[0x04 / 4] = 26;
	top[0x00 / 4] = 1;
	while (top[0x00 / 4] & 0x1)
		;

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	uint16_t **src_tmp;
	uint16_t **ascii_array;
	const int bus_width = 1024;
	const int instruction_bit = 16;
	const int train_num = 2;
	// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	// const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	const char *train_path[] = {"data/decorate/enlong", "data/decorate/frlong"};
	const int ngram = 3;
	const int core_num_max = 14;
	const int core_num = 14;
	const int instruction_num = 10;
	const int majority_addr = 26;
	int all_ngram = 0;
	int even = 0;
	unsigned long src_phys_tmp = src_phys;

	// -------------------------------------------

	clock_t end = clock();
	double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("初期化時間（CPU）: %lf[ms]\n", time);

	// -------------------------------------------

	// 英語とフランス語の数だけ繰り返す
	for (int l = 0; l < train_num; l++)
	{
		// データ準備時間
		start = clock();

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
		if (content == NULL)
		{
			perror("  Failed: calloc");
			exit(1);
		}
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

		// 何個の命令が必要か算出
		int all_instruction = all_ngram / core_num;
		if (all_ngram % core_num != 0)
		{
			all_instruction++;
		}
		all_instruction *= instruction_num;

		// 確認
		printf("all_instruction: %d\n\n", all_instruction);

		// ---------------------------------------------

		makeArray(&src_tmp, core_num, all_instruction);
		makeArray(&ascii_array, all_ngram, ngram);

		// 一時的な命令格納場所
		for (int i = 0; i < core_num; i++)
		{
			for (int j = 0; j < all_instruction; j++)
			{
				src_tmp[i][j] = 0;
			}
		}

		// 得られた文字列からアドレスを取得
		for (int i = 0; i < all_ngram; i++)
		{
			for (int j = 0; j < ngram; j++)
			{
				ascii_array[i][j] = (unsigned char)(content[i + j]) - 97;
			}
		}

		// ---------------------------------------------------
		// ↓ コード---------------------------------------------

		int instruction = 0;
		int core = 0;
		for (int i = 0; i < all_ngram; i++)
		{
			// load
			uint16_t addr = ascii_array[i][0];
			uint16_t inst = assemble("load", addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// move
			inst = assemble("move", 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// load
			addr = ascii_array[i][1];
			inst = assemble("load", addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// rshift
			inst = assemble("permute", 1);
			src_tmp[core][instruction] = inst;
			instruction++;

			// xor
			inst = assemble("pxor", 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// move
			inst = assemble("move", 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// load
			addr = ascii_array[i][2];
			inst = assemble("load", addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// rshift
			inst = assemble("permute", 2);
			src_tmp[core][instruction] = inst;
			instruction++;

			// rshift
			inst = assemble("pxor", 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// store
			inst = assemble("store", 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			if (core != (core_num - 1))
			{
				instruction -= instruction_num;
			}

			core = (core + 1) % core_num;
		}

		// ---------------------------------------------

		const int send_num_max = 33000000;
		int send_num = 0;
		int send_num_array[100];
		int send_num_count = 0;
		int count = 0;

		// 偶数のとき指定した値をsrc配列に入れておく
		if (even)
		{
			// load
			for (int i = 0; i < core_num_max; i++)
			{
				if (i == 0)
				{
					uint16_t addr = majority_addr;
					uint16_t inst = assemble("load", addr);
					src[send_num++] = inst;
					count++;
				}
				else
				{
					src[send_num++] = 0;
					count++;
				}
			}

			// store
			for (int i = 0; i < core_num_max; i++)
			{
				if (i == 0)
				{
					uint16_t inst = assemble("store", 0);
					src[send_num++] = inst;
					count++;
				}
				else
				{
					src[send_num++] = 0;
					count++;
				}
			}
		}

		// ---------------------------------------------

		// 命令をsrc配列に埋める
		for (int j = 0; j < all_instruction; j++)
		{
			for (int i = 0; i < core_num_max; i++)
			{
				if (i < core_num)
				{
					src[send_num++] = src_tmp[i][j];
					count++;
				}
				else
				{
					src[send_num++] = 0;
					count++;
				}
			}

			if (count >= send_num_max)
			{

				// Last命令
				for (int i = 0; i < core_num_max; i++)
				{
					if (i < core_num)
					{
						uint16_t inst = assemble("last", 0);
						src[send_num++] = inst;
						count++;
					}
					else
					{
						src[send_num++] = 0;
						count++;
					}
				}
				send_num_array[send_num_count++] = count;
				count = 0;
			}
		}

		// last命令
		for (int i = 0; i < core_num_max; i++)
		{
			if (i < core_num)
			{
				uint16_t inst = assemble("last", 0);
				src[send_num++] = inst;
				count++;
			}
			else
			{
				src[send_num++] = 0;
				count++;
			}
		}
		send_num_array[send_num_count++] = count;

		freeArray(&ascii_array, ngram);
		freeArray(&src_tmp, core_num);

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

			dma[0x30 / 4] = 4;
			dma[0x00 / 4] = 4;
			while (dma[0x00 / 4] & 0x4)
				;

			dma[0x00 / 4] = 1;
			dma[0x18 / 4] = src_phys;
			dma[0x28 / 4] = send_num_tmp * 2; // 16ビットがsend_num個

			dma[0x30 / 4] = 1;
			dma[0x48 / 4] = dst_phys;
			dma[0x58 / 4] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

			while ((dma[0x34 / 4] & 0x1000) != 0x1000)
				;

			src_phys += send_num_tmp * 2;
		}

		top[0x00 / 4] = 0;

		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
		printf("計算時間（アクセラレータ）: %lf[ms]\n", time);

		// 結果確認
		printf("\n");
		for (int j = 0; j < 32; j++)
		{
			printf("%u\n", dst[j]);
		}
		printf("\n");

		src_phys = src_phys_tmp;
	}

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	end = clock();
	time = ((double)(end - start_program)) / CLOCKS_PER_SEC * 1000.0;
	printf("プログラム合計時間（CPU＋アクセラレータ）: %lf[ms]\n", time);

	return 0;
}