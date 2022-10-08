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
const int ADDRNUM = 663;

// ADDRNUMが奇数かどうか
const int ODD = 1;

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
    conv.d0 = i;
    if (ODD && i >= (ADDRNUM - NGRAM))
    {
      conv.d1 = 0;
    }
    else
    {
      conv.d1 = i + NGRAM;
    }
    conv2.d0 = i;
    if (ODD && i >= (ADDRNUM - NGRAM))
    {
      conv2.d1 = 0;
    }
    else
    {
      conv2.d1 = i + NGRAM;
    }
    if (i == tmp)
    {
      i += NGRAM;
      tmp += (2 * NGRAM);
    }
    verilator_top->S_AXIS_TDATA[0] = conv.d0;
    verilator_top->S_AXIS_TDATA[1] = conv.d1;
    verilator_top->S_AXIS_TDATA[2] = conv2.d0;
    verilator_top->S_AXIS_TDATA[3] = conv2.d1;
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
    conv.d0 = verilator_top->M_AXIS_TDATA[0];
    conv.d1 = verilator_top->M_AXIS_TDATA[1];
    conv2.d0 = verilator_top->M_AXIS_TDATA[2];
    conv2.d1 = verilator_top->M_AXIS_TDATA[3];
    printf("  %u\n\n", conv.d0);
    putb(conv.d0);
    printf("  %u\n\n", conv.d1);
    printf("  %u\n\n", conv2.d0);
    printf("  %u\n\n", conv2.d0);
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
