// include
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h" // top.v
#include <string.h>
#include <iostream>

const int RANNUM = 512;
// const int RANNUM = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vluint64_t main_time = 0;
vluint64_t sim_start = 0;
vluint64_t sim_end = sim_start + 3000000;

VerilatedVcdC *tfp;
Vtop *verilator_top;

// Verilatorの代入が32bitごと
union
{
  struct
  {
    uint16_t data_0;
    uint16_t data_1;
  };
  uint32_t write_data;
} conv;

// 1クロック進みながら２回評価　（立ち下がり、立ち上がり）
void eval()
{
  verilator_top->S_AXI_ACLK = 0;
  verilator_top->AXIS_ACLK = 0;
  verilator_top->eval();

  if ((sim_start <= main_time) & ((main_time < sim_end) | (sim_end == 0)))
  {
    tfp->dump(main_time);
  }
  main_time += 5;

  verilator_top->S_AXI_ACLK = 1;
  verilator_top->AXIS_ACLK = 1;
  verilator_top->eval();

  if ((main_time >= sim_start) & ((main_time < sim_end) | (sim_end == 0)))
  {
    tfp->dump(main_time);
  }
  main_time += 5;

  return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

// 簡易アセンブラ
uint16_t assemble(const char inst_str[], uint16_t addr)
{
  if (strcmp(inst_str, "load") == 0 || strcmp(inst_str, "permute") == 0 || strcmp(inst_str, "simd_permute") == 0)
  {
    uint16_t result = 0;
    uint16_t inst = 0;

    // load
    if (strcmp(inst_str, "load") == 0)
    {
      inst = 40960;
      result = inst | addr;
    }

    else if (strcmp(inst_str, "permute") == 0)
    {
      inst = 34816;
      result = inst | addr;
    }

    else if (strcmp(inst_str, "simd_permute") == 0)
    {
      inst = 34816 + 1024;
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

    else if (strcmp(inst_str, "simd_xor") == 0)
    {
      inst = 8192 + 1024;
    }

    // pxor
    else if (strcmp(inst_str, "pxor") == 0)
    {
      inst = 24576;
    }

    else if (strcmp(inst_str, "simd_pxor") == 0)
    {
      inst = 24576 + 1024;
    }

    // store
    else if (strcmp(inst_str, "store") == 0)
    {
      inst = 4096;
    }

    else if (strcmp(inst_str, "simd_store") == 0)
    {
      inst = 4096 + 1024;
    }

    // pstore
    else if (strcmp(inst_str, "pstore") == 0)
    {
      inst = 20480;
    }

    else if (strcmp(inst_str, "simd_pstore") == 0)
    {
      inst = 20480 + 1024;
    }

    // move
    else if (strcmp(inst_str, "move") == 0)
    {
      inst = 2048;
    }

    else if (strcmp(inst_str, "simd_move") == 0)
    {
      inst = 2048 + 1024;
    }

    // pmove
    else if (strcmp(inst_str, "pmove") == 0)
    {
      inst = 18432;
    }

    else if (strcmp(inst_str, "simd_pmove") == 0)
    {
      inst = 18432 + 1024;
    }

    // last
    else if (strcmp(inst_str, "last") == 0)
    {
      inst = 256;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    NGRAM   = 1 ~
//    CORENUM = 1 - 14
//    ADDRNUM = NGRAMの倍数 (shifter_newを使ったテストをしているから。また、LASTが０のままになりtb.cppでは止まる。test.cppでは動くけどNGRAMの倍数以外は同じ値が出る)
//    DIM     = 32 or 1024
//    MAJORITY_ADDR = 偶数処理
//    argc    ... Verilatorに必要
//    **argv  ... Verilatorに必要
//    DEBUG   = DMA中断するか否か
void check(const int NGRAM, const int CORENUM, const int THREADSNUM, const int ADDRNUM, const int DIM, const int MAJORITY_ADDR, int argc, char **argv, const int DEBUG)
{

  // CORENUMの数すべてを使わないケースがあるか調べる
  const int REMAINDAR = (ADDRNUM / NGRAM) % (CORENUM * THREADSNUM);

  // あまりに使うコア数
  const int REMAINDAR_CORENUM = REMAINDAR / THREADSNUM;

  // 偶数処理
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

  // バス幅
  const int BUS = 32 / 32;

  // 最後の送信
  int LAST = (ADDRNUM / NGRAM) / (CORENUM * THREADSNUM);

  // CORENUMの倍数だったらきっちりコアを使い切るので、最後の数が１個減る
  if (REMAINDAR == 0)
  {
    LAST--;
  }

  LAST *= NGRAM * CORENUM * THREADSNUM;

  ////////////////////////////////////////////////////////////////////////////// Verilator setup /////////////////////////////////////////////////////////////////////////////////////////

  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  verilator_top = new Vtop;
  verilator_top->trace(tfp, 99);
  tfp->open("tmp.vcd");
  main_time = 0;

  //////////////////////////////////////////////////////////////////////////////// initial begin ///////////////////////////////////////////////////////////////////////////////////////////

  verilator_top->S_AXI_BREADY = 1;
  verilator_top->S_AXI_WSTRB = 15;
  verilator_top->S_AXI_RREADY = 1;
  verilator_top->S_AXIS_TSTRB = 255;
  verilator_top->S_AXIS_TLAST = 0;
  verilator_top->M_AXIS_TREADY = 1;

  verilator_top->S_AXI_ARESETN = 0;
  verilator_top->S_AXI_ACLK = 1;
  verilator_top->AXIS_ARESETN = 0;
  verilator_top->AXIS_ACLK = 1;
  verilator_top->S_AXI_ARVALID = 0;
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  verilator_top->S_AXIS_TVALID = 0;
  verilator_top->eval();
  main_time += 5;

  eval();
  eval();
  verilator_top->S_AXI_ARESETN = 1;
  verilator_top->AXIS_ARESETN = 1;
  eval();
  eval();

  //////////////////////////////////////////////////////////////////////////////// start /////////////////////////////////////////////////////////////////////////////

  // comunicate ===============================================================================================
  // RNG生成信号 (ランダムなハイパーベクトルを自動生成)
  // com <- 2;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 2; // 3でもいけるはず
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // 送信処理
  verilator_top->S_AXIS_TVALID = 1;
  // VALIDとDATAは同時に届くのでここのeval()はおかしい
  // eval();

  verilator_top->S_AXIS_TDATA = 88675123;
  eval();

  for (int k = 0; k < 12; k++)
  {
    verilator_top->S_AXIS_TDATA = xor128(0);
    eval();
  }

  if (DEBUG)
  {
    // 送信途中で止まる対策 -----------------------------
    verilator_top->S_AXIS_TVALID = 0;
    verilator_top->S_AXIS_TDATA = 0;
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    // ----------------------------------------------
  }

  for (int k = 0; k < 2; k++)
  {
    verilator_top->S_AXIS_TDATA = xor128(0);
    eval();
  }

  if (DEBUG)
  {
    // 送信途中で止まる対策 -----------------------------
    verilator_top->S_AXIS_TVALID = 0;
    verilator_top->S_AXIS_TDATA = 0;
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    // ----------------------------------------------
  }

  for (int k = 0; k < 17; k++)
  {
    verilator_top->S_AXIS_TDATA = xor128(0);
    eval();
  }

  for (int i = 0; i < RANNUM - 1; i++)
  {
    for (int k = 0; k < 13; k++)
    {
      verilator_top->S_AXIS_TDATA = xor128(0);
      eval();
    }

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      verilator_top->S_AXIS_TVALID = 0;
      verilator_top->S_AXIS_TDATA = 0;
      eval();
      eval();
      eval();
      verilator_top->S_AXIS_TVALID = 1;
      // ----------------------------------------------
    }

    for (int k = 0; k < 2; k++)
    {
      verilator_top->S_AXIS_TDATA = xor128(0);
      eval();
    }

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      verilator_top->S_AXIS_TVALID = 0;
      verilator_top->S_AXIS_TDATA = 0;
      eval();
      eval();
      eval();
      verilator_top->S_AXIS_TVALID = 1;
      // ----------------------------------------------
    }

    for (int k = 0; k < 17; k++)
    {
      verilator_top->S_AXIS_TDATA = xor128(0);
      eval();
    }
  }

  // 送信終了
  verilator_top->S_AXIS_TVALID = 0;
  verilator_top->S_AXIS_TDATA = 0;
  // comunicate ===============================================================================================

  ////////////////////////////////////////////////////////////////////////////// compute ///////////////////////////////////////////////////////////////////////////////

  // HDCプロセッサ起動
  // run <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 1;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // 送信処理
  verilator_top->S_AXIS_TVALID = 1;
  // VALIDとDATAは同時に届くのでここのeval()はおかしい
  // eval();

  int tmp = 0;

  // 偶数処理
  if (EVEN)
  {
    for (int k = 0; k < THREADSNUM; k++)
    {
      if (k == 0)
      {
        // load
        uint16_t addr = MAJORITY_ADDR;
        conv.data_0 = assemble("load", addr);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
      }
      else
      {
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
      }
      eval();
    }

    for (int k = 0; k < THREADSNUM; k++)
    {
      if (k == 0)
      {
        // store
        tmp = 0;
        conv.data_0 = assemble("store", 0);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
      }
      else
      {
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
      }
      eval();
    }
  }

  for (int j = 0; j < ADDRNUM; j += NGRAM * CORENUM * THREADSNUM)
  {
    // 余り処理
    if (REMAINDAR != 0 && j == LAST)
    {

      // load
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          uint16_t addr = NGRAM * i + j + (NGRAM * REMAINDAR_CORENUM * k);
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("load", addr);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("load", addr);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // move
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("move", 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("move", 0);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // load
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          uint16_t addr = NGRAM * i + 1 + j + (NGRAM * REMAINDAR_CORENUM * k);
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("load", addr);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("load", addr);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // Permutation
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("permute", 1);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("permute", 1);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // xor
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("pxor", 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("pxor", 0);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // move
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("move", 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("move", 0);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // load
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          uint16_t addr = NGRAM * i + 2 + j + (NGRAM * REMAINDAR_CORENUM * k);
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("load", addr);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("load", addr);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // Permutation
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("permute", 2);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("permute", 2);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // xor
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("pxor", 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("pxor", 0);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // store
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < REMAINDAR_CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("store", 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("store", 0);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (REMAINDAR_CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      // last
      tmp = 0;
      for (int i = 0; i < 1; i++)
      {
        conv.data_0 = assemble("last", 0);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < BUS; i++)
      {
        verilator_top->S_AXIS_TDATA = 0;
      }
      eval();
    } //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
      // load
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          uint16_t addr = NGRAM * i + j + (NGRAM * CORENUM * k);
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("load", addr);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("load", addr);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      //   // move
      // for (int k = 0; k < THREADSNUM; k++)
      // {
      //   tmp = 0;
      //   for (int i = 0; i < CORENUM; i++)
      //   {
      //     if (i % 2 == 0)
      //     {
      //       conv.data_0 = assemble("move", 0);
      //       conv.data_1 = 0;
      //     }
      //     else
      //     {
      //       conv.data_1 = assemble("move", 0);
      //       verilator_top->S_AXIS_TDATA = conv.write_data;
      //       tmp++;
      //     }
      //   }
      //   // 奇数のとき最後の代入ができていない
      //   if (CORENUM % 2 != 0)
      //   {
      //     verilator_top->S_AXIS_TDATA = conv.write_data;
      //     tmp++;
      //   }
      //   for (int i = tmp; i < BUS; i++)
      //   {
      //     verilator_top->S_AXIS_TDATA = 0;
      //   }
      //   eval();
      // }

      // simd_move
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        conv.data_0 = assemble("simd_move", 0);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // load
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          uint16_t addr = NGRAM * i + 1 + j + (NGRAM * CORENUM * k);
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("load", addr);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("load", addr);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      //   // Permutation
      // for (int k = 0; k < THREADSNUM; k++)
      // {
      //   tmp = 0;
      //   for (int i = 0; i < CORENUM; i++)
      //   {
      //     if (i % 2 == 0)
      //     {
      //       conv.data_0 = assemble("permute", 1);
      //       conv.data_1 = 0;
      //     }
      //     else
      //     {
      //       conv.data_1 = assemble("permute", 1);
      //       verilator_top->S_AXIS_TDATA = conv.write_data;
      //       tmp++;
      //     }
      //   }
      //   // 奇数のとき最後の代入ができていない
      //   if (CORENUM % 2 != 0)
      //   {
      //     verilator_top->S_AXIS_TDATA = conv.write_data;
      //     tmp++;
      //   }
      //   for (int i = tmp; i < BUS; i++)
      //   {
      //     verilator_top->S_AXIS_TDATA = 0;
      //   }
      //   eval();
      // }

      // Simd_Permutation
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        conv.data_0 = assemble("simd_permute", 1);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      //   // xor
      // for (int k = 0; k < THREADSNUM; k++)
      // {
      //   tmp = 0;
      //   for (int i = 0; i < CORENUM; i++)
      //   {
      //     if (i % 2 == 0)
      //     {
      //       conv.data_0 = assemble("pxor", 0);
      //       conv.data_1 = 0;
      //     }
      //     else
      //     {
      //       conv.data_1 = assemble("pxor", 0);
      //       verilator_top->S_AXIS_TDATA = conv.write_data;
      //       tmp++;
      //     }
      //   }
      //   // 奇数のとき最後の代入ができていない
      //   if (CORENUM % 2 != 0)
      //   {
      //     verilator_top->S_AXIS_TDATA = conv.write_data;
      //     tmp++;
      //   }
      //   for (int i = tmp; i < BUS; i++)
      //   {
      //     verilator_top->S_AXIS_TDATA = 0;
      //   }
      //   eval();
      // }

      // Simd_Xor
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        conv.data_0 = assemble("simd_pxor", 0);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      //   // move
      // for (int k = 0; k < THREADSNUM; k++)
      // {
      //   tmp = 0;
      //   for (int i = 0; i < CORENUM; i++)
      //   {
      //     if (i % 2 == 0)
      //     {
      //       conv.data_0 = assemble("move", 0);
      //       conv.data_1 = 0;
      //     }
      //     else
      //     {
      //       conv.data_1 = assemble("move", 0);
      //       verilator_top->S_AXIS_TDATA = conv.write_data;
      //       tmp++;
      //     }
      //   }
      //   // 奇数のとき最後の代入ができていない
      //   if (CORENUM % 2 != 0)
      //   {
      //     verilator_top->S_AXIS_TDATA = conv.write_data;
      //     tmp++;
      //   }
      //   for (int i = tmp; i < BUS; i++)
      //   {
      //     verilator_top->S_AXIS_TDATA = 0;
      //   }
      //   eval();
      // }

      // Simd_Move
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        conv.data_0 = assemble("simd_move", 0);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // load
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          uint16_t addr = NGRAM * i + 2 + j + (NGRAM * CORENUM * k);
          if (i % 2 == 0)
          {
            conv.data_0 = assemble("load", addr);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble("load", addr);
            verilator_top->S_AXIS_TDATA = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      //   // Permutation
      // for (int k = 0; k < THREADSNUM; k++)
      // {
      //   tmp = 0;
      //   for (int i = 0; i < CORENUM; i++)
      //   {
      //     if (i % 2 == 0)
      //     {
      //       conv.data_0 = assemble("permute", 2);
      //       conv.data_1 = 0;
      //     }
      //     else
      //     {
      //       conv.data_1 = assemble("permute", 2);
      //       verilator_top->S_AXIS_TDATA = conv.write_data;
      //       tmp++;
      //     }
      //   }
      //   // 奇数のとき最後の代入ができていない
      //   if (CORENUM % 2 != 0)
      //   {
      //     verilator_top->S_AXIS_TDATA = conv.write_data;
      //     tmp++;
      //   }
      //   for (int i = tmp; i < BUS; i++)
      //   {
      //     verilator_top->S_AXIS_TDATA = 0;
      //   }
      //   eval();
      // }

      // Simd_Permutation
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        conv.data_0 = assemble("simd_permute", 2);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      //   // xor
      // for (int k = 0; k < THREADSNUM; k++)
      // {
      //   tmp = 0;
      //   for (int i = 0; i < CORENUM; i++)
      //   {
      //     if (i % 2 == 0)
      //     {
      //       conv.data_0 = assemble("pxor", 0);
      //       conv.data_1 = 0;
      //     }
      //     else
      //     {
      //       conv.data_1 = assemble("pxor", 0);
      //       verilator_top->S_AXIS_TDATA = conv.write_data;
      //       tmp++;
      //     }
      //   }
      //   // 奇数のとき最後の代入ができていない
      //   if (CORENUM % 2 != 0)
      //   {
      //     verilator_top->S_AXIS_TDATA = conv.write_data;
      //     tmp++;
      //   }
      //   for (int i = tmp; i < BUS; i++)
      //   {
      //     verilator_top->S_AXIS_TDATA = 0;
      //   }
      //   eval();
      // }

      // Simd_xor
      for (int k = 0; k < THREADSNUM; k++)
      {
        tmp = 0;
        conv.data_0 = assemble("simd_pxor", 0);
        conv.data_1 = 0;
        verilator_top->S_AXIS_TDATA = conv.write_data;
        tmp++;
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        // ----------------------------------------------
      }

      // ラスト処理
      if (j == LAST)
      {
        //   // store
        // for (int k = 0; k < THREADSNUM; k++)
        // {
        //   tmp = 0;
        //   for (int i = 0; i < CORENUM; i++)
        //   {
        //     if (i % 2 == 0)
        //     {
        //       conv.data_0 = assemble("store", 0);
        //       conv.data_1 = 0;
        //     }
        //     else
        //     {
        //       conv.data_1 = assemble("store", 0);
        //       verilator_top->S_AXIS_TDATA = conv.write_data;
        //       tmp++;
        //     }
        //   }
        //   // 奇数のとき最後の代入ができていない
        //   if (CORENUM % 2 != 0)
        //   {
        //     verilator_top->S_AXIS_TDATA = conv.write_data;
        //     tmp++;
        //   }
        //   for (int i = tmp; i < BUS; i++)
        //   {
        //     verilator_top->S_AXIS_TDATA = 0;
        //   }
        //   eval();
        // }

        // simd_store
        for (int k = 0; k < THREADSNUM; k++)
        {
          tmp = 0;
          conv.data_0 = assemble("simd_store", 0);
          conv.data_1 = 0;
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
          for (int i = tmp; i < BUS; i++)
          {
            verilator_top->S_AXIS_TDATA = 0;
          }
          eval();
        }

        // last
        tmp = 0;
        for (int i = 0; i < 1; i++)
        {
          conv.data_0 = assemble("last", 0);
          conv.data_1 = 0;
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < BUS; i++)
        {
          verilator_top->S_AXIS_TDATA = 0;
        }
        eval();
      }
      else
      {
        //   // store
        // for (int k = 0; k < THREADSNUM; k++)
        // {
        //   tmp = 0;
        //   for (int i = 0; i < CORENUM; i++)
        //   {
        //     if (i % 2 == 0)
        //     {
        //       conv.data_0 = assemble("store", 0);
        //       conv.data_1 = 0;
        //     }
        //     else
        //     {
        //       conv.data_1 = assemble("store", 0);
        //       verilator_top->S_AXIS_TDATA = conv.write_data;
        //       tmp++;
        //     }
        //   }
        //   // 奇数のとき最後の代入ができていない
        //   if (CORENUM % 2 != 0)
        //   {
        //     verilator_top->S_AXIS_TDATA = conv.write_data;
        //     tmp++;
        //   }
        //   for (int i = tmp; i < BUS; i++)
        //   {
        //     verilator_top->S_AXIS_TDATA = 0;
        //   }
        //   eval();
        // }

        // simd_store
        for (int k = 0; k < THREADSNUM; k++)
        {
          tmp = 0;
          conv.data_0 = assemble("simd_store", 0);
          conv.data_1 = 0;
          verilator_top->S_AXIS_TDATA = conv.write_data;
          tmp++;
          for (int i = tmp; i < BUS; i++)
          {
            verilator_top->S_AXIS_TDATA = 0;
          }
          eval();
        }
      }
    }
  }

  // 送信終了
  verilator_top->S_AXIS_TVALID = 0;

  // 最後の送信途中で止まる対策 --------------
  for (int i = 0; i < BUS; i++)
  {
    verilator_top->S_AXIS_TDATA = 0;
  }
  eval();
  eval();
  eval();
  // -------------------------------------

  // 演算結果を待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  /////////////////////////////////////////////////////////////////////////////////////////  Output ////////////////////////////////////////////////////////////////////////////////////

  // 32bit出力
  if (DIM == 1)
  {
    // 16 * 2 = 32
    for (int i = 0; i < 2; i++)
    {
      if (i == 1)
      {
        printf("  %u\n", verilator_top->M_AXIS_TDATA);
      }
      eval();
    }
  }
  // 1024bit出力
  else
  {
    // 256 * 4 = 1024
    for (int i = 0; i < (32 / BUS); i++)
    {
      // 32 * 8 = 256
      for (int j = 0; j < BUS; j++)
      {
        printf("  %u\n", verilator_top->M_AXIS_TDATA);
      }
      eval();
    }
  }
  eval();
  eval();
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  // 終了処理
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 0;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  eval();
  eval();
  verilator_top->S_AXI_ARESETN = 0;
  verilator_top->AXIS_ARESETN = 0;
  eval();
  eval();

  delete verilator_top;
  tfp->close();
  return;
}

int main(int argc, char **argv)
{
  printf("\n ====================================== 開始 ========================================= \n\n");

  int DEBUG = 0;
  int ADDRNUM = 0;

  // NGRAM
  const int NGRAM = 3;

  // コア数可変
  const int CORENUM = 2;

  // スレッド数可変
  const int THREADSNUM = 5;

  // 偶数処理
  const int MAJORITY_ADDR = RANNUM - 1;

  // 次元数可変
  // const int DIM = 32 / 32;
  const int DIM = 1024 / 32;

  // テスト
  // const int SIMULATION_COUNT = 100;
  // for (int i = 30; i < SIMULATION_COUNT; i += 30)
  // {
  //   ADDRNUM = i;
  //   DEBUG = 1;
  //   check(NGRAM, CORENUM, THREADSNUM, ADDRNUM, DIM, MAJORITY_ADDR, argc, argv, DEBUG);
  // }

  // 単体テスト1
  ADDRNUM = 300;
  DEBUG = 1;
  check(NGRAM, CORENUM, THREADSNUM, ADDRNUM, DIM, MAJORITY_ADDR, argc, argv, DEBUG);

  xor128(1);

  // 単体テスト2
  ADDRNUM = 90;
  DEBUG = 1;
  check(NGRAM, CORENUM, THREADSNUM, ADDRNUM, DIM, MAJORITY_ADDR, argc, argv, DEBUG);

  printf("\n ======================================= 終了 ========================================= \n\n");
  return 0;
}