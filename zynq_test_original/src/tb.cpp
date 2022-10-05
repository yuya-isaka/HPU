#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

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

  /////////////////////////////////////////////////////////////////////////////////// Set Matrix ////////////////////////////////////////////////////////////////////////////////////////////

  int matrix[8][128];

  // 32bitを128個、8つのコアに格納
  printf("\n ------------------------- Set Matrix -------------------------- \n\n");
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

  // 読み出し (書き込みより読み出しの方が１サイクル多い)
  verilator_top->S_AXI_ARVALID = 1;
  verilator_top->S_AXI_ARADDR = 0;
  eval(); // 読み出しリクエスト
  eval(); // 格納完了
  // アドレス０に１を書き込んでいるので、１が出力されるはず
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

  // 送信
  // 8 * 128 * 32 = 32768bit
  // 32768bit / 64bit = 512回
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

  // 読み込んで確認
  verilator_top->S_AXI_ARVALID = 1;
  eval(); // 読み出しリクエスト
  eval(); // 格納完了
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

  //////////////////////////////////////////////////////////////////////////////////////// run ///////////////////////////////////////////////////////////////////////////////////////////////

  int sample[8][128];

  // 32bitを128個、8つのコアに格納
  printf("\n ------------------------- Sample %d Input -------------------------- \n\n", 0);
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 128; i++)
    {
      sample[j][i] = rand() & 0x000000ff;
      printf("%3d ", sample[j][i]);
    }
    printf("\n");
  }

  // run <- 1;
  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 2;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
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

  // 送信
  // 8 * 128 * 32 = 32768bit
  // 32768bit / 64bit = 512回
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

  /////////////////////////////////////////////////////////////////////////////////////// 結果確認 //////////////////////////////////////////////////////////////////////////////////

  int result[8][8];

  for (int num = 0; num < 3; num++)
  {

    // 0回目以外実行 ---------------------------------------------------------------
    if (num != 0)
    {

      // 演算終わって送られてくるの待つ
      while (!verilator_top->M_AXIS_TVALID)
      {
        eval();
      }

      printf("\n ------------------------- Sample %d Output -------------------------- \n\n", num - 1);
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          conv.wd = verilator_top->M_AXIS_TDATA;
          printf("%6d ", conv.d0);
          if (conv.d0 != result[i][j * 2 + 0])
          {
            printf("(Error Expecetd = %6d) ", result[i][j * 2 + 0]);
          }
          printf("%6d ", conv.d1);
          if (conv.d1 != result[i][j * 2 + 1])
          {
            printf("(Error Expecetd = %6d) ", result[i][j * 2 + 1]);
          }
          eval();
        }
        printf("\n");
      }
    }
    // ---------------------------------------------------------------------------

    // 2回目（最後）以外実行 ---------------------------------------------------------
    if ((num + 1) != 3)
    {

      // 理想の計算
      for (int j = 0; j < 8; j++)
      {
        int sum[8] = {};
        for (int k = 0; k < 128; k++)
        {
          for (int i = 0; i < 8; i++)
          {
            sum[i] += matrix[i][k] * sample[j][k];
          }
        }
        for (int oa = 0; oa < 8; oa++)
        {
          result[j][oa] = sum[oa];
        }
      }

      printf("\n ------------------------- Sample %d Input -------------------------- \n\n", num + 1);
      for (int j = 0; j < 8; j++)
      {
        for (int i = 0; i < 128; i++)
        {
          sample[j][i] = rand() & 0x000000ff;
          printf("%3d ", sample[j][i]);
        }
        printf("\n");
      }

      // 送信
      // 8 * 128 * 32 = 32768bit
      // 32768bit / 64bit = 512回
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

    }    // --------------------------------------------------------------------------------
    else // 最後に実行 ----------------------------------------------------------------------
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
    }
    // ------------------------------------------------------------------------------------
  }

  // 演算終わるの待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  // 理想の計算
  for (int j = 0; j < 8; j++)
  {
    int sum[8] = {};
    for (int k = 0; k < 128; k++)
    {
      for (int i = 0; i < 8; i++)
      {
        sum[i] += matrix[i][k] * sample[j][k];
      }
    }
    for (int oa = 0; oa < 8; oa++)
    {
      result[j][oa] = sum[oa];
    }
  }

  printf("\n ------------------------- Sample %d Output -------------------------- \n\n", 2);
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      conv.wd = verilator_top->M_AXIS_TDATA;
      printf("%6d ", conv.d0);
      if (conv.d0 != result[i][j * 2 + 0])
      {
        printf("(Error Expecetd = %6d) ", result[i][j * 2 + 0]);
      }
      printf("%6d ", conv.d1);
      if (conv.d1 != result[i][j * 2 + 1])
      {
        printf("(Error Expecetd = %6d) ", result[i][j * 2 + 1]);
      }
      eval();
    }
    printf("\n");
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
