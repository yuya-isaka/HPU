// include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include "hyper_vector.h"

#define DIM 1024 / 32

volatile int *top;
volatile int *dma;
volatile uint16_t *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

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

// 簡易アセンブラ
// 10種類の命令
uint16_t assemble(const char inst_str[], uint16_t addr)
{
  if (strcmp(inst_str, "load") == 0 || strcmp(inst_str, "wbitem") == 0 || strcmp(inst_str, "pwbitem") == 0 || strcmp(inst_str, "permute") == 0)
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

    // pxor
    if (strcmp(inst_str, "pxor") == 0)
    {
      inst = 24576;
    }

    // store
    else if (strcmp(inst_str, "store") == 0)
    {
      inst = 4096;
    }

    // pstore
    else if (strcmp(inst_str, "pstore") == 0)
    {
      inst = 20480;
    }

    // move
    else if (strcmp(inst_str, "move") == 0)
    {
      inst = 2048;
    }

    // pmove
    else if (strcmp(inst_str, "pmove") == 0)
    {
      inst = 18432;
    }

    // last
    else if (strcmp(inst_str, "last") == 0)
    {
      inst = 1024;
    }

    // wb
    else if (strcmp(inst_str, "wb") == 0)
    {
      inst = 512;
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

void hdc_init(void)
{
  int fd0, fd1, dmaf, topf;

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

  top = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, topf, 0);
  if (top == MAP_FAILED)
  {
    perror("mmap top");
    close(topf);
    return;
  }

  dma = (int *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, dmaf, 0);
  if (dma == MAP_FAILED)
  {
    perror("mmap dma");
    close(dmaf);
    return;
  }

  src = (uint16_t *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd0, 0);
  if (src == MAP_FAILED)
  {
    perror("mmap src");
    close(fd0);
    return;
  }

  dst = (int *)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
  if (dst == MAP_FAILED)
  {
    perror("mmap dst");
    close(fd1);
    return;
  }
}

void make_imem(const int RANNUM)
{
  // item_memory_num (乱数の数)
  top[0x04 / 4] = RANNUM - 1;

  // gen <- 1;
  top[0x00 / 4] = 1;

  // 乱数生成終了を待つ
  while (top[0x00 / 4] & 0x1)
    ;
}

int send_num = 0;
int BUSWIDTH = 0;
int THREADSNUM = 0;

void init(void)
{
  send_num = 0;
  BUSWIDTH = 256;
  THREADSNUM = 10;

  // dma reset
  dma[0x30 / 4] = 4;
  dma[0x00 / 4] = 4;
  while (dma[0x00 / 4] & 0x4)
    ;
}

void nop_hv(void)
{
  src[send_num++] = 0;
}

void nop_hv_core(void)
{
  for (int i = 0; i < (BUSWIDTH / 16); i++)
  {
    nop_hv();
  }
}

void load_hv(uint16_t addr)
{
  src[send_num++] = assemble("load", addr);
}

void load_hv_core(uint16_t core_num, uint16_t addr_array[core_num])
{
  for (int i = 0; i < (BUSWIDTH / 16); i++)
  {
    if (i < core_num)
    {
      load_hv(addr_array[i]);
    }
    else
    {
      nop_hv();
    }
  }
}

void load_hv_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num])
{
  for (int k = 0; k < THREADSNUM; k++)
  {
    if (k < thread_num)
    {
      uint16_t new_array[core_num];
      memcpy(new_array, addr_array[k], sizeof(uint16_t) * core_num);
      load_hv_core(core_num, new_array);
    }
    else
    {
      nop_hv_core();
    }
  }
}

void store_hv(void)
{
  src[send_num++] = assemble("store", 0);
}

void store_hv_core(uint16_t core_num)
{
  for (int i = 0; i < (BUSWIDTH / 16); i++)
  {
    if (i < core_num)
    {
      store_hv();
    }
    else
    {
      nop_hv();
    }
  }
}

void store_hv_thread(uint16_t thread_num, uint16_t core_num)
{
  for (int k = 0; k < THREADSNUM; k++)
  {
    if (k < thread_num)
    {
      store_hv_core(core_num);
    }
    else
    {
      nop_hv_core();
    }
  }
}

void move_hv(void)
{
  src[send_num++] = assemble("move", 0);
}

