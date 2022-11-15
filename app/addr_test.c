// include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint16_t
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h> // strcomp

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 可変パラメータ

// 次元数可変 (理想の計算に必要)
// #define DIM 32 / 32
#define DIM 1024 / 32

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 変わらん

// 追加されるランダムな値はRANNUM-1番目
#define RANNUM 512
#define BUSWIDTH 1024
unsigned int item_memory_array[DIM][RANNUM];
unsigned int item_memory_array_new[DIM][RANNUM];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 渡された32ビットのvを、バイナリでコマンドライン出力
void printb(unsigned int v)
{
  unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
  do
    putchar(mask & v ? '1' : '0');
  while (mask >>= 1);
}

// printbを使いつつ整形して、バイナリをコマンドライン出力
void putb(unsigned int v)
{
  putchar('0'), putchar('b'), printb(v), putchar('\n');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int shifter_32(unsigned int *v, unsigned int num)
{
  // num回 論理右シフト
  unsigned int tmp_v = *v >> num;

  // 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
  unsigned int tmp_num = (1 << num) - 1;
  *v = (*v & tmp_num) << (32 - num);

  return tmp_v;
}

void shifter_ngram(const int NGRAM)
{
  int num = 0;
  for (int i = 0; i < RANNUM; i++)
  {
    // ちゃんと初期化したら上手くいった
    unsigned int result_tmp[DIM];
    for (int j = 0; j < DIM; j++)
    {
      result_tmp[j] = 0;
    }
    for (int j = 0; j < DIM; j++)
    {
      unsigned int tmp = item_memory_array[j][i];
      unsigned int tmp_v = shifter_32(&tmp, num);
      result_tmp[j] |= tmp_v;
      if (j == 0)
      {
        result_tmp[DIM - 1] |= tmp;
      }
      else
      {
        result_tmp[j - 1] |= tmp;
      }
    }

    for (int j = 0; j < DIM; j++)
    {
      item_memory_array_new[j][i] = result_tmp[j];
    }

    num++;
    if (num == NGRAM)
    {
      num = 0;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int bounding(unsigned int result_array[], size_t size)
{
  unsigned int result = 0;

  unsigned int mask = (int)1 << (32 - 1);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int xor128(int reset)
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

  if (reset)
  {
    x = 123456789;
    y = 362436069;
    z = 521288629;
    w = 88675123;
    return 0;
  }
  else
  {

    // 前回のxを使う
    unsigned int t = x ^ (x << 11);
    // 更新
    x = y;
    y = z;
    z = w;

    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

volatile int *top;
volatile int *dma;
volatile uint16_t *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check(const int NGRAM, const int CORENUM, const int ADDRNUM, const int MAJORITY_ADDR)
{

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // 自動で決まるパラメータ

  const int REMAINDAR = (ADDRNUM / NGRAM) % CORENUM;
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;
  int LAST = (ADDRNUM / NGRAM) / CORENUM;
  if (REMAINDAR == 0)
  {
    LAST--;
  }
  LAST *= NGRAM * CORENUM;
  int ARNUM = ADDRNUM / NGRAM;
  if (EVEN)
  {
    ARNUM++;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // dma reset
  dma[0x30 / 4] = 4;
  dma[0x00 / 4] = 4;
  while (dma[0x00 / 4] & 0x4)
    ;

  //////////////////////////////////////////////////////////////////////////////////////// run ///////////////////////////////////////////////////////////////////////////////////////////////

  // run <- 1;
  top[0x00 / 4] = 2;

  int send_num = 0;

  //////////////////////////////////////////////// Even //////////////////////////////////////////////

  if (EVEN)
  {
    // load
    for (int i = 0; i < (BUSWIDTH / 16); i++)
    {
      if (i == 0)
      {
        uint16_t addr = MAJORITY_ADDR;
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
    for (int i = 0; i < (BUSWIDTH / 16); i++)
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

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  for (int j = 0; j < ADDRNUM; j++)
  {
    if (REMAINDAR != 0 && j == LAST)
    {
      // 1024bit ---------------------------------------------
      // 16bit命令ごとに入れるから64回必要
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t addr = NGRAM * i + j;
          uint16_t inst = assemble("load", addr);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t inst = assemble("move", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t addr = NGRAM * i + 1 + j;
          uint16_t inst = assemble("load", addr);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t inst = assemble("rshift", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t inst = assemble("xor", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t inst = assemble("move", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t addr = NGRAM * i + 2 + j;
          uint16_t inst = assemble("load", addr);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t inst = assemble("rshift", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t inst = assemble("rshift", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          uint16_t inst = assemble("xor", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < REMAINDAR)
        {
          // LASTは確定済みなので９を代入
          uint16_t inst = assemble("store", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // LAST命令
      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i == 0)
        {
          uint16_t inst = assemble("last", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      j += NGRAM * CORENUM - 1;
    }
    else // =========================================================================================
    {
      // 1024bit ---------------------------------------------
      // 16bit命令ごとに入れるから64回必要
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t addr = NGRAM * i + j;
          uint16_t inst = assemble("load", addr);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t inst = assemble("move", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t addr = NGRAM * i + 1 + j;
          uint16_t inst = assemble("load", addr);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t inst = assemble("rshift", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t inst = assemble("xor", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t inst = assemble("move", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t addr = NGRAM * i + 2 + j;
          uint16_t inst = assemble("load", addr);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t inst = assemble("rshift", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t inst = assemble("rshift", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
        {
          uint16_t inst = assemble("xor", 0);
          src[send_num] = inst;
        }
        else
        {
          src[send_num] = 0;
        }
        send_num++;
      }
      // ------------------------------------------------------

      // 1024bit ---------------------------------------------
      for (int i = 0; i < (BUSWIDTH / 16); i++)
      {
        if (i < CORENUM)
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
      // ------------------------------------------------------

      j += NGRAM * CORENUM - 1;
    }
  }

  // LAST命令
  // 1024bit ---------------------------------------------
  for (int i = 0; i < (BUSWIDTH / 16); i++)
  {
    if (i == 0)
    {
      uint16_t inst = assemble("last", 0);
      src[send_num] = inst;
    }
    else
    {

      src[send_num] = 0;
    }
    send_num++;
  }
  // ------------------------------------------------------

  // AXI DMA 送信の設定（UIO経由）
  dma[0x00 / 4] = 1;
  dma[0x18 / 4] = src_phys;
  dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

  // 受信設定
  // 送信チャネルの設定前に受信チャネルを設定すると変になるっぽい
  dma[0x30 / 4] = 1;
  dma[0x48 / 4] = dst_phys;
  dma[0x58 / 4] = (BUSWIDTH / 32) * 4; // 32個 * 4バイト = 128バイト = 1024ビット

  // 演算終了を待つ
  while ((dma[0x34 / 4] & 0x1000) != 0x1000)
    ;

  /////////////////////////////////////////////////////////////////////////////////////// 結果確認 //////////////////////////////////////////////////////////////////////////////////

  // printf("\n ------------------------- Sample Output -------------------------- \n\n");

  // 理想の計算
  item_memory_array[0][0] = 88675123;
  for (unsigned int j = 0; j < RANNUM; j++)
  {
    for (int i = 0; i < DIM; i++)
    {
      if (i == 0 && j == 0)
        continue;
      item_memory_array[i][j] = xor128(0);
    }
  }

  shifter_ngram(NGRAM);

  for (int j = 0; j < DIM; j++)
  {
    unsigned int *result_array = (unsigned int *)malloc(sizeof(unsigned int) * ARNUM);
    if (result_array == NULL)
    {
      exit(0);
    }
    unsigned int result = 0;
    int tmp = 0;
    int num = 0;
    for (int i = 0; i < ADDRNUM; i++)
    {
      result ^= item_memory_array_new[j][i];
      // printf("%d:%u\n", i, item_memory_array_new[j][i]);
      tmp += 1;
      if (tmp == NGRAM)
      {
        // printf("%u\n", result);
        // putb(result);
        result_array[num] = result;
        tmp = 0;
        result = 0;
        num += 1;
      }
    }
    // 多数決関数用
    if (EVEN)
    {
      // RANNUM-1を追加するランダム値に使う
      result_array[num] = item_memory_array[j][MAJORITY_ADDR];
      // printf("ランダム：%u\n", result_array[num]);
      // putb(result_array[num]);
    }
    unsigned int result_real = bounding(result_array, ARNUM);
    // printf("  %u\n", result_real);
    // putb(result_real);
    if (result_real != dst[j])
    {
      printf("\n  Error %u %u\n", result_real, dst[j]);
      printf("  CORENUM=%d  ADDRNUM=%d\n\n", CORENUM, ADDRNUM);
    }
    // else
    // {
    //   printf("  Success\n");
    // }

    free(result_array);
  }

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  // run <- 0;
  top[0x00 / 4] = 0;

  return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

  printf("\n ------------------------------ 開始 -------------------------------- \n\n");

  int fd0, fd1, dmaf, topf;

  // DMAバッファの物理アドレスを取得 ------------------------------------------------------------

  if ((fd0 = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY)) != -1)
  {
    char attr[1024];
    ssize_t done = read(fd0, attr, 1024);
    if (done < 0)
    {
      perror("Failed: read /sys/class/u-dma-buf/udmabuf0/phys_addr");
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
      perror("Failed: read /sys/class/u-dma-buf/udmabuf1/phys_addr");
    }
    sscanf(attr, "%lx", &dst_phys);
    close(fd0);
  }
  // printf("dst_phys: %lx\n", dst_phys);

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

  //////////////////////////////////////////////////////////////////////////////////////// gen ///////////////////////////////////////////////////////////////////////////////////////////////

  // item_memory_num (乱数の数)
  top[0x04 / 4] = RANNUM - 1;

  // gen <- 1;
  top[0x00 / 4] = 1;

  // 乱数生成終了を待つ
  while (top[0x00 / 4] & 0x1)
    ;

  ///////////////////////////////////////////////////////////////////////////////// initial, udmabuf, uio 設定 ///////////////////////////////////////////////////////////////////////////////////

  const int NGRAM = 3;
  const int MAJORITY_ADDR = 511;
  const int CORENUM_MAX = 32;

  int CORENUM = 0;
  int ADDRNUM = 0;
  for (int j = 1; j <= CORENUM_MAX; j++)
  {
    CORENUM = j;
    for (int i = 3; i <= RANNUM; i += 3)
    {
      ADDRNUM = i;

      check(NGRAM, CORENUM, ADDRNUM, MAJORITY_ADDR);
      xor128(1);
    }
  }

  printf("\nOK!\n");

  printf("\n ------------------------------ 終了 -------------------------------- \n\n");

  return 0;
}
