// include
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printb(unsigned int v)
{
  unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

volatile int *top;
volatile int *dma;
volatile int *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// item_memoryの数（top.vの設定値より１つ大きくする）
const int RANNUM = 1001;

// ADDRNUM / NGRAM + 1を設定 (必ず奇数になるようにする)
const int ARNUM = 321;

// 偶数 ... ADDRNUM/NGRAM/2-1をtop.vに設定  (例：900 ... 900/NGRAM/2-1=149)
// 奇数 ... ADDRNUM/NGRAM/2をtop.vに設定	(例:903 ... 903/NGRAM/2=150）
// tb.cppのADDRNUMとは一緒
// ADDRNUM + NGRAM を処理する設計にする（ADDRNUMは663で、今回なNGRAMで２個を連続で処理するから2の倍数の666で処理する）
const int ADDRNUM = 960;

// N-gram
const int NGRAM = 3;

// ADDRNUMが奇数か
const int ODD = 0;

// 送信ビット
const int BUSWIDTH = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{

  ///////////////////////////////////////////////////////////////////////////////// initial, udmabuf, uio 設定 ///////////////////////////////////////////////////////////////////////////////////

  printf("\n ------------------------------ 開始 -------------------------------- \n");

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

  //////////////////////////////////////////////////////////////////////////////////////// gen ///////////////////////////////////////////////////////////////////////////////////////////////

  // gen <- 1;
  top[0x00 / 4] = 1;

  // 乱数生成終了を待つ
  while (top[0x00 / 4] & 0x1)
    ;

  //////////////////////////////////////////////////////////////////////////////////////// run ///////////////////////////////////////////////////////////////////////////////////////////////

  // run <- 1;
  top[0x00 / 4] = 2;

  printf("\n ------------------------- Sample %d Input --------------------------- \n\n", 0);

  int send_num = 0;
  int tmp = NGRAM - 1;
  int tmp_2 = 0;
  for (int i = 0; i < ADDRNUM; i++)
  {
    // 32コア
    for (int j = 0; j < 32; j++)
    {
      src[tmp_2] = i + (NGRAM * j);
      tmp_2++;
      send_num++;
    }

    if (i == tmp)
    {
      i += NGRAM * 31;
      tmp += (32 * NGRAM); // 32個分を同時に送っているから32 * NGRAM
    }
  }

  // AXI DMA 送信の設定（UIO経由）
  dma[0x00 / 4] = 1;
  dma[0x18 / 4] = src_phys;
  dma[0x28 / 4] = send_num * 4;

  // 受信設定
  // 送信チャネルの設定前に受信チャネルを設定すると変になるっぽい
  dma[0x30 / 4] = 1;
  dma[0x48 / 4] = dst_phys;
  dma[0x58 / 4] = 32 * 4; // 32個 * 4バイト = 128バイト = 1024ビット

  // 演算終了を待つ
  while ((dma[0x34 / 4] & 0x1000) != 0x1000)
    ;

  /////////////////////////////////////////////////////////////////////////////////////// 結果確認 //////////////////////////////////////////////////////////////////////////////////

  printf("\n ------------------------- Sample %d Output -------------------------- \n\n", 1);

  // 理想の計算
  unsigned int item_memory_array[RANNUM];
  item_memory_array[0] = 88675123;
  for (unsigned int i = 1; i < RANNUM; i++)
  {
    item_memory_array[i] = xor128();
  }

  unsigned int result_array[ARNUM];
  unsigned int result = 0;
  tmp = 0;
  int num = 0;
  for (unsigned int i = 0; i < ADDRNUM; i++)
  {
    result ^= shifter(item_memory_array[i], tmp);
    tmp += 1;
    if (tmp == NGRAM)
    {
      putb(result);
      result_array[num] = result;
      tmp = 0;
      result = 0;
      num += 1;
    }
  }

  // 多数決関数用
  if ((ADDRNUM / NGRAM) < ARNUM)
  {
    result_array[num] = item_memory_array[RANNUM - 1];
    // printf("%u", item_memory_array[RANNUM - 1]);
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
  // printf("%u\n", dst[1]);
  // putb(dst[1]);

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  // run <- 0;
  top[0x00 / 4] = 0;

  printf("\n ------------------------------ 終了 -------------------------------- \n\n");

  return;
}
