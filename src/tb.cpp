// iclude
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"
#include <string.h>
#include <iostream>

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
  };
  uint32_t write_data;
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

// 可変のパラメータ

const int NGRAM = 3;
const int ADDRNUM = 144; // 現状12の倍数しかできない。その理由は命令をちゃんと設定していないから (4コアの時は12の倍数、３２コアの時は96の倍数)
const int LAST = ADDRNUM - 48;
const int CORENUM = 16;
const int RANNUM = 1000;
const int DIM = 32 / 32;
// top.v DIM
// top.v WI
// top.v buffer_ctrl DIM
// top.v rand_numの代入部分
// top.v core DIM

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 自動で決まるパラメータ

// const int ADDRJ = NGRAM - 1;
// const int ADDRI = ((ADDRNUM / NGRAM) - 1) / CORENUM;
// const int REMAINDER = (ADDRNUM / NGRAM) % CORENUM;
const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
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

  printf("\n ---------------------------- 開始 ----------------------------- \n");

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
  verilator_top->S_AXI_WDATA = RANNUM;
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

  printf("\n  生成！\n");
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
    for (int i = 0; i < CORENUM; i++)
    {
      conv.data_0 = NGRAM * i + j;
      conv.data_1 = 1;
      verilator_top->S_AXIS_TDATA[i] = conv.write_data;
    }
    for (int i = CORENUM; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    verilator_top->S_AXIS_TVALID = 0;
    eval();
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    eval();

    // 6
    for (int i = 0; i < CORENUM; i++)
    {
      conv.data_0 = 0;
      conv.data_1 = 64;
      verilator_top->S_AXIS_TDATA[i] = conv.write_data;
    }
    for (int i = CORENUM; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    verilator_top->S_AXIS_TVALID = 0;
    eval();
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    eval();

    // 1
    for (int i = 0; i < CORENUM; i++)
    {
      conv.data_0 = NGRAM * i + 1 + j;
      conv.data_1 = 2;
      verilator_top->S_AXIS_TDATA[i] = conv.write_data;
    }
    for (int i = CORENUM; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    verilator_top->S_AXIS_TVALID = 0;
    eval();
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    eval();

    // 4
    for (int i = 0; i < CORENUM; i++)
    {
      conv.data_0 = 0;
      conv.data_1 = 16;
      verilator_top->S_AXIS_TDATA[i] = conv.write_data;
    }
    for (int i = CORENUM; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    verilator_top->S_AXIS_TVALID = 0;
    eval();
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    eval();

    // 6
    for (int i = 0; i < CORENUM; i++)
    {
      conv.data_0 = 0;
      conv.data_1 = 64;
      verilator_top->S_AXIS_TDATA[i] = conv.write_data;
    }
    for (int i = CORENUM; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    verilator_top->S_AXIS_TVALID = 0;
    eval();
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    eval();

    // 1
    for (int i = 0; i < CORENUM; i++)
    {
      conv.data_0 = NGRAM * i + 2 + j;
      conv.data_1 = 2;
      verilator_top->S_AXIS_TDATA[i] = conv.write_data;
    }
    for (int i = CORENUM; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    verilator_top->S_AXIS_TVALID = 0;
    eval();
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    eval();

    // 2
    for (int i = 0; i < CORENUM; i++)
    {
      conv.data_0 = 0;
      conv.data_1 = 4;
      verilator_top->S_AXIS_TDATA[i] = conv.write_data;
    }
    for (int i = CORENUM; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    verilator_top->S_AXIS_TVALID = 0;
    eval();
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    eval();

    // 4
    for (int i = 0; i < CORENUM; i++)
    {

      conv.data_0 = 0;
      conv.data_1 = 16;
      verilator_top->S_AXIS_TDATA[i] = conv.write_data;
    }
    for (int i = CORENUM; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    verilator_top->S_AXIS_TVALID = 0;
    eval();
    eval();
    eval();
    eval();
    verilator_top->S_AXIS_TVALID = 1;
    eval();

    if (j == LAST)
    {
      // 7
      for (int i = 0; i < CORENUM; i++)
      {

        conv.data_0 = 0;
        conv.data_1 = 128;
        verilator_top->S_AXIS_TDATA[i] = conv.write_data;
      }
      for (int i = CORENUM; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();
    }
    else
    {
      // 5
      for (int i = 0; i < CORENUM; i++)
      {

        conv.data_0 = 0;
        conv.data_1 = 32;
        verilator_top->S_AXIS_TDATA[i] = conv.write_data;
      }
      for (int i = CORENUM; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();
    }

    j += NGRAM * CORENUM - 1;
  }

  // ↑ここを書き換える==================================================================

  verilator_top->S_AXIS_TVALID = 0;
  eval();

  // 演算結果を待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  // ==================================================================

  printf("\n --------------------------- Output ---------------------------- \n\n\n");

  for (int i = 0; i < 1; i++)
  {
    for (int j = 0; j < DIM; j++)
    {
      printf("  %u\n", verilator_top->M_AXIS_TDATA[j]);
      putb(verilator_top->M_AXIS_TDATA[j]);
      printf("\n");
    }
    // printf("  %u\n\n", verilator_top->M_AXIS_TDATA[0]);
    // putb(verilator_top->M_AXIS_TDATA[0]);
    eval();
  }

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

  printf("\n --------------------------- 終了 ------------------------------- \n\n");
  delete verilator_top;
  tfp->close();
  return 0;
}
