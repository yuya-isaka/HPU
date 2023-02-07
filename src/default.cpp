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

void check(const int THREADSNUM, const int DIM, int argc, char **argv, const int DEBUG)
{
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

  // アイテムメモリの設定
  verilator_top->S_AXI_AWADDR = 4;
  verilator_top->S_AXI_WDATA = RANNUM - 1; // 1023番目をランダムな値に使う
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // RNGリセット信号
  // reset <- 1;
  verilator_top->S_AXI_AWADDR = 8;
  verilator_top->S_AXI_WDATA = 1;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // RNG生成信号 (ランダムなハイパーベクトルを自動生成)
  // gen <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 1;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // RNG生成終了を待つ
  verilator_top->S_AXI_ARVALID = 1;
  eval();
  eval();
  while (0 != verilator_top->S_AXI_RDATA)
  {
    eval();
  }
  verilator_top->S_AXI_ARVALID = 0;
  eval();

  ////////////////////////////////////////////////////////////////////////////// compute ///////////////////////////////////////////////////////////////////////////////

  // HDCプロセッサ起動
  // run <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 2;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // 送信処理
  verilator_top->S_AXIS_TVALID = 1;
  eval();

  for (int k = 0; k < THREADSNUM; k++)
  {
    conv.data_0 = assemble("load", 0);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();
  }

  for (int k = 0; k < THREADSNUM; k++)
  {
    conv.data_0 = assemble("store", 0);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA = conv.write_data;
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

  for (int k = 0; k < 1; k++)
  {
    conv.data_0 = assemble("last", 0);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();
  }

  // 送信終了
  verilator_top->S_AXIS_TVALID = 0;

  // 最後の送信途中で止まる対策 --------------
  verilator_top->S_AXIS_TDATA = 0;
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
    for (int i = 0; i < 32; i++)
    {
      printf("  %u\n", verilator_top->M_AXIS_TDATA);
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
  const int THREADSNUM = 5;
  // 次元数可変
  // const int DIM = 32 / 32;
  const int DIM = 1024 / 32;

  // 単体テスト1
  DEBUG = 0;
  check(THREADSNUM, DIM, argc, argv, DEBUG);

  // 単体テスト2
  DEBUG = 1;
  check(THREADSNUM, DIM, argc, argv, DEBUG);

  printf("\n ======================================= 終了 ========================================= \n\n");
  return 0;
}