// include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include "hyper_vector.h"
#include "hdc_processor.h"

void check(const int NGRAM, const int CORENUM, const int ADDRNUM, const int MAJORITY_ADDR, const int IMEM_SIZE)
{

  hdc_init(0);
  hdc_dma_reset();

  const int REMAINDAR = (ADDRNUM / NGRAM) % (CORENUM * THREADS_NUM);
  const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

  int LAST = (ADDRNUM / NGRAM) / (CORENUM * THREADS_NUM);
  if (REMAINDAR == 0)
  {
    LAST--;
  }
  LAST *= NGRAM * CORENUM * THREADS_NUM;

  hdc_start();

  if (EVEN)
  {
    uint16_t addr_array[1][1] = {{MAJORITY_ADDR}};
    hdc_load_thread(1, 1, addr_array);

    hdc_store_thread(1, 1);
  }

  for (int j = 0; j < ADDRNUM; j += NGRAM * CORENUM * THREADS_NUM)
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

    uint16_t addr_array[THREADS_NUM][core_num];

    for (int k = 0; k < THREADS_NUM; k++)
    {
      for (int i = 0; i < core_num; i++)
      {
        addr_array[k][i] = NGRAM * i + j + (NGRAM * core_num * k);
      }
    }

    // load ---------------------------------------------
    hdc_load_thread(THREADS_NUM, core_num, addr_array);
    // ------------------------------------------------------

    // move ---------------------------------------------
    hdc_move_thread(THREADS_NUM, core_num);
    // ------------------------------------------------------

    for (int k = 0; k < THREADS_NUM; k++)
    {
      for (int i = 0; i < core_num; i++)
      {
        addr_array[k][i]++;
      }
    }

    // load ---------------------------------------------
    hdc_load_thread(THREADS_NUM, core_num, addr_array);
    // ------------------------------------------------------

    // permute ---------------------------------------------
    hdc_permute_thread(THREADS_NUM, core_num, 1);
    // ------------------------------------------------------

    // pxor ---------------------------------------------
    hdc_pxor_thread(THREADS_NUM, core_num);
    // ------------------------------------------------------

    // move ---------------------------------------------
    hdc_move_thread(THREADS_NUM, core_num);
    // ------------------------------------------------------

    for (int k = 0; k < THREADS_NUM; k++)
    {
      for (int i = 0; i < core_num; i++)
      {
        addr_array[k][i]++;
      }
    }

    // load ---------------------------------------------
    hdc_load_thread(THREADS_NUM, core_num, addr_array);
    // ------------------------------------------------------

    // permute ---------------------------------------------
    hdc_permute_thread(THREADS_NUM, core_num, 2);
    // ------------------------------------------------------

    // pxor ---------------------------------------------
    hdc_pxor_thread(THREADS_NUM, core_num);
    // ------------------------------------------------------

    // store ---------------------------------------------
    hdc_store_thread(THREADS_NUM, core_num);
    // ------------------------------------------------------
  }

  // LAST命令
  // 1024bit ---------------------------------------------
  hdc_last_core(1);
  // ------------------------------------------------------

  hdc_compute();

  hdc_finish();

  // =========================================================================================================================================

  hv_init();

  hv_t **item_memory = hv_make_imem(IMEM_SIZE);

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

  for (int i = 0; i < 32; i++)
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

  const int IMEM_SIZE = 1024;

  hdc_setup();

  hdc_make_imem(IMEM_SIZE);

  const int NGRAM = 3;
  const int CORENUM_MAX = 14;
  const int MAJORITY_ADDR = IMEM_SIZE - 1;

  for (int i = 30; i <= IMEM_SIZE; i += 30)
  {
    int ADDRNUM = i;
    check(NGRAM, CORENUM_MAX, ADDRNUM, MAJORITY_ADDR, IMEM_SIZE);
  }

  // int ADDRNUM = 30;
  // check(NGRAM, CORENUM_MAX, ADDRNUM, MAJORITY_ADDR, IMEM_SIZE);

  printf("\nOK!\n");
  printf("\n ------------------------------ 終了 -------------------------------- \n\n");

  return 0;
}
