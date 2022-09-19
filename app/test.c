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

void dma_reset()
{
  dma[0x30 / 4] = 4;
  dma[0x00 / 4] = 4;
  while (dma[0x00 / 4] & 0x4)
    ;
}

// ====================================================================================================================================================================================

int main(int argc, char **argv)
{

  printf("\n ---------------------------- 開始 ----------------------------- \n");

  ///////////////////////////////////////////////////////////////////////////////// udmabuf, uio 設定 ///////////////////////////////////////////////////////////////////////////////////

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

  //////////////////////////////////////////////////////////////////////////////////////// Set Matrix ////////////////////////////////////////////////////////////////////////////////////

  int matrix[8][128];

  // 32bitを128個、8つのコアに格納
  printf("\n ------------------------- Set Matrix -------------------------- \n\n");
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 128; i++)
    {
      matrix[j][i] = rand() & 0x000000ff;
      printf("%3d ", matrix[j][i]);
      src[j * 128 + i] = matrix[j][i];
    }
    printf("\n");
  }

  // matw <- 1;
  // アドレス0のレジスタのビット0に1を書くと行列メモリ書き込みモード
  // UIOで設定
  top[0x00 / 4] = 1;

  // AXI DMA 送信の設定（UIO経由）
  // 8 * 128 * 32 = 32768bit
  // 32768bit / 64bit = 512サイクル
  dma_reset();
  dma[0x00 / 4] = 1;           // 転送開始
  dma[0x18 / 4] = src_phys;    // 格納先のメモリアドレス
  dma[0x28 / 4] = 8 * 128 * 4; // ワード単位の長さ単位

  // 送信終了をUIO経由のビジーループで監視
  while ((dma[0x04 / 4] & 0x1000) != 0x1000)
    ;

  // matw <- 0;
  // 行列書き込みを終了
  top[0x00 / 4] = 0;

  //////////////////////////////////////////////////////////////////////////////////////// run ///////////////////////////////////////////////////////////////////////////////////////////////

  // run <- 1;
  // 起動
  top[0x00 / 4] = 2;

  int sample[8][128];

  // 32bitを128個、8つのコアに格納
  printf("\n ------------------------- Sample %d Input -------------------------- \n\n", 0);
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 128; i++)
    {
      sample[j][i] = rand() & 0x000000ff;
      printf("%3d ", sample[j][i]);
      src[j * 128 + i] = sample[j][i];
    }
    printf("\n");
  }

  // AXI DMA 送信の設定（UIO経由）
  // 8 * 128 * 32 = 32768bit
  // 32768bit / 64bit = 512サイクル
  dma_reset();
  dma[0x00 / 4] = 1;
  dma[0x18 / 4] = src_phys;
  dma[0x28 / 4] = 8 * 128 * 4;

  // 送信終了をUIO経由のビジーループで監視
  while ((dma[0x04 / 4] & 0x1000) != 0x1000)
    ;

  /////////////////////////////////////////////////////////////////////////////////////// 結果確認 //////////////////////////////////////////////////////////////////////////////////

  int result[8][8];

  for (int num = 0; num < 3; num++)
  {

    // 0回目以外実行 ---------------------------------------------------------------
    if (num != 0)
    {

      // 演算終わって送られてくるの待つ
      while ((dma[0x34 / 4] & 0x1000) != 0x1000)
        ;

      printf("\n ------------------------- Sample %d Output -------------------------- \n\n", num - 1);
      for (int j = 0; j < 8; j++)
      {
        for (int i = 0; i < 8; i++)
        {
          printf("%6d ", dst[j * 8 + i]);
          if (dst[j * 8 + i] != result[j][i])
          {
            printf("(Error Expecetd = %6d) ", result[j][i]);
          }
        }
        printf("\n");
      }
    }
    // ---------------------------------------------------------------------------

    // 受信設定
    // 受信チャネルの設定前に送信チャネルを設定すると変になるっぽい
    dma_reset();
    dma[0x30 / 4] = 1;
    dma[0x48 / 4] = dst_phys;
    dma[0x58 / 4] = 8 * 8 * 4;

    // 2回目（最後）以外実行 ---------------------------------------------------------
    if ((num + 1) != 3)
    {

      // 理想の計算
      for (int j = 0; j < 8; j++)
      {
        int sum[8] = {};
        for (int k = 0; k < 128; k++)
        {
          for (int i = 0; i < 8; i++)
          {
            sum[i] += matrix[i][k] * sample[j][k];
          }
        }
        for (int oa = 0; oa < 8; oa++)
        {
          result[j][oa] = sum[oa];
        }
      }

      printf("\n ------------------------- Sample %d Input -------------------------- \n\n", num + 1);
      for (int j = 0; j < 8; j++)
      {
        for (int i = 0; i < 128; i++)
        {
          sample[j][i] = rand() & 0x000000ff;
          printf("%3d ", sample[j][i]);
          src[j * 128 + i] = sample[j][i];
        }
        printf("\n");
      }

      // AXI DMA 送信の設定（UIO経由）
      // 8 * 128 * 32 = 32768bit
      // 32768bit / 64bit = 512サイクル
      // (上の受信設定でresetしているのでここでresetいらない)
      dma[0x00 / 4] = 1;
      dma[0x18 / 4] = src_phys;
      dma[0x28 / 4] = 8 * 128 * 4;

      // 送信終了をUIO経由のビジーループで監視
      while ((dma[0x04 / 4] & 0x1000) != 0x1000)
        ;
    }    // --------------------------------------------------------------------------------
    else // 最後に実行 ----------------------------------------------------------------------
    {
      // last <- 1;
      top[0x00 / 4] = 6;
    }
  }

  // 演算終わって送られてくるの待つ
  while ((dma[0x34 / 4] & 0x1000) != 0x1000)
    ;

  printf("\n ------------------------- Sample %d Output -------------------------- \n\n", 2);
  for (int j = 0; j < 8; j++)
  {
    int sum[8] = {};
    for (int k = 0; k < 128; k++)
    {
      for (int i = 0; i < 8; i++)
      {
        sum[i] += matrix[i][k] * sample[j][k];
      }
    }
    for (int i = 0; i < 8; i++)
    {
      printf("%6d ", dst[j * 8 + i]);
      if (dst[j * 8 + i] != sum[i])
      {
        printf("(Error Expecetd = %6d) ", sum[i]);
      }
    }
    printf("\n");
  }

  //////////////////////////////////////////////////////////////////////////////// FPGA停止 run <- 0; last <- 0; //////////////////////////////////////////////////////////////////////

  // run <- 0; last <- 0;
  top[0x00 / 4] = 0;

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  printf("\n ----------------------------- 終了 --------------------------------- \n");

  return;
}
