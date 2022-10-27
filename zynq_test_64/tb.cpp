// iclude
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"
#include <string.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 可変パラメータ

// 結果を何個出力するかに使う
const int DIM = 32 / 32;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 変わらん

const int RANNUM = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vluint64_t main_time = 0;
vluint64_t sim_start = 0;
vluint64_t sim_end = sim_start + 3000000;

VerilatedVcdC *tfp;
Vtop *verilator_top;

union
{
  struct
  {
    uint16_t data_0;
    uint16_t data_1;
    uint16_t data_2;
    uint16_t data_3;
  };
  uint64_t write_data;
} conv;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void eval()
{
  // Neg edge
  verilator_top->S_AXI_ACLK = 0;
  verilator_top->AXIS_ACLK = 0;
  // 立ち下がりの評価
  verilator_top->eval();

  if ((sim_start <= main_time) & ((main_time < sim_end) | (sim_end == 0)))
  {
    tfp->dump(main_time);
  }
  main_time += 5;

  // Pos edge
  verilator_top->S_AXI_ACLK = 1;
  verilator_top->AXIS_ACLK = 1;
  // 立ち上がりの評価
  verilator_top->eval();

  if ((main_time >= sim_start) & ((main_time < sim_end) | (sim_end == 0)))
  {
    tfp->dump(main_time);
  }
  main_time += 5;

  return;
}

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
  printf("  0"), putchar('b'), printb(v), printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check(const int NGRAM, const int CORENUM, const int ADDRNUM, int argc, char **argv, const int DEBUG)
{

  const int LAST = ADDRNUM - 48;
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

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

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // item_memory_num <- 1000;
  verilator_top->S_AXI_AWADDR = 4;
  verilator_top->S_AXI_WDATA = RANNUM - 1;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // matw <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 1;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  verilator_top->S_AXI_ARVALID = 1;
  eval();
  eval();
  while (0 != verilator_top->S_AXI_RDATA)
  {
    eval();
  }
  verilator_top->S_AXI_ARVALID = 0;
  eval();

  // printf("\n  生成！\n");
  // matwはここで０になっている

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Parameter セットアップ

  // even
  verilator_top->S_AXI_AWADDR = 8;
  verilator_top->S_AXI_WDATA = EVEN;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // run <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 2;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // ==================================================================

  // 送信
  verilator_top->S_AXIS_TVALID = 1;

  // ↓ここを書き換える==================================================================

  // ロード
  //  0. ロードデータをreg2に格納 (reg0 → reg2)
  //      a. 0000000000000001
  //      b. 1

  // Permutation
  //  1. ロードデータを1Permしたものをreg2に格納 (reg0 → Perm → reg2)
  //      a. 0000000000000010
  //      b. 2
  //  2. reg2をPermしたものをreg2に格納 (reg2 → Perm → reg2)
  //      a. 0000000000000100
  //      b. 4

  // Xor
  //  3. ロードデータとreg2をXorしたものをreg2に格納（reg0 Xor reg2 → reg2）
  //      a. 0000000000001000
  //      b. 8
  //  4. reg1とreg2をXorしたものをreg2に格納（reg1 Xor reg2 → reg2）
  //      a. 0000000000010000
  //      b. 16

  // ストア
  //  5. reg2の値を吐き出す
  //      a. 0000000000100000
  //      b. 32

  // Copy
  //  6. reg2 → reg1
  //      a. 0000000001000000
  //      b. 64

  // ラストストア
  // 7. 最後
  //      a. 0000000010000000
  //      a. 128

  // 3-gram 0,6,1,4,6,1,2,4,5

  for (int j = 0; j < ADDRNUM; j++)
  {
    // 0
    conv.data_0 = NGRAM * 0 + j;
    conv.data_1 = 1;
    conv.data_2 = NGRAM * 1 + j;
    conv.data_3 = 1;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      // verilator_top->S_AXIS_TVALID = 0;
      // for (int i = 0; i < 2; i++)
      // {
      //   verilator_top->S_AXIS_TDATA[i] = 0;
      // }
      // eval();
      // eval();
      // eval();
      // verilator_top->S_AXIS_TVALID = 1;
      // eval();
      // ----------------------------------------------
    }

    // 6
    conv.data_0 = 0;
    conv.data_1 = 64;
    conv.data_2 = 0;
    conv.data_3 = 64;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      // verilator_top->S_AXIS_TVALID = 0;
      // for (int i = 0; i < 2; i++)
      // {
      //   verilator_top->S_AXIS_TDATA[i] = 0;
      // }
      // eval();
      // eval();
      // eval();
      // verilator_top->S_AXIS_TVALID = 1;
      // eval();
      // ----------------------------------------------
    }

    // 1
    conv.data_0 = NGRAM * 0 + 1 + j;
    conv.data_1 = 2;
    conv.data_2 = NGRAM * 1 + 1 + j;
    conv.data_3 = 2;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      // verilator_top->S_AXIS_TVALID = 0;
      // for (int i = 0; i < 2; i++)
      // {
      //   verilator_top->S_AXIS_TDATA[i] = 0;
      // }
      // eval();
      // eval();
      // eval();
      // verilator_top->S_AXIS_TVALID = 1;
      // eval();
      // ----------------------------------------------
    }

    // 4
    conv.data_0 = 0;
    conv.data_1 = 16;
    conv.data_2 = 0;
    conv.data_3 = 16;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      // verilator_top->S_AXIS_TVALID = 0;
      // for (int i = 0; i < 2; i++)
      // {
      //   verilator_top->S_AXIS_TDATA[i] = 0;
      // }
      // eval();
      // eval();
      // eval();
      // verilator_top->S_AXIS_TVALID = 1;
      // eval();
      // ----------------------------------------------
    }

    // 6
    conv.data_0 = 0;
    conv.data_1 = 64;
    conv.data_2 = 0;
    conv.data_3 = 64;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      // verilator_top->S_AXIS_TVALID = 0;
      // for (int i = 0; i < 2; i++)
      // {
      //   verilator_top->S_AXIS_TDATA[i] = 0;
      // }
      // eval();
      // eval();
      // eval();
      // verilator_top->S_AXIS_TVALID = 1;
      // eval();
      // ----------------------------------------------
    }

    // 1
    conv.data_0 = NGRAM * 0 + 2 + j;
    conv.data_1 = 2;
    conv.data_2 = NGRAM * 1 + 2 + j;
    conv.data_3 = 2;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      // verilator_top->S_AXIS_TVALID = 0;
      // for (int i = 0; i < 2; i++)
      // {
      //   verilator_top->S_AXIS_TDATA[i] = 0;
      // }
      // eval();
      // eval();
      // eval();
      // verilator_top->S_AXIS_TVALID = 1;
      // eval();
      // ----------------------------------------------
    }

    // 2
    conv.data_0 = 0;
    conv.data_1 = 4;
    conv.data_2 = 0;
    conv.data_3 = 4;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      // verilator_top->S_AXIS_TVALID = 0;
      // for (int i = 0; i < 2; i++)
      // {
      //   verilator_top->S_AXIS_TDATA[i] = 0;
      // }
      // eval();
      // eval();
      // eval();
      // verilator_top->S_AXIS_TVALID = 1;
      // eval();
      // ----------------------------------------------
    }

    // 4
    conv.data_0 = 0;
    conv.data_1 = 16;
    conv.data_2 = 0;
    conv.data_3 = 16;
    verilator_top->S_AXIS_TDATA = conv.write_data;
    eval();

    if (DEBUG)
    {
      // 送信途中で止まる対策 -----------------------------
      // verilator_top->S_AXIS_TVALID = 0;
      // for (int i = 0; i < 2; i++)
      // {
      //   verilator_top->S_AXIS_TDATA[i] = 0;
      // }
      // eval();
      // eval();
      // eval();
      // verilator_top->S_AXIS_TVALID = 1;
      // eval();
      // ----------------------------------------------
    }

    if (j == LAST)
    {
      // 7
      conv.data_0 = 0;
      conv.data_1 = 128;
      conv.data_2 = 0;
      conv.data_3 = 128;
      verilator_top->S_AXIS_TDATA = conv.write_data;
      eval();
    }
    else
    {
      // 5
      conv.data_0 = 0;
      conv.data_1 = 32;
      conv.data_2 = 0;
      conv.data_3 = 32;
      verilator_top->S_AXIS_TDATA = conv.write_data;
      eval();
    }

    j += NGRAM * CORENUM - 1;
  }

  // ↑ここを書き換える==================================================================

  // 最後の送信途中で止まる対策 -----------------------------
  // verilator_top->S_AXIS_TVALID = 0;
  // for (int i = 0; i < 2; i++)
  // {
  //   verilator_top->S_AXIS_TDATA[i] = 0;
  // }
  // eval();
  // eval();
  // eval();
  // ----------------------------------------------

  // 演算結果を待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  eval();
  eval();
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////  Output ////////////////////////////////////////////////////////////////////////////////////

  // printf("\n --------------------------- Output ---------------------------- \n\n\n");

  for (int i = 0; i < 16; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      printf("  %u\n", verilator_top->M_AXIS_TDATA);
      // putb(verilator_top->M_AXIS_TDATA[j]);
      printf("\n");
    }
    //   printf("  %u\n", verilator_top->M_AXIS_TDATA[j]);
    // printf("  %u\n\n", verilator_top->M_AXIS_TDATA[0]);
    // putb(verilator_top->M_AXIS_TDATA[0]);
    eval();
  }
  eval();
  eval();
  eval();

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

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  delete verilator_top;
  tfp->close();
  return;
}

int main(int argc, char **argv)
{
  printf("\n ================================================= 開始 ================================================= \n\n");

  const int NGRAM = 3;
  const int CORENUM = 2;
  int DEBUG = 0;
  int ADDRNUM = 0;

  for (int i = 48; i < RANNUM; i += 48)
  {
    ADDRNUM = i;

    DEBUG = 0;
    check(NGRAM, CORENUM, ADDRNUM, argc, argv, DEBUG);
    // DEBUG = 1;
    // check(NGRAM, CORENUM, ADDRNUM, argc, argv, DEBUG);

    printf(" --------\n\n");
  }

  printf("\n ================================================= 終了 ================================================= \n\n");

  return 0;
}