#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

// ====================================================================================================================================================================================

volatile int *top;
volatile int *dma;
volatile int *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

// ====================================================================================================================================================================================

void main()
{

	printf("\n ------------------------------ 開始 -------------------------------- \n");

	///////////////////////////////////////////////////////////////////////////////// initial, udmabuf, uio 設定 ///////////////////////////////////////////////////////////////////////////////////

	// 参考文献
	// https://github.com/ikwzm/udmabuf/blob/master/Readme.ja.md

	int fd0, fd1, dmaf, topf;

	// DMAバッファの物理アドレスを取得 ------------------------------------------------------------

	// /sys/class/u-dma-buf/<device-name>/phys_addr はDMAバッファの物理アドレスが読めます
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

	// メモリアクセス用のデバイスファイルを開く (デバイスドライバファイルを開く)
	// バッファにアクセスする際に使用する
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

	// -- mmapについて --
	// 物理アドレスから仮想アドレスを取得 (アドレス変換)
	// NULL を指定すると新しい領域
	// マップしたい領域の長さを指定(バイト)。 (0x1000 = 4096(4KB))
	// マップの保護レベルを指定
	// 変更した結果が他のプロセスから見えるかを指定（ sharedにしておけば読み書き可能な空間としてマッピング）
	// openで取得したファイルハンドラを指定
	// 開始点となるファイルオフセット（ファイルマッピングの場合）。ページサイズの倍数とする制限がある(UIOで0にすると変になる)
	// -----------------

	// 対応表, 参考
	// https://pknight.hatenablog.com/entry/20100427/1272396732

	// uio1をユーザ空間にマッピング
	// (int *)にキャスト (汎用ポインタがここでは返ってくるので，何かしらにキャストする必要がある)
	// 0x1000 == 4096
	// 40000_0000
	top = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, topf, 0);
	if (top == MAP_FAILED)
	{
		perror("mmap");
		close(topf);
		return;
	}
	// uio0をユーザ空間にマッピング
	// 4040_0000
	dma = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, dmaf, 0);
	if (dma == MAP_FAILED)
	{
		perror("mmap");
		close(dmaf);
		return;
	}

	// udmabuf0をユーザ空間にマッピング
	// 0x00080000 == 524288
	// 0000_0000
	src = (int *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd0, 0);
	if (src == MAP_FAILED)
	{
		perror("mmap");
		close(fd0);
		return;
	}
	// udmabuf1をユーザ空間にマッピング
	// 0000_0000
	dst = (int *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
	if (dst == MAP_FAILED)
	{
		perror("mmap");
		close(fd1);
		return;
	}

	//////////////////////////////////////////////////////////////////////////////////////// mat ///////////////////////////////////////////////////////////////////////////////////////////////

	// mat <- 1;
	top[0x00 / 4] = 1;

	// 乱数生成終わるのを待つ
	while (top[0x00 / 4] & 0x1)
		;

	printf("\n ------------------------------ 終了 -------------------------------- \n\n");

	return;
}
