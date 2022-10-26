// include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint16_t
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// const int RANNUM = 1001;
// const int DIM = 1024 / 32;
#define RANNUM 1001
#define DIM 32 / 32

unsigned int item_memory_array[DIM][RANNUM];
unsigned int item_memory_array_new[DIM][RANNUM];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

union
{
  struct
  {
    uint16_t data_0;
    uint16_t data_1;
  };
  uint32_t write_data;
} conv;

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

unsigned int shifter_2(unsigned int *v, unsigned int num)
{
  // num回 論理右シフト
  unsigned int tmp_v = *v >> num;

  // 右にシフトしたやつを取り出して、左に(32-num)回 論理左シフト
  unsigned int tmp_num = (1 << num) - 1;
  *v = (*v & tmp_num) << (32 - num);

  return tmp_v;
}

void shifter_new(const int NGRAM)
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
      unsigned int tmp_v = shifter_2(&tmp, num);
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

unsigned int grab_bit(unsigned int result_array[], size_t size)
{
  unsigned int result = 0;

  // 次元数可変
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

volatile int *top;
volatile int *dma;
volatile int *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 可変のパラメータ

// const int NGRAM = 3;
// const int ADDRNUM = 900;
// const int CORENUM = 4;
// const int BUSWIDTH = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check(const int NGRAM, const int ADDRNUM, const int CORENUM, const int BUSWIDTH)
{

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // 自動で決まるパラメータ

  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;
  int ARNUM = ADDRNUM / NGRAM;
  const int LAST = ADDRNUM - 48;
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

  //////////////////////////////////////////////////////////////////////////////////////// gen ///////////////////////////////////////////////////////////////////////////////////////////////

  // item_memory_num (乱数の数)
  top[0x04 / 4] = RANNUM - 1;

  // gen <- 1;
  top[0x00 / 4] = 1;

  // 乱数生成終了を待つ
  while (top[0x00 / 4] & 0x1)
    ;

  //////////////////////////////////////////////////////////////////////////////////////// run ///////////////////////////////////////////////////////////////////////////////////////////////

  // even
  top[0x08 / 4] = EVEN;

  //////////////////////////////////////////////////////////////////////////////////////// run ///////////////////////////////////////////////////////////////////////////////////////////////

  // run <- 1;
  top[0x00 / 4] = 2;

  // printf("\n ------------------------- Sample Input --------------------------- \n\n");

  int send_num = 0;
  int tmp = NGRAM - 1;
  int tmp_2 = 0;
  for (int j = 0; j < ADDRNUM; j++)
  {
    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        conv.data_0 = NGRAM * i + j;
        conv.data_1 = 1;
        src[tmp_2] = conv.write_data;
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        conv.data_0 = 0;
        conv.data_1 = 64;
        src[tmp_2] = conv.write_data;
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        conv.data_0 = NGRAM * i + 1 + j;
        conv.data_1 = 2;
        src[tmp_2] = conv.write_data;
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        conv.data_0 = 0;
        conv.data_1 = 16;
        src[tmp_2] = conv.write_data;
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        conv.data_0 = 0;
        conv.data_1 = 64;
        src[tmp_2] = conv.write_data;
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        conv.data_0 = NGRAM * i + 2 + j;
        conv.data_1 = 2;
        src[tmp_2] = conv.write_data;
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        conv.data_0 = 0;
        conv.data_1 = 4;
        src[tmp_2] = conv.write_data;
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        conv.data_0 = 0;
        conv.data_1 = 16;
        src[tmp_2] = conv.write_data;
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    // 1024bit ---------------------------------------------
    for (int i = 0; i < (BUSWIDTH / 32); i++)
    {
      if (i < CORENUM)
      {
        if (j == LAST)
        {
          conv.data_0 = 0;
          conv.data_1 = 128;
          src[tmp_2] = conv.write_data;
        }
        else
        {
          conv.data_0 = 0;
          conv.data_1 = 32;
          src[tmp_2] = conv.write_data;
        }
      }
      else
      {
        src[tmp_2] = 0;
      }
      tmp_2++;
      send_num++;
    }
    // ------------------------------------------------------

    j += NGRAM * CORENUM - 1;
    // if (j == tmp)
    // {
    //   j += NGRAM * (CORENUM - 1);
    //   tmp += (CORENUM * NGRAM); // 32個分を同時に送っているから32 * NGRAM
    // }
  }

  // AXI DMA 送信の設定（UIO経由）
  dma[0x00 / 4] = 1;
  dma[0x18 / 4] = src_phys;
  dma[0x28 / 4] = send_num * 4;

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

  shifter_new(NGRAM);

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
        // putb(result);
        // printf("%u\n", result);
        result_array[num] = result;
        tmp = 0;
        result = 0;
        num += 1;
      }
    }
    // 多数決関数用
    if (EVEN)
    {
      result_array[num] = item_memory_array[j][RANNUM - 1];
      // putb(result_array[num]);
      // printf("ランダム：%u\n", result_array[num]);
    }
    unsigned int result_real = grab_bit(result_array, ARNUM);
    // printf("  %x\n", result_real);
    // printf("  %u\n", result_real);
    // putb(result_real);
    // printf("\n");
    if (result_real != dst[j])
    {
      printf("Error %u %u\n", result_real, dst[j]);
    }
    else
    {
      printf("Success\n");
    }

    free(result_array);
  }

  // for (int j = 0; j < 32; j++)
  // {
  //   printf("%u\n", dst[j]);
  // }

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  // run <- 0;
  top[0x00 / 4] = 0;

  return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

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
  src = (int *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd0, 0);
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

  ///////////////////////////////////////////////////////////////////////////////// initial, udmabuf, uio 設定 ///////////////////////////////////////////////////////////////////////////////////

  // NGRAM, ADDRNUM, CORENUM, BUSWIDTH

  // for (int i = 3; i <= 999; i += 3)
  // {
  //   check(3, i, 16, 1001, 1024);
  //   xor128(1);
  // }
  check(3, 48, 16, 1024);
  // xor128(1);
  // check(3, 96, 16, 1024);
  // xor128(1);
  // check(3, 144, 16, 1024);

  printf("\n ------------------------------ 終了 -------------------------------- \n\n");

  return 0;
}