void move_hv_core(uint16_t core_num)
{
  for (int i = 0; i < (BUSWIDTH / 16); i++)
  {
    if (i < core_num)
    {
      move_hv();
    }
    else
    {
      nop_hv();
    }
  }
}

void move_hv_thread(uint16_t thread_num, uint16_t core_num)
{
  for (int k = 0; k < THREADSNUM; k++)
  {
    if (k < thread_num)
    {
      move_hv_core(core_num);
    }
    else
    {
      nop_hv_core();
    }
  }
}

void permute_hv(uint16_t permute_num)
{
  src[send_num++] = assemble("permute", permute_num);
}

void permute_hv_core(uint16_t core_num, uint16_t permute_num)
{
  for (int i = 0; i < (BUSWIDTH / 16); i++)
  {
    if (i < core_num)
    {
      permute_hv(permute_num);
    }
    else
    {
      nop_hv();
    }
  }
}

void permute_hv_thread(uint16_t thread_num, uint16_t core_num, uint16_t permute_num)
{
  for (int k = 0; k < THREADSNUM; k++)
  {
    if (k < thread_num)
    {
      permute_hv_core(core_num, permute_num);
    }
    else
    {
      nop_hv_core();
    }
  }
}

void pxor_hv(void)
{
  src[send_num++] = assemble("pxor", 0);
}

void pxor_hv_core(uint16_t core_num)
{
  for (int i = 0; i < (BUSWIDTH / 16); i++)
  {
    if (i < core_num)
    {
      pxor_hv();
    }
    else
    {
      nop_hv();
    }
  }
}

void pxor_hv_thread(uint16_t thread_num, uint16_t core_num)
{
  for (int k = 0; k < THREADSNUM; k++)
  {
    if (k < thread_num)
    {
      pxor_hv_core(core_num);
    }
    else
    {
      nop_hv_core();
    }
  }
}

void last_hv(void)
{
  src[send_num++] = assemble("last", 0);
}

void last_hv_core(uint16_t core_num)
{
  for (int i = 0; i < (BUSWIDTH / 16); i++)
  {
    if (i < core_num)
    {
      last_hv();
    }
    else
    {
      nop_hv();
    }
  }
}

void last_hv_thread(uint16_t thread_num, uint16_t core_num)
{
  for (int k = 0; k < THREADSNUM; k++)
  {
    if (k < thread_num)
    {
      last_hv_core(core_num);
    }
    else
    {
      nop_hv_core();
    }
  }
}

void hv_start(void)
{
  // run <- 1;
  top[0x00 / 4] = 2;
}

void hv_send(void)
{
  // AXI DMA 送信の設定（UIO経由）
  dma[0x00 / 4] = 1;
  dma[0x18 / 4] = src_phys;
  dma[0x28 / 4] = send_num * 2; // 16ビットがsend_num個

  // 受信設定
  // 送信チャネルの設定前に受信チャネルを設定すると変になるっぽい
  dma[0x30 / 4] = 1;
  dma[0x48 / 4] = dst_phys;
  dma[0x58 / 4] = 128; // 32個 * 4バイト = 128バイト = 1024ビット

  // 演算終了を待つ
  while ((dma[0x34 / 4] & 0x1000) != 0x1000)
    ;
}

