#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"
#include <string.h>

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
Vtop *verilator_top;

// ====================================================================================================================================================================================

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

  // --------------------------------------------------------------------

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

// ====================================================================================================================================================================================

int main(int argc, char **argv)
{

  ////////////////////////////////////////////////////////////////////////////// Verilator setup /////////////////////////////////////////////////////////////////////////////////////////

  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  verilator_top = new Vtop;
  verilator_top->trace(tfp, 99); // requires explicit max levels param
  tfp->open("tmp.vcd");
  main_time = 0;

  //////////////////////////////////////////////////////////////////////////////// initial begin ///////////////////////////////////////////////////////////////////////////////////////////

  printf("\n ---------------------------- 開始 ----------------------------- \n");

  verilator_top->S_AXI_BREADY = 1;
  verilator_top->S_AXI_WSTRB = 15; // ストローブ信号,wstrb は wdata のうち実際に書き込む部位をバイト単位で指定します
  verilator_top->S_AXI_RREADY = 1;
  verilator_top->S_AXIS_TSTRB = 255; // ストリーム用のストローブ信号
  verilator_top->S_AXIS_TLAST = 0;   // データ区切り信号
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
  for (int i = 0; i < 24; i += 2)
  {
    conv.d0 = i;
    conv.d1 = i + 1;
    verilator_top->S_AXIS_TDATA = conv.wd;
    eval();
  }
  verilator_top->S_AXIS_TVALID = 0;
  eval();

  verilator_top->S_AXIS_TVALID = 1;
  for (int i = 0; i < 24; i += 2)
  {
    conv.d0 = i;
    conv.d1 = i + 1;
    verilator_top->S_AXIS_TDATA = conv.wd;
    eval();
  }
  verilator_top->S_AXIS_TVALID = 0;
  eval();

  // 演算終わって送られてくるの待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  printf("\n ------------------------- Output -------------------------- \n\n");

  conv.wd = verilator_top->M_AXIS_TDATA;
  printf("%6d ", conv.d0);
  printf("%6d ", conv.d1);
  printf("\n");

  // last <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 6;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // 演算終わって送られてくるの待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  // int result;

  // // 理想の計算
  // for (int j = 0; j < 8; j++)
  // {
  //   int sum[8] = {};
  //   for (int k = 0; k < 128; k++)
  //   {
  //     for (int i = 0; i < 8; i++)
  //     {
  //       sum[i] += matrix[i][k] * sample[j][k];
  //     }
  //   }
  //   for (int oa = 0; oa < 8; oa++)
  //   {
  //     result[j][oa] = sum[oa];
  //   }
  // }

  printf("\n ------------------------- Output -------------------------- \n\n");
  conv.wd = verilator_top->M_AXIS_TDATA;
  printf("%6d ", conv.d0);
  printf("%6d ", conv.d1);
  printf("\n");
  // for (int i = 0; i < 8; i++)
  // {
  //   for (int j = 0; j < 4; j++)
  //   {
  //     conv.wd = verilator_top->M_AXIS_TDATA;
  //     printf("%6d ", conv.d0);
  //     if (conv.d0 != result[i][j * 2 + 0])
  //     {
  //       printf("(Error Expecetd = %6d) ", result[i][j * 2 + 0]);
  //     }
  //     printf("%6d ", conv.d1);
  //     if (conv.d1 != result[i][j * 2 + 1])
  //     {
  //       printf("(Error Expecetd = %6d) ", result[i][j * 2 + 1]);
  //     }
  //     eval();
  //   }
  //   printf("\n");
  // }

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

  printf("\n ----------------------------- 終了 --------------------------------- \n");
  delete verilator_top;
  tfp->close();
  return 0;
}
