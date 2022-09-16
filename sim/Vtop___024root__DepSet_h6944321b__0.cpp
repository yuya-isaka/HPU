// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_h1a8234e4_0;
extern const VlUnpacked<CData/*2:0*/, 128> Vtop__ConstPool__TABLE_h938fc429_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_h853816a4_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vtop__ConstPool__TABLE_h5acfcdbc_0;

VL_INLINE_OPT void Vtop___024root___sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__0\n"); );
    // Init
    CData/*6:0*/ __Vtableidx1;
    CData/*1:0*/ __Vdly__top__DOT__mat_ctrl__DOT__core_sel;
    CData/*2:0*/ __Vdly__top__DOT__mat_a;
    CData/*0:0*/ __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run;
    CData/*3:0*/ __Vdly__top__DOT__src_ctrl__DOT__i;
    CData/*1:0*/ __Vdly__top__DOT__src_en;
    CData/*0:0*/ __Vdly__top__DOT__p;
    CData/*2:0*/ __Vdly__top__DOT__exe_ctrl__DOT__j;
    CData/*1:0*/ __Vdly__top__DOT__out_ctrl__DOT__i;
    CData/*1:0*/ __Vdly__top__DOT__out_ctrl__DOT__j;
    CData/*3:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v0;
    QData/*63:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v0;
    CData/*3:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v0;
    QData/*63:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v0;
    CData/*2:0*/ __Vdly__top__DOT__dst_ctrl__DOT__i;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__dst_buf__DOT__buff0__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__dst_buf__DOT__buff0__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__dst_buf__DOT__buff0__v0;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__dst_buf__DOT__buff1__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__dst_buf__DOT__buff1__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__dst_buf__DOT__buff1__v0;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__dst_buf__DOT__buff2__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__dst_buf__DOT__buff2__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__dst_buf__DOT__buff2__v0;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__dst_buf__DOT__buff3__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__dst_buf__DOT__buff3__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__dst_buf__DOT__buff3__v0;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdly__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdly__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdly__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdly__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
    // Body
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v0 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v0 = 0U;
    __Vdly__top__DOT__mat_a = vlSelf->top__DOT__mat_a;
    __Vdly__top__DOT__mat_ctrl__DOT__core_sel = vlSelf->top__DOT__mat_ctrl__DOT__core_sel;
    __Vdly__top__DOT__out_ctrl__DOT__j = vlSelf->top__DOT__out_ctrl__DOT__j;
    __Vdly__top__DOT__dst_ctrl__DOT__i = vlSelf->top__DOT__dst_ctrl__DOT__i;
    __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run 
        = vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run;
    __Vdly__top__DOT__src_ctrl__DOT__i = vlSelf->top__DOT__src_ctrl__DOT__i;
    __Vdly__top__DOT__p = vlSelf->top__DOT__p;
    __Vdly__top__DOT__src_en = vlSelf->top__DOT__src_en;
    __Vdly__top__DOT__exe_ctrl__DOT__j = vlSelf->top__DOT__exe_ctrl__DOT__j;
    __Vdly__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left 
        = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
    __Vdly__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left 
        = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
    __Vdly__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left 
        = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
    __Vdly__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left 
        = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
    __Vdlyvset__top__DOT__dst_buf__DOT__buff3__v0 = 0U;
    __Vdlyvset__top__DOT__dst_buf__DOT__buff2__v0 = 0U;
    __Vdlyvset__top__DOT__dst_buf__DOT__buff1__v0 = 0U;
    __Vdlyvset__top__DOT__dst_buf__DOT__buff0__v0 = 0U;
    __Vdly__top__DOT__out_ctrl__DOT__i = vlSelf->top__DOT__out_ctrl__DOT__i;
    vlSelf->top__DOT__src_buf__DOT__ia_ = ((2U & ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr) 
                                                  >> 4U)) 
                                           | (1U & (IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr)));
    if ((8U & (IData)(vlSelf->top__DOT__mat_v))) {
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0 
            = (IData)(vlSelf->S_AXIS_TDATA);
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->top__DOT__mat_a;
    }
    if ((4U & (IData)(vlSelf->top__DOT__mat_v))) {
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0 
            = (IData)(vlSelf->S_AXIS_TDATA);
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->top__DOT__mat_a;
    }
    if ((2U & (IData)(vlSelf->top__DOT__mat_v))) {
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0 
            = (IData)(vlSelf->S_AXIS_TDATA);
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->top__DOT__mat_a;
    }
    if ((1U & (IData)(vlSelf->top__DOT__mat_v))) {
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0 
            = (IData)(vlSelf->S_AXIS_TDATA);
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->top__DOT__mat_a;
    }
    if (((IData)(vlSelf->top__DOT__src_ctrl__DOT__start) 
         & ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a) 
            >> 4U))) {
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v0 
            = vlSelf->S_AXIS_TDATA;
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v0 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v0 
            = (0xfU & (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a));
    }
    if (((IData)(vlSelf->top__DOT__src_ctrl__DOT__start) 
         & (~ ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a) 
               >> 4U)))) {
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v0 
            = vlSelf->S_AXIS_TDATA;
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v0 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v0 
            = (0xfU & (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a));
    }
    if ((1U & ((~ (IData)(vlSelf->AXIS_ARESETN)) | 
               (~ (IData)(vlSelf->top__DOT__matw))))) {
        __Vdly__top__DOT__mat_ctrl__DOT__core_sel = 0U;
        __Vdly__top__DOT__mat_a = 0U;
    } else if (vlSelf->S_AXIS_TVALID) {
        __Vdly__top__DOT__mat_a = (7U & ((IData)(1U) 
                                         + (IData)(vlSelf->top__DOT__mat_a)));
        if ((7U == (IData)(vlSelf->top__DOT__mat_a))) {
            __Vdly__top__DOT__mat_ctrl__DOT__core_sel 
                = (3U & ((IData)(1U) + (IData)(vlSelf->top__DOT__mat_ctrl__DOT__core_sel)));
        }
    }
    if ((1U & (~ ((IData)(vlSelf->top__DOT__src_ctrl__DOT__start) 
                  & ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a) 
                     >> 4U))))) {
        if (((IData)(vlSelf->top__DOT__exec) & ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr) 
                                                >> 5U))) {
            vlSelf->top__DOT__src_buf__DOT__wd1 = vlSelf->top__DOT__src_buf__DOT__buff1
                [(0xfU & ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr) 
                          >> 1U))];
        }
    }
    if ((1U & (~ ((IData)(vlSelf->top__DOT__src_ctrl__DOT__start) 
                  & (~ ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a) 
                        >> 4U)))))) {
        if (((IData)(vlSelf->top__DOT__exec) & (~ ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr) 
                                                   >> 5U)))) {
            vlSelf->top__DOT__src_buf__DOT__wd0 = vlSelf->top__DOT__src_buf__DOT__buff0
                [(0xfU & ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr) 
                          >> 1U))];
        }
    }
    if ((1U & ((~ (IData)(vlSelf->S_AXIS_TREADY)) | 
               (~ (IData)(vlSelf->top__DOT__run))))) {
        __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run = 0U;
        __Vdly__top__DOT__src_ctrl__DOT__i = 0U;
    } else if (((IData)(vlSelf->top__DOT__src_ctrl__DOT__start) 
                | (IData)(vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run))) {
        if (vlSelf->top__DOT__src_ctrl__DOT__last_i) {
            if (vlSelf->top__DOT__src_ctrl__DOT__sen) {
                __Vdly__top__DOT__src_ctrl__DOT__i = 0U;
                __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run = 0U;
            }
        } else {
            if (vlSelf->top__DOT__src_ctrl__DOT__sen) {
                __Vdly__top__DOT__src_ctrl__DOT__i 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelf->top__DOT__src_ctrl__DOT__i)));
            }
            __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run = 1U;
        }
    }
    vlSelf->top__DOT__sum_update = ((IData)(vlSelf->top__DOT__run) 
                                    & (IData)(vlSelf->top__DOT__out_ctrl__DOT__update_after_start));
    if (vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next) {
        __Vdly__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left = 0U;
    } else if (vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next) {
        __Vdly__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left 
            = (vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left 
               + (vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2 
                  * vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2));
    }
    if (vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next) {
        __Vdly__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left = 0U;
    } else if (vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next) {
        __Vdly__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left 
            = (vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left 
               + (vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2 
                  * vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2));
    }
    if (vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next) {
        __Vdly__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left = 0U;
    } else if (vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next) {
        __Vdly__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left 
            = (vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left 
               + (vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2 
                  * vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2));
    }
    if (vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next) {
        __Vdly__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left = 0U;
    } else if (vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next) {
        __Vdly__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left 
            = (vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left 
               + (vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2 
                  * vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2));
    }
    if ((((IData)(vlSelf->top__DOT__out_period) & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr)) 
         & ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr) 
            >> 4U))) {
        __Vdlyvval__top__DOT__dst_buf__DOT__buff3__v0 
            = vlSelf->top__DOT__acc[0U];
        __Vdlyvset__top__DOT__dst_buf__DOT__buff3__v0 = 1U;
        __Vdlyvdim0__top__DOT__dst_buf__DOT__buff3__v0 
            = (7U & ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr) 
                     >> 1U));
    }
    if (((IData)(vlSelf->top__DOT__out_period) & (0x10U 
                                                  == 
                                                  (0x11U 
                                                   & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr))))) {
        __Vdlyvval__top__DOT__dst_buf__DOT__buff2__v0 
            = vlSelf->top__DOT__acc[0U];
        __Vdlyvset__top__DOT__dst_buf__DOT__buff2__v0 = 1U;
        __Vdlyvdim0__top__DOT__dst_buf__DOT__buff2__v0 
            = (7U & ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr) 
                     >> 1U));
    }
    if (((IData)(vlSelf->top__DOT__out_period) & (1U 
                                                  == 
                                                  (0x11U 
                                                   & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr))))) {
        __Vdlyvval__top__DOT__dst_buf__DOT__buff1__v0 
            = vlSelf->top__DOT__acc[0U];
        __Vdlyvset__top__DOT__dst_buf__DOT__buff1__v0 = 1U;
        __Vdlyvdim0__top__DOT__dst_buf__DOT__buff1__v0 
            = (7U & ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr) 
                     >> 1U));
    }
    if (((IData)(vlSelf->top__DOT__out_period) & (0U 
                                                  == 
                                                  (0x11U 
                                                   & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr))))) {
        __Vdlyvval__top__DOT__dst_buf__DOT__buff0__v0 
            = vlSelf->top__DOT__acc[0U];
        __Vdlyvset__top__DOT__dst_buf__DOT__buff0__v0 = 1U;
        __Vdlyvdim0__top__DOT__dst_buf__DOT__buff0__v0 
            = (7U & ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr) 
                     >> 1U));
    }
    if (vlSelf->top__DOT__out_period) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right 
            = vlSelf->top__DOT__acc[4U];
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right 
            = vlSelf->top__DOT__acc[3U];
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right 
            = vlSelf->top__DOT__acc[2U];
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right 
            = vlSelf->top__DOT__acc[1U];
    }
    if ((1U & (~ ((IData)(vlSelf->top__DOT__out_period) 
                  & (0x10U == (0x11U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr))))))) {
        if (((IData)(vlSelf->top__DOT__stream_v) & 
             ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a) 
              >> 3U))) {
            vlSelf->top__DOT__dst_buf__DOT__stream_1 
                = ((0xffffffff00000000ULL & vlSelf->top__DOT__dst_buf__DOT__stream_1) 
                   | (IData)((IData)(vlSelf->top__DOT__dst_buf__DOT__buff2
                                     [(7U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))])));
        }
    }
    if ((1U & (~ (((IData)(vlSelf->top__DOT__out_period) 
                   & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr)) 
                  & ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr) 
                     >> 4U))))) {
        if (((IData)(vlSelf->top__DOT__stream_v) & 
             ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a) 
              >> 3U))) {
            vlSelf->top__DOT__dst_buf__DOT__stream_1 
                = ((0xffffffffULL & vlSelf->top__DOT__dst_buf__DOT__stream_1) 
                   | ((QData)((IData)(vlSelf->top__DOT__dst_buf__DOT__buff3
                                      [(7U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))])) 
                      << 0x20U));
        }
    }
    if ((1U & (~ ((IData)(vlSelf->top__DOT__out_period) 
                  & (0U == (0x11U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr))))))) {
        if (((IData)(vlSelf->top__DOT__stream_v) & 
             (~ ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a) 
                 >> 3U)))) {
            vlSelf->top__DOT__dst_buf__DOT__stream_0 
                = ((0xffffffff00000000ULL & vlSelf->top__DOT__dst_buf__DOT__stream_0) 
                   | (IData)((IData)(vlSelf->top__DOT__dst_buf__DOT__buff0
                                     [(7U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))])));
        }
    }
    if ((1U & (~ ((IData)(vlSelf->top__DOT__out_period) 
                  & (1U == (0x11U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr))))))) {
        if (((IData)(vlSelf->top__DOT__stream_v) & 
             (~ ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a) 
                 >> 3U)))) {
            vlSelf->top__DOT__dst_buf__DOT__stream_0 
                = ((0xffffffffULL & vlSelf->top__DOT__dst_buf__DOT__stream_0) 
                   | ((QData)((IData)(vlSelf->top__DOT__dst_buf__DOT__buff1
                                      [(7U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))])) 
                      << 0x20U));
        }
    }
    vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay = 
        ((IData)(vlSelf->top__DOT__run) & (IData)(vlSelf->top__DOT__s_init));
    vlSelf->top__DOT__mat_a = __Vdly__top__DOT__mat_a;
    vlSelf->top__DOT__mat_ctrl__DOT__core_sel = __Vdly__top__DOT__mat_ctrl__DOT__core_sel;
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v0) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v0] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v0;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v0) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v0] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v0;
    }
    if (vlSelf->top__DOT__run) {
        if (vlSelf->M_AXIS_TREADY) {
            vlSelf->top__DOT__dst_ctrl__DOT__start_check 
                = vlSelf->top__DOT__s_fin_in;
        }
        if (((IData)(vlSelf->top__DOT__out_ctrl__DOT__start) 
             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run))) {
            if (vlSelf->top__DOT__out_ctrl__DOT__last_j) {
                __Vdly__top__DOT__out_ctrl__DOT__j = 0U;
                vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run = 0U;
            } else {
                __Vdly__top__DOT__out_ctrl__DOT__j 
                    = (3U & ((IData)(1U) + (IData)(vlSelf->top__DOT__out_ctrl__DOT__j)));
                vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run = 1U;
            }
        }
        if (((IData)(vlSelf->top__DOT__dst_ctrl__DOT__start) 
             | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run))) {
            if (vlSelf->top__DOT__dst_ctrl__DOT__last_i) {
                if (vlSelf->M_AXIS_TREADY) {
                    __Vdly__top__DOT__dst_ctrl__DOT__i = 0U;
                    vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run = 0U;
                }
            } else {
                if (vlSelf->M_AXIS_TREADY) {
                    __Vdly__top__DOT__dst_ctrl__DOT__i 
                        = (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__dst_ctrl__DOT__i)));
                }
                vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run = 1U;
            }
        }
        vlSelf->top__DOT__dst_ctrl__DOT__i = __Vdly__top__DOT__dst_ctrl__DOT__i;
        vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run 
            = __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run;
        vlSelf->top__DOT__src_ctrl__DOT__i = __Vdly__top__DOT__src_ctrl__DOT__i;
        if (((IData)(vlSelf->top__DOT__src_ctrl__DOT__last_i) 
             & (0U == (IData)(vlSelf->top__DOT__src_en)))) {
            __Vdly__top__DOT__p = (1U & (~ (IData)(vlSelf->top__DOT__p)));
        } else if (vlSelf->top__DOT__s_fin_in) {
            __Vdly__top__DOT__p = (1U & (~ (IData)(vlSelf->top__DOT__p)));
        }
        if (vlSelf->top__DOT__src_ctrl__DOT__last_i) {
            __Vdly__top__DOT__src_en = ((IData)(__Vdly__top__DOT__src_en) 
                                        | (3U & ((IData)(1U) 
                                                 << 
                                                 (1U 
                                                  & (~ (IData)(vlSelf->top__DOT__p))))));
        } else if (((IData)(vlSelf->top__DOT__s_fin_in) 
                    & ((IData)(vlSelf->top__DOT__src_en) 
                       >> (1U & (~ (IData)(vlSelf->top__DOT__p)))))) {
            __Vdly__top__DOT__src_en = ((~ ((IData)(1U) 
                                            << (IData)(vlSelf->top__DOT__p))) 
                                        & (IData)(__Vdly__top__DOT__src_en));
        }
    } else {
        vlSelf->top__DOT__dst_ctrl__DOT__start_check = 0U;
        vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run = 0U;
        __Vdly__top__DOT__out_ctrl__DOT__j = 0U;
        vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run = 0U;
        __Vdly__top__DOT__dst_ctrl__DOT__i = 0U;
        vlSelf->top__DOT__dst_ctrl__DOT__i = __Vdly__top__DOT__dst_ctrl__DOT__i;
        vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run 
            = __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run;
        vlSelf->top__DOT__src_ctrl__DOT__i = __Vdly__top__DOT__src_ctrl__DOT__i;
        __Vdly__top__DOT__p = 1U;
        __Vdly__top__DOT__src_en = 0U;
    }
    vlSelf->top__DOT__p = __Vdly__top__DOT__p;
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left 
        = __Vdly__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left 
        = __Vdly__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left 
        = __Vdly__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left 
        = __Vdly__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
    if (__Vdlyvset__top__DOT__dst_buf__DOT__buff2__v0) {
        vlSelf->top__DOT__dst_buf__DOT__buff2[__Vdlyvdim0__top__DOT__dst_buf__DOT__buff2__v0] 
            = __Vdlyvval__top__DOT__dst_buf__DOT__buff2__v0;
    }
    if (__Vdlyvset__top__DOT__dst_buf__DOT__buff3__v0) {
        vlSelf->top__DOT__dst_buf__DOT__buff3[__Vdlyvdim0__top__DOT__dst_buf__DOT__buff3__v0] 
            = __Vdlyvval__top__DOT__dst_buf__DOT__buff3__v0;
    }
    if (__Vdlyvset__top__DOT__dst_buf__DOT__buff0__v0) {
        vlSelf->top__DOT__dst_buf__DOT__buff0[__Vdlyvdim0__top__DOT__dst_buf__DOT__buff0__v0] 
            = __Vdlyvval__top__DOT__dst_buf__DOT__buff0__v0;
    }
    if (__Vdlyvset__top__DOT__dst_buf__DOT__buff1__v0) {
        vlSelf->top__DOT__dst_buf__DOT__buff1[__Vdlyvdim0__top__DOT__dst_buf__DOT__buff1__v0] 
            = __Vdlyvval__top__DOT__dst_buf__DOT__buff1__v0;
    }
    vlSelf->top__DOT____Vcellinp__src_buf__src_a = 
        ((0x10U & ((~ (IData)(vlSelf->top__DOT__p)) 
                   << 4U)) | (IData)(vlSelf->top__DOT__src_ctrl__DOT__i));
    vlSelf->top__DOT____Vcellinp__dst_buf__stream_a 
        = ((8U & ((~ (IData)(vlSelf->top__DOT__p)) 
                  << 3U)) | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__i));
    if (vlSelf->top__DOT__run) {
        if (vlSelf->M_AXIS_TREADY) {
            vlSelf->M_AXIS_TVALID = vlSelf->top__DOT__dst_ctrl__DOT__stream_active;
        }
        vlSelf->top__DOT__out_addr = vlSelf->top__DOT__out_ctrl__DOT__out_addr_pre;
    } else {
        vlSelf->M_AXIS_TVALID = 0U;
        vlSelf->top__DOT__out_addr = 0U;
    }
    vlSelf->top__DOT____Vcellinp__dst_buf__out_addr 
        = (((IData)(vlSelf->top__DOT__p) << 4U) | (IData)(vlSelf->top__DOT__out_addr));
    vlSelf->top__DOT__out_ctrl__DOT__update_after_start 
        = ((IData)(vlSelf->top__DOT__run) & (IData)(vlSelf->top__DOT__out_ctrl__DOT__start));
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next 
        = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next;
    if (vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2 
            = vlSelf->top__DOT__exec_src_data;
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2 
            = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data;
    } else {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next = 0U;
    }
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next 
        = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next;
    if (vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2 
            = vlSelf->top__DOT__exec_src_data;
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2 
            = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data;
    } else {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next = 0U;
    }
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next 
        = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next;
    if (vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2 
            = vlSelf->top__DOT__exec_src_data;
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2 
            = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data;
    } else {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next = 0U;
    }
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next 
        = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next;
    if (vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2 
            = vlSelf->top__DOT__exec_src_data;
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2 
            = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data;
    } else {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next = 0U;
    }
    if (vlSelf->top__DOT__sum_update) {
        vlSelf->top__DOT__acc[3U] = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
        vlSelf->top__DOT__acc[2U] = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
        vlSelf->top__DOT__acc[1U] = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
        vlSelf->top__DOT__acc[0U] = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
    } else {
        vlSelf->top__DOT__acc[3U] = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right;
        vlSelf->top__DOT__acc[2U] = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right;
        vlSelf->top__DOT__acc[1U] = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right;
        vlSelf->top__DOT__acc[0U] = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right;
    }
    if (vlSelf->top__DOT__run) {
        if ((((IData)(vlSelf->top__DOT__k_fin) & (IData)(vlSelf->top__DOT__out_busy)) 
             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))) {
            vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention 
                = ((IData)(vlSelf->top__DOT__k_fin) 
                   & (IData)(vlSelf->top__DOT__out_busy));
        }
        vlSelf->top__DOT__k_fin = vlSelf->top__DOT__exe_ctrl__DOT__last_j;
        if ((1U & (~ ((IData)(vlSelf->top__DOT__src_ctrl__DOT__last_i) 
                      & (0U == (IData)(vlSelf->top__DOT__src_en)))))) {
            if (vlSelf->top__DOT__s_fin_in) {
                vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo = 0U;
            } else if (vlSelf->top__DOT__s_fin) {
                vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo = 1U;
            }
        }
        if (((IData)(vlSelf->top__DOT__s_init) | (IData)(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run))) {
            if (vlSelf->top__DOT__out_ctrl__DOT__last_i) {
                if (vlSelf->top__DOT__out_ctrl__DOT__last_j) {
                    __Vdly__top__DOT__out_ctrl__DOT__i = 0U;
                    vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run = 0U;
                }
            } else {
                if (vlSelf->top__DOT__out_ctrl__DOT__last_j) {
                    __Vdly__top__DOT__out_ctrl__DOT__i 
                        = (3U & ((IData)(1U) + (IData)(vlSelf->top__DOT__out_ctrl__DOT__i)));
                }
                vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run = 1U;
            }
        }
        if ((1U & ((~ (IData)(vlSelf->top__DOT__out_busy)) 
                   | ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                      | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))))) {
            vlSelf->top__DOT__exe_ctrl__DOT__k_init_next 
                = (((IData)(vlSelf->top__DOT__s_init) 
                    | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre)) 
                   & (~ (IData)(vlSelf->top__DOT__s_init)));
        }
    } else {
        vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention = 0U;
        vlSelf->top__DOT__k_fin = 0U;
        vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo = 0U;
        vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run = 0U;
        __Vdly__top__DOT__out_ctrl__DOT__i = 0U;
        vlSelf->top__DOT__exe_ctrl__DOT__k_init_next = 0U;
    }
    vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre 
        = (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run) 
            | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__start)) 
           & (~ (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j)));
    __Vtableidx1 = (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                     << 5U) | ((0x10U & ((~ (IData)(vlSelf->top__DOT__run)) 
                                         << 4U)) | 
                               (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_i) 
                                 << 3U) | (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j) 
                                            << 2U) 
                                           | (((IData)(vlSelf->top__DOT__s_init) 
                                               << 1U) 
                                              | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run))))));
    vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre 
        = Vtop__ConstPool__TABLE_h1a8234e4_0[__Vtableidx1];
    if ((2U & Vtop__ConstPool__TABLE_h938fc429_0[__Vtableidx1])) {
        vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run 
            = Vtop__ConstPool__TABLE_h853816a4_0[__Vtableidx1];
    }
    if ((4U & Vtop__ConstPool__TABLE_h938fc429_0[__Vtableidx1])) {
        vlSelf->top__DOT__exe_ctrl__DOT__i = Vtop__ConstPool__TABLE_h5acfcdbc_0
            [__Vtableidx1];
    }
    vlSelf->M_AXIS_TDATA = ((8U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))
                             ? vlSelf->top__DOT__dst_buf__DOT__stream_1
                             : vlSelf->top__DOT__dst_buf__DOT__stream_0);
    if (vlSelf->top__DOT__run) {
        if (vlSelf->M_AXIS_TREADY) {
            vlSelf->top__DOT__dst_ctrl__DOT__stream_active 
                = vlSelf->top__DOT__dst_ctrl__DOT__stream_active_pre;
        }
        vlSelf->top__DOT__out_ctrl__DOT__out_addr_pre 
            = (0xfU & (((IData)(vlSelf->top__DOT__out_ctrl__DOT__i) 
                        << 2U) + (IData)(vlSelf->top__DOT__out_ctrl__DOT__j)));
    } else {
        vlSelf->top__DOT__dst_ctrl__DOT__stream_active = 0U;
        vlSelf->top__DOT__out_ctrl__DOT__out_addr_pre = 0U;
    }
    vlSelf->top__DOT__out_ctrl__DOT__i = __Vdly__top__DOT__out_ctrl__DOT__i;
    vlSelf->top__DOT__out_ctrl__DOT__j = __Vdly__top__DOT__out_ctrl__DOT__j;
    vlSelf->top__DOT__exec_src_data = ((2U & (IData)(vlSelf->top__DOT__src_buf__DOT__ia_))
                                        ? ((1U & (IData)(vlSelf->top__DOT__src_buf__DOT__ia_))
                                            ? (IData)(
                                                      (vlSelf->top__DOT__src_buf__DOT__wd1 
                                                       >> 0x20U))
                                            : (IData)(vlSelf->top__DOT__src_buf__DOT__wd1))
                                        : ((1U & (IData)(vlSelf->top__DOT__src_buf__DOT__ia_))
                                            ? (IData)(
                                                      (vlSelf->top__DOT__src_buf__DOT__wd0 
                                                       >> 0x20U))
                                            : (IData)(vlSelf->top__DOT__src_buf__DOT__wd0)));
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next 
        = vlSelf->top__DOT__k_init;
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next 
        = vlSelf->top__DOT__exec;
    if ((1U & (~ ((IData)(vlSelf->top__DOT__mat_v) 
                  >> 3U)))) {
        if (vlSelf->top__DOT__exec) {
            vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data 
                = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix
                [vlSelf->top__DOT__exe_ctrl__DOT__j];
        }
    }
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next 
        = vlSelf->top__DOT__k_init;
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next 
        = vlSelf->top__DOT__exec;
    if ((1U & (~ ((IData)(vlSelf->top__DOT__mat_v) 
                  >> 2U)))) {
        if (vlSelf->top__DOT__exec) {
            vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data 
                = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix
                [vlSelf->top__DOT__exe_ctrl__DOT__j];
        }
    }
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next 
        = vlSelf->top__DOT__k_init;
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next 
        = vlSelf->top__DOT__exec;
    if ((1U & (~ ((IData)(vlSelf->top__DOT__mat_v) 
                  >> 1U)))) {
        if (vlSelf->top__DOT__exec) {
            vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data 
                = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix
                [vlSelf->top__DOT__exe_ctrl__DOT__j];
        }
    }
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next 
        = vlSelf->top__DOT__k_init;
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next 
        = vlSelf->top__DOT__exec;
    if ((1U & (~ (IData)(vlSelf->top__DOT__mat_v)))) {
        if (vlSelf->top__DOT__exec) {
            vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data 
                = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix
                [vlSelf->top__DOT__exe_ctrl__DOT__j];
        }
    }
    if (vlSelf->top__DOT__run) {
        if (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
             | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run))) {
            if (vlSelf->top__DOT__exe_ctrl__DOT__last_j) {
                __Vdly__top__DOT__exe_ctrl__DOT__j = 0U;
                vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run = 0U;
            } else {
                __Vdly__top__DOT__exe_ctrl__DOT__j 
                    = (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j)));
                vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run = 1U;
            }
        }
        vlSelf->top__DOT__exe_ctrl__DOT__start = vlSelf->top__DOT__k_init;
        if ((((IData)(vlSelf->top__DOT__k_init) & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre)) 
             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))) {
            vlSelf->top__DOT__out_busy = ((IData)(vlSelf->top__DOT__k_init) 
                                          & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre));
        }
        vlSelf->top__DOT__out_ctrl__DOT__last_j_next 
            = vlSelf->top__DOT__out_ctrl__DOT__last_j;
    } else {
        vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run = 0U;
        __Vdly__top__DOT__exe_ctrl__DOT__j = 0U;
        vlSelf->top__DOT__exe_ctrl__DOT__start = 0U;
        vlSelf->top__DOT__out_busy = 0U;
        vlSelf->top__DOT__out_ctrl__DOT__last_j_next = 0U;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0;
    }
    vlSelf->top__DOT__exe_ctrl__DOT__j = __Vdly__top__DOT__exe_ctrl__DOT__j;
    vlSelf->top__DOT__k_init = (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay) 
                                 | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__k_init_next)) 
                                & (~ (IData)(vlSelf->top__DOT__out_busy)));
    if (vlSelf->top__DOT__run) {
        if (((IData)(vlSelf->top__DOT__src_ctrl__DOT__last_i) 
             & (0U == (IData)(vlSelf->top__DOT__src_en)))) {
            vlSelf->top__DOT__s_init = 1U;
        } else if (vlSelf->top__DOT__s_fin_in) {
            vlSelf->top__DOT__s_init = (1U & (~ (IData)(vlSelf->top__DOT__last)));
        } else if ((1U & (~ (IData)(vlSelf->top__DOT__s_fin)))) {
            vlSelf->top__DOT__s_init = 0U;
        }
    } else {
        vlSelf->top__DOT__s_init = 0U;
    }
    vlSelf->top__DOT__src_en = __Vdly__top__DOT__src_en;
    vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr 
        = (((IData)(vlSelf->top__DOT__p) << 5U) | (0x1fU 
                                                   & (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                                                       << 3U) 
                                                      + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j))));
    vlSelf->top__DOT__exec = ((IData)(vlSelf->top__DOT__run) 
                              & (IData)(vlSelf->top__DOT__exe_ctrl__DOT____Vcellinp__d_exec__in));
    vlSelf->top__DOT__exe_ctrl__DOT__last_j = ((7U 
                                                == (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j)) 
                                               & ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run) 
                                                  | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__start)));
    vlSelf->S_AXIS_TREADY = (3U != (IData)(vlSelf->top__DOT__src_en));
    vlSelf->top__DOT__s_fin = ((IData)(vlSelf->top__DOT__run) 
                               & ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period) 
                                  & (IData)(vlSelf->top__DOT__out_fin)));
    vlSelf->top__DOT__exe_ctrl__DOT____Vcellinp__d_exec__in 
        = ((IData)(vlSelf->top__DOT__k_init) | ((IData)(vlSelf->top__DOT__exec) 
                                                & (~ (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j))));
    if (vlSelf->top__DOT__run) {
        if (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_i) 
             | (IData)(vlSelf->top__DOT__out_fin))) {
            vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period 
                = vlSelf->top__DOT__exe_ctrl__DOT__last_i;
        }
    } else {
        vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period = 0U;
    }
    vlSelf->top__DOT__exe_ctrl__DOT__last_i = (((3U 
                                                 == (IData)(vlSelf->top__DOT__exe_ctrl__DOT__i)) 
                                                & ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run) 
                                                   | (IData)(vlSelf->top__DOT__s_init))) 
                                               & (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j));
    if (vlSelf->top__DOT__run) {
        vlSelf->top__DOT__out_period = vlSelf->top__DOT__out_ctrl__DOT__out_period_pre;
        vlSelf->top__DOT__out_fin = ((IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre) 
                                     & (~ (IData)(vlSelf->top__DOT__out_ctrl__DOT__j_period)));
        vlSelf->top__DOT__out_ctrl__DOT__out_period_pre 
            = ((IData)(vlSelf->top__DOT__out_ctrl__DOT__j_period) 
               | (IData)(vlSelf->top__DOT__out_ctrl__DOT__start));
        if (((IData)(vlSelf->top__DOT__out_ctrl__DOT__start) 
             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))) {
            vlSelf->top__DOT__out_ctrl__DOT__j_period 
                = vlSelf->top__DOT__out_ctrl__DOT__start;
        }
    } else {
        vlSelf->top__DOT__out_period = 0U;
        vlSelf->top__DOT__out_ctrl__DOT__out_period_pre = 0U;
        vlSelf->top__DOT__out_ctrl__DOT__j_period = 0U;
    }
    vlSelf->top__DOT__out_ctrl__DOT__start = (((IData)(vlSelf->top__DOT__k_fin) 
                                               & (~ (IData)(vlSelf->top__DOT__out_ctrl__DOT__j_period))) 
                                              | ((IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next) 
                                                 & (IData)(vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention)));
    vlSelf->top__DOT__out_ctrl__DOT__last_j = ((3U 
                                                == (IData)(vlSelf->top__DOT__out_ctrl__DOT__j)) 
                                               & ((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run) 
                                                  | (IData)(vlSelf->top__DOT__out_ctrl__DOT__start)));
    vlSelf->top__DOT__out_ctrl__DOT__last_i = (((3U 
                                                 == (IData)(vlSelf->top__DOT__out_ctrl__DOT__i)) 
                                                & ((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run) 
                                                   | (IData)(vlSelf->top__DOT__s_init))) 
                                               & (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j));
}

