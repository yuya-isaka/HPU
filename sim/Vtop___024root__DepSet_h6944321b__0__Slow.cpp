// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___initial__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___initial__TOP__0\n"); );
    // Body
    vlSelf->M_AXIS_TSTRB = 0xffU;
    vlSelf->M_AXIS_TLAST = 0U;
    vlSelf->S_AXI_BRESP = 0U;
    vlSelf->S_AXI_RRESP = 0U;
}

VL_ATTR_COLD void Vtop___024root___settle__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___settle__TOP__0\n"); );
    // Body
    vlSelf->top__DOT__acc[4U] = 0U;
    vlSelf->top__DOT____Vcellinp__src_buf__src_a = 
        ((0x100U & ((~ (IData)(vlSelf->top__DOT__p)) 
                    << 8U)) | (IData)(vlSelf->top__DOT__src_ctrl__DOT__i));
    vlSelf->top__DOT____Vcellinp__dst_buf__out_addr 
        = (((IData)(vlSelf->top__DOT__p) << 4U) | (IData)(vlSelf->top__DOT__out_addr));
    if (vlSelf->top__DOT__update) {
        vlSelf->top__DOT__acc[0U] = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
        vlSelf->top__DOT__acc[1U] = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
        vlSelf->top__DOT__acc[2U] = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
        vlSelf->top__DOT__acc[3U] = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
    } else {
        vlSelf->top__DOT__acc[0U] = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right;
        vlSelf->top__DOT__acc[1U] = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right;
        vlSelf->top__DOT__acc[2U] = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right;
        vlSelf->top__DOT__acc[3U] = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right;
    }
    vlSelf->top__DOT____Vcellinp__dst_buf__stream_a 
        = ((8U & ((~ (IData)(vlSelf->top__DOT__p)) 
                  << 3U)) | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__i));
    vlSelf->top__DOT__dst_ctrl__DOT__start = ((IData)(vlSelf->M_AXIS_TREADY) 
                                              & (IData)(vlSelf->top__DOT__dst_ctrl__DOT__start_check));
    vlSelf->top__DOT__stream_v = ((IData)(vlSelf->top__DOT__dst_ctrl__DOT__stream_active) 
                                  & (IData)(vlSelf->M_AXIS_TREADY));
    vlSelf->top__DOT__mat_v = (((IData)(vlSelf->S_AXIS_TVALID) 
                                & (IData)(vlSelf->top__DOT__matw))
                                ? (0xfU & ((IData)(1U) 
                                           << (IData)(vlSelf->top__DOT__mat_ctrl__DOT__core_sel)))
                                : 0U);
    vlSelf->top__DOT__k_init = (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay) 
                                 | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__k_init_next)) 
                                & (~ (IData)(vlSelf->top__DOT__out_busy)));
    vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr 
        = (((IData)(vlSelf->top__DOT__p) << 8U) | (0xffU 
                                                   & (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                                                       << 6U) 
                                                      + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j))));
    vlSelf->top__DOT__exe_ctrl__DOT__last_j = ((0x3fU 
                                                == (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j)) 
                                               & ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run) 
                                                  | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__start)));
    vlSelf->S_AXIS_TREADY = (3U != (IData)(vlSelf->top__DOT__src_en));
    vlSelf->top__DOT__s_fin_in = ((((IData)(vlSelf->top__DOT__s_fin) 
                                    | (IData)(vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo)) 
                                   & (((IData)(vlSelf->top__DOT__src_en) 
                                       >> (1U & (~ (IData)(vlSelf->top__DOT__p)))) 
                                      | (IData)(vlSelf->top__DOT__last))) 
                                  & (IData)(vlSelf->M_AXIS_TREADY));
    vlSelf->top__DOT__out_ctrl__DOT__start = (((IData)(vlSelf->top__DOT__k_fin) 
                                               & (~ (IData)(vlSelf->top__DOT__out_ctrl__DOT__j_period))) 
                                              | ((IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next) 
                                                 & (IData)(vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention)));
    vlSelf->top__DOT__INI = (0U == (IData)(vlSelf->top__DOT__state));
    vlSelf->top__DOT__AW = (1U == (IData)(vlSelf->top__DOT__state));
    vlSelf->top__DOT__W = (2U == (IData)(vlSelf->top__DOT__state));
    vlSelf->top__DOT__AWW = (3U == (IData)(vlSelf->top__DOT__state));
    vlSelf->top__DOT__AR1 = (4U == (IData)(vlSelf->top__DOT__state));
    vlSelf->top__DOT__AR2 = (8U == (IData)(vlSelf->top__DOT__state));
    vlSelf->S_AXI_AWREADY = ((0U == (IData)(vlSelf->top__DOT__state)) 
                             | (2U == (IData)(vlSelf->top__DOT__state)));
    vlSelf->S_AXI_WREADY = ((0U == (IData)(vlSelf->top__DOT__state)) 
                            | (1U == (IData)(vlSelf->top__DOT__state)));
    vlSelf->S_AXI_ARREADY = (0U == (IData)(vlSelf->top__DOT__state));
    vlSelf->S_AXI_BVALID = (3U == (IData)(vlSelf->top__DOT__state));
    vlSelf->S_AXI_RVALID = (8U == (IData)(vlSelf->top__DOT__state));
    vlSelf->top__DOT__register_w = (IData)(((3U == (IData)(vlSelf->top__DOT__state)) 
                                            & (0U == 
                                               (0x300U 
                                                & (IData)(vlSelf->top__DOT__write_addr)))));
    if ((8U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))) {
        vlSelf->M_AXIS_TDATA[0U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0U];
        vlSelf->M_AXIS_TDATA[1U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[1U];
        vlSelf->M_AXIS_TDATA[2U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[2U];
        vlSelf->M_AXIS_TDATA[3U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[3U];
        vlSelf->M_AXIS_TDATA[4U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[4U];
        vlSelf->M_AXIS_TDATA[5U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[5U];
        vlSelf->M_AXIS_TDATA[6U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[6U];
        vlSelf->M_AXIS_TDATA[7U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[7U];
        vlSelf->M_AXIS_TDATA[8U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[8U];
        vlSelf->M_AXIS_TDATA[9U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[9U];
        vlSelf->M_AXIS_TDATA[0xaU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0xaU];
        vlSelf->M_AXIS_TDATA[0xbU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0xbU];
        vlSelf->M_AXIS_TDATA[0xcU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0xcU];
        vlSelf->M_AXIS_TDATA[0xdU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0xdU];
        vlSelf->M_AXIS_TDATA[0xeU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0xeU];
        vlSelf->M_AXIS_TDATA[0xfU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0xfU];
        vlSelf->M_AXIS_TDATA[0x10U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x10U];
        vlSelf->M_AXIS_TDATA[0x11U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x11U];
        vlSelf->M_AXIS_TDATA[0x12U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x12U];
        vlSelf->M_AXIS_TDATA[0x13U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x13U];
        vlSelf->M_AXIS_TDATA[0x14U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x14U];
        vlSelf->M_AXIS_TDATA[0x15U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x15U];
        vlSelf->M_AXIS_TDATA[0x16U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x16U];
        vlSelf->M_AXIS_TDATA[0x17U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x17U];
        vlSelf->M_AXIS_TDATA[0x18U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x18U];
        vlSelf->M_AXIS_TDATA[0x19U] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x19U];
        vlSelf->M_AXIS_TDATA[0x1aU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1aU];
        vlSelf->M_AXIS_TDATA[0x1bU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1bU];
        vlSelf->M_AXIS_TDATA[0x1cU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1cU];
        vlSelf->M_AXIS_TDATA[0x1dU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1dU];
        vlSelf->M_AXIS_TDATA[0x1eU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1eU];
        vlSelf->M_AXIS_TDATA[0x1fU] = vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1fU];
    } else {
        vlSelf->M_AXIS_TDATA[0U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0U];
        vlSelf->M_AXIS_TDATA[1U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[1U];
        vlSelf->M_AXIS_TDATA[2U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[2U];
        vlSelf->M_AXIS_TDATA[3U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[3U];
        vlSelf->M_AXIS_TDATA[4U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[4U];
        vlSelf->M_AXIS_TDATA[5U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[5U];
        vlSelf->M_AXIS_TDATA[6U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[6U];
        vlSelf->M_AXIS_TDATA[7U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[7U];
        vlSelf->M_AXIS_TDATA[8U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[8U];
        vlSelf->M_AXIS_TDATA[9U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[9U];
        vlSelf->M_AXIS_TDATA[0xaU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0xaU];
        vlSelf->M_AXIS_TDATA[0xbU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0xbU];
        vlSelf->M_AXIS_TDATA[0xcU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0xcU];
        vlSelf->M_AXIS_TDATA[0xdU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0xdU];
        vlSelf->M_AXIS_TDATA[0xeU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0xeU];
        vlSelf->M_AXIS_TDATA[0xfU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0xfU];
        vlSelf->M_AXIS_TDATA[0x10U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x10U];
        vlSelf->M_AXIS_TDATA[0x11U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x11U];
        vlSelf->M_AXIS_TDATA[0x12U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x12U];
        vlSelf->M_AXIS_TDATA[0x13U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x13U];
        vlSelf->M_AXIS_TDATA[0x14U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x14U];
        vlSelf->M_AXIS_TDATA[0x15U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x15U];
        vlSelf->M_AXIS_TDATA[0x16U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x16U];
        vlSelf->M_AXIS_TDATA[0x17U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x17U];
        vlSelf->M_AXIS_TDATA[0x18U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x18U];
        vlSelf->M_AXIS_TDATA[0x19U] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x19U];
        vlSelf->M_AXIS_TDATA[0x1aU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1aU];
        vlSelf->M_AXIS_TDATA[0x1bU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1bU];
        vlSelf->M_AXIS_TDATA[0x1cU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1cU];
        vlSelf->M_AXIS_TDATA[0x1dU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1dU];
        vlSelf->M_AXIS_TDATA[0x1eU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1eU];
        vlSelf->M_AXIS_TDATA[0x1fU] = vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1fU];
    }
    vlSelf->top__DOT__dst_ctrl__DOT__last_i = (((0U 
                                                 == (IData)(vlSelf->top__DOT__dst_ctrl__DOT__i)) 
                                                & ((IData)(vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run) 
                                                   | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__start))) 
                                               & (IData)(vlSelf->M_AXIS_TREADY));
    vlSelf->top__DOT__exe_ctrl__DOT____Vcellinp__d_exec__in 
        = ((IData)(vlSelf->top__DOT__k_init) | ((IData)(vlSelf->top__DOT__exec) 
                                                & (~ (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j))));
    vlSelf->top__DOT__exe_ctrl__DOT__last_i = (((3U 
                                                 == (IData)(vlSelf->top__DOT__exe_ctrl__DOT__i)) 
                                                & ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run) 
                                                   | (IData)(vlSelf->top__DOT__s_init))) 
                                               & (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j));
    vlSelf->top__DOT__src_ctrl__DOT__sen = ((IData)(vlSelf->S_AXIS_TVALID) 
                                            & (IData)(vlSelf->S_AXIS_TREADY));
    vlSelf->top__DOT__out_ctrl__DOT__last_j = ((3U 
                                                == (IData)(vlSelf->top__DOT__out_ctrl__DOT__j)) 
                                               & ((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run) 
                                                  | (IData)(vlSelf->top__DOT__out_ctrl__DOT__start)));
    vlSelf->top__DOT__dst_ctrl__DOT__stream_active_pre 
        = (((IData)(vlSelf->top__DOT__s_fin_in) | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__stream_active)) 
           & (~ (IData)(vlSelf->top__DOT__dst_ctrl__DOT__last_i)));
    vlSelf->top__DOT__src_ctrl__DOT__start = (((IData)(vlSelf->top__DOT__src_ctrl__DOT__sen) 
                                               & (IData)(vlSelf->top__DOT__run)) 
                                              & (~ (IData)(vlSelf->top__DOT__matw)));
    vlSelf->top__DOT__out_ctrl__DOT__last_i = (((3U 
                                                 == (IData)(vlSelf->top__DOT__out_ctrl__DOT__i)) 
                                                & ((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run) 
                                                   | (IData)(vlSelf->top__DOT__s_init))) 
                                               & (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j));
    vlSelf->top__DOT__src_ctrl__DOT__last_i = (((0xe0U 
                                                 == (IData)(vlSelf->top__DOT__src_ctrl__DOT__i)) 
                                                & ((IData)(vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run) 
                                                   | (IData)(vlSelf->top__DOT__src_ctrl__DOT__start))) 
                                               & (IData)(vlSelf->top__DOT__src_ctrl__DOT__sen));
}

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    Vtop___024root___initial__TOP__0(vlSelf);
    vlSelf->__Vclklast__TOP__AXIS_ACLK = vlSelf->AXIS_ACLK;
    vlSelf->__Vclklast__TOP__S_AXI_ACLK = vlSelf->S_AXI_ACLK;
}

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Body
    Vtop___024root___settle__TOP__0(vlSelf);
    vlSelf->__Vm_traceActivity[3U] = 1U;
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
}

VL_ATTR_COLD void Vtop___024root___final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___final\n"); );
}

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->S_AXI_ACLK = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_ARESETN = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_AWADDR = VL_RAND_RESET_I(32);
    vlSelf->S_AXI_AWVALID = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_AWREADY = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_WDATA = VL_RAND_RESET_I(32);
    vlSelf->S_AXI_WSTRB = VL_RAND_RESET_I(4);
    vlSelf->S_AXI_WVALID = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_WREADY = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_BRESP = VL_RAND_RESET_I(2);
    vlSelf->S_AXI_BVALID = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_BREADY = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_ARADDR = VL_RAND_RESET_I(32);
    vlSelf->S_AXI_ARVALID = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_ARREADY = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_RDATA = VL_RAND_RESET_I(32);
    vlSelf->S_AXI_RRESP = VL_RAND_RESET_I(2);
    vlSelf->S_AXI_RVALID = VL_RAND_RESET_I(1);
    vlSelf->S_AXI_RREADY = VL_RAND_RESET_I(1);
    vlSelf->AXIS_ACLK = VL_RAND_RESET_I(1);
    vlSelf->AXIS_ARESETN = VL_RAND_RESET_I(1);
    vlSelf->M_AXIS_TVALID = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(1024, vlSelf->M_AXIS_TDATA);
    vlSelf->M_AXIS_TSTRB = VL_RAND_RESET_I(8);
    vlSelf->M_AXIS_TLAST = VL_RAND_RESET_I(1);
    vlSelf->M_AXIS_TREADY = VL_RAND_RESET_I(1);
    vlSelf->S_AXIS_TREADY = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(1024, vlSelf->S_AXIS_TDATA);
    vlSelf->S_AXIS_TSTRB = VL_RAND_RESET_I(8);
    vlSelf->S_AXIS_TLAST = VL_RAND_RESET_I(1);
    vlSelf->S_AXIS_TVALID = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__run = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__matw = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__last = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__mat_v = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__mat_a = VL_RAND_RESET_I(6);
    vlSelf->top__DOT__src_en = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__p = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__s_fin_in = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__s_init = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__s_fin = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__k_init = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__k_fin = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exec = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_busy = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_period = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_fin = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_addr = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__update = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exec_src_data = VL_RAND_RESET_I(32);
    vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr = VL_RAND_RESET_I(9);
    vlSelf->top__DOT____Vcellinp__src_buf__src_a = VL_RAND_RESET_I(9);
    vlSelf->top__DOT__stream_v = VL_RAND_RESET_I(1);
    vlSelf->top__DOT____Vcellinp__dst_buf__out_addr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT____Vcellinp__dst_buf__stream_a = VL_RAND_RESET_I(4);
    for (int __Vi0=0; __Vi0<5; ++__Vi0) {
        vlSelf->top__DOT__acc[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->top__DOT__state = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__write_addr = VL_RAND_RESET_I(10);
    vlSelf->top__DOT__read_addr = VL_RAND_RESET_I(10);
    vlSelf->top__DOT__write_data = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__INI = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__AW = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__W = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__AWW = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__AR1 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__AR2 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__control = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__register_w = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__mat_ctrl__DOT__core_sel = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__src_ctrl__DOT__sen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__src_ctrl__DOT__start = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__src_ctrl__DOT__last_i = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__src_ctrl__DOT__i = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__last_i = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__last_j = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__i = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__exe_ctrl__DOT__j = VL_RAND_RESET_I(6);
    vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__k_init_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__start = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT____Vcellinp__d_exec__in = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__out_addr_pre = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__out_ctrl__DOT__last_i = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__last_j = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__i = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__out_ctrl__DOT__j = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__out_ctrl__DOT__last_j_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__out_period_pre = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__update_after_start = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__start = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__j_period = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run = VL_RAND_RESET_I(1);
    for (int __Vi0=0; __Vi0<256; ++__Vi0) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0=0; __Vi0<256; ++__Vi0) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->top__DOT__dst_ctrl__DOT__i = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__dst_ctrl__DOT__last_i = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dst_ctrl__DOT__start = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dst_ctrl__DOT__start_check = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dst_ctrl__DOT__stream_active = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dst_ctrl__DOT__stream_active_pre = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(1024, vlSelf->top__DOT__dst_buf__DOT__stream_0);
    VL_RAND_RESET_W(1024, vlSelf->top__DOT__dst_buf__DOT__stream_1);
    for (int __Vi0=0; __Vi0<8; ++__Vi0) {
        vlSelf->top__DOT__dst_buf__DOT__buff0[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0=0; __Vi0<8; ++__Vi0) {
        vlSelf->top__DOT__dst_buf__DOT__buff1[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0=0; __Vi0<8; ++__Vi0) {
        vlSelf->top__DOT__dst_buf__DOT__buff2[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0=0; __Vi0<8; ++__Vi0) {
        vlSelf->top__DOT__dst_buf__DOT__buff3[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0=0; __Vi0<64; ++__Vi0) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2 = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<64; ++__Vi0) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2 = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<64; ++__Vi0) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2 = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<64; ++__Vi0) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2 = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }
}
