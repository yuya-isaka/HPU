#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

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
vluint64_t vcdstart = 0;
vluint64_t vcdend = vcdstart + 300000;

VerilatedVcdC *tfp;
Vtop *verilator_top;

void eval()
{
  // negedge clk /////////////////////////////
  verilator_top->S_AXI_ACLK = 0;
  verilator_top->AXIS_ACLK = 0;

  verilator_top->eval();

  if ((main_time >= vcdstart) & ((main_time < vcdend) | (vcdend == 0)))
    tfp->dump(main_time);
  main_time += 5;

  // posegedge clk /////////////////////////////
  verilator_top->S_AXI_ACLK = 1;
  verilator_top->AXIS_ACLK = 1;

  verilator_top->eval();

  if ((main_time >= vcdstart) & ((main_time < vcdend) | (vcdend == 0)))
    tfp->dump(main_time);
  main_time += 5;

  return;
}

int main(int argc, char **argv)
{

  // Verilator setup /////////////////////////////
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  verilator_top = new Vtop;
  verilator_top->trace(tfp, 99); // requires explicit max levels param
  tfp->open("tmp.vcd");
  main_time = 0;

  // initial begin /////////////////////////////
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

  ////////////////////// Set Matrix /////////////////////////////
  int matrix[4][8];

  printf("\n--- Set Matrix ---\n");
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      matrix[j][i] = rand() & 0x000000ff;
      printf("%3d ", matrix[j][i]);
    }
    printf("\n");
  }
  // matw <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 1;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();
  eval();

  verilator_top->S_AXIS_TVALID = 1;
  for (int i = 0; i < 32; i++)
  {
    verilator_top->S_AXIS_TDATA = matrix[i / 8][i % 8];
    eval();
  }
  verilator_top->S_AXIS_TVALID = 0;

  // matw <- 0;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 0;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();
  eval();

  ////////////////////// run /////////////////////////////
  // run <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 2;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();
  eval();

  int sample[4][8];

  printf("\n--- Sample %d Input ---\n", 0);
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      sample[j][i] = rand() & 0x000000ff;
      printf("%3d ", sample[j][i]);
    }
    printf("\n");
  }

  verilator_top->S_AXIS_TVALID = 1;
  for (int i = 0; i < 16; i++)
  {
    conv.d0 = sample[i * 2 / 8][(i * 2 % 8) + 0];
    conv.d1 = sample[i * 2 / 8][(i * 2 % 8) + 1];
    verilator_top->S_AXIS_TDATA = conv.wd;
    eval();
  }
  verilator_top->S_AXIS_TVALID = 0;
  eval();

  int result[4][4];

  for (int num = 0; num < 3; num++)
  {
    if (num != 0)
    {
      // 演算終わって送られてくるの待つ
      while (!verilator_top->M_AXIS_TVALID)
      {
        eval();
      }
      printf("\n--- Sample %d Output ---\n", num - 1);
      for (int j = 0; j < 4; j++)
      {
        for (int i = 0; i < 2; i++)
        {
          conv.wd = verilator_top->M_AXIS_TDATA;
          printf("%6d ", conv.d0);
          if (conv.d0 != result[j][i * 2 + 0])
          {
            printf("(Error Expecetd = %6d) ", result[j][i * 2 + 0]);
          }
          printf("%6d ", conv.d1);
          if (conv.d1 != result[j][i * 2 + 1])
          {
            printf("(Error Expecetd = %6d) ", result[j][i * 2 + 1]);
          }
          eval();
        }
        printf("\n");
      }
    }

    if ((num + 1) != 3)
    {
      for (int j = 0; j < 4; j++)
      {
        int sum[4] = {};
        for (int k = 0; k < 8; k++)
        {
          for (int i = 0; i < 4; i++)
          {
            sum[i] += matrix[i][k] * sample[j][k];
          }
        }
        for (int oa = 0; oa < 4; oa++)
        {
          result[j][oa] = sum[oa];
        }
      }
      printf("\n--- Sample %d Input ---\n", num + 1);
      for (int j = 0; j < 4; j++)
      {
        for (int i = 0; i < 8; i++)
        {
          sample[j][i] = rand() & 0x000000ff;
          printf("%3d ", sample[j][i]);
        }
        printf("\n");
      }

      // データ送る
      verilator_top->S_AXIS_TVALID = 1;
      for (int i = 0; i < 16; i++)
      {
        conv.d0 = sample[i * 2 / 8][(i * 2 % 8) + 0];
        conv.d1 = sample[i * 2 / 8][(i * 2 % 8) + 1];
        verilator_top->S_AXIS_TDATA = conv.wd;
        eval();
      }
      verilator_top->S_AXIS_TVALID = 0;
      eval();
    }
    else
    {
      // last <- 1;
      verilator_top->S_AXI_AWADDR = 0;
      verilator_top->S_AXI_WDATA = 6;
      verilator_top->S_AXI_AWVALID = 1;
      verilator_top->S_AXI_WVALID = 1;
      eval();
      verilator_top->S_AXI_AWVALID = 0;
      verilator_top->S_AXI_WVALID = 0;
      eval();
      eval();
    }
  }
  // 演算おワテ送られてくるの待つ
  // ここではlast信号が立っているので，次の演算はもう実行されていない
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }
  printf("\n--- Sample %d Output ---\n", 2);
  for (int j = 0; j < 4; j++)
  {
    int sum[4] = {};
    for (int k = 0; k < 8; k++)
    {
      for (int i = 0; i < 4; i++)
      {
        sum[i] += matrix[i][k] * sample[j][k];
      }
    }
    for (int i = 0; i < 2; i++)
    {
      conv.wd = verilator_top->M_AXIS_TDATA;
      printf("%6d ", conv.d0);
      if (conv.d0 != sum[i * 2 + 0])
      {
        printf("(Error Expecetd = %6d) ", sum[i * 2 + 0]);
      }
      printf("%6d ", conv.d1);
      if (conv.d1 != sum[i * 2 + 1])
      {
        printf("(Error Expecetd = %6d) ", sum[i * 2 + 1]);
      }
      eval();
    }
    printf("\n");
  }

  // run <- 0; last <- 0;
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
  eval();
  verilator_top->S_AXI_ARESETN = 0;
  verilator_top->AXIS_ARESETN = 0;
  eval();
  eval();

  // $finish; end /////////////////////////////
  delete verilator_top;
  tfp->close();
  return 0;
}