VL_INLINE_OPT void Vtop___024root___sequent__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__1\n"); );
    // Body
    if ((IData)(((4U == (IData)(vlSelf->top__DOT__state)) 
                 & (0U == (0x300U & (IData)(vlSelf->top__DOT__read_addr)))))) {
        vlSelf->S_AXI_RDATA = 0U;
        if ((0U == (0x3fcU & ((IData)(vlSelf->top__DOT__read_addr) 
                              << 2U)))) {
            vlSelf->S_AXI_RDATA = ((0xfffffff8U & vlSelf->S_AXI_RDATA) 
                                   | (((IData)(vlSelf->top__DOT__last) 
                                       << 2U) | (((IData)(vlSelf->top__DOT__run) 
                                                  << 1U) 
                                                 | (IData)(vlSelf->top__DOT__matw))));
        } else if ((0x10U == (0x3fcU & ((IData)(vlSelf->top__DOT__read_addr) 
                                        << 2U)))) {
            vlSelf->S_AXI_RDATA = vlSelf->top__DOT__control;
        }
    }
    if (vlSelf->S_AXI_ARESETN) {
        if (vlSelf->top__DOT__register_w) {
            if ((0U != (0x3fcU & ((IData)(vlSelf->top__DOT__write_addr) 
                                  << 2U)))) {
                if ((0x10U == (0x3fcU & ((IData)(vlSelf->top__DOT__write_addr) 
                                         << 2U)))) {
                    vlSelf->top__DOT__control = vlSelf->top__DOT__write_data;
                }
            }
            if ((0U == (0x3fcU & ((IData)(vlSelf->top__DOT__write_addr) 
                                  << 2U)))) {
                vlSelf->top__DOT__matw = (1U & vlSelf->top__DOT__write_data);
                vlSelf->top__DOT__last = (1U & (vlSelf->top__DOT__write_data 
                                                >> 2U));
                vlSelf->top__DOT__run = (1U & (vlSelf->top__DOT__write_data 
                                               >> 1U));
            }
        }
        if ((0U == (IData)(vlSelf->top__DOT__state))) {
            if ((1U & (~ ((IData)(vlSelf->S_AXI_AWVALID) 
                          & (IData)(vlSelf->S_AXI_WVALID))))) {
                if ((1U & (~ (IData)(vlSelf->S_AXI_AWVALID)))) {
                    if ((1U & (~ (IData)(vlSelf->S_AXI_WVALID)))) {
                        if (vlSelf->S_AXI_ARVALID) {
                            vlSelf->top__DOT__read_addr 
                                = (0x3ffU & (vlSelf->S_AXI_ARADDR 
                                             >> 2U));
                        }
                    }
                }
            }
            if (((IData)(vlSelf->S_AXI_AWVALID) & (IData)(vlSelf->S_AXI_WVALID))) {
                vlSelf->top__DOT__write_data = vlSelf->S_AXI_WDATA;
                vlSelf->top__DOT__write_addr = (0x3ffU 
                                                & (vlSelf->S_AXI_AWADDR 
                                                   >> 2U));
            } else {
                if ((1U & (~ (IData)(vlSelf->S_AXI_AWVALID)))) {
                    if (vlSelf->S_AXI_WVALID) {
                        vlSelf->top__DOT__write_data 
                            = vlSelf->S_AXI_WDATA;
                    }
                }
                if (vlSelf->S_AXI_AWVALID) {
                    vlSelf->top__DOT__write_addr = 
                        (0x3ffU & (vlSelf->S_AXI_AWADDR 
                                   >> 2U));
                }
            }
        } else {
            if ((1U == (IData)(vlSelf->top__DOT__state))) {
                if (vlSelf->S_AXI_WVALID) {
                    vlSelf->top__DOT__write_data = vlSelf->S_AXI_WDATA;
                }
            }
            if ((1U != (IData)(vlSelf->top__DOT__state))) {
                if ((2U == (IData)(vlSelf->top__DOT__state))) {
                    if (vlSelf->S_AXI_AWVALID) {
                        vlSelf->top__DOT__write_addr 
                            = (0x3ffU & (vlSelf->S_AXI_AWADDR 
                                         >> 2U));
                    }
                }
            }
        }
        if (vlSelf->top__DOT__INI) {
            if (((IData)(vlSelf->S_AXI_AWVALID) & (IData)(vlSelf->S_AXI_WVALID))) {
                vlSelf->top__DOT__state = 3U;
            } else if (vlSelf->S_AXI_AWVALID) {
                vlSelf->top__DOT__state = 1U;
            } else if (vlSelf->S_AXI_WVALID) {
                vlSelf->top__DOT__state = 2U;
            } else if (vlSelf->S_AXI_ARVALID) {
                vlSelf->top__DOT__state = 4U;
            }
        } else if (vlSelf->top__DOT__AW) {
            if (vlSelf->S_AXI_WVALID) {
                vlSelf->top__DOT__state = 3U;
            }
        } else if (vlSelf->top__DOT__W) {
            if (vlSelf->S_AXI_AWVALID) {
                vlSelf->top__DOT__state = 3U;
            }
        } else if (vlSelf->top__DOT__AWW) {
            if (vlSelf->S_AXI_BREADY) {
                vlSelf->top__DOT__state = 0U;
            }
        } else if (vlSelf->top__DOT__AR1) {
            vlSelf->top__DOT__state = 8U;
        } else if (vlSelf->top__DOT__AR2) {
            if (vlSelf->S_AXI_RREADY) {
                vlSelf->top__DOT__state = 0U;
            }
        }
    } else {
        vlSelf->top__DOT__control = 0U;
        vlSelf->top__DOT__matw = 0U;
        vlSelf->top__DOT__last = 0U;
        vlSelf->top__DOT__run = 0U;
        vlSelf->top__DOT__write_data = 0U;
        vlSelf->top__DOT__write_addr = 0U;
        vlSelf->top__DOT__state = 0U;
    }
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
}

