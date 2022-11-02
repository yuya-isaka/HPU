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

// 動的 //////////////////////////////////////////////////////////////////////////////////////////

// 次元数 (現状変えられない)
const int HVLENGTH = 1024; // デフォルト
// バス幅 (現状変えられない)
const int BUS_MAX = 1024; // デフォルト

// ランダム生成の数
const int RANDAM_MAX = 1024; // デフォルト
int RANDAM = 0;
// エンコーディングの実行回数 (asm_array[EXEC_NUM][][9])
const int EXEC_NUM = 1; // デフォルト
// コア数 (asm_array[][CORE_NUM][])
const int CORE_MAX = 16; // デフォルト
int CORE_NUM = 0;
// 一まとまりの命令数 (asm_array[][][9小命令 * 大命令 / CORE_NUM])
// CORE_NUMにおける命令の総数
// 9, 3, 16
// 9小命令 * 大命令 == 全ての命令数
// 全ての命令数 / CORE_NUM == 小命令 * (大命令 / CORE_NUM)
// 小命令はそれ以上分けられない（セット） = 小命令はレジスタを共有しているから分けられない

// int num = 大命令 / CORE_NUM;
// if (大命令　　% CORE_NUM != 0) {
//	num++;
//}
// int all_num = 小命令 * num;

// 言葉に置き換える
// 大命令 ... スレッド（もっといい言葉に）
// 小命令 ... 段数

const int INSTRUCTION_NUM = 9; // N-gram 9命令 * (all_ngram / 16)
// 計算する数が偶数か奇数か
const int EVEN = 0; // デフォルト
// asm_array
const int asm_array[EXEC_NUM][CORE_NUM][INSTRUCTION_NUM];

//////////////////////////////////////////////////////////////////////////////////////////////////

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

	// dma reset
	dma[0x30 / 4] = 4;
	dma[0x00 / 4] = 4;
	while (dma[0x00 / 4] & 0x4)
		;

	// item_memory_num (乱数の数)
	top[0x04 / 4] = RANNUM - 1;

	// gen <- 1;
	top[0x00 / 4] = 1;

	// 乱数生成終了を待つ
	while (top[0x00 / 4] & 0x1)
		;

	///////////////

	// asm_array[2][10][9]の時
	// asm_array[2] ... 英語、フランス語
	// asm_array[2][10] ... 英語とフランス語それぞれで10個の一まとまりの命令
	// asm_array[2][10][9] ... 一まとまりの命令の数

	// [2] ... EXEC_NUM
	// [10] ... INSTRUCTION_CHUNK_NUM
	// [9] ... INSTRUCTION_NUM

	// train_num (英語とフランス語なら２)
	for (int i = 0; i < EXEC_NUM; i++)
	{
		// even
		top[0x08 / 4] = EVEN;

		// run <- 1;
		top[0x00 / 4] = 2;

		int send_num = 0;
		for (int j = 0; j < INSTRUCTION_CHUNK_NUM; j += (BUS_MAX / CORENUM))
		{
			for (int k = 0; k < INSTRUCTION_NUM; k++)
			{
				for (int l = 0; l < (BUS_MAX / CORENUM); l++)
				{
					if (l < CORENUM)
					{
						src[send_num] = asm_array[i][j + l][k];
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
		dma[0x58 / 4] = (BUS_MAX / 32) * 4; // 32個 * 4バイト = 128バイト = 1024ビット

		// 演算終了を待つ
		while ((dma[0x34 / 4] & 0x1000) != 0x1000)
			;

		// 演算結果確認
		for (int j = 0; j < (BUS_MAX / 32); j++)
		{
			printf("%u", dst[j]);
		}

		// run <- 0;
		top[0x00 / 4] = 0;
	}

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	return 0;
}
