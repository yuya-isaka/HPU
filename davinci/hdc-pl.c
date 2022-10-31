
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint16_t
#include <time.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

volatile int *top;
volatile int *dma;
volatile uint16_t *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

// --------------------------------------- メモリリークチェック、デストラクター -----------------------------------------

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

uint16_t instruction(int addr_flag, unsigned int inst_num, uint16_t addr)
{
	if (addr_flag)
	{
		uint16_t result = 0;
		if (inst_num == 1)
		{
			uint16_t inst = 3 << 14;
			result = inst | addr;
		}
		else if (inst_num == 2)
		{
			uint16_t inst = 5 << 13;
			result = inst | addr;
		}
		else if (inst_num == 4)
		{
			uint16_t inst = 9 << 12;
			result = inst | addr;
		}
		else if (inst_num == 6)
		{
			uint16_t inst = 17 << 11;
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
		if (inst_num == 3)
		{
			inst = 1 << 14;
		}
		else if (inst_num == 5)
		{
			inst = 1 << 13;
		}
		else if (inst_num == 7)
		{
			inst = 1 << 12;
		}
		else if (inst_num == 8)
		{
			inst = 1 << 11;
		}
		else if (inst_num == 9)
		{
			inst = 1 << 10;
		}
		else if (inst_num == 10)
		{
			inst = 1 << 9;
		}
		else
		{
			printf("error");
		}
		return inst;
	}
}

// -------------------------------------------  パラメータ設定 ---------------------------------------------------

// n-gram
const int NGRAM = 3;

// 次元数
const int LENGTH = 1000;

// 学習対象の個数（英語、フランス語）
int train_num = 2;

// 訓練データ指定
// const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"}; // 文字数少なめ
// const char *train_path[] = {"data/decorate/en2", "data/decorate/fr2"}; // 文字数少なめよりは多め
const char *train_path[] = {"data/decorate/en", "data/decorate/fr"}; // 文字数多め

// テストの個数（英語、フランス語）
int test_num = 2;

// テストデータ指定
const char *test_path[] = {"data/decorate/t1", "data/decorate/t2"};

// --------------------------------------------------------- エンコード関数 ---------------------------------------------------------------

unsigned int **encoding(const char *path, const int NGRAM, int *EVEN, const unsigned int INSTRUCTION_NUM, const unsigned int CORENUM)
{
	// ファイルオープン
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL)
	{
		perror("  Failed to open file");
		exit(1);
	}

	// 何文字?
	int ch;
	int num = 0;
	while (((ch = fgetc(file)) != EOF) && ((ch = fgetc(file) != 255))) // ubuntu:EOF == -1,  petalinux:EOF == 255
	{
		num++;
	}
	fseek(file, 0, SEEK_SET);
	char *content = (char *)calloc(num, sizeof(char));
	fread(content, sizeof(char), num, file);
	fclose(file);
	// debug
	// printf("%d\n", num);			  		// 27
	// printf("%s\n", content);		  		// myname...
	// printf("%lu\n", strlen(content)); 	// 27

	// ngramの数（パラメータから計算）
	int all_ngram = strlen(content) - NGRAM + 1;

	*EVEN = ((all_ngram / NGRAM) % 2) == 0;

	// ポインタ型を格納する配列をポインタ宣言
	unsigned int **src;
	unsigned int **ascii_array;
	// 該当ポインタにキャストして、数分確保
	ascii_array = (unsigned int **)calloc(all_ngram, sizeof(unsigned int));
	src = (unsigned int **)calloc(all_ngram, sizeof(unsigned int));
	for (int i = 0; i < all_ngram; i++)
	{
		ascii_array[i] = (unsigned int *)calloc(NGRAM, sizeof(unsigned int));
		src[i] = (unsigned int *)calloc(INSTRUCTION_NUM, sizeof(unsigned int));
	}
	// ↓
	// src[all_ngram][NGRAM]が完成

	for (int i = 0; i < all_ngram; i++)
	{
		for (int j = 0; j < NGRAM; j++)
		{
			ascii_array[i][j] = (unsigned char)(content[i + j]);
		}
	}

	for (int i = 0; i < all_ngram; i++)
	{
		// 1
		int tmp = 0;
		uint16_t addr = ascii_array[i][0];
		uint16_t inst = instruction(1, 1, addr);
		src[i][tmp] = inst;
		tmp++;

		// 10
		inst = instruction(0, 10, 0);
		src[i][tmp] = inst;
		tmp++;

		// 2
		addr = ascii_array[i][1];
		inst = instruction(1, 2, addr);
		src[i][tmp] = inst;
		tmp++;

		// 7
		inst = instruction(0, 7, 0);
		src[i][tmp] = inst;
		tmp++;

		// 10
		inst = instruction(0, 10, 0);
		src[i][tmp] = inst;
		tmp++;

		// 2
		addr = ascii_array[i][2];
		inst = instruction(1, 2, addr);
		src[i][tmp] = inst;
		tmp++;

		// 3
		inst = instruction(0, 3, 0);
		src[i][tmp] = inst;
		tmp++;

		// 7
		inst = instruction(0, 7, 0);
		src[i][tmp] = inst;
		tmp++;

		// 8 or 9
		if (i == (all_ngram - 1))
		{
			inst = instruction(0, 9, 0);
			src[i][tmp] = inst;
			tmp++;
		}
		else
		{
			inst = instruction(0, 8, 0);
			src[i][tmp] = inst;
			tmp++;
		}
	}

	return src;
}