void finish(void)
{
  // run <- 0;
  top[0x00 / 4] = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check(const int NGRAM, const int CORENUM, const int ADDRNUM, const int MAJORITY_ADDR)
{
  init();

  const int REMAINDAR = (ADDRNUM / NGRAM) % (CORENUM * THREADSNUM);
  const int REMAINDAR_CORENUM = REMAINDAR / THREADSNUM;
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

  int LAST = (ADDRNUM / NGRAM) / (CORENUM * THREADSNUM);
  if (REMAINDAR == 0)
  {
    LAST--;
  }
  LAST *= NGRAM * CORENUM * THREADSNUM;

  hv_start();

  if (EVEN)
  {
    uint16_t addr_array[1][1] = {{MAJORITY_ADDR}};
    load_hv_thread(1, 1, addr_array);

    store_hv_thread(1, 1);
  }

  for (int j = 0; j < ADDRNUM; j += NGRAM * CORENUM * THREADSNUM)
  {
    uint16_t core_num;
    if (REMAINDAR != 0 && j == LAST)
    {
      core_num = REMAINDAR_CORENUM;
    }
    else
    {
      core_num = CORENUM;
    }

    uint16_t addr_array[THREADSNUM][core_num];

    for (int k = 0; k < THREADSNUM; k++)
    {
      for (int i = 0; i < core_num; i++)
      {
        addr_array[k][i] = NGRAM * i + j + (NGRAM * core_num * k);
      }
    }

    // load ---------------------------------------------
    load_hv_thread(THREADSNUM, core_num, addr_array);
    // ------------------------------------------------------

    // move ---------------------------------------------
    move_hv_thread(THREADSNUM, core_num);
    // ------------------------------------------------------

    for (int k = 0; k < THREADSNUM; k++)
    {
      for (int i = 0; i < core_num; i++)
      {
        addr_array[k][i]++;
      }
    }

    // load ---------------------------------------------
    load_hv_thread(THREADSNUM, core_num, addr_array);
    // ------------------------------------------------------

    // permute ---------------------------------------------
    permute_hv_thread(THREADSNUM, core_num, 1);
    // ------------------------------------------------------

    // pxor ---------------------------------------------
    pxor_hv_thread(THREADSNUM, core_num);
    // ------------------------------------------------------

    // move ---------------------------------------------
    move_hv_thread(THREADSNUM, core_num);
    // ------------------------------------------------------

    for (int k = 0; k < THREADSNUM; k++)
    {
      for (int i = 0; i < core_num; i++)
      {
        addr_array[k][i]++;
      }
    }

    // load ---------------------------------------------
    load_hv_thread(THREADSNUM, core_num, addr_array);
    // ------------------------------------------------------

    // permute ---------------------------------------------
    permute_hv_thread(THREADSNUM, core_num, 2);
    // ------------------------------------------------------

    // pxor ---------------------------------------------
    pxor_hv_thread(THREADSNUM, core_num);
    // ------------------------------------------------------

    // store ---------------------------------------------
    store_hv_thread(THREADSNUM, core_num);
    // ------------------------------------------------------
  }

  // LAST命令
  // 1024bit ---------------------------------------------
  last_hv_core(1);
  // ------------------------------------------------------

  hv_send();

  finish();

  // =========================================================================================================================================

  hv_init();

  hv_t **item_memory = hv_make_imem(512);

  for (int i = 0; i < ADDRNUM; i += 3)
  {
    hv_t *bound_tmp = hv_make();
    for (int j = 0; j < NGRAM; j++)
    {
      hv_t *perm_result = hv_perm(item_memory[i + j], j);
      hv_t *bind_result = hv_bind(bound_tmp, perm_result);
      hv_copy(bound_tmp, bind_result);

      hv_free(bind_result);
      hv_free(perm_result);
    }

    hv_bound(bound_tmp);

    hv_free(bound_tmp);
  }

  if (EVEN)
  {
    hv_bound(item_memory[MAJORITY_ADDR]);
  }
  hv_t *result = hv_bound_result();

  // hv_print(result);

  // ===========================================================================================================================================

  for (int i = 0; i < DIM; i++)
  {
    if (result[i] != dst[i])
    {
      printf("\n  Error %u %u\n", result[i], dst[i]);
      printf("  CORENUM=%d  ADDRNUM=%d\n\n", CORENUM, ADDRNUM);
    }
    // else
    // {
    //   printf("  Success\n");
    // }
  }

  hv_free(result);
  hv_finish();

  return;
}

int main()
{
  printf("\n ------------------------------ 開始 -------------------------------- \n\n");

  hdc_init();

  make_imem(512);

  const int NGRAM = 3;
  const int CORENUM_MAX = 14;
  const int MAJORITY_ADDR = 511;

  for (int i = 30; i <= 512; i += 30)
  {
    int ADDRNUM = i;
    check(NGRAM, CORENUM_MAX, ADDRNUM, MAJORITY_ADDR);
  }

  // int ADDRNUM = 30;
  // check(NGRAM, CORENUM_MAX, ADDRNUM, MAJORITY_ADDR);

  printf("\nOK!\n");
  printf("\n ------------------------------ 終了 -------------------------------- \n\n");

  return 0;
}
