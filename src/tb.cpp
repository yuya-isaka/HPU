// include
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h" // top.v
#include <string.h>
#include <iostream>

const int RANNUM = 512;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vluint64_t main_time = 0;
vluint64_t sim_start = 0;
vluint64_t sim_end = sim_start + 3000000;

VerilatedVcdC *tfp;
Vtop *verilator_top;

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
uint32_t assemble(const char inst_str[], uint32_t addr)
{
  uint32_t inst = 0;
  uint32_t result = 0;

  if (strcmp(inst_str, "load.1") == 0)
  {
    inst = 2147487744;
    result = inst | addr;
  }

  else if (strcmp(inst_str, "xor.121") == 0)
  {
    result = 2147491840;
  }

  else if (strcmp(inst_str, "xor.p21") == 0)
  {
    result = 2147500032;
  }

  else if (strcmp(inst_str, "xor.p11") == 0)
  {
    result = 2147516416;
  }

  else if (strcmp(inst_str, "move.21") == 0)
  {
    result = 2147549184;
  }

  else if (strcmp(inst_str, "move.p1") == 0)
  {
    result = 2147614720;
  }

  else if (strcmp(inst_str, "load.2") == 0)
  {
    inst = 1073745920;
    result = inst | addr;
  }

  else if (strcmp(inst_str, "xor.122") == 0)
  {
    result = 1073750016;
  }

  else if (strcmp(inst_str, "xor.p22") == 0)
  {
    result = 1073758208;
  }

  else if (strcmp(inst_str, "xor.p12") == 0)
  {
    result = 1073774592;
  }

  else if (strcmp(inst_str, "move.12") == 0)
  {
    result = 1073807360;
  }

  else if (strcmp(inst_str, "move.p2") == 0)
  {
    result = 1073872896;
  }

  else if (strcmp(inst_str, "permute.2") == 0)
  {
    inst = 536875008;
    result = inst | addr;
  }

  else if (strcmp(inst_str, "permute.1") == 0)
  {
    inst = 536870912;
    result = inst | addr;
  }

  else if (strcmp(inst_str, "store.2") == 0)
  {
    result = 268439552;
  }

  else if (strcmp(inst_str, "store.1") == 0)
  {
    result = 268443648;
  }

  else if (strcmp(inst_str, "store.p") == 0)
  {
    result = 268451840;
  }

  else if (strcmp(inst_str, "last") == 0)
  {
    result = 268468224;
  }

  else if (strcmp(inst_str, "nop") == 0)
  {
    result = 0;
  }

  else
  {
    printf("error");
  }

  return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

  // 偶数処理
  if (EVEN)
  {
    for (int k = 0; k < THREADSNUM; k++)
    {
      if (k == 0)
      {
        // load
        uint32_t addr = MAJORITY_ADDR;
        verilator_top->S_AXIS_TDATA = assemble("load.2", addr);
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
        verilator_top->S_AXIS_TDATA = assemble("store.2", 0);
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
    // load
    for (int k = 0; k < THREADSNUM; k++)
    {
      uint32_t addr = j + (NGRAM * CORENUM * k);
      verilator_top->S_AXIS_TDATA = assemble("load.1", addr);
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
      uint32_t addr = 1 + j + (NGRAM * CORENUM * k);
      verilator_top->S_AXIS_TDATA = assemble("load.2", addr);
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

    for (int k = 0; k < THREADSNUM; k++)
    {
      verilator_top->S_AXIS_TDATA = assemble("permute.2", 1);
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

    for (int k = 0; k < THREADSNUM; k++)
    {
      verilator_top->S_AXIS_TDATA = assemble("xor.p11", 0);
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
      uint32_t addr = 2 + j + (NGRAM * CORENUM * k);
      verilator_top->S_AXIS_TDATA = assemble("load.2", addr);
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

    for (int k = 0; k < THREADSNUM; k++)
    {
      verilator_top->S_AXIS_TDATA = assemble("permute.2", 2);
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

    for (int k = 0; k < THREADSNUM; k++)
    {
      verilator_top->S_AXIS_TDATA = assemble("xor.p11", 0);
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
      for (int k = 0; k < THREADSNUM; k++)
      {
        verilator_top->S_AXIS_TDATA = assemble("store.1", 0);
        eval();
      }

      // last
      verilator_top->S_AXIS_TDATA = assemble("last", 0);
      eval();
    }
    else
    {
      for (int k = 0; k < THREADSNUM; k++)
      {
        verilator_top->S_AXIS_TDATA = assemble("store.1", 0);
        eval();
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
  const int CORENUM = 1;

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