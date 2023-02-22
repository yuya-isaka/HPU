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

// Check関数
void check(const int NGRAM, const int CORENUM, const int ADDRNUM, const int MAJORITY_ADDR, const int IMEM_SIZE)
{
  const int EPOCH = (ADDRNUM / NGRAM) / (CORENUM * THREADS_NUM);
  const int REMAINDAR = (ADDRNUM / NGRAM) % (CORENUM * THREADS_NUM);
  const int REMAINDAR_CORENUM = REMAINDAR / THREADS_NUM;
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;
  const int LAST = EPOCH * NGRAM * CORENUM * THREADS_NUM;

  // SEND_NUM初期化 & DMAリセット
  hdc_init(0);

  // HDCプロセッサ起動
  hdc_start();

  // 偶数処理
  if (EVEN)
  {
    uint16_t addr_array[1] = {MAJORITY_ADDR};
    hdc_load_thread(1, 1, addr_array);

    hdc_store_thread(1, 1);
  }

  // LASTまで繰り返す
  for (int j = 0; j < LAST; j += NGRAM * CORENUM * THREADS_NUM)
  {
    uint16_t core_num = CORENUM;
    uint16_t addr_array[THREADS_NUM];
    // printf("\n");

    // アドレス
    for (uint16_t k = 0; k < THREADS_NUM; k++)
    {
      addr_array[k] = j + (NGRAM * core_num * k);
      // printf("%d : ", addr_array[k]);
    }

    // load ---------------------------------------------
    hdc_load_thread(THREADS_NUM, core_num, addr_array);
    // ------------------------------------------------------

    // move ---------------------------------------------
    hdc_move_thread(THREADS_NUM, core_num);
    // ------------------------------------------------------

    // アドレス
    for (int k = 0; k < THREADS_NUM; k++)
    {
      addr_array[k]++;
      // printf("%d : ", addr_array[k]);
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

    // アドレス
    for (int k = 0; k < THREADS_NUM; k++)
    {
      addr_array[k]++;
      // printf("%d : ", addr_array[k]);
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

  // 余り
  if (REMAINDAR != 0)
  {
    uint16_t core_num = REMAINDAR_CORENUM;
    uint16_t addr_array[THREADS_NUM];

    // アドレス
    for (int k = 0; k < THREADS_NUM; k++)
    {
      addr_array[k] = NGRAM + LAST + (NGRAM * core_num * k);
    }

    // load ---------------------------------------------
    hdc_load_thread(THREADS_NUM, core_num, addr_array);
    // ------------------------------------------------------

    // move ---------------------------------------------
    hdc_move_thread(THREADS_NUM, core_num);
    // ------------------------------------------------------

    // アドレス
    for (int k = 0; k < THREADS_NUM; k++)
    {
      addr_array[k]++;
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

    // アドレス
    for (int k = 0; k < THREADS_NUM; k++)
    {
      addr_array[k]++;
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

  // last -------------------------------------------------
  hdc_last();
  // ------------------------------------------------------

  // 計算開始
  hdc_compute();

  // HDCプロセッサ終了
  hdc_finish();

  // =========================================================================================================================================

  // HV初期化
  hv_init();

  // アイテムメモリ初期化
  hv_t **item_memory = hv_make_imem(IMEM_SIZE);

  for (int i = 0; i < ADDRNUM; i += 3)
  {
    // Bounding格納変数
    hv_t *bound_tmp = hv_make();

    for (int j = 0; j < NGRAM; j++)
    {
      // Permutation
      hv_t *perm_result = hv_perm(item_memory[i + j], j);

      // Binding
      hv_t *bind_result = hv_bind(bound_tmp, perm_result);

      // Copy
      hv_copy(bound_tmp, bind_result);

      // Free
      hv_free(bind_result);
      hv_free(perm_result);
    }

    // Bounding
    hv_bound(bound_tmp);

    // Free
    hv_free(bound_tmp);
  }

  // 偶数処理
  if (EVEN)
  {
    hv_bound(item_memory[MAJORITY_ADDR]);
  }

  // Bounding結果取り出し
  hv_t *result = hv_bound_result();

  // // 結果出力
  // hv_print(result);

  // =========================================================================================================================================

  for (int i = 0; i < 32; i++)
  {
    // 結果確認
    if (result[i] != dst[i])
    {
      printf("\n  Error %u %u\n", result[i], dst[i]);
      printf("  CORENUM=%d  ADDRNUM=%d\n\n", CORENUM, ADDRNUM);
    }
  }

  // Free
  hv_free(result);

  // HV終了
  hv_finish();

  return;
}

uint32_t xor128(int reset)
{
  // 初期値
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;

  // リセット信号
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
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }
}

int main(void)
{
  printf("\n ------------------------------ 開始 -------------------------------- \n\n");

  const int IMEM_SIZE = 512;
  const int NGRAM = 3;
  const int CORENUM_MAX = 1;
  const int MAJORITY_ADDR = IMEM_SIZE - 1;

  // HDCプロセッサメモリ準備
  hdc_setup();

  // HDCプロセッサアイテムメモリ準備
  hdc_com_start();
  hdc_com_gen(88675123);
  for (int i = 0; i < 31; i++)
  {
    hdc_com_gen(xor128(0));
  }
  for (int i = 0; i < 511; i++)
  {
    for (int j = 0; j < 32; j++)
    {
      hdc_com_gen(xor128(0));
    }
  }
  hdc_compute_only();
  hdc_finish();

  // テスト
  for (int j = 0; j < 100; j++)
  {
    for (int i = (NGRAM * THREADS_NUM); i <= IMEM_SIZE; i += (NGRAM * THREADS_NUM))
    {
      int ADDRNUM = i;
      check(NGRAM, CORENUM_MAX, ADDRNUM, MAJORITY_ADDR, IMEM_SIZE);
    }
  }

  // // 単体テスト
  // int ADDRNUM = 30;
  // check(NGRAM, CORENUM_MAX, ADDRNUM, MAJORITY_ADDR, IMEM_SIZE);

  printf("\nOK!\n");
  printf("\n ------------------------------ 終了 -------------------------------- \n\n");
  return 0;
}