VL_INLINE_OPT void Vtop___024root___combo__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___combo__TOP__0\n"); );
    // Body
    vlSelf->top__DOT__dst_ctrl__DOT__start = ((IData)(vlSelf->M_AXIS_TREADY) 
                                              & (IData)(vlSelf->top__DOT__dst_ctrl__DOT__start_check));
    vlSelf->top__DOT__stream_v = ((IData)(vlSelf->top__DOT__dst_ctrl__DOT__stream_active) 
                                  & (IData)(vlSelf->M_AXIS_TREADY));
    vlSelf->top__DOT__src_ctrl__DOT__sen = ((IData)(vlSelf->S_AXIS_TVALID) 
                                            & (IData)(vlSelf->S_AXIS_TREADY));
    vlSelf->top__DOT__mat_v = (((IData)(vlSelf->S_AXIS_TVALID) 
                                & (IData)(vlSelf->top__DOT__matw))
                                ? (0xfU & ((IData)(1U) 
                                           << (IData)(vlSelf->top__DOT__mat_ctrl__DOT__core_sel)))
                                : 0U);
    vlSelf->top__DOT__s_fin_in = ((((IData)(vlSelf->top__DOT__s_fin) 
                                    | (IData)(vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo)) 
                                   & (((IData)(vlSelf->top__DOT__src_en) 
                                       >> (1U & (~ (IData)(vlSelf->top__DOT__p)))) 
                                      | (IData)(vlSelf->top__DOT__last))) 
                                  & (IData)(vlSelf->M_AXIS_TREADY));
    vlSelf->top__DOT__dst_ctrl__DOT__last_i = (((7U 
                                                 == (IData)(vlSelf->top__DOT__dst_ctrl__DOT__i)) 
                                                & ((IData)(vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run) 
                                                   | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__start))) 
                                               & (IData)(vlSelf->M_AXIS_TREADY));
    vlSelf->top__DOT__src_ctrl__DOT__start = (((IData)(vlSelf->top__DOT__src_ctrl__DOT__sen) 
                                               & (IData)(vlSelf->top__DOT__run)) 
                                              & (~ (IData)(vlSelf->top__DOT__matw)));
    vlSelf->top__DOT__dst_ctrl__DOT__stream_active_pre 
        = (((IData)(vlSelf->top__DOT__s_fin_in) | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__stream_active)) 
           & (~ (IData)(vlSelf->top__DOT__dst_ctrl__DOT__last_i)));
    vlSelf->top__DOT__src_ctrl__DOT__last_i = (((0xfU 
                                                 == (IData)(vlSelf->top__DOT__src_ctrl__DOT__i)) 
                                                & ((IData)(vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run) 
                                                   | (IData)(vlSelf->top__DOT__src_ctrl__DOT__start))) 
                                               & (IData)(vlSelf->top__DOT__src_ctrl__DOT__sen));
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->AXIS_ACLK) & (~ (IData)(vlSelf->__Vclklast__TOP__AXIS_ACLK)))) {
        Vtop___024root___sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    if (((IData)(vlSelf->S_AXI_ACLK) & (~ (IData)(vlSelf->__Vclklast__TOP__S_AXI_ACLK)))) {
        Vtop___024root___sequent__TOP__1(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    Vtop___024root___combo__TOP__0(vlSelf);
    vlSelf->__Vm_traceActivity[3U] = 1U;
    // Final
    vlSelf->__Vclklast__TOP__AXIS_ACLK = vlSelf->AXIS_ACLK;
    vlSelf->__Vclklast__TOP__S_AXI_ACLK = vlSelf->S_AXI_ACLK;
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->S_AXI_ACLK & 0xfeU))) {
        Verilated::overWidthError("S_AXI_ACLK");}
    if (VL_UNLIKELY((vlSelf->S_AXI_ARESETN & 0xfeU))) {
        Verilated::overWidthError("S_AXI_ARESETN");}
    if (VL_UNLIKELY((vlSelf->S_AXI_AWVALID & 0xfeU))) {
        Verilated::overWidthError("S_AXI_AWVALID");}
    if (VL_UNLIKELY((vlSelf->S_AXI_WSTRB & 0xf0U))) {
        Verilated::overWidthError("S_AXI_WSTRB");}
    if (VL_UNLIKELY((vlSelf->S_AXI_WVALID & 0xfeU))) {
        Verilated::overWidthError("S_AXI_WVALID");}
    if (VL_UNLIKELY((vlSelf->S_AXI_BREADY & 0xfeU))) {
        Verilated::overWidthError("S_AXI_BREADY");}
    if (VL_UNLIKELY((vlSelf->S_AXI_ARVALID & 0xfeU))) {
        Verilated::overWidthError("S_AXI_ARVALID");}
    if (VL_UNLIKELY((vlSelf->S_AXI_RREADY & 0xfeU))) {
        Verilated::overWidthError("S_AXI_RREADY");}
    if (VL_UNLIKELY((vlSelf->AXIS_ACLK & 0xfeU))) {
        Verilated::overWidthError("AXIS_ACLK");}
    if (VL_UNLIKELY((vlSelf->AXIS_ARESETN & 0xfeU))) {
        Verilated::overWidthError("AXIS_ARESETN");}
    if (VL_UNLIKELY((vlSelf->M_AXIS_TREADY & 0xfeU))) {
        Verilated::overWidthError("M_AXIS_TREADY");}
    if (VL_UNLIKELY((vlSelf->S_AXIS_TLAST & 0xfeU))) {
        Verilated::overWidthError("S_AXIS_TLAST");}
    if (VL_UNLIKELY((vlSelf->S_AXIS_TVALID & 0xfeU))) {
        Verilated::overWidthError("S_AXIS_TVALID");}
}
#endif  // VL_DEBUG
