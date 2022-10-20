// include
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsv_test.h"
#include <string.h>
#include <iostream>

//====================================================================================================================================================================================

vluint64_t main_time = 0;
vluint64_t sim_start = 0;
vluint64_t sim_end = sim_start + 300000;

VerilatedVcdC *tfp;
Vsv_test *verilator_top;

void eval()
{
  // Neg edge
  verilator_top->clk = 0;
  // 立ち下がりの評価
  verilator_top->eval();

  if ((sim_start <= main_time) & ((main_time < sim_end) | (sim_end == 0)))
  {
    tfp->dump(main_time);
  }
  main_time += 5;

  //-----------

  // Pos edge
  verilator_top->clk = 1;
  // 立ち上がりの評価
  verilator_top->eval();

  if ((main_time >= sim_start) & ((main_time < sim_end) | (sim_end == 0)))
  {
    tfp->dump(main_time);
  }
  main_time += 5;

  return;
}

//====================================================================================================================================================================================

union
{
  struct
  {
    int32_t d0;
    int32_t d1;
  };
  uint64_t wd;
} conv;

void printb(unsigned int v)
{
  unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
  do
    putchar(mask & v ? '1' : '0');
  while (mask >>= 1);
}

void putb(unsigned int v)
{
  putchar('0'), putchar('b'), printb(v), putchar('\n');
}

//====================================================================================================================================================================================

int main(int argc, char **argv)
{

  // 初期設定
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  verilator_top = new Vsv_test;
  verilator_top->trace(tfp, 99);
  tfp->open("tmp.vcd");
  main_time = 0;

  // main処理
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  printf("\n ------------------------------- 開始 ------------------------------- \n\n");

  verilator_top->rstn = 0;
  verilator_top->eval();
  main_time += 5;

  eval();
  eval();
  verilator_top->rstn = 1;
  eval();

  for (int i = 0; i < 10; i++)
  {
    verilator_top->in = i;
    verilator_top->permutation = 3;
    eval();
    // printf("   %d:  %10u\n", i, verilator_top->out_1);
    // printf("   %d:  %10u\n", i, verilator_top->out_2);
    putb(i);
    putb(verilator_top->out_1);
    putb(verilator_top->out_2);
    printf("\n");
  }

  printf("\n ------------------------------- 終了 ------------------------------- \n\n");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // 修了処置
  delete verilator_top;
  tfp->close();
  return 0;
}
