#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

// ====================================================================================================================================================================================

void printb(unsigned int v)
{
  unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
  // printf("%lu\n", sizeof(v));
  do
    putchar(mask & v ? '1' : '0');
  while (mask >>= 1);
}

void putb(unsigned int v)
{
  putchar('0'), putchar('b'), printb(v), putchar('\n');
}

unsigned int shifter(unsigned int v, unsigned int num)
{
  // num回 論理右シフト
  unsigned int tmp = v >> num;

  // 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
  unsigned int tmp_num = (1 << num) - 1;
  unsigned int tmp_v = (v & tmp_num) << ((sizeof(v) * 8) - num);

  tmp_v = tmp_v | tmp;
  return tmp_v;
}

unsigned int grab_bit(unsigned int result_array[], size_t size)
{
  unsigned int result = 0;

  unsigned int mask = (int)1 << (sizeof(result_array[0]) * 8 - 1);
  while (mask)
  {
    int tmp = 0;
    for (int i = 0; i < size; i++)
    {
      tmp += (mask & result_array[i] ? 1 : 0);
    }
    if (tmp > (size / 2))
    {
      result += mask;
    }
    mask >>= 1;
  }
  return result;
}

unsigned int xor128(void)
{
  // 内部で値を保持（seed） パターン１
  // static unsigned int x = 2380889285;
  // static unsigned int y = 1631889387;
  // static unsigned int z = 1698655726;
  // static unsigned int w = 2336862850;

  // 内部で値を保持（seed） パターン２
  static unsigned int x = 123456789;
  static unsigned int y = 362436069;
  static unsigned int z = 521288629;
  static unsigned int w = 88675123;

  // 前回のxを使う
  unsigned int t = x ^ (x << 11);
  // 更新
  x = y;
  y = z;
  z = w;

  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

// ====================================================================================================================================================================================

volatile int *top;
volatile int *dma;
volatile int *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

// ====================================================================================================================================================================================

// const int RANNUM = 100;
// const int ARNUM = 30;
// const int ADDRNUM = 90;
// const int ADDRNUMNUM = 180;
const int RANNUM = 1000;
const int ARNUM = 300;
const int ADDRNUM = 900;
const int ADDRNUMNUM = 1800;

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

  // dma reset
  dma[0x30 / 4] = 4;
  dma[0x00 / 4] = 4;
  while (dma[0x00 / 4] & 0x4)
    ;

  //////////////////////////////////////////////////////////////////////////////////////// mat ///////////////////////////////////////////////////////////////////////////////////////////////

  // mat <- 1;
  top[0x00 / 4] = 1;

  // 乱数生成終わるのを待つ
  while (top[0x00 / 4] & 0x1)
    ;

  //////////////////////////////////////////////////////////////////////////////////////// run ///////////////////////////////////////////////////////////////////////////////////////////////

  // run <- 1;
  // 起動
  top[0x00 / 4] = 2;

  printf("\n ------------------------- Sample %d Input --------------------------- \n\n", 0);

  int sample[ADDRNUMNUM]; // 動的
  int tmp = 0;
  for (int i = 0; i < ADDRNUMNUM; i += 2) // 動的
  {
    // ここにアドレスを指定
    // ここでは0-23のアドレスを入力
    sample[i] = tmp;
    sample[i + 1] = tmp;
    printf("%3d ", sample[i]);

    src[i] = sample[i];
    src[i + 1] = sample[i + 1];
    tmp++;
  }

  // AXI DMA 送信の設定（UIO経由）
  // 8 * 128 * 32 = 32768bit
  // 32768bit / 64bit = 512サイクル
  dma[0x00 / 4] = 1;
  dma[0x18 / 4] = src_phys;
  dma[0x28 / 4] = ADDRNUMNUM * 4; // 動的

  // 受信設定
  // 送信チャネルの設定前に受信チャネルを設定すると変になるっぽい
  dma[0x30 / 4] = 1;
  dma[0x48 / 4] = dst_phys;
  dma[0x58 / 4] = 2 * 4;

  // // 送信終了をUIO経由のビジーループで監視
  // while ((dma[0x04 / 4] & 0x1000) != 0x1000)
  //   ;

  // for (int i = 0; i < 24; i++) // 動的
  // {
  //   // ここにアドレスを指定
  //   // ここでは0-23のアドレスを入力
  //   // 今回は２回ハイパーベクトルを求めている
  //   sample[i] = i;
  //   printf("%3d ", sample[i]);

  //   src[i] = sample[i];
  // }

  // AXI DMA 送信の設定（UIO経由）
  // 8 * 128 * 32 = 32768bit
  // 32768bit / 64bit = 512サイクル
  // dma[0x00 / 4] = 1;
  // dma[0x18 / 4] = src_phys;
  // dma[0x28 / 4] = 24 * 4; // 動的

  // 送信終了をUIO経由のビジーループで監視
  // while ((dma[0x04 / 4] & 0x1000) != 0x1000)
  //   ;

  // 演算終わって送られてくるの待つ
  while ((dma[0x34 / 4] & 0x1000) != 0x1000)
    ;

  //////////////////////////////////////////////////////////////////////////////////////////////////

  printf("\n ------------------------- Sample %d Output -------------------------- \n\n", 1);

  // 現状、乱数生成器がないので、33215360を起点に下ランダムな値をitem_memory_arrayに入力
  // これはテスト用
  unsigned int item_memory_array[RANNUM];
  item_memory_array[0] = 88675123;
  for (unsigned int i = 1; i < RANNUM; i++)
  {
    item_memory_array[i] = xor128();
  }

  unsigned int result_array[ARNUM]; // 動的 今回24個のアドレスで3-gramなので、24/3=8
  unsigned int result = 0;
  // 理想の計算
  tmp = 0;
  int num = 0;
  for (unsigned int i = 0; i < ADDRNUM; i++) // 動的
  {
    result ^= shifter(item_memory_array[i], tmp);
    tmp += 1;
    if (tmp == 3) // 将来的には動的、現状3-gram
    {
      putb(result);
      result_array[num] = result;
      tmp = 0;
      result = 0;
      num += 1;
    }
  }

  unsigned int result_real = grab_bit(result_array, sizeof(result_array) / sizeof(result_array[0]));
  printf("%u\n", result_real);
  putb(result_real);
  if (result_real != dst[0])
  {
    printf("Error\n");
  }
  else
  {
    printf("Success\n");
  }
  printf("%u\n", dst[0]);
  putb(dst[0]);
  printf("%u\n", dst[1]);
  putb(dst[1]);

  // 受信設定
  // 受信チャネルの設定前に送信チャネルを設定すると変になるっぽい
  // dma[0x30 / 4] = 1;
  // dma[0x48 / 4] = dst_phys;
  // dma[0x58 / 4] = 2 * 4;

  /////////////////////////////////////////////////////////////////////////////////////// 結果確認 //////////////////////////////////////////////////////////////////////////////////

  // last <- 1;
  // top[0x00 / 4] = 6;

  // 演算終わって送られてくるの待つ
  // while ((dma[0x34 / 4] & 0x1000) != 0x1000)
  //   ;

  printf("\n ------------------------- Sample %d Output -------------------------- \n\n", 1);

  // unsigned int result_array[8];
  // result = 0;
  // tmp = 0;
  // num = 0;
  // for (unsigned int i = 0; i < 24; i++) // 動的
  // {
  //   result ^= shifter(item_memory_array[i], tmp);
  //   tmp += 1;
  //   if (tmp == 3) // 将来的には動的
  //   {
  //     putb(result);
  //     result_array[num] = result;
  //     tmp = 0;
  //     result = 0;
  //     num += 1;
  //   }
  // }

  // result_real = grab_bit(result_array, sizeof(result_array) / sizeof(result_array[0]));
  // printf("%d\n", result_real);
  // putb(result_real);
  // if (result_real != dst[0])
  // {
  //   printf("Error\n");
  // }
  // else
  // {
  //   printf("Success\n");
  // }
  // printf("%d\n", dst[0]);
  // putb(dst[0]);

  //////////////////////////////////////////////////////////////////////////////// FPGA停止 run <- 0; last <- 0; //////////////////////////////////////////////////////////////////////

  // run <- 0; last <- 0;
  top[0x00 / 4] = 0;

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  printf("\n ------------------------------ 終了 -------------------------------- \n\n");

  return;
}
