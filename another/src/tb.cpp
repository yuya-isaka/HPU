#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

///////////////////////////////////////////////////////////////

union
{
  struct
  {
    int32_t d0;
    int32_t d1;
  };
  uint64_t wd;
} conv;

////////////////////////////////////////////////////////////////

vluint64_t main_time = 0;
vluint64_t vcdstart = 0;
vluint64_t vcdend = vcdstart + 300000;

VerilatedVcdC *tfp;
Vtop *verilator_top;

////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////

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

  ////////////////////// Set Matrix /////////////////////////////

  int matrix[8][128];

  // 32bitを128個、8つのコアに格納
  printf("\n--- Set Matrix ---\n");
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 128; i++)
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
  // 2個でも一個でも変わらん

  // アドレスを指定せずにデータを取ってたけど、これは、アドレスの初期値が０だからたまたまうまくできていた。
  verilator_top->S_AXI_ARVALID = 1;
  eval();
  eval();
  if (1 != verilator_top->S_AXI_RDATA)
  {
    printf("(Error Expecetd = %d) ", 1);
  }
  else
  {

    printf("\n S_AXI_RDATA: %d \n", verilator_top->S_AXI_RDATA);
  }
  verilator_top->S_AXI_ARVALID = 0;
  eval();
  eval();

  // TVALIDの次から送信していく
  // 32個を想定
  // 32bitを2個ずつ順番に送信
  verilator_top->S_AXIS_TVALID = 1;
  int pp = 0;
  for (int i = 0; i < 512; i++)
  {
    conv.d0 = matrix[i * 2 / 128][pp];
    conv.d1 = matrix[i * 2 / 128][pp + 1];
    verilator_top->S_AXIS_TDATA = conv.wd;
    pp += 2;
    if (pp >= 128)
      pp = 0;
    eval();
  }
  // 00,01  02,03  04,05 .... 0126,0127(63回)  10,11
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

  verilator_top->S_AXI_ARVALID = 1;
  eval();
  eval();
  if (0 != verilator_top->S_AXI_RDATA)
  {
    printf("(Error Expecetd = %d) ", 0);
  }
  else
  {

    printf("\n S_AXI_RDATA: %d \n", verilator_top->S_AXI_RDATA);
  }
  verilator_top->S_AXI_ARVALID = 0;
  eval();
  eval();

  ////////////////////// run ////////////////////////////////////////////////////////////////////

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

  verilator_top->S_AXI_ARVALID = 1;
  eval();
  eval();
  if (2 != verilator_top->S_AXI_RDATA)
  {
    printf("(Error Expecetd = %d) ", 2);
  }
  else
  {

    printf("\n S_AXI_RDATA: %d \n", verilator_top->S_AXI_RDATA);
  }
  verilator_top->S_AXI_ARVALID = 0;
  eval();
  eval();

  int sample[8][128];

  // 同じく32bitを64個、４コア分渡す
  printf("\n--- Sample %d Input ---\n", 0);
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 128; i++)
    {
      sample[j][i] = rand() & 0x000000ff;
      printf("%3d ", sample[j][i]);
    }
    printf("\n");
  }

  // 16個を想定
  verilator_top->S_AXIS_TVALID = 1;
  pp = 0;
  for (int i = 0; i < 512; i++)
  {
    conv.d0 = sample[i * 2 / 128][pp];
    conv.d1 = sample[i * 2 / 128][pp + 1];
    verilator_top->S_AXIS_TDATA = conv.wd;
    pp += 2;
    if (pp >= 128)
      pp = 0;
    eval();
  }
  verilator_top->S_AXIS_TVALID = 0;
  eval();

  int result[8][8];

  for (int num = 0; num < 3; num++)
  {
    if (num != 0)
    {
      // 演算終わって送られてくるの待つ
      while (!verilator_top->M_AXIS_TVALID)
      {
        eval();
      }
      int d[64];
      printf("\n--- Sample %d Output ---\n", num - 1);
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          int d0 = verilator_top->M_AXIS_TDATA[0];
          int d1 = verilator_top->M_AXIS_TDATA[1];
          printf("%6d %6d ", d0, d1);
          eval();
        }
        printf("\n");
      }
      eval();

      int d[16] = {d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15};

      int kk = 0;
      for (int j = 0; j < 4; j++)
      {
        for (int i = 0; i < 4; i++)
        {
          if (d[kk] != result[j][i])
          {
            printf("(Error Expecetd = %6d) ", result[j][i]);
          }
          kk += 1;
        }
        printf("\n");
      }
    }

    if ((num + 1) != 3)
    {
      for (int j = 0; j < 4; j++)
      {
        int sum[4] = {};
        for (int k = 0; k < 64; k++)
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
      for (int j = 0; j < 8; j++)
      {
        for (int i = 0; i < 128; i++)
        {
          sample[j][i] = rand() & 0x000000ff;
          printf("%3d ", sample[j][i]);
        }
        printf("\n");
      }

      // データ送る
      verilator_top->S_AXIS_TVALID = 1;
      pp = 0;
      for (int i = 0; i < 512; i++)
      {
        conv.d0 = sample[i * 2 / 128][pp];
        conv.d1 = sample[i * 2 / 128][pp + 1];
        verilator_top->S_AXIS_TDATA = conv.wd;
        pp += 2;
        if (pp >= 128)
          pp = 0;
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

      // check
      verilator_top->S_AXI_ARVALID = 1;
      eval();
      eval();
      if (6 != verilator_top->S_AXI_RDATA)
      {
        printf("(Error Expecetd = %d) ", 6);
      }
      else
      {

        printf("\n S_AXI_RDATA: %d \n", verilator_top->S_AXI_RDATA);
      }
      verilator_top->S_AXI_ARVALID = 0;
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
  int d0 = verilator_top->M_AXIS_TDATA[0];
  int d1 = verilator_top->M_AXIS_TDATA[1];
  int d2 = verilator_top->M_AXIS_TDATA[2];
  int d3 = verilator_top->M_AXIS_TDATA[3];
  int d4 = verilator_top->M_AXIS_TDATA[4];
  int d5 = verilator_top->M_AXIS_TDATA[5];
  int d6 = verilator_top->M_AXIS_TDATA[6];
  int d7 = verilator_top->M_AXIS_TDATA[7];
  int d8 = verilator_top->M_AXIS_TDATA[8];
  int d9 = verilator_top->M_AXIS_TDATA[9];
  int d10 = verilator_top->M_AXIS_TDATA[10];
  int d11 = verilator_top->M_AXIS_TDATA[11];
  int d12 = verilator_top->M_AXIS_TDATA[12];
  int d13 = verilator_top->M_AXIS_TDATA[13];
  int d14 = verilator_top->M_AXIS_TDATA[14];
  int d15 = verilator_top->M_AXIS_TDATA[15];
  printf("%6d ", d0);
  printf("%6d ", d1);
  printf("%6d ", d2);
  printf("%6d ", d3);
  printf("\n");
  printf("%6d ", d4);
  printf("%6d ", d5);
  printf("%6d ", d6);
  printf("%6d ", d7);
  printf("\n");
  printf("%6d ", d8);
  printf("%6d ", d9);
  printf("%6d ", d10);
  printf("%6d ", d11);
  printf("\n");
  printf("%6d ", d12);
  printf("%6d ", d13);
  printf("%6d ", d14);
  printf("%6d ", d15);
  printf("\n");
  eval();

  int d[16] = {d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15};

  for (int j = 0; j < 4; j++)
  {
    int sum[4] = {};
    for (int k = 0; k < 64; k++)
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

  int kk = 0;
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 4; i++)
    {
      if (d[kk] != result[j][i])
      {
        printf("(Error Expecetd = %6d) ", result[j][i]);
      }
      kk += 1;
    }
    printf("\n");
  }

  // run <- 0; last <- 0; ////////////////////////////////////////////////////////////////////

  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 0;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();
  eval();

  verilator_top->S_AXI_ARVALID = 1;
  eval();
  eval();
  if (0 != verilator_top->S_AXI_RDATA)
  {
    printf("(Error Expecetd = %d) ", 0);
  }
  else
  {

    printf("\n S_AXI_RDATA: %d \n", verilator_top->S_AXI_RDATA);
  }
  verilator_top->S_AXI_ARVALID = 0;
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
