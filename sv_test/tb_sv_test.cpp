#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsv_test.h"
#include <string.h>
#include <iostream>

// ====================================================================================================================================================================================

union
{
  struct
  {
    int32_t d0;
    int32_t d1;
  };
  uint64_t wd;
} conv;

vluint64_t main_time = 0;
vluint64_t sim_start = 0;
vluint64_t sim_end = sim_start + 300000;

VerilatedVcdC *tfp;
Vsv_test *verilator_top;

// ====================================================================================================================================================================================

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

  // --------------------------------------------------------------------

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
  putchar('0'), putchar('b'), printb(v), putchar('\n');
}

// ====================================================================================================================================================================================

int main(int argc, char **argv)
{

  ////////////////////////////////////////////////////////////////////////////// Verilator setup /////////////////////////////////////////////////////////////////////////////////////////

  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  verilator_top = new Vsv_test;
  verilator_top->trace(tfp, 99); // requires explicit max levels param
  tfp->open("tmp.vcd");
  main_time = 0;

  //////////////////////////////////////////////////////////////////////////////// initial begin ///////////////////////////////////////////////////////////////////////////////////////////

  printf("\n ---------------------------- 開始 ----------------------------- \n");

  verilator_top->rstn = 0;
  verilator_top->eval();
  main_time += 5;

  eval();
  eval();
  verilator_top->rstn = 1;
  eval();
  eval();

  for (int i = 0; i < 10; i++)
  {
    printf("%d:%llu\n", i, verilator_top->rand_num);
    // putb(tmp);
    // printf("\n");
    eval();
  }

  printf("\n ----------------------------- 終了 --------------------------------- \n");
  delete verilator_top;
  tfp->close();
  return 0;
}
