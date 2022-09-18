#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

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

// 参考文献
// https://github.com/ikwzm/udmabuf/blob/master/Readme.ja.md

void main()
{

  int fd0, fd1, dmaf, topf;

  // DMAバッファの物理アドレスを取得 --------------------------------------------------------------------

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

  // DMAバッファにユーザ空間から書き込む設定 --------------------------------------------------------------------

  // バッファにアクセスする際に使用する
  // メモリアクセス用のデバイスファイルを開く (デバイスドライバファイルを開く)
  if ((fd0 = open("/dev/udmabuf0", O_RDWR)) < 0)
  {
    perror("open");
    return;
  }
  if ((fd1 = open("/dev/udmabuf1", O_RDWR)) < 0)
  {
    perror("open");
    return;
  }
  if ((dmaf = open("/dev/uio0", O_RDWR | O_SYNC)) < 0)
  {
    perror("open");
    return;
  }
  if ((topf = open("/dev/uio1", O_RDWR | O_SYNC)) < 0)
  {
    perror("open");
    return;
  }

  // 仮想アドレスを取得
  // NULL を指定すると新しい領域
  // マップしたい領域の長さを指定(バイト)。 (0x1000 = 4096(4KB))
  // マップの保護レベルを指定
  // 変更した結果が他のプロセスから見えるかを指定（ sharedにしておけば読み書き可能な空間としてマッピング）
  // openで取得したファイルハンドラを指定
  // 開始点となるファイルオフセット（ファイルマッピングの場合）。ページサイズの倍数とする制限がある(UIOで0にすると変になる)

  // 対応表
  // https://pknight.hatenablog.com/entry/20100427/1272396732

  // uio1をユーザ空間にマッピング
  // 0x1000 == 4096
  // 今回は(int *)にキャスト
  // 汎用ポインタがここでは返ってくるので，何かしらにキャストする必要がある
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

  ////////////////////// Set Matrix /////////////////////////////
  int matrix[8][128];

  // matrixはまとめて送られる設定にしていない、まとめて送ってしまっても、使えずに終わるので
  // まとめて送る分は同じデータにしておいて対応をしているっぽい
  // matrixをまとめて送って保存するような設定にした場合は、違う書き方にできる
  // coreで渡しているデータを見たらわかる
  // mat_dに渡しているのはS_AXIS_TDATA[31:0]だけ
  printf("\n--- Set Matrix ---\n");
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 128; i++)
    {
      matrix[j][i] = rand() & 0x000000ff;
      printf("%3d ", matrix[j][i]);
      // src[(j * 8 + i)] = matrix[j][i]; // これやと失敗する
      src[j * 128 + i] = matrix[j][i]; // 0 2 4 6 8 10 12 14 | 16 18 20 22 24 26 28 30 | 32 ... 62
    }
    printf("\n");
  }

  // matw <- 1;
  // アドレス0のレジスタのビット0に1を書くと行列メモリ書き込みモードに入ります。
  // UIOで設定
  top[0x00 / 4] = 1;

  // AXI DMA transfer tx
  // 入力データをUIOで設定 (入力を設定する場所は一定)
  dma_reset();
  dma[0x00 / 4] = 1;           // 転送開始
  dma[0x18 / 4] = src_phys;    // 格納先のメモリアドレス
  dma[0x28 / 4] = 8 * 128 * 4; // ワード単位の長さ単位 // 64 * 4 * 4 * 2 をしないといけないね。上のやつを見ると。 // 64 * 4個を4バイト分確保。そして二倍にして送る
  // dma[0x28 / 4] = 8 * 4 * 4;

  // Wait for the tx to finish
  // 終了をUIOで監視 (下の監視のやつとアドレスが違う)
  while ((dma[0x04 / 4] & 0x1000) != 0x1000)
    ;

  // matw <- 0;
  // 書き込み終了をUIOで設定
  top[0x00 / 4] = 0;

  ////////////////////// run /////////////////////////////
  // run <- 1;
  top[0x00 / 4] = 2;

  int sample[8][128];

  // tb.cppでは16個でまとめて64送っている
  // ここではまとめてsrcの01 23 45 が送られる？
  // srcで置いたものが01とかをまとめて送られるので、
  // sampleの場合は問題ないが
  // matrixの場合はまとめて送られる設定にしていないので、ちょっと困ると
  printf("\n--- Sample %d Input ---\n", 0);
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

  // AXI DMA transfer tx
  dma_reset();
  dma[0x00 / 4] = 1;
  dma[0x18 / 4] = src_phys;
  dma[0x28 / 4] = 8 * 128 * 4; // 4095 (64bit 64ビート　のバースト転送)

  // Wait for the tx to finish
  while ((dma[0x04 / 4] & 0x1000) != 0x1000)
    ;

  int result[8][8];

  for (int num = 0; num < 3; num++)
  {
    if (num != 0)
    {
      // Wait for the rx to finish
      while ((dma[0x34 / 4] & 0x1000) != 0x1000)
        ;

      printf("\n--- Sample %d Output ---\n", num - 1);
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

    // AXI DMA transfer rx
    dma_reset();
    // 受信チャネルを設定する前に送信チャネルを設定すると、先頭の4ワード分データが消える。
    // なんのための FIFO なんだろうか？ DMA も自前で作っちゃうのが早いのだろうか…
    // [追記 送信チャネル設定前に受信チャネルを設定すれば動くので、もう少し頑張ってみます。
    // スループットを上げるにはこれ使った方がよさそうだし。]
    dma[0x30 / 4] = 1;
    dma[0x48 / 4] = dst_phys;
    dma[0x58 / 4] = 8 * 8 * 4;

    if ((num + 1) != 3)
    {
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
      printf("\n--- Sample %d Input ---\n", num + 1);
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
      // AXI DMA transfer tx
      dma[0x00 / 4] = 1;
      dma[0x18 / 4] = src_phys;
      dma[0x28 / 4] = 8 * 128 * 4;

      // Wait for the tx to finish
      while ((dma[0x04 / 4] & 0x1000) != 0x1000)
        ;
    }
    else
    {
      // last <- 1;
      top[0x00 / 4] = 6;
    }
  }
  // Wait for the rx to finish
  while ((dma[0x34 / 4] & 0x1000) != 0x1000)
    ;

  printf("\n--- Sample %d Output ---\n", 2);
  for (int j = 0; j < 8; j++)
  {
    int sum[8] = {};
    for (int k = 0; k < 8; k++)
    {
      for (int i = 0; i < 128; i++)
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

  // run <- 0; last <- 0;
  top[0x00 / 4] = 0;

  printf("pass\n");

  return;
}
