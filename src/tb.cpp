
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"
#include <string.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 追加されるランダムな値はRANNUM-1番目
const int RANNUM = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vluint64_t main_time = 0;
vluint64_t sim_start = 0;
vluint64_t sim_end = sim_start + 3000000;

VerilatedVcdC *tfp;
Vtop *verilator_top;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// データをまとめて格納するユニオン型
union
{
  struct
  {
    uint16_t data_0;
    uint16_t data_1;
  };
  uint32_t write_data;
} conv;

// 1クロック進みながら２回評価　（立ち下がり、立ち上がり）
void eval()
{
  verilator_top->S_AXI_ACLK = 0;
  verilator_top->AXIS_ACLK = 0;
  verilator_top->eval();

  if ((sim_start <= main_time) & ((main_time < sim_end) | (sim_end == 0)))
  {
    tfp->dump(main_time);
  }
  main_time += 5;

  verilator_top->S_AXI_ACLK = 1;
  verilator_top->AXIS_ACLK = 1;
  verilator_top->eval();

  if ((main_time >= sim_start) & ((main_time < sim_end) | (sim_end == 0)))
  {
    tfp->dump(main_time);
  }
  main_time += 5;

  return;
}

// 渡された32ビットのvを、バイナリでコマンドライン出力
void printb(unsigned int v)
{
  // sizeof(v) == 4バイト
  unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
  do
    putchar(mask & v ? '1' : '0');
  while (mask >>= 1);
}

// printbを使いつつ整形して、バイナリをコマンドライン出力
void putb(unsigned int v)
{
  printf("  0"), putchar('b'), printb(v), printf("\n");
}

