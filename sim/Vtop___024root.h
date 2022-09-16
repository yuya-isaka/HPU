// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;
VL_MODULE(Vtop___024root) {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(S_AXI_ACLK,0,0);
        VL_IN8(AXIS_ACLK,0,0);
        VL_IN8(S_AXI_ARESETN,0,0);
        VL_IN8(S_AXI_AWVALID,0,0);
        VL_OUT8(S_AXI_AWREADY,0,0);
        VL_IN8(S_AXI_WSTRB,3,0);
        VL_IN8(S_AXI_WVALID,0,0);
        VL_OUT8(S_AXI_WREADY,0,0);
        VL_OUT8(S_AXI_BRESP,1,0);
        VL_OUT8(S_AXI_BVALID,0,0);
        VL_IN8(S_AXI_BREADY,0,0);
        VL_IN8(S_AXI_ARVALID,0,0);
        VL_OUT8(S_AXI_ARREADY,0,0);
        VL_OUT8(S_AXI_RRESP,1,0);
        VL_OUT8(S_AXI_RVALID,0,0);
        VL_IN8(S_AXI_RREADY,0,0);
        VL_IN8(AXIS_ARESETN,0,0);
        VL_OUT8(M_AXIS_TVALID,0,0);
        VL_OUT8(M_AXIS_TSTRB,7,0);
        VL_OUT8(M_AXIS_TLAST,0,0);
        VL_IN8(M_AXIS_TREADY,0,0);
        VL_OUT8(S_AXIS_TREADY,0,0);
        VL_IN8(S_AXIS_TSTRB,7,0);
        VL_IN8(S_AXIS_TLAST,0,0);
        VL_IN8(S_AXIS_TVALID,0,0);
        CData/*0:0*/ top__DOT__run;
        CData/*0:0*/ top__DOT__matw;
        CData/*0:0*/ top__DOT__last;
        CData/*3:0*/ top__DOT__mat_v;
        CData/*2:0*/ top__DOT__mat_a;
        CData/*1:0*/ top__DOT__src_en;
        CData/*0:0*/ top__DOT__p;
        CData/*0:0*/ top__DOT__s_fin_in;
        CData/*0:0*/ top__DOT__s_init;
        CData/*0:0*/ top__DOT__s_fin;
        CData/*0:0*/ top__DOT__k_init;
        CData/*0:0*/ top__DOT__k_fin;
        CData/*0:0*/ top__DOT__exec;
        CData/*0:0*/ top__DOT__out_busy;
        CData/*0:0*/ top__DOT__out_period;
        CData/*0:0*/ top__DOT__out_fin;
        CData/*3:0*/ top__DOT__out_addr;
        CData/*0:0*/ top__DOT__sum_update;
        CData/*5:0*/ top__DOT____Vcellinp__src_buf__exec_src_addr;
        CData/*4:0*/ top__DOT____Vcellinp__src_buf__src_a;
        CData/*0:0*/ top__DOT__stream_v;
        CData/*4:0*/ top__DOT____Vcellinp__dst_buf__out_addr;
        CData/*3:0*/ top__DOT____Vcellinp__dst_buf__stream_a;
        CData/*3:0*/ top__DOT__state;
        CData/*0:0*/ top__DOT__INI;
        CData/*0:0*/ top__DOT__AW;
        CData/*0:0*/ top__DOT__W;
        CData/*0:0*/ top__DOT__AWW;
        CData/*0:0*/ top__DOT__AR1;
        CData/*0:0*/ top__DOT__AR2;
        CData/*0:0*/ top__DOT__register_w;
        CData/*1:0*/ top__DOT__mat_ctrl__DOT__core_sel;
        CData/*0:0*/ top__DOT__src_ctrl__DOT__sen;
        CData/*0:0*/ top__DOT__src_ctrl__DOT__start;
        CData/*0:0*/ top__DOT__src_ctrl__DOT__last_i;
        CData/*3:0*/ top__DOT__src_ctrl__DOT__i;
        CData/*0:0*/ top__DOT__src_ctrl__DOT__l_i__DOT__run;
        CData/*0:0*/ top__DOT__s_ctrl__DOT__s_fin_dayo;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__last_i;
    };
    struct {
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__last_j;
        CData/*1:0*/ top__DOT__exe_ctrl__DOT__i;
        CData/*2:0*/ top__DOT__exe_ctrl__DOT__j;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__s_init_delay;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__k_init_next;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__start;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__s_fin_period;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT____Vcellinp__d_exec__in;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__l_i__DOT__run;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre;
        CData/*0:0*/ top__DOT__exe_ctrl__DOT__l_j__DOT__run;
        CData/*3:0*/ top__DOT__out_ctrl__DOT__out_addr_pre;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__last_i;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__last_j;
        CData/*1:0*/ top__DOT__out_ctrl__DOT__i;
        CData/*1:0*/ top__DOT__out_ctrl__DOT__j;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__last_j_next;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__out_period_pre;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__update_after_start;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__start;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__k_fin_retention;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__j_period;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__l_i__DOT__run;
        CData/*0:0*/ top__DOT__out_ctrl__DOT__l_j__DOT__run;
        CData/*1:0*/ top__DOT__src_buf__DOT__ia_;
        CData/*2:0*/ top__DOT__dst_ctrl__DOT__i;
        CData/*0:0*/ top__DOT__dst_ctrl__DOT__last_i;
        CData/*0:0*/ top__DOT__dst_ctrl__DOT__start;
        CData/*0:0*/ top__DOT__dst_ctrl__DOT__start_check;
        CData/*0:0*/ top__DOT__dst_ctrl__DOT__stream_active;
        CData/*0:0*/ top__DOT__dst_ctrl__DOT__stream_active_pre;
        CData/*0:0*/ top__DOT__dst_ctrl__DOT__l_da__DOT__run;
        CData/*0:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next;
        CData/*0:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next;
        CData/*0:0*/ __Vclklast__TOP__AXIS_ACLK;
        CData/*0:0*/ __Vclklast__TOP__S_AXI_ACLK;
        SData/*9:0*/ top__DOT__write_addr;
        SData/*9:0*/ top__DOT__read_addr;
        VL_IN(S_AXI_AWADDR,31,0);
        VL_IN(S_AXI_WDATA,31,0);
        VL_IN(S_AXI_ARADDR,31,0);
        VL_OUT(S_AXI_RDATA,31,0);
        IData/*31:0*/ top__DOT__exec_src_data;
        IData/*31:0*/ top__DOT__write_data;
        IData/*31:0*/ top__DOT__control;
        IData/*31:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data;
        IData/*31:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right;
        IData/*31:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
        IData/*31:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2;
    };
    struct {
        IData/*31:0*/ top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2;
        IData/*31:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data;
        IData/*31:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right;
        IData/*31:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
        IData/*31:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2;
        IData/*31:0*/ top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2;
        IData/*31:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data;
        IData/*31:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right;
        IData/*31:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
        IData/*31:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2;
        IData/*31:0*/ top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2;
        IData/*31:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data;
        IData/*31:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right;
        IData/*31:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
        IData/*31:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2;
        IData/*31:0*/ top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2;
        VL_OUT64(M_AXIS_TDATA,63,0);
        VL_IN64(S_AXIS_TDATA,63,0);
        QData/*63:0*/ top__DOT__src_buf__DOT__wd0;
        QData/*63:0*/ top__DOT__src_buf__DOT__wd1;
        QData/*63:0*/ top__DOT__dst_buf__DOT__stream_0;
        QData/*63:0*/ top__DOT__dst_buf__DOT__stream_1;
        VlUnpacked<IData/*31:0*/, 5> top__DOT__acc;
        VlUnpacked<QData/*63:0*/, 16> top__DOT__src_buf__DOT__buff0;
        VlUnpacked<QData/*63:0*/, 16> top__DOT__src_buf__DOT__buff1;
        VlUnpacked<IData/*31:0*/, 8> top__DOT__dst_buf__DOT__buff0;
        VlUnpacked<IData/*31:0*/, 8> top__DOT__dst_buf__DOT__buff1;
        VlUnpacked<IData/*31:0*/, 8> top__DOT__dst_buf__DOT__buff2;
        VlUnpacked<IData/*31:0*/, 8> top__DOT__dst_buf__DOT__buff3;
        VlUnpacked<IData/*31:0*/, 8> top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix;
        VlUnpacked<IData/*31:0*/, 8> top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix;
        VlUnpacked<IData/*31:0*/, 8> top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix;
        VlUnpacked<IData/*31:0*/, 8> top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix;
        VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    };

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
