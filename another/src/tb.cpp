#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

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

  int matrix[4][64];

  // 32bitを64個（2048bit）、４つのコアに格納
  printf("\n--- Set Matrix ---\n");
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 64; i++) // 2048 bit
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
  // 32bitを32個ずつ順番に送信
  verilator_top->S_AXIS_TVALID = 1;
  for (int i = 0; i < 8; i++)
  {
    verilator_top->S_AXIS_TDATA[0] = matrix[i * 2 / 4][(i * 32 % 64) + 0];
    verilator_top->S_AXIS_TDATA[1] = matrix[i * 2 / 4][(i * 32 % 64) + 1];
    verilator_top->S_AXIS_TDATA[2] = matrix[i * 2 / 4][(i * 32 % 64) + 2];
    verilator_top->S_AXIS_TDATA[3] = matrix[i * 2 / 4][(i * 32 % 64) + 3];
    verilator_top->S_AXIS_TDATA[4] = matrix[i * 2 / 4][(i * 32 % 64) + 4];
    verilator_top->S_AXIS_TDATA[5] = matrix[i * 2 / 4][(i * 32 % 64) + 5];
    verilator_top->S_AXIS_TDATA[6] = matrix[i * 2 / 4][(i * 32 % 64) + 6];
    verilator_top->S_AXIS_TDATA[7] = matrix[i * 2 / 4][(i * 32 % 64) + 7];
    verilator_top->S_AXIS_TDATA[8] = matrix[i * 2 / 4][(i * 32 % 64) + 8];
    verilator_top->S_AXIS_TDATA[9] = matrix[i * 2 / 4][(i * 32 % 64) + 9];
    verilator_top->S_AXIS_TDATA[10] = matrix[i * 2 / 4][(i * 32 % 64) + 10];
    verilator_top->S_AXIS_TDATA[11] = matrix[i * 2 / 4][(i * 32 % 64) + 11];
    verilator_top->S_AXIS_TDATA[12] = matrix[i * 2 / 4][(i * 32 % 64) + 12];
    verilator_top->S_AXIS_TDATA[13] = matrix[i * 2 / 4][(i * 32 % 64) + 13];
    verilator_top->S_AXIS_TDATA[14] = matrix[i * 2 / 4][(i * 32 % 64) + 14];
    verilator_top->S_AXIS_TDATA[15] = matrix[i * 2 / 4][(i * 32 % 64) + 15];
    verilator_top->S_AXIS_TDATA[16] = matrix[i * 2 / 4][(i * 32 % 64) + 16];
    verilator_top->S_AXIS_TDATA[17] = matrix[i * 2 / 4][(i * 32 % 64) + 17];
    verilator_top->S_AXIS_TDATA[18] = matrix[i * 2 / 4][(i * 32 % 64) + 18];
    verilator_top->S_AXIS_TDATA[19] = matrix[i * 2 / 4][(i * 32 % 64) + 19];
    verilator_top->S_AXIS_TDATA[20] = matrix[i * 2 / 4][(i * 32 % 64) + 20];
    verilator_top->S_AXIS_TDATA[21] = matrix[i * 2 / 4][(i * 32 % 64) + 21];
    verilator_top->S_AXIS_TDATA[22] = matrix[i * 2 / 4][(i * 32 % 64) + 22];
    verilator_top->S_AXIS_TDATA[23] = matrix[i * 2 / 4][(i * 32 % 64) + 23];
    verilator_top->S_AXIS_TDATA[24] = matrix[i * 2 / 4][(i * 32 % 64) + 24];
    verilator_top->S_AXIS_TDATA[25] = matrix[i * 2 / 4][(i * 32 % 64) + 25];
    verilator_top->S_AXIS_TDATA[26] = matrix[i * 2 / 4][(i * 32 % 64) + 26];
    verilator_top->S_AXIS_TDATA[27] = matrix[i * 2 / 4][(i * 32 % 64) + 27];
    verilator_top->S_AXIS_TDATA[28] = matrix[i * 2 / 4][(i * 32 % 64) + 28];
    verilator_top->S_AXIS_TDATA[29] = matrix[i * 2 / 4][(i * 32 % 64) + 29];
    verilator_top->S_AXIS_TDATA[30] = matrix[i * 2 / 4][(i * 32 % 64) + 30];
    verilator_top->S_AXIS_TDATA[31] = matrix[i * 2 / 4][(i * 32 % 64) + 31];
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

  int sample[4][64];

  // 同じく32bitを64個、４コア分渡す
  printf("\n--- Sample %d Input ---\n", 0);
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 64; i++)
    {
      sample[j][i] = rand() & 0x000000ff;
      printf("%3d ", sample[j][i]);
    }
    printf("\n");
  }

  // 16個を想定
  verilator_top->S_AXIS_TVALID = 1;
  for (int i = 0; i < 8; i++)
  {
    verilator_top->S_AXIS_TDATA[0] = sample[i * 2 / 4][(i * 32 % 64) + 0];
    verilator_top->S_AXIS_TDATA[1] = sample[i * 2 / 4][(i * 32 % 64) + 1];
    verilator_top->S_AXIS_TDATA[2] = sample[i * 2 / 4][(i * 32 % 64) + 2];
    verilator_top->S_AXIS_TDATA[3] = sample[i * 2 / 4][(i * 32 % 64) + 3];
    verilator_top->S_AXIS_TDATA[4] = sample[i * 2 / 4][(i * 32 % 64) + 4];
    verilator_top->S_AXIS_TDATA[5] = sample[i * 2 / 4][(i * 32 % 64) + 5];
    verilator_top->S_AXIS_TDATA[6] = sample[i * 2 / 4][(i * 32 % 64) + 6];
    verilator_top->S_AXIS_TDATA[7] = sample[i * 2 / 4][(i * 32 % 64) + 7];
    verilator_top->S_AXIS_TDATA[8] = sample[i * 2 / 4][(i * 32 % 64) + 8];
    verilator_top->S_AXIS_TDATA[9] = sample[i * 2 / 4][(i * 32 % 64) + 9];
    verilator_top->S_AXIS_TDATA[10] = sample[i * 2 / 4][(i * 32 % 64) + 10];
    verilator_top->S_AXIS_TDATA[11] = sample[i * 2 / 4][(i * 32 % 64) + 11];
    verilator_top->S_AXIS_TDATA[12] = sample[i * 2 / 4][(i * 32 % 64) + 12];
    verilator_top->S_AXIS_TDATA[13] = sample[i * 2 / 4][(i * 32 % 64) + 13];
    verilator_top->S_AXIS_TDATA[14] = sample[i * 2 / 4][(i * 32 % 64) + 14];
    verilator_top->S_AXIS_TDATA[15] = sample[i * 2 / 4][(i * 32 % 64) + 15];
    verilator_top->S_AXIS_TDATA[16] = sample[i * 2 / 4][(i * 32 % 64) + 16];
    verilator_top->S_AXIS_TDATA[17] = sample[i * 2 / 4][(i * 32 % 64) + 17];
    verilator_top->S_AXIS_TDATA[18] = sample[i * 2 / 4][(i * 32 % 64) + 18];
    verilator_top->S_AXIS_TDATA[19] = sample[i * 2 / 4][(i * 32 % 64) + 19];
    verilator_top->S_AXIS_TDATA[20] = sample[i * 2 / 4][(i * 32 % 64) + 20];
    verilator_top->S_AXIS_TDATA[21] = sample[i * 2 / 4][(i * 32 % 64) + 21];
    verilator_top->S_AXIS_TDATA[22] = sample[i * 2 / 4][(i * 32 % 64) + 22];
    verilator_top->S_AXIS_TDATA[23] = sample[i * 2 / 4][(i * 32 % 64) + 23];
    verilator_top->S_AXIS_TDATA[24] = sample[i * 2 / 4][(i * 32 % 64) + 24];
    verilator_top->S_AXIS_TDATA[25] = sample[i * 2 / 4][(i * 32 % 64) + 25];
    verilator_top->S_AXIS_TDATA[26] = sample[i * 2 / 4][(i * 32 % 64) + 26];
    verilator_top->S_AXIS_TDATA[27] = sample[i * 2 / 4][(i * 32 % 64) + 27];
    verilator_top->S_AXIS_TDATA[28] = sample[i * 2 / 4][(i * 32 % 64) + 28];
    verilator_top->S_AXIS_TDATA[29] = sample[i * 2 / 4][(i * 32 % 64) + 29];
    verilator_top->S_AXIS_TDATA[30] = sample[i * 2 / 4][(i * 32 % 64) + 30];
    verilator_top->S_AXIS_TDATA[31] = sample[i * 2 / 4][(i * 32 % 64) + 31];
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
      for (int j = 0; j < 4; j++)
      {
        for (int i = 0; i < 64; i++)
        {
          sample[j][i] = rand() & 0x000000ff;
          printf("%3d ", sample[j][i]);
        }
        printf("\n");
      }

      // データ送る
      verilator_top->S_AXIS_TVALID = 1;
      for (int i = 0; i < 8; i++)
      {
        verilator_top->S_AXIS_TDATA[0] = sample[i * 2 / 4][(i * 32 % 64) + 0];
        verilator_top->S_AXIS_TDATA[1] = sample[i * 2 / 4][(i * 32 % 64) + 1];
        verilator_top->S_AXIS_TDATA[2] = sample[i * 2 / 4][(i * 32 % 64) + 2];
        verilator_top->S_AXIS_TDATA[3] = sample[i * 2 / 4][(i * 32 % 64) + 3];
        verilator_top->S_AXIS_TDATA[4] = sample[i * 2 / 4][(i * 32 % 64) + 4];
        verilator_top->S_AXIS_TDATA[5] = sample[i * 2 / 4][(i * 32 % 64) + 5];
        verilator_top->S_AXIS_TDATA[6] = sample[i * 2 / 4][(i * 32 % 64) + 6];
        verilator_top->S_AXIS_TDATA[7] = sample[i * 2 / 4][(i * 32 % 64) + 7];
        verilator_top->S_AXIS_TDATA[8] = sample[i * 2 / 4][(i * 32 % 64) + 8];
        verilator_top->S_AXIS_TDATA[9] = sample[i * 2 / 4][(i * 32 % 64) + 9];
        verilator_top->S_AXIS_TDATA[10] = sample[i * 2 / 4][(i * 32 % 64) + 10];
        verilator_top->S_AXIS_TDATA[11] = sample[i * 2 / 4][(i * 32 % 64) + 11];
        verilator_top->S_AXIS_TDATA[12] = sample[i * 2 / 4][(i * 32 % 64) + 12];
        verilator_top->S_AXIS_TDATA[13] = sample[i * 2 / 4][(i * 32 % 64) + 13];
        verilator_top->S_AXIS_TDATA[14] = sample[i * 2 / 4][(i * 32 % 64) + 14];
        verilator_top->S_AXIS_TDATA[15] = sample[i * 2 / 4][(i * 32 % 64) + 15];
        verilator_top->S_AXIS_TDATA[16] = sample[i * 2 / 4][(i * 32 % 64) + 16];
        verilator_top->S_AXIS_TDATA[17] = sample[i * 2 / 4][(i * 32 % 64) + 17];
        verilator_top->S_AXIS_TDATA[18] = sample[i * 2 / 4][(i * 32 % 64) + 18];
        verilator_top->S_AXIS_TDATA[19] = sample[i * 2 / 4][(i * 32 % 64) + 19];
        verilator_top->S_AXIS_TDATA[20] = sample[i * 2 / 4][(i * 32 % 64) + 20];
        verilator_top->S_AXIS_TDATA[21] = sample[i * 2 / 4][(i * 32 % 64) + 21];
        verilator_top->S_AXIS_TDATA[22] = sample[i * 2 / 4][(i * 32 % 64) + 22];
        verilator_top->S_AXIS_TDATA[23] = sample[i * 2 / 4][(i * 32 % 64) + 23];
        verilator_top->S_AXIS_TDATA[24] = sample[i * 2 / 4][(i * 32 % 64) + 24];
        verilator_top->S_AXIS_TDATA[25] = sample[i * 2 / 4][(i * 32 % 64) + 25];
        verilator_top->S_AXIS_TDATA[26] = sample[i * 2 / 4][(i * 32 % 64) + 26];
        verilator_top->S_AXIS_TDATA[27] = sample[i * 2 / 4][(i * 32 % 64) + 27];
        verilator_top->S_AXIS_TDATA[28] = sample[i * 2 / 4][(i * 32 % 64) + 28];
        verilator_top->S_AXIS_TDATA[29] = sample[i * 2 / 4][(i * 32 % 64) + 29];
        verilator_top->S_AXIS_TDATA[30] = sample[i * 2 / 4][(i * 32 % 64) + 30];
        verilator_top->S_AXIS_TDATA[31] = sample[i * 2 / 4][(i * 32 % 64) + 31];
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