// 簡易アセンブラ
uint16_t assemble(int addr_flag, unsigned int inst_num, uint16_t addr)
{
  if (addr_flag)
  {
    uint16_t result = 0;
    // load
    if (inst_num == 1)
    {
      uint16_t inst = 3 << 14;
      result = inst | addr;
    }
    // l.rshift
    else if (inst_num == 2)
    {
      uint16_t inst = 5 << 13;
      result = inst | addr;
    }
    // l.lshift
    else if (inst_num == 4)
    {
      uint16_t inst = 9 << 12;
      result = inst | addr;
    }
    // l.xor
    else if (inst_num == 6)
    {
      uint16_t inst = 17 << 11;
      result = inst | addr;
    }
    // lastback
    else if (inst_num == 11)
    {
      uint16_t inst = 33 << 10;
      result = inst | addr;
    }
    else
    {
      printf("error");
    }
    return result;
  }
  else
  {
    uint16_t inst = 0;
    // rshift
    if (inst_num == 3)
    {
      inst = 1 << 14;
    }
    // lshift
    else if (inst_num == 5)
    {
      inst = 1 << 13;
    }
    // xor
    else if (inst_num == 7)
    {
      inst = 1 << 12;
    }
    // store
    else if (inst_num == 8)
    {
      inst = 1 << 11;
    }
    // lastore
    else if (inst_num == 9)
    {
      inst = 1 << 10;
    }
    // move
    else if (inst_num == 10)
    {
      inst = 1 << 9;
    }
    else
    {
      printf("error");
    }
    return inst;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// write_backでかきもどしたあたいを、再度偶数のときのランダムな値として使う実験
void check2(const int NGRAM, const int CORENUM, const int ADDRNUM, const int DIM, const int MAJORITY_ADDR, int argc, char **argv, const int DEBUG)
{

  // CORENUMの数すべてを使わないケースがあるか調べる
  const int REMAINDAR = (ADDRNUM / NGRAM) % CORENUM;

  // ADDRNUM(計算する個数)が偶数か否かを設定(後で変えるかも)
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

  // 最後の送信
  int LAST = (ADDRNUM / NGRAM) / CORENUM;
  // CORENUMの倍数だったらきっちりコアを使い切るので、最後の数が１個減る
  if (REMAINDAR == 0)
  {
    LAST--;
  }
  // 最後の送信がいつかを求める
  LAST *= NGRAM * CORENUM;

  ////////////////////////////////////////////////////////////////////////////// Verilator setup /////////////////////////////////////////////////////////////////////////////////////////

  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  verilator_top = new Vtop;
  verilator_top->trace(tfp, 99);
  tfp->open("tmp.vcd");
  main_time = 0;

  //////////////////////////////////////////////////////////////////////////////// initial begin ///////////////////////////////////////////////////////////////////////////////////////////

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
  verilator_top->S_AXI_WDATA = RANNUM - 1; // 1023番目をランダムな値に使う
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // gen <- 1;
  // ランダムなハイパーベクトルを自動生成
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
  // ---- genはここで０になっている ----

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

  int tmp = 0;

  // EVEN ===========================================================================

  if (EVEN)
  {
    // load
    uint16_t addr = MAJORITY_ADDR;
    conv.data_0 = assemble(1, 1, addr);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
    tmp++;
    for (int i = tmp; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    // store
    tmp = 0;
    conv.data_0 = assemble(0, 8, 0);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
    tmp++;
    for (int i = tmp; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();
  }

  // ↓ここを書き換える==================================================================

  for (int j = 0; j < ADDRNUM; j++)
  {

    if (REMAINDAR != 0 && j == LAST)
    {

      // 1 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 1, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 1, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + 1 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + 2 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 3 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 3, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 3, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 9 (ここは必ずラストの命令) -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 9, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 9, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      j += NGRAM * CORENUM - 1;
    } /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
      // 1 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 1, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 1, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + 1 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + 2 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 3 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 3, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 3, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      if (j == LAST)
      {
        // 9 -------------------------------------------------------------------
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            // conv.data_0 = assemble(0, 9, 0);
            conv.data_0 = assemble(1, 11, 1023);
            conv.data_1 = 0;
          }
          else
          {
            // conv.data_1 = assemble(0, 9, 0);
            conv.data_0 = assemble(1, 11, 1023);
            verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
        // 残り埋める
        for (int i = tmp; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
      }
      else
      {
        // 8 -------------------------------------------------------------------
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble(0, 8, 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble(0, 8, 0);
            verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
        // 残り埋める
        for (int i = tmp; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
      }

      // 更新
      j += NGRAM * CORENUM - 1;
    }
  }

  // ↑ここを書き換える==================================================================

  verilator_top->S_AXIS_TVALID = 0;

  // 最後の送信途中で止まる対策 --------------
  for (int i = 0; i < 32; i++)
  {
    verilator_top->S_AXIS_TDATA[i] = 0;
  }
  eval();
  eval();
  eval();
  // -------------------------------------

  // 演算結果を待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  eval();
  eval();
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////  Output ////////////////////////////////////////////////////////////////////////////////////

  // printf("\n --------------------------- Output ---------------------------- \n\n\n");

  unsigned int check_num[DIM];
  for (int i = 0; i < 1; i++)
  {
    for (int j = 0; j < DIM; j++)
    {
      check_num[j] = verilator_top->M_AXIS_TDATA[j];
    }
    eval();
  }
  eval();
  eval();
  eval();

  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 0;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

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

  tmp = 0;

  // EVEN ===========================================================================

  if (EVEN)
  {
    // load
    uint16_t addr = MAJORITY_ADDR;
    conv.data_0 = assemble(1, 1, addr);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
    tmp++;
    for (int i = tmp; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    // store
    tmp = 0;
    conv.data_0 = assemble(0, 8, 0);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
    tmp++;
    for (int i = tmp; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();
  }

  // ↓ここを書き換える==================================================================

  for (int j = 0; j < ADDRNUM; j++)
  {

    if (REMAINDAR != 0 && j == LAST)
    {

      // 1 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 1, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 1, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + 1 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + 2 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 3 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 3, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 3, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 9 (ここは必ずラストの命令) -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 9, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 9, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      j += NGRAM * CORENUM - 1;
    } /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
      // 1 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 1, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 1, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + 1 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + 2 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 3 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 3, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 3, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      if (j == LAST)
      {
        // 9 -------------------------------------------------------------------
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble(0, 9, 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble(0, 9, 0);
            verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
        // 残り埋める
        for (int i = tmp; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
      }
      else
      {
        // 8 -------------------------------------------------------------------
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble(0, 8, 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble(0, 8, 0);
            verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
        // 残り埋める
        for (int i = tmp; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
      }

      // 更新
      j += NGRAM * CORENUM - 1;
    }
  }

  // ↑ここを書き換える==================================================================

  verilator_top->S_AXIS_TVALID = 0;

  // 最後の送信途中で止まる対策 --------------
  for (int i = 0; i < 32; i++)
  {
    verilator_top->S_AXIS_TDATA[i] = 0;
  }
  eval();
  eval();
  eval();
  // -------------------------------------

  // 演算結果を待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  eval();
  eval();
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////  Output ////////////////////////////////////////////////////////////////////////////////////

  // printf("\n --------------------------- Output ---------------------------- \n\n\n");

  for (int i = 0; i < 1; i++)
  {
    for (int j = 0; j < DIM; j++)
    {
      if (verilator_top->M_AXIS_TDATA[j] == check_num[j])
      {
        printf("成功！\n");
      }
      // putb(verilator_top->M_AXIS_TDATA[j]);
    }
    eval();
  }
  eval();
  eval();
  eval();

  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 0;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  eval();
  eval();
  verilator_top->S_AXI_ARESETN = 0;
  verilator_top->AXIS_ARESETN = 0;
  eval();
  eval();

  delete verilator_top;
  tfp->close();
  return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// N-gram専用check関数
// 簡易アセンブラを使って、直接アセンブラを記述 (関数使ったやつに書き直す)
//    NGRAM   = 1 ~
//    CORENUM = 1 - 16
//    ADDRNUM = NGRAMの倍数 (shifter_newを使ったテストをしているから。また、LASTが０のままになりtb.cppでは止まる。test.cppでは動くけどNGRAMの倍数以外は同じ値が出る)
//    DIM     = 32 or 1024
//    argc    ... Verilatorに必要
//    **argv  ... Verilatorに必要
//    DEBUG   = DMA中断するか否か
void check(const int NGRAM, const int CORENUM, const int ADDRNUM, const int DIM, const int MAJORITY_ADDR, int argc, char **argv, const int DEBUG)
{

  // CORENUMの数すべてを使わないケースがあるか調べる
  const int REMAINDAR = (ADDRNUM / NGRAM) % CORENUM;

  // ADDRNUM(計算する個数)が偶数か否かを設定(後で変えるかも)
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;

  // 最後の送信
  int LAST = (ADDRNUM / NGRAM) / CORENUM;
  // CORENUMの倍数だったらきっちりコアを使い切るので、最後の数が１個減る
  if (REMAINDAR == 0)
  {
    LAST--;
  }
  // 最後の送信がいつかを求める
  LAST *= NGRAM * CORENUM;

  ////////////////////////////////////////////////////////////////////////////// Verilator setup /////////////////////////////////////////////////////////////////////////////////////////

  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  verilator_top = new Vtop;
  verilator_top->trace(tfp, 99);
  tfp->open("tmp.vcd");
  main_time = 0;

  //////////////////////////////////////////////////////////////////////////////// initial begin ///////////////////////////////////////////////////////////////////////////////////////////

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
  verilator_top->S_AXI_WDATA = RANNUM - 1; // 1023番目をランダムな値に使う
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  // gen <- 1;
  // ランダムなハイパーベクトルを自動生成
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
  // ---- genはここで０になっている ----

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

  int tmp = 0;

  // EVEN ===========================================================================

  if (EVEN)
  {
    // load
    uint16_t addr = MAJORITY_ADDR;
    conv.data_0 = assemble(1, 1, addr);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
    tmp++;
    for (int i = tmp; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();

    // store
    tmp = 0;
    conv.data_0 = assemble(0, 8, 0);
    conv.data_1 = 0;
    verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
    tmp++;
    for (int i = tmp; i < 32; i++)
    {
      verilator_top->S_AXIS_TDATA[i] = 0;
    }
    eval();
  }

  // ↓ここを書き換える==================================================================

  for (int j = 0; j < ADDRNUM; j++)
  {

    if (REMAINDAR != 0 && j == LAST)
    {

      // 1 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 1, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 1, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + 1 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + 2 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 3 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 3, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 3, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 9 (ここは必ずラストの命令) -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 9, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 9, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (REMAINDAR % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      j += NGRAM * CORENUM - 1;
    } /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
      // 1 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 1, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 1, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + 1 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 10 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 10, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 2 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        uint16_t addr = NGRAM * i + 2 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(1, 2, addr);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 3 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 3, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 3, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      // 7 -------------------------------------------------------------------
      tmp = 0;
      for (int i = 0; i < CORENUM; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = assemble(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = assemble(0, 7, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
      }
      // 奇数のとき最後の代入ができていない
      if (CORENUM % 2 != 0)
      {
        verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
        tmp++;
      }
      // 残り埋める
      for (int i = tmp; i < 32; i++)
      {
        verilator_top->S_AXIS_TDATA[i] = 0;
      }
      eval();

      if (DEBUG)
      {
        // 送信途中で止まる対策 -----------------------------
        verilator_top->S_AXIS_TVALID = 0;
        for (int i = 0; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
        eval();
        eval();
        verilator_top->S_AXIS_TVALID = 1;
        eval();
        // ----------------------------------------------
      }

      if (j == LAST)
      {
        // 9 -------------------------------------------------------------------
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            // conv.data_0 = assemble(0, 9, 0);
            conv.data_0 = assemble(1, 11, 1023);
            conv.data_1 = 0;
          }
          else
          {
            // conv.data_1 = assemble(0, 9, 0);
            conv.data_0 = assemble(1, 11, 1023);
            verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
        // 残り埋める
        for (int i = tmp; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
      }
      else
      {
        // 8 -------------------------------------------------------------------
        tmp = 0;
        for (int i = 0; i < CORENUM; i++)
        {
          if (i % 2 == 0)
          {
            conv.data_0 = assemble(0, 8, 0);
            conv.data_1 = 0;
          }
          else
          {
            conv.data_1 = assemble(0, 8, 0);
            verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
            tmp++;
          }
        }
        // 奇数のとき最後の代入ができていない
        if (CORENUM % 2 != 0)
        {
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
        // 残り埋める
        for (int i = tmp; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
      }

      // 更新
      j += NGRAM * CORENUM - 1;
    }
  }

  // ↑ここを書き換える==================================================================

  verilator_top->S_AXIS_TVALID = 0;

  // 最後の送信途中で止まる対策 --------------
  for (int i = 0; i < 32; i++)
  {
    verilator_top->S_AXIS_TDATA[i] = 0;
  }
  eval();
  eval();
  eval();
  // -------------------------------------

  // 演算結果を待つ
  while (!verilator_top->M_AXIS_TVALID)
  {
    eval();
  }

  eval();
  eval();
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////  Output ////////////////////////////////////////////////////////////////////////////////////

  // printf("\n --------------------------- Output ---------------------------- \n\n\n");

  for (int i = 0; i < 1; i++)
  {
    for (int j = 0; j < DIM; j++)
    {
      printf("  %u\n", verilator_top->M_AXIS_TDATA[j]);
      // putb(verilator_top->M_AXIS_TDATA[j]);
    }
    eval();
  }
  eval();
  eval();
  eval();

  verilator_top->S_AXI_AWADDR = 0;
  verilator_top->S_AXI_WDATA = 0;
  verilator_top->S_AXI_AWVALID = 1;
  verilator_top->S_AXI_WVALID = 1;
  eval();
  verilator_top->S_AXI_AWVALID = 0;
  verilator_top->S_AXI_WVALID = 0;
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  eval();
  eval();
  verilator_top->S_AXI_ARESETN = 0;
  verilator_top->AXIS_ARESETN = 0;
  eval();
  eval();

  delete verilator_top;
  tfp->close();
  return;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
  printf("\n ====================================== 開始 ========================================= \n\n");

  const int NGRAM = 3;
  const int CORENUM = 1;
  int DEBUG = 0;
  int ADDRNUM = 0;
  // 次元数可変 (結果を何個出力するかに使う)
  const int DIM = 32 / 32;
  // const int DIM = 1024 / 32;
  const int MAJORITY_ADDR = 1023;

  const int SIMULATION_COUNT = 100;
  for (int i = 3; i < SIMULATION_COUNT; i += 3)
  {
    ADDRNUM = i;

    DEBUG = 1;
    // check(NGRAM, CORENUM, ADDRNUM, DIM, MAJORITY_ADDR, argc, argv, DEBUG);
    check2(NGRAM, CORENUM, ADDRNUM, DIM, MAJORITY_ADDR, argc, argv, DEBUG);

    printf(" -------------------\n\n");
  }

  // ADDRNUM = 42;
  // DEBUG = 0;
  // check(NGRAM, CORENUM, ADDRNUM, DIM, MAJORITY_ADDR, argc, argv, DEBUG);
  // printf(" --------\n\n");
  // ADDRNUM = 54;
  // DEBUG = 1;
  // check(NGRAM, CORENUM, ADDRNUM, DIM,MAJORITY_ADDR, argc, argv, DEBUG);

  printf("\n ======================================= 終了 ========================================= \n\n");

  return 0;
}