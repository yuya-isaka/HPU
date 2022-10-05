// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_INLINE_OPT void Vtop___024root___sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__0\n"); );
    // Body
    vlSelf->top__DOT__count = ((IData)(vlSelf->rst)
                                ? 0U : ((0xaU == vlSelf->top__DOT__count)
                                         ? 0U : ((IData)(1U) 
                                                 + vlSelf->top__DOT__count)));
    vlSelf->top__DOT__sysclk = (5U >= vlSelf->top__DOT__count);
}

extern const VlUnpacked<CData/*5:0*/, 64> Vtop__ConstPool__TABLE_h0c9d45d8_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vtop__ConstPool__TABLE_hf81d59db_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vtop__ConstPool__TABLE_hb9b05b2c_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vtop__ConstPool__TABLE_h5b03ed05_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vtop__ConstPool__TABLE_h2f9c8a38_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vtop__ConstPool__TABLE_h6d321f39_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vtop__ConstPool__TABLE_hb15f4d25_0;

VL_INLINE_OPT void Vtop___024root___sequent__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__1\n"); );
    // Init
    CData/*5:0*/ __Vtableidx1;
    CData/*4:0*/ __Vdlyvdim0__top__DOT__Core__DOT__register__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__Core__DOT__register__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__Core__DOT__register__v0;
    IData/*31:0*/ __Vdly__top__DOT__Core__DOT__pc;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__Core__DOT__Dmem__DOT__mem__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__Core__DOT__Dmem__DOT__mem__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__Core__DOT__Dmem__DOT__mem__v0;
    VlWide<3>/*95:0*/ __Vtemp_h1837cfa2__0;
    // Body
    __Vdlyvset__top__DOT__Core__DOT__Dmem__DOT__mem__v0 = 0U;
    __Vdlyvset__top__DOT__Core__DOT__register__v0 = 0U;
    __Vdly__top__DOT__Core__DOT__pc = vlSelf->top__DOT__Core__DOT__pc;
    if (vlSelf->rst) {
        vlSelf->top__DOT__Core__DOT__register[0U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[1U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[2U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[3U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[4U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[5U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[6U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[7U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[8U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[9U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0xaU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0xbU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0xcU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0xdU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0xeU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0xfU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x10U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x11U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x12U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x13U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x14U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x15U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x16U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x17U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x18U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x19U] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x1aU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x1bU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x1cU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x1dU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x1eU] = 0U;
        vlSelf->top__DOT__Core__DOT__register[0x1fU] = 0U;
        vlSelf->top__DOT__Seven__DOT__seg_counter = 0U;
        __Vdly__top__DOT__Core__DOT__pc = 0U;
    } else {
        vlSelf->top__DOT__Seven__DOT__seg_counter = 
            ((0x61a80U == vlSelf->top__DOT__Seven__DOT__seg_counter)
              ? 0U : ((IData)(1U) + vlSelf->top__DOT__Seven__DOT__seg_counter));
        if (vlSelf->top__DOT__Core__DOT__state_wb) {
            __Vdly__top__DOT__Core__DOT__pc = ((0x10U 
                                                & vlSelf->top__DOT__Core__DOT__de[0U])
                                                ? (
                                                   (0U 
                                                    != vlSelf->top__DOT__Core__DOT__alu_out)
                                                    ? 
                                                   (vlSelf->top__DOT__Core__DOT__pc 
                                                    + 
                                                    ((vlSelf->top__DOT__Core__DOT__de[1U] 
                                                      << 0x17U) 
                                                     | (vlSelf->top__DOT__Core__DOT__de[0U] 
                                                        >> 9U)))
                                                    : 
                                                   ((IData)(4U) 
                                                    + vlSelf->top__DOT__Core__DOT__pc))
                                                : (
                                                   (8U 
                                                    & vlSelf->top__DOT__Core__DOT__de[0U])
                                                    ? 
                                                   (vlSelf->top__DOT__Core__DOT__pc 
                                                    + 
                                                    ((vlSelf->top__DOT__Core__DOT__de[1U] 
                                                      << 0x17U) 
                                                     | (vlSelf->top__DOT__Core__DOT__de[0U] 
                                                        >> 9U)))
                                                    : 
                                                   ((4U 
                                                     & vlSelf->top__DOT__Core__DOT__de[0U])
                                                     ? 
                                                    (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                     + 
                                                     ((vlSelf->top__DOT__Core__DOT__de[1U] 
                                                       << 0x17U) 
                                                      | (vlSelf->top__DOT__Core__DOT__de[0U] 
                                                         >> 9U)))
                                                     : 
                                                    ((2U 
                                                      & vlSelf->top__DOT__Core__DOT__de[0U])
                                                      ? 
                                                     ((IData)(4U) 
                                                      + vlSelf->top__DOT__Core__DOT__pc)
                                                      : 
                                                     ((1U 
                                                       & vlSelf->top__DOT__Core__DOT__de[0U])
                                                       ? 
                                                      ((IData)(4U) 
                                                       + vlSelf->top__DOT__Core__DOT__pc)
                                                       : 
                                                      ((IData)(4U) 
                                                       + vlSelf->top__DOT__Core__DOT__pc))))));
        }
    }
    if ((1U & vlSelf->top__DOT__Core__DOT__dmem[0U])) {
        __Vdlyvval__top__DOT__Core__DOT__Dmem__DOT__mem__v0 
            = ((vlSelf->top__DOT__Core__DOT__dmem[1U] 
                << 0x1fU) | (vlSelf->top__DOT__Core__DOT__dmem[0U] 
                             >> 1U));
        __Vdlyvset__top__DOT__Core__DOT__Dmem__DOT__mem__v0 = 1U;
        __Vdlyvdim0__top__DOT__Core__DOT__Dmem__DOT__mem__v0 
            = (0x1ffU & (vlSelf->top__DOT__Core__DOT__dmem[1U] 
                         >> 3U));
    }
    vlSelf->top__DOT__Core__DOT____Vcellout__Dmem__read_data 
        = vlSelf->top__DOT__Core__DOT__Dmem__DOT__mem
        [(0x1ffU & (vlSelf->top__DOT__Core__DOT__dmem[3U] 
                    >> 3U))];
    vlSelf->top__DOT__Core__DOT____Vcellout__Imem__inst 
        = vlSelf->top__DOT__Core__DOT__Imem__DOT__mem
        [(0x3fU & (IData)((vlSelf->top__DOT__Core__DOT__imem 
                           >> 0x22U)))];
    if ((1U & (~ (IData)(vlSelf->rst)))) {
        if (vlSelf->top__DOT__Core__DOT__state_wb) {
            __Vdlyvval__top__DOT__Core__DOT__register__v0 
                = ((IData)((0U != (0xcU & vlSelf->top__DOT__Core__DOT__de[0U])))
                    ? ((IData)(4U) + vlSelf->top__DOT__Core__DOT__pc)
                    : ((0x40U & vlSelf->top__DOT__Core__DOT__de[0U])
                        ? ((vlSelf->top__DOT__Core__DOT__dmem[3U] 
                            << 0x1fU) | (vlSelf->top__DOT__Core__DOT__dmem[2U] 
                                         >> 1U)) : 
                       ((2U & vlSelf->top__DOT__Core__DOT__de[0U])
                         ? ((vlSelf->top__DOT__Core__DOT__de[1U] 
                             << 0x17U) | (vlSelf->top__DOT__Core__DOT__de[0U] 
                                          >> 9U)) : 
                        ((1U & vlSelf->top__DOT__Core__DOT__de[0U])
                          ? (vlSelf->top__DOT__Core__DOT__pc 
                             + ((vlSelf->top__DOT__Core__DOT__de[1U] 
                                 << 0x17U) | (vlSelf->top__DOT__Core__DOT__de[0U] 
                                              >> 9U)))
                          : vlSelf->top__DOT__Core__DOT__alu_out))));
            __Vdlyvset__top__DOT__Core__DOT__register__v0 = 1U;
            __Vdlyvdim0__top__DOT__Core__DOT__register__v0 
                = (0x1fU & (vlSelf->top__DOT__Core__DOT__de[1U] 
                            >> 0x13U));
        }
    }
    if (__Vdlyvset__top__DOT__Core__DOT__Dmem__DOT__mem__v0) {
        vlSelf->top__DOT__Core__DOT__Dmem__DOT__mem[__Vdlyvdim0__top__DOT__Core__DOT__Dmem__DOT__mem__v0] 
            = __Vdlyvval__top__DOT__Core__DOT__Dmem__DOT__mem__v0;
    }
    if (__Vdlyvset__top__DOT__Core__DOT__register__v0) {
        vlSelf->top__DOT__Core__DOT__register[__Vdlyvdim0__top__DOT__Core__DOT__register__v0] 
            = __Vdlyvval__top__DOT__Core__DOT__register__v0;
    }
    vlSelf->top__DOT__Core__DOT__pc = __Vdly__top__DOT__Core__DOT__pc;
    vlSelf->top__DOT__Core__DOT__dmem[2U] = ((1U & 
                                              vlSelf->top__DOT__Core__DOT__dmem[2U]) 
                                             | (vlSelf->top__DOT__Core__DOT____Vcellout__Dmem__read_data 
                                                << 1U));
    vlSelf->top__DOT__Core__DOT__dmem[3U] = ((0xfffffffeU 
                                              & vlSelf->top__DOT__Core__DOT__dmem[3U]) 
                                             | (vlSelf->top__DOT__Core__DOT____Vcellout__Dmem__read_data 
                                                >> 0x1fU));
    if ((0x186a0U > vlSelf->top__DOT__Seven__DOT__seg_counter)) {
        vlSelf->anode = 0xeU;
        vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary 
            = VL_MODDIV_III(32, vlSelf->top__DOT__Core__DOT__register
                            [0xaU], (IData)(0xaU));
        vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__Vfuncout 
            = ((8U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                ? ((4U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                    ? ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                            ? 0xeU : 6U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                                             ? 0x21U
                                             : 0x46U))
                    : ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                            ? 3U : 8U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                                           ? 0x10U : 0U)))
                : ((4U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                    ? ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                            ? 0x58U : 2U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                                              ? 0x12U
                                              : 0x19U))
                    : ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                            ? 0x30U : 0x24U) : ((1U 
                                                 & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__binary)
                                                 ? 0x79U
                                                 : 0x40U))));
        vlSelf->seg = vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__3__Vfuncout;
    } else if ((0x30d40U > vlSelf->top__DOT__Seven__DOT__seg_counter)) {
        vlSelf->anode = 0xdU;
        vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary 
            = VL_MODDIV_III(32, VL_DIV_III(32, vlSelf->top__DOT__Core__DOT__register
                                           [0xaU], (IData)(0xaU)), (IData)(0xaU));
        vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__Vfuncout 
            = ((8U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                ? ((4U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                    ? ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                            ? 0xeU : 6U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                                             ? 0x21U
                                             : 0x46U))
                    : ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                            ? 3U : 8U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                                           ? 0x10U : 0U)))
                : ((4U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                    ? ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                            ? 0x58U : 2U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                                              ? 0x12U
                                              : 0x19U))
                    : ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                            ? 0x30U : 0x24U) : ((1U 
                                                 & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__binary)
                                                 ? 0x79U
                                                 : 0x40U))));
        vlSelf->seg = vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__4__Vfuncout;
    } else if ((0x493e0U > vlSelf->top__DOT__Seven__DOT__seg_counter)) {
        vlSelf->anode = 0xbU;
        vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary 
            = VL_MODDIV_III(32, VL_DIV_III(32, vlSelf->top__DOT__Core__DOT__register
                                           [0xaU], (IData)(0x64U)), (IData)(0xaU));
        vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__Vfuncout 
            = ((8U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                ? ((4U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                    ? ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                            ? 0xeU : 6U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                                             ? 0x21U
                                             : 0x46U))
                    : ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                            ? 3U : 8U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                                           ? 0x10U : 0U)))
                : ((4U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                    ? ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                            ? 0x58U : 2U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                                              ? 0x12U
                                              : 0x19U))
                    : ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                            ? 0x30U : 0x24U) : ((1U 
                                                 & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__binary)
                                                 ? 0x79U
                                                 : 0x40U))));
        vlSelf->seg = vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__5__Vfuncout;
    } else {
        vlSelf->anode = 7U;
        vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary 
            = VL_MODDIV_III(32, VL_DIV_III(32, vlSelf->top__DOT__Core__DOT__register
                                           [0xaU], (IData)(0x3e8U)), (IData)(0xaU));
        vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__Vfuncout 
            = ((8U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                ? ((4U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                    ? ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                            ? 0xeU : 6U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                                             ? 0x21U
                                             : 0x46U))
                    : ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                            ? 3U : 8U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                                           ? 0x10U : 0U)))
                : ((4U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                    ? ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                            ? 0x58U : 2U) : ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                                              ? 0x12U
                                              : 0x19U))
                    : ((2U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                        ? ((1U & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                            ? 0x30U : 0x24U) : ((1U 
                                                 & vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__binary)
                                                 ? 0x79U
                                                 : 0x40U))));
        vlSelf->seg = vlSelf->__Vfunc_top__DOT__Seven__DOT__decode__6__Vfuncout;
    }
    vlSelf->led = (0xffffU & vlSelf->top__DOT__Core__DOT__register
                   [0xaU]);
    vlSelf->top__DOT__Core__DOT__imem = (((QData)((IData)(vlSelf->top__DOT__Core__DOT__pc)) 
                                          << 0x20U) 
                                         | (QData)((IData)(vlSelf->top__DOT__Core__DOT____Vcellout__Imem__inst)));
    __Vtableidx1 = (((IData)(vlSelf->top__DOT__Core__DOT__state_ma) 
                     << 5U) | (((IData)(vlSelf->top__DOT__Core__DOT__state_ex) 
                                << 4U) | (((IData)(vlSelf->top__DOT__Core__DOT__state_de) 
                                           << 3U) | 
                                          (((IData)(vlSelf->top__DOT__Core__DOT__state_if) 
                                            << 2U) 
                                           | (((IData)(vlSelf->top__DOT__Core__DOT__state_idle) 
                                               << 1U) 
                                              | (IData)(vlSelf->rst))))));
    if ((1U & Vtop__ConstPool__TABLE_h0c9d45d8_0[__Vtableidx1])) {
        vlSelf->top__DOT__Core__DOT__state_idle = Vtop__ConstPool__TABLE_hf81d59db_0
            [__Vtableidx1];
    }
    if ((2U & Vtop__ConstPool__TABLE_h0c9d45d8_0[__Vtableidx1])) {
        vlSelf->top__DOT__Core__DOT__state_if = Vtop__ConstPool__TABLE_hb9b05b2c_0
            [__Vtableidx1];
    }
    if ((4U & Vtop__ConstPool__TABLE_h0c9d45d8_0[__Vtableidx1])) {
        vlSelf->top__DOT__Core__DOT__state_de = Vtop__ConstPool__TABLE_h5b03ed05_0
            [__Vtableidx1];
    }
    if ((8U & Vtop__ConstPool__TABLE_h0c9d45d8_0[__Vtableidx1])) {
        vlSelf->top__DOT__Core__DOT__state_ex = Vtop__ConstPool__TABLE_h2f9c8a38_0
            [__Vtableidx1];
    }
    if ((0x10U & Vtop__ConstPool__TABLE_h0c9d45d8_0
         [__Vtableidx1])) {
        vlSelf->top__DOT__Core__DOT__state_ma = Vtop__ConstPool__TABLE_h6d321f39_0
            [__Vtableidx1];
    }
    if ((0x20U & Vtop__ConstPool__TABLE_h0c9d45d8_0
         [__Vtableidx1])) {
        vlSelf->top__DOT__Core__DOT__state_wb = Vtop__ConstPool__TABLE_hb15f4d25_0
            [__Vtableidx1];
    }
    vlSelf->top__DOT__Core__DOT__de[0U] = ((0xfffffff0U 
                                            & vlSelf->top__DOT__Core__DOT__de[0U]) 
                                           | (((0x6fU 
                                                == 
                                                (0x7fU 
                                                 & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                               << 3U) 
                                              | (((0x67U 
                                                   == 
                                                   (0x7fU 
                                                    & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                  << 2U) 
                                                 | (((0x37U 
                                                      == 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                     << 1U) 
                                                    | (0x17U 
                                                       == 
                                                       (0x7fU 
                                                        & (IData)(vlSelf->top__DOT__Core__DOT__imem)))))));
    vlSelf->top__DOT__Core__DOT__de[0U] = ((0xffffff0fU 
                                            & vlSelf->top__DOT__Core__DOT__de[0U]) 
                                           | (0xfffffff0U 
                                              & (((0x13U 
                                                   == 
                                                   (0x7fU 
                                                    & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                  << 7U) 
                                                 | (((3U 
                                                      == 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                     << 6U) 
                                                    | (((0x23U 
                                                         == 
                                                         (0x7fU 
                                                          & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                        << 5U) 
                                                       | ((0x63U 
                                                           == 
                                                           (0x7fU 
                                                            & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                          << 4U))))));
    vlSelf->top__DOT__Core__DOT__Decode__DOT__i_type 
        = (((3U == (0x7fU & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
            | (0x13U == (0x7fU & (IData)(vlSelf->top__DOT__Core__DOT__imem)))) 
           | (0x67U == (0x7fU & (IData)(vlSelf->top__DOT__Core__DOT__imem))));
    vlSelf->top__DOT__Core__DOT__Decode__DOT__u_type 
        = ((0x37U == (0x7fU & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
           | (0x17U == (0x7fU & (IData)(vlSelf->top__DOT__Core__DOT__imem))));
    vlSelf->top__DOT__Core__DOT__de[1U] = ((0x7ffffU 
                                            & vlSelf->top__DOT__Core__DOT__de[1U]) 
                                           | (0xfff80000U 
                                              & (((((((0x33U 
                                                       == 
                                                       (0x7fU 
                                                        & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                      | (IData)(vlSelf->top__DOT__Core__DOT__Decode__DOT__i_type)) 
                                                     | (0x23U 
                                                        == 
                                                        (0x7fU 
                                                         & (IData)(vlSelf->top__DOT__Core__DOT__imem)))) 
                                                    | (0x63U 
                                                       == 
                                                       (0x7fU 
                                                        & (IData)(vlSelf->top__DOT__Core__DOT__imem))))
                                                    ? 
                                                   (0x1fU 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__Core__DOT__imem 
                                                               >> 0xfU)))
                                                    : 0U) 
                                                  << 0x1dU) 
                                                 | ((((((0x33U 
                                                         == 
                                                         (0x7fU 
                                                          & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                        | (0x23U 
                                                           == 
                                                           (0x7fU 
                                                            & (IData)(vlSelf->top__DOT__Core__DOT__imem)))) 
                                                       | (0x63U 
                                                          == 
                                                          (0x7fU 
                                                           & (IData)(vlSelf->top__DOT__Core__DOT__imem))))
                                                       ? 
                                                      (0x1fU 
                                                       & (IData)(
                                                                 (vlSelf->top__DOT__Core__DOT__imem 
                                                                  >> 0x14U)))
                                                       : 0U) 
                                                     << 0x18U) 
                                                    | ((((((0x33U 
                                                            == 
                                                            (0x7fU 
                                                             & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                           | (IData)(vlSelf->top__DOT__Core__DOT__Decode__DOT__i_type)) 
                                                          | (0x6fU 
                                                             == 
                                                             (0x7fU 
                                                              & (IData)(vlSelf->top__DOT__Core__DOT__imem)))) 
                                                         | (IData)(vlSelf->top__DOT__Core__DOT__Decode__DOT__u_type))
                                                         ? 
                                                        (0x1fU 
                                                         & (IData)(
                                                                   (vlSelf->top__DOT__Core__DOT__imem 
                                                                    >> 7U)))
                                                         : 0U) 
                                                       << 0x13U)))));
    vlSelf->top__DOT__Core__DOT__de[2U] = (3U & ((0x7ffffU 
                                                  & ((((((0x33U 
                                                          == 
                                                          (0x7fU 
                                                           & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                         | (IData)(vlSelf->top__DOT__Core__DOT__Decode__DOT__i_type)) 
                                                        | (0x23U 
                                                           == 
                                                           (0x7fU 
                                                            & (IData)(vlSelf->top__DOT__Core__DOT__imem)))) 
                                                       | (0x63U 
                                                          == 
                                                          (0x7fU 
                                                           & (IData)(vlSelf->top__DOT__Core__DOT__imem))))
                                                       ? 
                                                      (0x1fU 
                                                       & (IData)(
                                                                 (vlSelf->top__DOT__Core__DOT__imem 
                                                                  >> 0xfU)))
                                                       : 0U) 
                                                     >> 3U)) 
                                                 | ((0x7ffffU 
                                                     & (((((0x33U 
                                                            == 
                                                            (0x7fU 
                                                             & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                           | (0x23U 
                                                              == 
                                                              (0x7fU 
                                                               & (IData)(vlSelf->top__DOT__Core__DOT__imem)))) 
                                                          | (0x63U 
                                                             == 
                                                             (0x7fU 
                                                              & (IData)(vlSelf->top__DOT__Core__DOT__imem))))
                                                          ? 
                                                         (0x1fU 
                                                          & (IData)(
                                                                    (vlSelf->top__DOT__Core__DOT__imem 
                                                                     >> 0x14U)))
                                                          : 0U) 
                                                        >> 8U)) 
                                                    | ((((((0x33U 
                                                            == 
                                                            (0x7fU 
                                                             & (IData)(vlSelf->top__DOT__Core__DOT__imem))) 
                                                           | (IData)(vlSelf->top__DOT__Core__DOT__Decode__DOT__i_type)) 
                                                          | (0x6fU 
                                                             == 
                                                             (0x7fU 
                                                              & (IData)(vlSelf->top__DOT__Core__DOT__imem)))) 
                                                         | (IData)(vlSelf->top__DOT__Core__DOT__Decode__DOT__u_type))
                                                         ? 
                                                        (0x1fU 
                                                         & (IData)(
                                                                   (vlSelf->top__DOT__Core__DOT__imem 
                                                                    >> 7U)))
                                                         : 0U) 
                                                       >> 0xdU))));
    vlSelf->top__DOT__Core__DOT____Vcellout__Decode__imm 
        = ((IData)(vlSelf->top__DOT__Core__DOT__Decode__DOT__i_type)
            ? (((- (IData)((1U & (IData)((vlSelf->top__DOT__Core__DOT__imem 
                                          >> 0x1fU))))) 
                << 0xcU) | (0xfffU & (IData)((vlSelf->top__DOT__Core__DOT__imem 
                                              >> 0x14U))))
            : ((0x23U == (0x7fU & (IData)(vlSelf->top__DOT__Core__DOT__imem)))
                ? (((- (IData)((1U & (IData)((vlSelf->top__DOT__Core__DOT__imem 
                                              >> 0x1fU))))) 
                    << 0xcU) | ((0xfe0U & ((IData)(
                                                   (vlSelf->top__DOT__Core__DOT__imem 
                                                    >> 0x19U)) 
                                           << 5U)) 
                                | (0x1fU & (IData)(
                                                   (vlSelf->top__DOT__Core__DOT__imem 
                                                    >> 7U)))))
                : ((0x63U == (0x7fU & (IData)(vlSelf->top__DOT__Core__DOT__imem)))
                    ? (((- (IData)((1U & (IData)((vlSelf->top__DOT__Core__DOT__imem 
                                                  >> 0x1fU))))) 
                        << 0xcU) | ((0x800U & ((IData)(
                                                       (vlSelf->top__DOT__Core__DOT__imem 
                                                        >> 7U)) 
                                               << 0xbU)) 
                                    | ((0x7e0U & ((IData)(
                                                          (vlSelf->top__DOT__Core__DOT__imem 
                                                           >> 0x19U)) 
                                                  << 5U)) 
                                       | (0x1eU & ((IData)(
                                                           (vlSelf->top__DOT__Core__DOT__imem 
                                                            >> 8U)) 
                                                   << 1U)))))
                    : ((0x6fU == (0x7fU & (IData)(vlSelf->top__DOT__Core__DOT__imem)))
                        ? (((- (IData)((1U & (IData)(
                                                     (vlSelf->top__DOT__Core__DOT__imem 
                                                      >> 0x1fU))))) 
                            << 0x14U) | ((0xff000U 
                                          & ((IData)(
                                                     (vlSelf->top__DOT__Core__DOT__imem 
                                                      >> 0xcU)) 
                                             << 0xcU)) 
                                         | ((0x800U 
                                             & ((IData)(
                                                        (vlSelf->top__DOT__Core__DOT__imem 
                                                         >> 0x14U)) 
                                                << 0xbU)) 
                                            | (0x7feU 
                                               & ((IData)(
                                                          (vlSelf->top__DOT__Core__DOT__imem 
                                                           >> 0x15U)) 
                                                  << 1U)))))
                        : ((IData)(vlSelf->top__DOT__Core__DOT__Decode__DOT__u_type)
                            ? ((IData)((vlSelf->top__DOT__Core__DOT__imem 
                                        >> 0xcU)) << 0xcU)
                            : 0U)))));
    vlSelf->top__DOT__Core__DOT__de[0U] = ((0xffU & 
                                            vlSelf->top__DOT__Core__DOT__de[0U]) 
                                           | ((IData)(
                                                      (((QData)((IData)(
                                                                        (7U 
                                                                         & (IData)(
                                                                                (vlSelf->top__DOT__Core__DOT__imem 
                                                                                >> 0xcU))))) 
                                                        << 0x28U) 
                                                       | (((QData)((IData)(
                                                                           ((0x1bU 
                                                                             == 
                                                                             (0x7fU 
                                                                              & (IData)(vlSelf->top__DOT__Core__DOT__imem)))
                                                                             ? 
                                                                            (0x7fU 
                                                                             & (IData)(
                                                                                (vlSelf->top__DOT__Core__DOT__imem 
                                                                                >> 0x19U)))
                                                                             : 0U))) 
                                                           << 0x21U) 
                                                          | (((QData)((IData)(vlSelf->top__DOT__Core__DOT____Vcellout__Decode__imm)) 
                                                              << 1U) 
                                                             | (QData)((IData)(
                                                                               (0x33U 
                                                                                == 
                                                                                (0x7fU 
                                                                                & (IData)(vlSelf->top__DOT__Core__DOT__imem))))))))) 
                                              << 8U));
    vlSelf->top__DOT__Core__DOT__de[1U] = ((0xfff80000U 
                                            & vlSelf->top__DOT__Core__DOT__de[1U]) 
                                           | (((IData)(
                                                       (((QData)((IData)(
                                                                         (7U 
                                                                          & (IData)(
                                                                                (vlSelf->top__DOT__Core__DOT__imem 
                                                                                >> 0xcU))))) 
                                                         << 0x28U) 
                                                        | (((QData)((IData)(
                                                                            ((0x1bU 
                                                                              == 
                                                                              (0x7fU 
                                                                               & (IData)(vlSelf->top__DOT__Core__DOT__imem)))
                                                                              ? 
                                                                             (0x7fU 
                                                                              & (IData)(
                                                                                (vlSelf->top__DOT__Core__DOT__imem 
                                                                                >> 0x19U)))
                                                                              : 0U))) 
                                                            << 0x21U) 
                                                           | (((QData)((IData)(vlSelf->top__DOT__Core__DOT____Vcellout__Decode__imm)) 
                                                               << 1U) 
                                                              | (QData)((IData)(
                                                                                (0x33U 
                                                                                == 
                                                                                (0x7fU 
                                                                                & (IData)(vlSelf->top__DOT__Core__DOT__imem))))))))) 
                                               >> 0x18U) 
                                              | ((IData)(
                                                         ((((QData)((IData)(
                                                                            (7U 
                                                                             & (IData)(
                                                                                (vlSelf->top__DOT__Core__DOT__imem 
                                                                                >> 0xcU))))) 
                                                            << 0x28U) 
                                                           | (((QData)((IData)(
                                                                               ((0x1bU 
                                                                                == 
                                                                                (0x7fU 
                                                                                & (IData)(vlSelf->top__DOT__Core__DOT__imem)))
                                                                                 ? 
                                                                                (0x7fU 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__Core__DOT__imem 
                                                                                >> 0x19U)))
                                                                                 : 0U))) 
                                                               << 0x21U) 
                                                              | (((QData)((IData)(vlSelf->top__DOT__Core__DOT____Vcellout__Decode__imm)) 
                                                                  << 1U) 
                                                                 | (QData)((IData)(
                                                                                (0x33U 
                                                                                == 
                                                                                (0x7fU 
                                                                                & (IData)(vlSelf->top__DOT__Core__DOT__imem)))))))) 
                                                          >> 0x20U)) 
                                                 << 8U)));
    vlSelf->top__DOT__Core__DOT__rs1_data = ((0U == 
                                              (0x1fU 
                                               & ((vlSelf->top__DOT__Core__DOT__de[2U] 
                                                   << 3U) 
                                                  | (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                     >> 0x1dU))))
                                              ? 0U : 
                                             vlSelf->top__DOT__Core__DOT__register
                                             [(0x1fU 
                                               & ((vlSelf->top__DOT__Core__DOT__de[2U] 
                                                   << 3U) 
                                                  | (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                     >> 0x1dU)))]);
    vlSelf->top__DOT__Core__DOT__rs2_data = ((0U == 
                                              (0x1fU 
                                               & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                  >> 0x18U)))
                                              ? 0U : 
                                             vlSelf->top__DOT__Core__DOT__register
                                             [(0x1fU 
                                               & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                  >> 0x18U))]);
    vlSelf->top__DOT__Core__DOT__Alu__DOT__op2 = ((IData)(
                                                          (0U 
                                                           != 
                                                           (0xe0U 
                                                            & vlSelf->top__DOT__Core__DOT__de[0U])))
                                                   ? 
                                                  ((vlSelf->top__DOT__Core__DOT__de[1U] 
                                                    << 0x17U) 
                                                   | (vlSelf->top__DOT__Core__DOT__de[0U] 
                                                      >> 9U))
                                                   : vlSelf->top__DOT__Core__DOT__rs2_data);
    vlSelf->top__DOT__Core__DOT__alu_out = ((IData)(
                                                    (0U 
                                                     != 
                                                     (0x60U 
                                                      & vlSelf->top__DOT__Core__DOT__de[0U])))
                                             ? (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                + vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                             : ((IData)(
                                                        (0U 
                                                         != 
                                                         (0x180U 
                                                          & vlSelf->top__DOT__Core__DOT__de[0U])))
                                                 ? 
                                                (((((((((0U 
                                                         == 
                                                         ((0x3f8U 
                                                           & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                              >> 6U)) 
                                                          | (7U 
                                                             & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                >> 0x10U)))) 
                                                        | (0x100U 
                                                           == 
                                                           ((0x3f8U 
                                                             & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                >> 6U)) 
                                                            | (7U 
                                                               & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                  >> 0x10U))))) 
                                                       | (6U 
                                                          == 
                                                          ((0x3f8U 
                                                            & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                               >> 6U)) 
                                                           | (7U 
                                                              & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                 >> 0x10U))))) 
                                                      | (7U 
                                                         == 
                                                         ((0x3f8U 
                                                           & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                              >> 6U)) 
                                                          | (7U 
                                                             & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                >> 0x10U))))) 
                                                     | (4U 
                                                        == 
                                                        ((0x3f8U 
                                                          & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                             >> 6U)) 
                                                         | (7U 
                                                            & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                               >> 0x10U))))) 
                                                    | (1U 
                                                       == 
                                                       ((0x3f8U 
                                                         & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                            >> 6U)) 
                                                        | (7U 
                                                           & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                              >> 0x10U))))) 
                                                   | (2U 
                                                      == 
                                                      ((0x3f8U 
                                                        & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                           >> 6U)) 
                                                       | (7U 
                                                          & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                             >> 0x10U))))) 
                                                  | (3U 
                                                     == 
                                                     ((0x3f8U 
                                                       & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                          >> 6U)) 
                                                      | (7U 
                                                         & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                            >> 0x10U)))))
                                                  ? 
                                                 ((0U 
                                                   == 
                                                   ((0x3f8U 
                                                     & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                        >> 6U)) 
                                                    | (7U 
                                                       & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                          >> 0x10U))))
                                                   ? 
                                                  (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                   + vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                   : 
                                                  ((0x100U 
                                                    == 
                                                    ((0x3f8U 
                                                      & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                         >> 6U)) 
                                                     | (7U 
                                                        & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                           >> 0x10U))))
                                                    ? 
                                                   (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                    - vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                    : 
                                                   ((6U 
                                                     == 
                                                     ((0x3f8U 
                                                       & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                          >> 6U)) 
                                                      | (7U 
                                                         & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                            >> 0x10U))))
                                                     ? 
                                                    (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                     | vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                     : 
                                                    ((7U 
                                                      == 
                                                      ((0x3f8U 
                                                        & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                           >> 6U)) 
                                                       | (7U 
                                                          & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                             >> 0x10U))))
                                                      ? 
                                                     (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                      & vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                      : 
                                                     ((4U 
                                                       == 
                                                       ((0x3f8U 
                                                         & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                            >> 6U)) 
                                                        | (7U 
                                                           & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                              >> 0x10U))))
                                                       ? 
                                                      (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                       ^ vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                       : 
                                                      ((1U 
                                                        == 
                                                        ((0x3f8U 
                                                          & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                             >> 6U)) 
                                                         | (7U 
                                                            & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                               >> 0x10U))))
                                                        ? 
                                                       (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                        << 
                                                        (0x1fU 
                                                         & vlSelf->top__DOT__Core__DOT__Alu__DOT__op2))
                                                        : 
                                                       ((2U 
                                                         == 
                                                         ((0x3f8U 
                                                           & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                              >> 6U)) 
                                                          | (7U 
                                                             & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                >> 0x10U))))
                                                         ? 
                                                        (VL_LTS_III(32, vlSelf->top__DOT__Core__DOT__rs1_data, vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                          ? 1U
                                                          : 0U)
                                                         : 
                                                        ((vlSelf->top__DOT__Core__DOT__rs1_data 
                                                          < vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                          ? 1U
                                                          : 0U))))))))
                                                  : 
                                                 ((5U 
                                                   == 
                                                   ((0x3f8U 
                                                     & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                        >> 6U)) 
                                                    | (7U 
                                                       & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                          >> 0x10U))))
                                                   ? 
                                                  (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                   >> 
                                                   (0x1fU 
                                                    & vlSelf->top__DOT__Core__DOT__Alu__DOT__op2))
                                                   : 
                                                  ((0x105U 
                                                    == 
                                                    ((0x3f8U 
                                                      & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                         >> 6U)) 
                                                     | (7U 
                                                        & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                           >> 0x10U))))
                                                    ? 
                                                   (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                    >> 
                                                    (0x1fU 
                                                     & vlSelf->top__DOT__Core__DOT__Alu__DOT__op2))
                                                    : 0U)))
                                                 : 
                                                ((0x10U 
                                                  & vlSelf->top__DOT__Core__DOT__de[0U])
                                                  ? 
                                                 ((0x40000U 
                                                   & vlSelf->top__DOT__Core__DOT__de[1U])
                                                   ? 
                                                  ((0x20000U 
                                                    & vlSelf->top__DOT__Core__DOT__de[1U])
                                                    ? 
                                                   ((0x10000U 
                                                     & vlSelf->top__DOT__Core__DOT__de[1U])
                                                     ? 
                                                    (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                     >= vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                     : 
                                                    (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                     < vlSelf->top__DOT__Core__DOT__Alu__DOT__op2))
                                                    : 
                                                   ((0x10000U 
                                                     & vlSelf->top__DOT__Core__DOT__de[1U])
                                                     ? 
                                                    VL_GTES_III(32, vlSelf->top__DOT__Core__DOT__rs1_data, vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                     : 
                                                    VL_LTS_III(32, vlSelf->top__DOT__Core__DOT__rs1_data, vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)))
                                                   : 
                                                  ((0x20000U 
                                                    & vlSelf->top__DOT__Core__DOT__de[1U])
                                                    ? 0U
                                                    : 
                                                   ((0x10000U 
                                                     & vlSelf->top__DOT__Core__DOT__de[1U])
                                                     ? 
                                                    (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                     != vlSelf->top__DOT__Core__DOT__Alu__DOT__op2)
                                                     : 
                                                    (vlSelf->top__DOT__Core__DOT__rs1_data 
                                                     == vlSelf->top__DOT__Core__DOT__Alu__DOT__op2))))
                                                  : 0U)));
    vlSelf->top__DOT__Core__DOT__dmem[3U] = ((1U & 
                                              vlSelf->top__DOT__Core__DOT__dmem[3U]) 
                                             | (vlSelf->top__DOT__Core__DOT__alu_out 
                                                << 1U));
    vlSelf->top__DOT__Core__DOT__dmem[4U] = (vlSelf->top__DOT__Core__DOT__alu_out 
                                             >> 0x1fU);
    __Vtemp_h1837cfa2__0[1U] = (((IData)((((QData)((IData)(vlSelf->top__DOT__Core__DOT__alu_out)) 
                                           << 0x20U) 
                                          | (QData)((IData)(
                                                            ((0U 
                                                              == 
                                                              (7U 
                                                               & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                  >> 0x10U)))
                                                              ? 
                                                             (0xffU 
                                                              & vlSelf->top__DOT__Core__DOT__rs2_data)
                                                              : 
                                                             ((1U 
                                                               == 
                                                               (7U 
                                                                & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                   >> 0x10U)))
                                                               ? 
                                                              (0xffffU 
                                                               & vlSelf->top__DOT__Core__DOT__rs2_data)
                                                               : vlSelf->top__DOT__Core__DOT__rs2_data)))))) 
                                 >> 0x1fU) | ((IData)(
                                                      ((((QData)((IData)(vlSelf->top__DOT__Core__DOT__alu_out)) 
                                                         << 0x20U) 
                                                        | (QData)((IData)(
                                                                          ((0U 
                                                                            == 
                                                                            (7U 
                                                                             & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                                >> 0x10U)))
                                                                            ? 
                                                                           (0xffU 
                                                                            & vlSelf->top__DOT__Core__DOT__rs2_data)
                                                                            : 
                                                                           ((1U 
                                                                             == 
                                                                             (7U 
                                                                              & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                                >> 0x10U)))
                                                                             ? 
                                                                            (0xffffU 
                                                                             & vlSelf->top__DOT__Core__DOT__rs2_data)
                                                                             : vlSelf->top__DOT__Core__DOT__rs2_data))))) 
                                                       >> 0x20U)) 
                                              << 1U));
    vlSelf->top__DOT__Core__DOT__dmem[0U] = (((IData)(
                                                      (((QData)((IData)(vlSelf->top__DOT__Core__DOT__alu_out)) 
                                                        << 0x20U) 
                                                       | (QData)((IData)(
                                                                         ((0U 
                                                                           == 
                                                                           (7U 
                                                                            & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                               >> 0x10U)))
                                                                           ? 
                                                                          (0xffU 
                                                                           & vlSelf->top__DOT__Core__DOT__rs2_data)
                                                                           : 
                                                                          ((1U 
                                                                            == 
                                                                            (7U 
                                                                             & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                                >> 0x10U)))
                                                                            ? 
                                                                           (0xffffU 
                                                                            & vlSelf->top__DOT__Core__DOT__rs2_data)
                                                                            : vlSelf->top__DOT__Core__DOT__rs2_data)))))) 
                                              << 1U) 
                                             | ((IData)(vlSelf->top__DOT__Core__DOT__state_ma) 
                                                & (vlSelf->top__DOT__Core__DOT__de[0U] 
                                                   >> 5U)));
    vlSelf->top__DOT__Core__DOT__dmem[1U] = __Vtemp_h1837cfa2__0[1U];
    vlSelf->top__DOT__Core__DOT__dmem[2U] = ((0xfffffffeU 
                                              & vlSelf->top__DOT__Core__DOT__dmem[2U]) 
                                             | ((IData)(
                                                        ((((QData)((IData)(vlSelf->top__DOT__Core__DOT__alu_out)) 
                                                           << 0x20U) 
                                                          | (QData)((IData)(
                                                                            ((0U 
                                                                              == 
                                                                              (7U 
                                                                               & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                                >> 0x10U)))
                                                                              ? 
                                                                             (0xffU 
                                                                              & vlSelf->top__DOT__Core__DOT__rs2_data)
                                                                              : 
                                                                             ((1U 
                                                                               == 
                                                                               (7U 
                                                                                & (vlSelf->top__DOT__Core__DOT__de[1U] 
                                                                                >> 0x10U)))
                                                                               ? 
                                                                              (0xffffU 
                                                                               & vlSelf->top__DOT__Core__DOT__rs2_data)
                                                                               : vlSelf->top__DOT__Core__DOT__rs2_data))))) 
                                                         >> 0x20U)) 
                                                >> 0x1fU));
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vtop___024root___sequent__TOP__0(vlSelf);
    }
    if (((IData)(vlSelf->top__DOT__sysclk) & (~ (IData)(vlSelf->__Vclklast__TOP__top__DOT__sysclk)))) {
        Vtop___024root___sequent__TOP__1(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
    vlSelf->__Vclklast__TOP__top__DOT__sysclk = vlSelf->top__DOT__sysclk;
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
