// iclude
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

union
{
  struct
  {
    uint16_t data_0;
    uint16_t data_1;
  };
  uint32_t write_data;
} conv;

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
  printf("  0"), putchar('b'), printb(v), printf("\n");
}

uint16_t instruction(int addr_flag, unsigned int inst_num, uint16_t addr)
{
  if (addr_flag)
  {
    uint16_t result = 0;
    if (inst_num == 1)
    {
      uint16_t inst = 3 << 14;
      result = inst | addr;
    }
    else if (inst_num == 2)
    {
      uint16_t inst = 5 << 13;
      result = inst | addr;
    }
    else if (inst_num == 4)
    {
      uint16_t inst = 9 << 12;
      result = inst | addr;
    }
    else if (inst_num == 6)
    {
      uint16_t inst = 17 << 11;
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
    if (inst_num == 3)
    {
      inst = 1 << 14;
    }
    else if (inst_num == 5)
    {
      inst = 1 << 13;
    }
    else if (inst_num == 7)
    {
      inst = 1 << 12;
    }
    else if (inst_num == 8)
    {
      inst = 1 << 11;
    }
    else if (inst_num == 9)
    {
      inst = 1 << 10;
    }
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check(const int NGRAM, const int CORENUM, const int ADDRNUM, const int DIM, int argc, char **argv, const int DEBUG)
{

  // 最低限 = NGRAMの倍数(3の倍数)であることは保証されている（今回のテストケースではそれしか対応していないから）
  // 16コアすべてを使わないケースがあるか調べる
  const int REMAINDAR = (ADDRNUM / 3) % 16;
  const int EVEN = ((ADDRNUM / NGRAM) % 2) == 0;
  int LAST = (ADDRNUM / 3) / 16;
  if (REMAINDAR == 0)
  {
    LAST--;
  }
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

  // printf("\n  生成！\n");
  // matwはここで０になっている

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Parameter セットアップ

  // even
  verilator_top->S_AXI_AWADDR = 8;
  verilator_top->S_AXI_WDATA = EVEN;
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

  // ==================================================================

  // 送信
  verilator_top->S_AXIS_TVALID = 1;

  // ↓ここを書き換える==================================================================

  int tmp = 0;
  for (int j = 0; j < ADDRNUM; j++)
  {

    if (REMAINDAR != 0 && j == LAST)
    {

      // 1
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + j;
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(1, 1, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(1, 1, addr);
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

      // 10
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(0, 10, 0);
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

      // 2
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + 1 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(1, 2, addr);
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

      // 7
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(0, 7, 0);
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

      // 10
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(0, 10, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(0, 10, 0);
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

      // 2
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        uint16_t addr = NGRAM * i + 2 + j;
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(1, 2, addr);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(1, 2, addr);
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

      // 3
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(0, 3, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(0, 3, 0);
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

      // 7
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(0, 7, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(0, 7, 0);
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

      // 9
      tmp = 0;
      for (int i = 0; i < REMAINDAR; i++)
      {
        if (i % 2 == 0)
        {
          conv.data_0 = instruction(0, 9, 0);
          conv.data_1 = 0;
        }
        else
        {
          conv.data_1 = instruction(0, 9, 0);
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

      j += NGRAM * CORENUM - 1;
    }
    else
    {
      // 1
      tmp = 0;
      for (int i = 0; i < CORENUM; i += 2)
      {
        uint16_t addr = NGRAM * i + j;
        conv.data_0 = instruction(1, 1, addr);

        addr = NGRAM * (i + 1) + j;
        conv.data_1 = instruction(1, 1, addr);

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

      // 10
      tmp = 0;
      for (int i = 0; i < CORENUM; i += 2)
      {
        conv.data_0 = instruction(0, 10, 0);
        conv.data_1 = instruction(0, 10, 0);
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

      // 2
      tmp = 0;
      for (int i = 0; i < CORENUM; i += 2)
      {
        uint16_t addr = NGRAM * i + 1 + j;
        conv.data_0 = instruction(1, 2, addr);
        addr = NGRAM * (i + 1) + 1 + j;
        conv.data_1 = instruction(1, 2, addr);
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

      // 7
      tmp = 0;
      for (int i = 0; i < CORENUM; i += 2)
      {
        conv.data_0 = instruction(0, 7, 0);
        conv.data_1 = instruction(0, 7, 0);
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

      // 10
      tmp = 0;
      for (int i = 0; i < CORENUM; i += 2)
      {
        conv.data_0 = instruction(0, 10, 0);
        conv.data_1 = instruction(0, 10, 0);
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

      // 2
      tmp = 0;
      for (int i = 0; i < CORENUM; i += 2)
      {
        uint16_t addr = NGRAM * i + 2 + j;
        conv.data_0 = instruction(1, 2, addr);
        addr = NGRAM * (i + 1) + 2 + j;
        conv.data_1 = instruction(1, 2, addr);
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

      // 3
      tmp = 0;
      for (int i = 0; i < CORENUM; i += 2)
      {
        conv.data_0 = instruction(0, 3, 0);
        conv.data_1 = instruction(0, 3, 0);
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

      // 7
      tmp = 0;
      for (int i = 0; i < CORENUM; i += 2)
      {
        conv.data_0 = instruction(0, 7, 0);
        conv.data_1 = instruction(0, 7, 0);
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

      if (j == LAST)
      {
        // 9
        tmp = 0;
        for (int i = 0; i < CORENUM; i += 2)
        {

          conv.data_0 = instruction(0, 9, 0);
          conv.data_1 = instruction(0, 9, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
      }
      else
      {
        // 8
        tmp = 0;
        for (int i = 0; i < CORENUM; i += 2)
        {

          conv.data_0 = instruction(0, 8, 0);
          conv.data_1 = instruction(0, 8, 0);
          verilator_top->S_AXIS_TDATA[tmp] = conv.write_data;
          tmp++;
        }
        for (int i = tmp; i < 32; i++)
        {
          verilator_top->S_AXIS_TDATA[i] = 0;
        }
        eval();
      }

      j += NGRAM * CORENUM - 1;
    }
  }

  // ↑ここを書き換える==================================================================

  // 最後の送信途中で止まる対策 -----------------------------
  verilator_top->S_AXIS_TVALID = 0;
  for (int i = 0; i < 32; i++)
  {
    verilator_top->S_AXIS_TDATA[i] = 0;
  }
  eval();
  eval();
  eval();
  // ----------------------------------------------

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
      printf("\n");
    }
    // printf("  %u\n\n", verilator_top->M_AXIS_TDATA[0]);
    // putb(verilator_top->M_AXIS_TDATA[0]);
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

  eval();
  eval();
  verilator_top->S_AXI_ARESETN = 0;
  verilator_top->AXIS_ARESETN = 0;
  eval();
  eval();

  /////////////////////////////////////////////////////////////////////////////////////////  終了 ////////////////////////////////////////////////////////////////////////////////////

  delete verilator_top;
  tfp->close();
  return;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
  printf("\n ================================================= 開始 ================================================= \n\n");

  const int NGRAM = 3;
  const int CORENUM = 16;
  int DEBUG = 0;
  int ADDRNUM = 0;
  // 次元数可変 (結果を何個出力するかに使う)
  // const int DIM = 1024 / 32;
  const int DIM = 32 / 32;

  for (int i = 3; i < RANNUM; i += 3)
  {
    ADDRNUM = i;

    DEBUG = 1;
    check(NGRAM, CORENUM, ADDRNUM, DIM, argc, argv, DEBUG);

    printf(" --------\n\n");
  }

  // ADDRNUM = 51;
  // DEBUG = 1;
  // check(NGRAM, CORENUM, ADDRNUM, DIM, argc, argv, DEBUG);
  // printf(" --------\n\n");
  // ADDRNUM = 54;
  // DEBUG = 1;
  // check(NGRAM, CORENUM, ADDRNUM, DIM, argc, argv, DEBUG);

  printf("\n ================================================= 終了 ================================================= \n\n");

  return 0;
}