// --------------------------------------------------------------- main program ----------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	int fd0, fd1, dmaf, topf;

	// DMAバッファの物理アドレスを取得 ------------------------------------------------------------

	if ((fd0 = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		read(fd0, attr, 1024);
		sscanf(attr, "%lx", &src_phys);
		close(fd0);
	}
	if ((fd0 = open("/sys/class/u-dma-buf/udmabuf1/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		read(fd0, attr, 1024);
		sscanf(attr, "%lx", &dst_phys);
		close(fd0);
	}

	// DMAバッファにユーザ空間から書き込む設定 -----------------------------------------------------

	if ((fd0 = open("/dev/udmabuf0", O_RDWR)) < 0)
	{
		perror("Failed: open /dev/udmabuf0");
		return 0;
	}
	if ((fd1 = open("/dev/udmabuf1", O_RDWR)) < 0)
	{
		perror("Failed: open /dev/udmabuf1");
		return 0;
	}
	if ((dmaf = open("/dev/uio0", O_RDWR | O_SYNC)) < 0)
	{
		perror("Falied: open /dev/uio0");
		return 0;
	}
	if ((topf = open("/dev/uio1", O_RDWR | O_SYNC)) < 0)
	{
		perror("Failed: open /dev/uio1");
		return 0;
	}

	// 対応表, 参考
	// https://pknight.hatenablog.com/entry/20100427/1272396732

	// uio1をユーザ空間にマッピング
	// (int *)にキャスト (汎用ポインタがここでは返ってくるので，何かしらにキャストする必要がある)
	// 0x1000 == 4096
	// 40000_0000
	top = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, topf, 0);
	if (top == MAP_FAILED)
	{
		perror("mmap top");
		close(topf);
		return 0;
	}
	// uio0をユーザ空間にマッピング
	// 4040_0000
	dma = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, dmaf, 0);
	if (dma == MAP_FAILED)
	{
		perror("mmap dma");
		close(dmaf);
		return 0;
	}

	// udmabuf0をユーザ空間にマッピング
	// 0x00080000 == 524288
	// 0000_0000
	src = (uint16_t *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd0, 0);
	if (src == MAP_FAILED)
	{
		perror("mmap src");
		close(fd0);
		return 0;
	}
	// udmabuf1をユーザ空間にマッピング
	// 0000_0000
	dst = (int *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
	if (dst == MAP_FAILED)
	{
		perror("mmap dst");
		close(fd1);
		return 0;
	}

	const int NGRAM = 3;
	int EVEN;

	// dma reset
	dma[0x30 / 4] = 4;
	dma[0x00 / 4] = 4;
	while (dma[0x00 / 4] & 0x4)
		;

	// item_memory_num (乱数の数)
	top[0x04 / 4] = 130 - 1;

	// gen <- 1;
	top[0x00 / 4] = 1;

	// 乱数生成終了を待つ
	while (top[0x00 / 4] & 0x1)
		;

	///////////////

	// train_num (英語とフランス語なら２)
	for (int i = 0; i < train_num; i++)
	{
		unsigned int **tmp;
		const unsigned int INSTRUCTION_NUM = 9;
		const unsigned int CORENUM = 16;
		tmp = encoding(train_path[i], NGRAM, &EVEN, INSTRUCTION_NUM, CORENUM);
		// even
		top[0x08 / 4] = EVEN;

		// run <- 1;
		top[0x00 / 4] = 2;

		int send_num = 0;

		size_t length = (sizeof(src) / sizeof(unsigned int *));
		// 応急処置 ----------
		int remainder = length % 48;
		length -= remainder;
		// ------------------
		for (int j = 0; j < length; j += (1024 / CORENUM))
		{
			for (int k = 0; k < INSTRUCTION_NUM; k++)
			{
				for (int l = 0; l < (1024 / CORENUM); l++)
				{
					if (l < CORENUM)
					{
						src[send_num] = tmp[j + l][k];
					}
					else
					{
						src[send_num] = 0;
					}
					send_num++;
				}
			}
		}
		// AXI DMA 送信の設定（UIO経由）
		dma[0x00 / 4] = 1;
		dma[0x18 / 4] = src_phys;
		dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

		// 受信設定
		// 送信チャネルの設定前に受信チャネルを設定すると変になるっぽい
		dma[0x30 / 4] = 1;
		dma[0x48 / 4] = dst_phys;
		dma[0x58 / 4] = (1024 / 32) * 4; // 32個 * 4バイト = 128バイト = 1024ビット

		// 演算終了を待つ
		while ((dma[0x34 / 4] & 0x1000) != 0x1000)
			;

		for (int j = 0; j < (1024 / 32); j++)
		{
			printf("%u", dst[j]);
		}

		// run <- 0;
		top[0x00 / 4] = 0;
	}

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	return 0;
}
