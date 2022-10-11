// iclude
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"
#include <string.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

union
{
  struct
  {
    unsigned int d0;
    unsigned int d1;
  };
  uint64_t wd;
} conv;

union
{
  struct
  {
    unsigned int d0;
    unsigned int d1;
  };
  uint64_t wd;
} conv2;

vluint64_t main_time = 0;
vluint64_t sim_start = 0;
vluint64_t sim_end = sim_start + 300000;

VerilatedVcdC *tfp;
Vtop *verilator_top;

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
  printf("  0"), putchar('b'), printb(v), printf("\n\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// N-gram
const int NGRAM = 3;

// test.cppのADDRNUMと同じ
// const int ADDRNUM = 960;
const int ADDRNUM = 900;

// ADDRNUMが奇数かどうか
// const int ODD = 0;

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
  verilator_top->S_AXI_AWADDR = 16;
  verilator_top->S_AXI_WDATA = 1000;
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

  // addr_j <- 2;
  verilator_top->S_AXI_AWADDR = 4;
  verilator_top->S_AXI_WDATA = 2;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // addr_i <- 9;
  verilator_top->S_AXI_AWADDR = 8;
  verilator_top->S_AXI_WDATA = 9;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // remainder <- 20;
  verilator_top->S_AXI_AWADDR = 12;
  verilator_top->S_AXI_WDATA = 20;
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

  // 送信
  verilator_top->S_AXIS_TVALID = 1;
  int tmp = NGRAM - 1;
  for (int i = 0; i < ADDRNUM; i++)
  {
    for (int j = 0; j < 32; j++)
    {
      verilator_top->S_AXIS_TDATA[j] = i + (NGRAM * j);
    }
    if (i == tmp)
    {
      i += NGRAM * 31; // 後でi++であげてくれる。 // 0, 96, 192, 288, 384, 480, 576, 672, 768, 864, 960
      tmp += (32 * NGRAM);
    }
    eval();
  }
  verilator_top->S_AXIS_TVALID = 0;
  eval();

  // 演算結果を待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  printf("\n --------------------------- Output ---------------------------- \n\n");

  for (int i = 0; i < 1; i++)
  {
    // for (int j = 0; j < 32; j++)
    // {
    //   printf("  %u\n\n", verilator_top->M_AXIS_TDATA[j]);
    //   putb(verilator_top->M_AXIS_TDATA[j]);
    // }
    printf("  %u\n\n", verilator_top->M_AXIS_TDATA[0]);
    putb(verilator_top->M_AXIS_TDATA[0]);
    eval();
  }

  //////////////////////////////////////////////////////////////////////////////// FPGA停止 run <- 0; last <- 0; //////////////////////////////////////////////////////////////////////

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

  printf("\n --------------------------- 終了 ------------------------------- \n");
  delete verilator_top;
  tfp->close();
  return 0;
}
