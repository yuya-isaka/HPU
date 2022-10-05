// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;

class Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    CData/*0:0*/ top__DOT__sysclk;
    VL_IN8(rst,0,0);
    VL_OUT8(anode,3,0);
    VL_OUT8(seg,6,0);
    CData/*0:0*/ top__DOT__Core__DOT__state_idle;
    CData/*0:0*/ top__DOT__Core__DOT__state_if;
    CData/*0:0*/ top__DOT__Core__DOT__state_de;
    CData/*0:0*/ top__DOT__Core__DOT__state_ex;
    CData/*0:0*/ top__DOT__Core__DOT__state_ma;
    CData/*0:0*/ top__DOT__Core__DOT__state_wb;
    CData/*0:0*/ top__DOT__Core__DOT__Decode__DOT__i_type;
    CData/*0:0*/ top__DOT__Core__DOT__Decode__DOT__u_type;
    CData/*6:0*/ __Vfunc_top__DOT__Seven__DOT__decode__3__Vfuncout;
    CData/*6:0*/ __Vfunc_top__DOT__Seven__DOT__decode__4__Vfuncout;
    CData/*6:0*/ __Vfunc_top__DOT__Seven__DOT__decode__5__Vfuncout;
    CData/*6:0*/ __Vfunc_top__DOT__Seven__DOT__decode__6__Vfuncout;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__top__DOT__sysclk;
    VL_OUT16(led,15,0);
    IData/*31:0*/ top__DOT__count;
    IData/*31:0*/ top__DOT__Core__DOT__pc;
    IData/*31:0*/ top__DOT__Core__DOT____Vcellout__Imem__inst;
    IData/*31:0*/ top__DOT__Core__DOT____Vcellout__Decode__imm;
    IData/*31:0*/ top__DOT__Core__DOT__rs1_data;
    IData/*31:0*/ top__DOT__Core__DOT__rs2_data;
    IData/*31:0*/ top__DOT__Core__DOT__alu_out;
    IData/*31:0*/ top__DOT__Core__DOT____Vcellout__Dmem__read_data;
    IData/*31:0*/ top__DOT__Core__DOT__Alu__DOT__op2;
    IData/*31:0*/ top__DOT__Seven__DOT__seg_counter;
    IData/*31:0*/ __Vfunc_top__DOT__Seven__DOT__decode__3__binary;
    IData/*31:0*/ __Vfunc_top__DOT__Seven__DOT__decode__4__binary;
    IData/*31:0*/ __Vfunc_top__DOT__Seven__DOT__decode__5__binary;
    IData/*31:0*/ __Vfunc_top__DOT__Seven__DOT__decode__6__binary;
    QData/*63:0*/ top__DOT__Core__DOT__imem;
    VlWide<3>/*65:0*/ top__DOT__Core__DOT__de;
    VlWide<5>/*128:0*/ top__DOT__Core__DOT__dmem;
    VlUnpacked<IData/*31:0*/, 32> top__DOT__Core__DOT__register;
    VlUnpacked<IData/*31:0*/, 64> top__DOT__Core__DOT__Imem__DOT__mem;
    VlUnpacked<IData/*31:0*/, 512> top__DOT__Core__DOT__Dmem__DOT__mem;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
