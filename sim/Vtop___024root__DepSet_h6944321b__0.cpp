// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

extern const VlUnpacked<CData/*1:0*/, 256> Vtop__ConstPool__TABLE_ha11f361b_0;
extern const VlUnpacked<CData/*0:0*/, 256> Vtop__ConstPool__TABLE_h34d0b3b7_0;
extern const VlUnpacked<CData/*2:0*/, 256> Vtop__ConstPool__TABLE_h7fa9360f_0;
extern const VlWide<16>/*511:0*/ Vtop__ConstPool__CONST_h93e1b771_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vtop__ConstPool__TABLE_h7fa9c123_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_h98a60f23_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vtop__ConstPool__TABLE_h82cdba00_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_h32a2a51b_0;
extern const VlUnpacked<CData/*2:0*/, 128> Vtop__ConstPool__TABLE_h7cee3bde_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_hccdad1c1_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vtop__ConstPool__TABLE_h5c27fcbf_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vtop__ConstPool__TABLE_h1f72a610_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_hab58eb6f_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_h02f8e7c9_0;

VL_INLINE_OPT void Vtop___024root___sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__0\n"); );
    // Init
    CData/*6:0*/ __Vtableidx1;
    CData/*6:0*/ __Vtableidx2;
    CData/*6:0*/ __Vtableidx3;
    CData/*7:0*/ __Vtableidx4;
    CData/*1:0*/ __Vdly__top__DOT__mat_ctrl__DOT__core_sel;
    CData/*5:0*/ __Vdly__top__DOT__mat_a;
    CData/*0:0*/ __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run;
    CData/*7:0*/ __Vdly__top__DOT__src_ctrl__DOT__i;
    CData/*1:0*/ __Vdly__top__DOT__src_en;
    CData/*0:0*/ __Vdly__top__DOT__p;
    CData/*5:0*/ __Vdly__top__DOT__exe_ctrl__DOT__j;
    CData/*1:0*/ __Vdly__top__DOT__out_ctrl__DOT__i;
    CData/*1:0*/ __Vdly__top__DOT__out_ctrl__DOT__j;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v0;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v1;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v1;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v1;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v2;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v2;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v2;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v3;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v3;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v3;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v4;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v4;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v4;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v5;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v5;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v5;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v6;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v6;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v6;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v7;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v7;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v7;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v8;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v8;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v8;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v9;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v9;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v9;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v10;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v10;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v10;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v11;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v11;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v11;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v12;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v12;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v12;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v13;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v13;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v13;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v14;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v14;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v14;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v15;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v15;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v15;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v16;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v16;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v16;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v17;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v17;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v17;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v18;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v18;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v18;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v19;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v19;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v19;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v20;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v20;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v20;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v21;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v21;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v21;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v22;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v22;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v22;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v23;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v23;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v23;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v24;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v24;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v24;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v25;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v25;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v25;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v26;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v26;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v26;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v27;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v27;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v27;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v28;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v28;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v28;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v29;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v29;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v29;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v30;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v30;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v30;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v31;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff0__v31;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff0__v31;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v0;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v1;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v1;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v1;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v2;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v2;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v2;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v3;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v3;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v3;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v4;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v4;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v4;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v5;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v5;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v5;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v6;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v6;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v6;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v7;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v7;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v7;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v8;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v8;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v8;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v9;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v9;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v9;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v10;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v10;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v10;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v11;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v11;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v11;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v12;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v12;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v12;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v13;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v13;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v13;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v14;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v14;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v14;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v15;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v15;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v15;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v16;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v16;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v16;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v17;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v17;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v17;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v18;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v18;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v18;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v19;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v19;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v19;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v20;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v20;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v20;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v21;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v21;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v21;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v22;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v22;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v22;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v23;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v23;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v23;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v24;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v24;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v24;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v25;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v25;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v25;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v26;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v26;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v26;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v27;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v27;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v27;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v28;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v28;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v28;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v29;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v29;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v29;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v30;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v30;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v30;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v31;
    IData/*31:0*/ __Vdlyvval__top__DOT__src_buf__DOT__buff1__v31;
    CData/*0:0*/ __Vdlyvset__top__DOT__src_buf__DOT__buff1__v31;
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
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31;
    IData/*31:0*/ __Vdly__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31;
    IData/*31:0*/ __Vdly__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31;
    IData/*31:0*/ __Vdly__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31;
    IData/*31:0*/ __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31;
    CData/*0:0*/ __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31;
    IData/*31:0*/ __Vdly__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
    // Body
    __Vdly__top__DOT__mat_a = vlSelf->top__DOT__mat_a;
    __Vdly__top__DOT__mat_ctrl__DOT__core_sel = vlSelf->top__DOT__mat_ctrl__DOT__core_sel;
    __Vdly__top__DOT__out_ctrl__DOT__j = vlSelf->top__DOT__out_ctrl__DOT__j;
    __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run 
        = vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run;
    __Vdly__top__DOT__src_ctrl__DOT__i = vlSelf->top__DOT__src_ctrl__DOT__i;
    __Vdly__top__DOT__p = vlSelf->top__DOT__p;
    __Vdly__top__DOT__src_en = vlSelf->top__DOT__src_en;
    __Vdly__top__DOT__exe_ctrl__DOT__j = vlSelf->top__DOT__exe_ctrl__DOT__j;
    __Vdlyvset__top__DOT__dst_buf__DOT__buff3__v0 = 0U;
    __Vdlyvset__top__DOT__dst_buf__DOT__buff2__v0 = 0U;
    __Vdlyvset__top__DOT__dst_buf__DOT__buff1__v0 = 0U;
    __Vdlyvset__top__DOT__dst_buf__DOT__buff0__v0 = 0U;
    __Vdly__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left 
        = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
    __Vdly__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left 
        = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
    __Vdly__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left 
        = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
    __Vdly__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left 
        = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
    __Vdly__top__DOT__out_ctrl__DOT__i = vlSelf->top__DOT__out_ctrl__DOT__i;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v0 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v1 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v2 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v3 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v4 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v5 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v6 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v7 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v8 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v9 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v10 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v11 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v12 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v13 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v14 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v15 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v16 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v17 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v18 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v19 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v20 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v21 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v22 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v23 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v24 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v25 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v26 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v27 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v28 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v29 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v30 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff1__v31 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v0 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v1 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v2 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v3 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v4 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v5 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v6 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v7 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v8 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v9 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v10 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v11 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v12 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v13 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v14 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v15 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v16 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v17 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v18 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v19 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v20 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v21 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v22 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v23 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v24 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v25 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v26 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v27 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v28 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v29 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v30 = 0U;
    __Vdlyvset__top__DOT__src_buf__DOT__buff0__v31 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30 = 0U;
    __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31 = 0U;
    if ((1U & ((~ (IData)(vlSelf->AXIS_ARESETN)) | 
               (~ (IData)(vlSelf->top__DOT__matw))))) {
        __Vdly__top__DOT__mat_ctrl__DOT__core_sel = 0U;
        __Vdly__top__DOT__mat_a = 0U;
    } else if (vlSelf->S_AXIS_TVALID) {
        __Vdly__top__DOT__mat_a = (0x3fU & ((IData)(0x20U) 
                                            + (IData)(vlSelf->top__DOT__mat_a)));
        if ((0x20U == (IData)(vlSelf->top__DOT__mat_a))) {
            __Vdly__top__DOT__mat_ctrl__DOT__core_sel 
                = (3U & ((IData)(1U) + (IData)(vlSelf->top__DOT__mat_ctrl__DOT__core_sel)));
        }
    }
    __Vtableidx4 = (((IData)(vlSelf->top__DOT__dst_ctrl__DOT__i) 
                     << 5U) | (((IData)(vlSelf->M_AXIS_TREADY) 
                                << 4U) | (((IData)(vlSelf->top__DOT__dst_ctrl__DOT__last_i) 
                                           << 3U) | 
                                          (((IData)(vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run) 
                                            << 2U) 
                                           | (((IData)(vlSelf->top__DOT__dst_ctrl__DOT__start) 
                                               << 1U) 
                                              | (1U 
                                                 & (~ (IData)(vlSelf->top__DOT__run))))))));
    if ((1U & Vtop__ConstPool__TABLE_ha11f361b_0[__Vtableidx4])) {
        vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run 
            = Vtop__ConstPool__TABLE_h34d0b3b7_0[__Vtableidx4];
    }
    if ((2U & Vtop__ConstPool__TABLE_ha11f361b_0[__Vtableidx4])) {
        vlSelf->top__DOT__dst_ctrl__DOT__i = Vtop__ConstPool__TABLE_h7fa9360f_0
            [__Vtableidx4];
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
                    = (0xffU & ((IData)(0x20U) + (IData)(vlSelf->top__DOT__src_ctrl__DOT__i)));
            }
            __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run = 1U;
        }
    }
    vlSelf->top__DOT__update = ((IData)(vlSelf->top__DOT__run) 
                                & (IData)(vlSelf->top__DOT__out_ctrl__DOT__update_after_start));
    if (((IData)(vlSelf->top__DOT__stream_v) & ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a) 
                                                >> 3U))) {
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x10U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x11U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[1U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x12U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[2U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x13U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[3U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x14U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[4U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x15U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[5U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x16U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[6U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x17U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[7U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x18U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[8U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x19U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[9U];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1aU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xaU];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1bU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xbU];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1cU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xcU];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1dU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xdU];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1eU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xeU];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0x1fU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xfU];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff2
            [(7U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[2U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff2
            [(7U & ((IData)(1U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[4U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff2
            [(7U & ((IData)(2U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[6U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff2
            [(7U & ((IData)(3U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[8U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff2
            [(7U & ((IData)(4U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0xaU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff2
            [(7U & ((IData)(5U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0xcU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff2
            [(7U & ((IData)(6U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0xeU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff2
            [(7U & ((IData)(7U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[1U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff3
            [(7U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[3U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff3
            [(7U & ((IData)(1U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[5U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff3
            [(7U & ((IData)(2U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[7U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff3
            [(7U & ((IData)(3U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[9U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff3
            [(7U & ((IData)(4U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0xbU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff3
            [(7U & ((IData)(5U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0xdU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff3
            [(7U & ((IData)(6U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_1[0xfU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff3
            [(7U & ((IData)(7U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
    }
    if (((IData)(vlSelf->top__DOT__stream_v) & (~ ((IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a) 
                                                   >> 3U)))) {
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x10U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x11U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[1U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x12U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[2U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x13U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[3U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x14U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[4U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x15U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[5U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x16U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[6U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x17U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[7U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x18U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[8U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x19U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[9U];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1aU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xaU];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1bU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xbU];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1cU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xcU];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1dU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xdU];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1eU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xeU];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0x1fU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xfU];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff0
            [(7U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[2U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff0
            [(7U & ((IData)(1U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[4U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff0
            [(7U & ((IData)(2U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[6U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff0
            [(7U & ((IData)(3U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[8U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff0
            [(7U & ((IData)(4U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0xaU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff0
            [(7U & ((IData)(5U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0xcU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff0
            [(7U & ((IData)(6U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0xeU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff0
            [(7U & ((IData)(7U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[1U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff1
            [(7U & (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[3U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff1
            [(7U & ((IData)(1U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[5U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff1
            [(7U & ((IData)(2U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[7U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff1
            [(7U & ((IData)(3U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[9U] 
            = vlSelf->top__DOT__dst_buf__DOT__buff1
            [(7U & ((IData)(4U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0xbU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff1
            [(7U & ((IData)(5U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0xdU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff1
            [(7U & ((IData)(6U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
        vlSelf->top__DOT__dst_buf__DOT__stream_0[0xfU] 
            = vlSelf->top__DOT__dst_buf__DOT__buff1
            [(7U & ((IData)(7U) + (IData)(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a)))];
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
    vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay = 
        ((IData)(vlSelf->top__DOT__run) & (IData)(vlSelf->top__DOT__s_init));
    __Vtableidx3 = (((IData)(vlSelf->top__DOT__out_ctrl__DOT__i) 
                     << 5U) | (((IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j) 
                                << 4U) | (((IData)(vlSelf->top__DOT__out_ctrl__DOT__last_i) 
                                           << 3U) | 
                                          (((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run) 
                                            << 2U) 
                                           | (((IData)(vlSelf->top__DOT__s_init) 
                                               << 1U) 
                                              | (1U 
                                                 & (~ (IData)(vlSelf->top__DOT__run))))))));
    if ((1U & Vtop__ConstPool__TABLE_h7fa9c123_0[__Vtableidx3])) {
        vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run 
            = Vtop__ConstPool__TABLE_h98a60f23_0[__Vtableidx3];
    }
    if ((2U & Vtop__ConstPool__TABLE_h7fa9c123_0[__Vtableidx3])) {
        __Vdly__top__DOT__out_ctrl__DOT__i = Vtop__ConstPool__TABLE_h82cdba00_0
            [__Vtableidx3];
    }
    if (((IData)(vlSelf->top__DOT__src_ctrl__DOT__start) 
         & ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a) 
            >> 8U))) {
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v0 
            = vlSelf->S_AXIS_TDATA[0U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v0 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v0 
            = (0xffU & (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v1 
            = vlSelf->S_AXIS_TDATA[1U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v1 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v1 
            = (0xffU & ((IData)(1U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v2 
            = vlSelf->S_AXIS_TDATA[2U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v2 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v2 
            = (0xffU & ((IData)(2U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v3 
            = vlSelf->S_AXIS_TDATA[3U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v3 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v3 
            = (0xffU & ((IData)(3U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v4 
            = vlSelf->S_AXIS_TDATA[4U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v4 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v4 
            = (0xffU & ((IData)(4U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v5 
            = vlSelf->S_AXIS_TDATA[5U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v5 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v5 
            = (0xffU & ((IData)(5U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v6 
            = vlSelf->S_AXIS_TDATA[6U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v6 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v6 
            = (0xffU & ((IData)(6U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v7 
            = vlSelf->S_AXIS_TDATA[7U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v7 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v7 
            = (0xffU & ((IData)(7U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v8 
            = vlSelf->S_AXIS_TDATA[8U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v8 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v8 
            = (0xffU & ((IData)(8U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v9 
            = vlSelf->S_AXIS_TDATA[9U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v9 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v9 
            = (0xffU & ((IData)(9U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v10 
            = vlSelf->S_AXIS_TDATA[0xaU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v10 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v10 
            = (0xffU & ((IData)(0xaU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v11 
            = vlSelf->S_AXIS_TDATA[0xbU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v11 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v11 
            = (0xffU & ((IData)(0xbU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v12 
            = vlSelf->S_AXIS_TDATA[0xcU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v12 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v12 
            = (0xffU & ((IData)(0xcU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v13 
            = vlSelf->S_AXIS_TDATA[0xdU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v13 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v13 
            = (0xffU & ((IData)(0xdU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v14 
            = vlSelf->S_AXIS_TDATA[0xeU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v14 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v14 
            = (0xffU & ((IData)(0xeU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v15 
            = vlSelf->S_AXIS_TDATA[0xfU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v15 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v15 
            = (0xffU & ((IData)(0xfU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v16 
            = vlSelf->S_AXIS_TDATA[0x10U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v16 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v16 
            = (0xffU & ((IData)(0x10U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v17 
            = vlSelf->S_AXIS_TDATA[0x11U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v17 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v17 
            = (0xffU & ((IData)(0x11U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v18 
            = vlSelf->S_AXIS_TDATA[0x12U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v18 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v18 
            = (0xffU & ((IData)(0x12U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v19 
            = vlSelf->S_AXIS_TDATA[0x13U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v19 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v19 
            = (0xffU & ((IData)(0x13U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v20 
            = vlSelf->S_AXIS_TDATA[0x14U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v20 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v20 
            = (0xffU & ((IData)(0x14U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v21 
            = vlSelf->S_AXIS_TDATA[0x15U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v21 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v21 
            = (0xffU & ((IData)(0x15U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v22 
            = vlSelf->S_AXIS_TDATA[0x16U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v22 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v22 
            = (0xffU & ((IData)(0x16U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v23 
            = vlSelf->S_AXIS_TDATA[0x17U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v23 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v23 
            = (0xffU & ((IData)(0x17U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v24 
            = vlSelf->S_AXIS_TDATA[0x18U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v24 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v24 
            = (0xffU & ((IData)(0x18U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v25 
            = vlSelf->S_AXIS_TDATA[0x19U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v25 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v25 
            = (0xffU & ((IData)(0x19U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v26 
            = vlSelf->S_AXIS_TDATA[0x1aU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v26 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v26 
            = (0xffU & ((IData)(0x1aU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v27 
            = vlSelf->S_AXIS_TDATA[0x1bU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v27 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v27 
            = (0xffU & ((IData)(0x1bU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v28 
            = vlSelf->S_AXIS_TDATA[0x1cU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v28 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v28 
            = (0xffU & ((IData)(0x1cU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v29 
            = vlSelf->S_AXIS_TDATA[0x1dU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v29 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v29 
            = (0xffU & ((IData)(0x1dU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v30 
            = vlSelf->S_AXIS_TDATA[0x1eU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v30 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v30 
            = (0xffU & ((IData)(0x1eU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff1__v31 
            = vlSelf->S_AXIS_TDATA[0x1fU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff1__v31 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v31 
            = (0xffU & ((IData)(0x1fU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
    }
    if (((IData)(vlSelf->top__DOT__src_ctrl__DOT__start) 
         & (~ ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a) 
               >> 8U)))) {
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v0 
            = vlSelf->S_AXIS_TDATA[0U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v0 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v0 
            = (0xffU & (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v1 
            = vlSelf->S_AXIS_TDATA[1U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v1 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v1 
            = (0xffU & ((IData)(1U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v2 
            = vlSelf->S_AXIS_TDATA[2U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v2 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v2 
            = (0xffU & ((IData)(2U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v3 
            = vlSelf->S_AXIS_TDATA[3U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v3 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v3 
            = (0xffU & ((IData)(3U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v4 
            = vlSelf->S_AXIS_TDATA[4U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v4 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v4 
            = (0xffU & ((IData)(4U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v5 
            = vlSelf->S_AXIS_TDATA[5U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v5 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v5 
            = (0xffU & ((IData)(5U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v6 
            = vlSelf->S_AXIS_TDATA[6U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v6 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v6 
            = (0xffU & ((IData)(6U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v7 
            = vlSelf->S_AXIS_TDATA[7U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v7 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v7 
            = (0xffU & ((IData)(7U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v8 
            = vlSelf->S_AXIS_TDATA[8U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v8 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v8 
            = (0xffU & ((IData)(8U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v9 
            = vlSelf->S_AXIS_TDATA[9U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v9 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v9 
            = (0xffU & ((IData)(9U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v10 
            = vlSelf->S_AXIS_TDATA[0xaU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v10 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v10 
            = (0xffU & ((IData)(0xaU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v11 
            = vlSelf->S_AXIS_TDATA[0xbU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v11 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v11 
            = (0xffU & ((IData)(0xbU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v12 
            = vlSelf->S_AXIS_TDATA[0xcU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v12 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v12 
            = (0xffU & ((IData)(0xcU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v13 
            = vlSelf->S_AXIS_TDATA[0xdU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v13 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v13 
            = (0xffU & ((IData)(0xdU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v14 
            = vlSelf->S_AXIS_TDATA[0xeU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v14 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v14 
            = (0xffU & ((IData)(0xeU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v15 
            = vlSelf->S_AXIS_TDATA[0xfU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v15 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v15 
            = (0xffU & ((IData)(0xfU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v16 
            = vlSelf->S_AXIS_TDATA[0x10U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v16 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v16 
            = (0xffU & ((IData)(0x10U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v17 
            = vlSelf->S_AXIS_TDATA[0x11U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v17 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v17 
            = (0xffU & ((IData)(0x11U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v18 
            = vlSelf->S_AXIS_TDATA[0x12U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v18 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v18 
            = (0xffU & ((IData)(0x12U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v19 
            = vlSelf->S_AXIS_TDATA[0x13U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v19 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v19 
            = (0xffU & ((IData)(0x13U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v20 
            = vlSelf->S_AXIS_TDATA[0x14U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v20 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v20 
            = (0xffU & ((IData)(0x14U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v21 
            = vlSelf->S_AXIS_TDATA[0x15U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v21 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v21 
            = (0xffU & ((IData)(0x15U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v22 
            = vlSelf->S_AXIS_TDATA[0x16U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v22 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v22 
            = (0xffU & ((IData)(0x16U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v23 
            = vlSelf->S_AXIS_TDATA[0x17U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v23 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v23 
            = (0xffU & ((IData)(0x17U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v24 
            = vlSelf->S_AXIS_TDATA[0x18U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v24 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v24 
            = (0xffU & ((IData)(0x18U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v25 
            = vlSelf->S_AXIS_TDATA[0x19U];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v25 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v25 
            = (0xffU & ((IData)(0x19U) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v26 
            = vlSelf->S_AXIS_TDATA[0x1aU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v26 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v26 
            = (0xffU & ((IData)(0x1aU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v27 
            = vlSelf->S_AXIS_TDATA[0x1bU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v27 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v27 
            = (0xffU & ((IData)(0x1bU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v28 
            = vlSelf->S_AXIS_TDATA[0x1cU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v28 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v28 
            = (0xffU & ((IData)(0x1cU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v29 
            = vlSelf->S_AXIS_TDATA[0x1dU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v29 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v29 
            = (0xffU & ((IData)(0x1dU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v30 
            = vlSelf->S_AXIS_TDATA[0x1eU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v30 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v30 
            = (0xffU & ((IData)(0x1eU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
        __Vdlyvval__top__DOT__src_buf__DOT__buff0__v31 
            = vlSelf->S_AXIS_TDATA[0x1fU];
        __Vdlyvset__top__DOT__src_buf__DOT__buff0__v31 = 1U;
        __Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v31 
            = (0xffU & ((IData)(0x1fU) + (IData)(vlSelf->top__DOT____Vcellinp__src_buf__src_a)));
    }
    if ((8U & (IData)(vlSelf->top__DOT__mat_v))) {
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->S_AXIS_TDATA[0U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->top__DOT__mat_a;
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1 
            = vlSelf->S_AXIS_TDATA[1U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1 
            = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2 
            = vlSelf->S_AXIS_TDATA[2U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2 
            = (0x3fU & ((IData)(2U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3 
            = vlSelf->S_AXIS_TDATA[3U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3 
            = (0x3fU & ((IData)(3U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4 
            = vlSelf->S_AXIS_TDATA[4U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4 
            = (0x3fU & ((IData)(4U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5 
            = vlSelf->S_AXIS_TDATA[5U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5 
            = (0x3fU & ((IData)(5U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6 
            = vlSelf->S_AXIS_TDATA[6U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6 
            = (0x3fU & ((IData)(6U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7 
            = vlSelf->S_AXIS_TDATA[7U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7 
            = (0x3fU & ((IData)(7U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8 
            = vlSelf->S_AXIS_TDATA[8U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8 
            = (0x3fU & ((IData)(8U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9 
            = vlSelf->S_AXIS_TDATA[9U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9 
            = (0x3fU & ((IData)(9U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10 
            = vlSelf->S_AXIS_TDATA[0xaU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10 
            = (0x3fU & ((IData)(0xaU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11 
            = vlSelf->S_AXIS_TDATA[0xbU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11 
            = (0x3fU & ((IData)(0xbU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12 
            = vlSelf->S_AXIS_TDATA[0xcU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12 
            = (0x3fU & ((IData)(0xcU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13 
            = vlSelf->S_AXIS_TDATA[0xdU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13 
            = (0x3fU & ((IData)(0xdU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14 
            = vlSelf->S_AXIS_TDATA[0xeU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14 
            = (0x3fU & ((IData)(0xeU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15 
            = vlSelf->S_AXIS_TDATA[0xfU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15 
            = (0x3fU & ((IData)(0xfU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16 
            = vlSelf->S_AXIS_TDATA[0x10U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16 
            = (0x3fU & ((IData)(0x10U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17 
            = vlSelf->S_AXIS_TDATA[0x11U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17 
            = (0x3fU & ((IData)(0x11U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18 
            = vlSelf->S_AXIS_TDATA[0x12U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18 
            = (0x3fU & ((IData)(0x12U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19 
            = vlSelf->S_AXIS_TDATA[0x13U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19 
            = (0x3fU & ((IData)(0x13U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20 
            = vlSelf->S_AXIS_TDATA[0x14U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20 
            = (0x3fU & ((IData)(0x14U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21 
            = vlSelf->S_AXIS_TDATA[0x15U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21 
            = (0x3fU & ((IData)(0x15U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22 
            = vlSelf->S_AXIS_TDATA[0x16U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22 
            = (0x3fU & ((IData)(0x16U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23 
            = vlSelf->S_AXIS_TDATA[0x17U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23 
            = (0x3fU & ((IData)(0x17U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24 
            = vlSelf->S_AXIS_TDATA[0x18U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24 
            = (0x3fU & ((IData)(0x18U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25 
            = vlSelf->S_AXIS_TDATA[0x19U];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25 
            = (0x3fU & ((IData)(0x19U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26 
            = vlSelf->S_AXIS_TDATA[0x1aU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26 
            = (0x3fU & ((IData)(0x1aU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27 
            = vlSelf->S_AXIS_TDATA[0x1bU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27 
            = (0x3fU & ((IData)(0x1bU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28 
            = vlSelf->S_AXIS_TDATA[0x1cU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28 
            = (0x3fU & ((IData)(0x1cU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29 
            = vlSelf->S_AXIS_TDATA[0x1dU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29 
            = (0x3fU & ((IData)(0x1dU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30 
            = vlSelf->S_AXIS_TDATA[0x1eU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30 
            = (0x3fU & ((IData)(0x1eU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31 
            = vlSelf->S_AXIS_TDATA[0x1fU];
        __Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31 
            = (0x3fU & ((IData)(0x1fU) + (IData)(vlSelf->top__DOT__mat_a)));
    }
    if ((4U & (IData)(vlSelf->top__DOT__mat_v))) {
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->S_AXIS_TDATA[0U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->top__DOT__mat_a;
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1 
            = vlSelf->S_AXIS_TDATA[1U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1 
            = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2 
            = vlSelf->S_AXIS_TDATA[2U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2 
            = (0x3fU & ((IData)(2U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3 
            = vlSelf->S_AXIS_TDATA[3U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3 
            = (0x3fU & ((IData)(3U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4 
            = vlSelf->S_AXIS_TDATA[4U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4 
            = (0x3fU & ((IData)(4U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5 
            = vlSelf->S_AXIS_TDATA[5U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5 
            = (0x3fU & ((IData)(5U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6 
            = vlSelf->S_AXIS_TDATA[6U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6 
            = (0x3fU & ((IData)(6U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7 
            = vlSelf->S_AXIS_TDATA[7U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7 
            = (0x3fU & ((IData)(7U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8 
            = vlSelf->S_AXIS_TDATA[8U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8 
            = (0x3fU & ((IData)(8U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9 
            = vlSelf->S_AXIS_TDATA[9U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9 
            = (0x3fU & ((IData)(9U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10 
            = vlSelf->S_AXIS_TDATA[0xaU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10 
            = (0x3fU & ((IData)(0xaU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11 
            = vlSelf->S_AXIS_TDATA[0xbU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11 
            = (0x3fU & ((IData)(0xbU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12 
            = vlSelf->S_AXIS_TDATA[0xcU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12 
            = (0x3fU & ((IData)(0xcU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13 
            = vlSelf->S_AXIS_TDATA[0xdU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13 
            = (0x3fU & ((IData)(0xdU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14 
            = vlSelf->S_AXIS_TDATA[0xeU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14 
            = (0x3fU & ((IData)(0xeU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15 
            = vlSelf->S_AXIS_TDATA[0xfU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15 
            = (0x3fU & ((IData)(0xfU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16 
            = vlSelf->S_AXIS_TDATA[0x10U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16 
            = (0x3fU & ((IData)(0x10U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17 
            = vlSelf->S_AXIS_TDATA[0x11U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17 
            = (0x3fU & ((IData)(0x11U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18 
            = vlSelf->S_AXIS_TDATA[0x12U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18 
            = (0x3fU & ((IData)(0x12U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19 
            = vlSelf->S_AXIS_TDATA[0x13U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19 
            = (0x3fU & ((IData)(0x13U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20 
            = vlSelf->S_AXIS_TDATA[0x14U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20 
            = (0x3fU & ((IData)(0x14U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21 
            = vlSelf->S_AXIS_TDATA[0x15U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21 
            = (0x3fU & ((IData)(0x15U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22 
            = vlSelf->S_AXIS_TDATA[0x16U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22 
            = (0x3fU & ((IData)(0x16U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23 
            = vlSelf->S_AXIS_TDATA[0x17U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23 
            = (0x3fU & ((IData)(0x17U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24 
            = vlSelf->S_AXIS_TDATA[0x18U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24 
            = (0x3fU & ((IData)(0x18U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25 
            = vlSelf->S_AXIS_TDATA[0x19U];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25 
            = (0x3fU & ((IData)(0x19U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26 
            = vlSelf->S_AXIS_TDATA[0x1aU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26 
            = (0x3fU & ((IData)(0x1aU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27 
            = vlSelf->S_AXIS_TDATA[0x1bU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27 
            = (0x3fU & ((IData)(0x1bU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28 
            = vlSelf->S_AXIS_TDATA[0x1cU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28 
            = (0x3fU & ((IData)(0x1cU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29 
            = vlSelf->S_AXIS_TDATA[0x1dU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29 
            = (0x3fU & ((IData)(0x1dU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30 
            = vlSelf->S_AXIS_TDATA[0x1eU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30 
            = (0x3fU & ((IData)(0x1eU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31 
            = vlSelf->S_AXIS_TDATA[0x1fU];
        __Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31 
            = (0x3fU & ((IData)(0x1fU) + (IData)(vlSelf->top__DOT__mat_a)));
    }
    if ((2U & (IData)(vlSelf->top__DOT__mat_v))) {
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->S_AXIS_TDATA[0U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->top__DOT__mat_a;
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1 
            = vlSelf->S_AXIS_TDATA[1U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1 
            = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2 
            = vlSelf->S_AXIS_TDATA[2U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2 
            = (0x3fU & ((IData)(2U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3 
            = vlSelf->S_AXIS_TDATA[3U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3 
            = (0x3fU & ((IData)(3U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4 
            = vlSelf->S_AXIS_TDATA[4U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4 
            = (0x3fU & ((IData)(4U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5 
            = vlSelf->S_AXIS_TDATA[5U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5 
            = (0x3fU & ((IData)(5U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6 
            = vlSelf->S_AXIS_TDATA[6U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6 
            = (0x3fU & ((IData)(6U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7 
            = vlSelf->S_AXIS_TDATA[7U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7 
            = (0x3fU & ((IData)(7U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8 
            = vlSelf->S_AXIS_TDATA[8U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8 
            = (0x3fU & ((IData)(8U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9 
            = vlSelf->S_AXIS_TDATA[9U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9 
            = (0x3fU & ((IData)(9U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10 
            = vlSelf->S_AXIS_TDATA[0xaU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10 
            = (0x3fU & ((IData)(0xaU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11 
            = vlSelf->S_AXIS_TDATA[0xbU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11 
            = (0x3fU & ((IData)(0xbU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12 
            = vlSelf->S_AXIS_TDATA[0xcU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12 
            = (0x3fU & ((IData)(0xcU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13 
            = vlSelf->S_AXIS_TDATA[0xdU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13 
            = (0x3fU & ((IData)(0xdU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14 
            = vlSelf->S_AXIS_TDATA[0xeU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14 
            = (0x3fU & ((IData)(0xeU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15 
            = vlSelf->S_AXIS_TDATA[0xfU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15 
            = (0x3fU & ((IData)(0xfU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16 
            = vlSelf->S_AXIS_TDATA[0x10U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16 
            = (0x3fU & ((IData)(0x10U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17 
            = vlSelf->S_AXIS_TDATA[0x11U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17 
            = (0x3fU & ((IData)(0x11U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18 
            = vlSelf->S_AXIS_TDATA[0x12U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18 
            = (0x3fU & ((IData)(0x12U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19 
            = vlSelf->S_AXIS_TDATA[0x13U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19 
            = (0x3fU & ((IData)(0x13U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20 
            = vlSelf->S_AXIS_TDATA[0x14U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20 
            = (0x3fU & ((IData)(0x14U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21 
            = vlSelf->S_AXIS_TDATA[0x15U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21 
            = (0x3fU & ((IData)(0x15U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22 
            = vlSelf->S_AXIS_TDATA[0x16U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22 
            = (0x3fU & ((IData)(0x16U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23 
            = vlSelf->S_AXIS_TDATA[0x17U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23 
            = (0x3fU & ((IData)(0x17U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24 
            = vlSelf->S_AXIS_TDATA[0x18U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24 
            = (0x3fU & ((IData)(0x18U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25 
            = vlSelf->S_AXIS_TDATA[0x19U];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25 
            = (0x3fU & ((IData)(0x19U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26 
            = vlSelf->S_AXIS_TDATA[0x1aU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26 
            = (0x3fU & ((IData)(0x1aU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27 
            = vlSelf->S_AXIS_TDATA[0x1bU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27 
            = (0x3fU & ((IData)(0x1bU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28 
            = vlSelf->S_AXIS_TDATA[0x1cU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28 
            = (0x3fU & ((IData)(0x1cU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29 
            = vlSelf->S_AXIS_TDATA[0x1dU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29 
            = (0x3fU & ((IData)(0x1dU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30 
            = vlSelf->S_AXIS_TDATA[0x1eU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30 
            = (0x3fU & ((IData)(0x1eU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31 
            = vlSelf->S_AXIS_TDATA[0x1fU];
        __Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31 
            = (0x3fU & ((IData)(0x1fU) + (IData)(vlSelf->top__DOT__mat_a)));
    }
    if ((1U & (IData)(vlSelf->top__DOT__mat_v))) {
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->S_AXIS_TDATA[0U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0 
            = vlSelf->top__DOT__mat_a;
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1 
            = vlSelf->S_AXIS_TDATA[1U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1 
            = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2 
            = vlSelf->S_AXIS_TDATA[2U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2 
            = (0x3fU & ((IData)(2U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3 
            = vlSelf->S_AXIS_TDATA[3U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3 
            = (0x3fU & ((IData)(3U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4 
            = vlSelf->S_AXIS_TDATA[4U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4 
            = (0x3fU & ((IData)(4U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5 
            = vlSelf->S_AXIS_TDATA[5U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5 
            = (0x3fU & ((IData)(5U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6 
            = vlSelf->S_AXIS_TDATA[6U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6 
            = (0x3fU & ((IData)(6U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7 
            = vlSelf->S_AXIS_TDATA[7U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7 
            = (0x3fU & ((IData)(7U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8 
            = vlSelf->S_AXIS_TDATA[8U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8 
            = (0x3fU & ((IData)(8U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9 
            = vlSelf->S_AXIS_TDATA[9U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9 
            = (0x3fU & ((IData)(9U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10 
            = vlSelf->S_AXIS_TDATA[0xaU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10 
            = (0x3fU & ((IData)(0xaU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11 
            = vlSelf->S_AXIS_TDATA[0xbU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11 
            = (0x3fU & ((IData)(0xbU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12 
            = vlSelf->S_AXIS_TDATA[0xcU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12 
            = (0x3fU & ((IData)(0xcU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13 
            = vlSelf->S_AXIS_TDATA[0xdU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13 
            = (0x3fU & ((IData)(0xdU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14 
            = vlSelf->S_AXIS_TDATA[0xeU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14 
            = (0x3fU & ((IData)(0xeU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15 
            = vlSelf->S_AXIS_TDATA[0xfU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15 
            = (0x3fU & ((IData)(0xfU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16 
            = vlSelf->S_AXIS_TDATA[0x10U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16 
            = (0x3fU & ((IData)(0x10U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17 
            = vlSelf->S_AXIS_TDATA[0x11U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17 
            = (0x3fU & ((IData)(0x11U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18 
            = vlSelf->S_AXIS_TDATA[0x12U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18 
            = (0x3fU & ((IData)(0x12U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19 
            = vlSelf->S_AXIS_TDATA[0x13U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19 
            = (0x3fU & ((IData)(0x13U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20 
            = vlSelf->S_AXIS_TDATA[0x14U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20 
            = (0x3fU & ((IData)(0x14U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21 
            = vlSelf->S_AXIS_TDATA[0x15U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21 
            = (0x3fU & ((IData)(0x15U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22 
            = vlSelf->S_AXIS_TDATA[0x16U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22 
            = (0x3fU & ((IData)(0x16U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23 
            = vlSelf->S_AXIS_TDATA[0x17U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23 
            = (0x3fU & ((IData)(0x17U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24 
            = vlSelf->S_AXIS_TDATA[0x18U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24 
            = (0x3fU & ((IData)(0x18U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25 
            = vlSelf->S_AXIS_TDATA[0x19U];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25 
            = (0x3fU & ((IData)(0x19U) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26 
            = vlSelf->S_AXIS_TDATA[0x1aU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26 
            = (0x3fU & ((IData)(0x1aU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27 
            = vlSelf->S_AXIS_TDATA[0x1bU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27 
            = (0x3fU & ((IData)(0x1bU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28 
            = vlSelf->S_AXIS_TDATA[0x1cU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28 
            = (0x3fU & ((IData)(0x1cU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29 
            = vlSelf->S_AXIS_TDATA[0x1dU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29 
            = (0x3fU & ((IData)(0x1dU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30 
            = vlSelf->S_AXIS_TDATA[0x1eU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30 
            = (0x3fU & ((IData)(0x1eU) + (IData)(vlSelf->top__DOT__mat_a)));
        __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31 
            = vlSelf->S_AXIS_TDATA[0x1fU];
        __Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31 = 1U;
        __Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31 
            = (0x3fU & ((IData)(0x1fU) + (IData)(vlSelf->top__DOT__mat_a)));
    }
    vlSelf->top__DOT__mat_ctrl__DOT__core_sel = __Vdly__top__DOT__mat_ctrl__DOT__core_sel;
    vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run 
        = __Vdly__top__DOT__src_ctrl__DOT__l_i__DOT__run;
    vlSelf->top__DOT__src_ctrl__DOT__i = __Vdly__top__DOT__src_ctrl__DOT__i;
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
        __Vdly__top__DOT__p = 1U;
        __Vdly__top__DOT__src_en = 0U;
    }
    vlSelf->top__DOT__p = __Vdly__top__DOT__p;
    if (__Vdlyvset__top__DOT__dst_buf__DOT__buff3__v0) {
        vlSelf->top__DOT__dst_buf__DOT__buff3[__Vdlyvdim0__top__DOT__dst_buf__DOT__buff3__v0] 
            = __Vdlyvval__top__DOT__dst_buf__DOT__buff3__v0;
    }
    if (__Vdlyvset__top__DOT__dst_buf__DOT__buff2__v0) {
        vlSelf->top__DOT__dst_buf__DOT__buff2[__Vdlyvdim0__top__DOT__dst_buf__DOT__buff2__v0] 
            = __Vdlyvval__top__DOT__dst_buf__DOT__buff2__v0;
    }
    if (__Vdlyvset__top__DOT__dst_buf__DOT__buff1__v0) {
        vlSelf->top__DOT__dst_buf__DOT__buff1[__Vdlyvdim0__top__DOT__dst_buf__DOT__buff1__v0] 
            = __Vdlyvval__top__DOT__dst_buf__DOT__buff1__v0;
    }
    if (__Vdlyvset__top__DOT__dst_buf__DOT__buff0__v0) {
        vlSelf->top__DOT__dst_buf__DOT__buff0[__Vdlyvdim0__top__DOT__dst_buf__DOT__buff0__v0] 
            = __Vdlyvval__top__DOT__dst_buf__DOT__buff0__v0;
    }
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left 
        = __Vdly__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left;
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left 
        = __Vdly__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left;
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left 
        = __Vdly__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left;
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left 
        = __Vdly__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left;
    vlSelf->top__DOT__mat_a = __Vdly__top__DOT__mat_a;
    vlSelf->top__DOT____Vcellinp__src_buf__src_a = 
        ((0x100U & ((~ (IData)(vlSelf->top__DOT__p)) 
                    << 8U)) | (IData)(vlSelf->top__DOT__src_ctrl__DOT__i));
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
    if (vlSelf->top__DOT__update) {
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
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next 
        = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next;
    if (vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2 
            = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data;
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2 
            = vlSelf->top__DOT__exec_src_data;
    } else {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next = 0U;
    }
    vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next 
        = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next;
    if (vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2 
            = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data;
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2 
            = vlSelf->top__DOT__exec_src_data;
    } else {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next = 0U;
    }
    vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next 
        = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next;
    if (vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2 
            = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data;
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2 
            = vlSelf->top__DOT__exec_src_data;
    } else {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next = 0U;
    }
    vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next 
        = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next;
    if (vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2 
            = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data;
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2 
            = vlSelf->top__DOT__exec_src_data;
    } else {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next = 0U;
    }
    if (vlSelf->top__DOT__run) {
        if ((((IData)(vlSelf->top__DOT__k_fin) & (IData)(vlSelf->top__DOT__out_busy)) 
             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))) {
            vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention 
                = ((IData)(vlSelf->top__DOT__k_fin) 
                   & (IData)(vlSelf->top__DOT__out_busy));
        }
        vlSelf->top__DOT__k_fin = vlSelf->top__DOT__exe_ctrl__DOT__last_j;
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
        vlSelf->top__DOT__exe_ctrl__DOT__k_init_next = 0U;
    }
    vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre 
        = (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run) 
            | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__start)) 
           & (~ (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j)));
    __Vtableidx2 = (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                     << 5U) | ((0x10U & ((~ (IData)(vlSelf->top__DOT__run)) 
                                         << 4U)) | 
                               (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_i) 
                                 << 3U) | (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j) 
                                            << 2U) 
                                           | (((IData)(vlSelf->top__DOT__s_init) 
                                               << 1U) 
                                              | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run))))));
    vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre 
        = Vtop__ConstPool__TABLE_h32a2a51b_0[__Vtableidx2];
    if ((2U & Vtop__ConstPool__TABLE_h7cee3bde_0[__Vtableidx2])) {
        vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run 
            = Vtop__ConstPool__TABLE_hccdad1c1_0[__Vtableidx2];
    }
    if ((4U & Vtop__ConstPool__TABLE_h7cee3bde_0[__Vtableidx2])) {
        vlSelf->top__DOT__exe_ctrl__DOT__i = Vtop__ConstPool__TABLE_h5c27fcbf_0
            [__Vtableidx2];
    }
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
    vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next 
        = vlSelf->top__DOT__k_init;
    if (vlSelf->top__DOT__exec) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data 
            = vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix
            [vlSelf->top__DOT__exe_ctrl__DOT__j];
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data 
            = vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix
            [vlSelf->top__DOT__exe_ctrl__DOT__j];
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data 
            = vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix
            [vlSelf->top__DOT__exe_ctrl__DOT__j];
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data 
            = vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix
            [vlSelf->top__DOT__exe_ctrl__DOT__j];
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next 
            = vlSelf->top__DOT__k_init;
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next 
            = vlSelf->top__DOT__k_init;
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next = 1U;
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next 
            = vlSelf->top__DOT__k_init;
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next = 1U;
    } else {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next = 0U;
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next 
            = vlSelf->top__DOT__k_init;
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next = 0U;
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next 
            = vlSelf->top__DOT__k_init;
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next = 0U;
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next 
            = vlSelf->top__DOT__k_init;
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next = 0U;
    }
    if (((IData)(vlSelf->top__DOT__exec) & (~ ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr) 
                                               >> 8U)))) {
        vlSelf->top__DOT__exec_src_data = vlSelf->top__DOT__src_buf__DOT__buff0
            [(0xffU & (IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr))];
    }
    if (((IData)(vlSelf->top__DOT__exec) & ((IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr) 
                                            >> 8U))) {
        vlSelf->top__DOT__exec_src_data = vlSelf->top__DOT__src_buf__DOT__buff1
            [(0xffU & (IData)(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr))];
    }
    if (vlSelf->top__DOT__run) {
        if (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
             | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run))) {
            if (vlSelf->top__DOT__exe_ctrl__DOT__last_j) {
                __Vdly__top__DOT__exe_ctrl__DOT__j = 0U;
                vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run = 0U;
            } else {
                __Vdly__top__DOT__exe_ctrl__DOT__j 
                    = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j)));
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
    __Vtableidx1 = (((IData)(vlSelf->top__DOT__s_fin) 
                     << 6U) | (((IData)(vlSelf->top__DOT__last) 
                                << 5U) | (((IData)(vlSelf->top__DOT__s_fin_in) 
                                           << 4U) | 
                                          (((IData)(vlSelf->top__DOT__src_en) 
                                            << 2U) 
                                           | (((IData)(vlSelf->top__DOT__src_ctrl__DOT__last_i) 
                                               << 1U) 
                                              | (IData)(vlSelf->top__DOT__run))))));
    if ((1U & Vtop__ConstPool__TABLE_h1f72a610_0[__Vtableidx1])) {
        vlSelf->top__DOT__s_init = Vtop__ConstPool__TABLE_hab58eb6f_0
            [__Vtableidx1];
    }
    if ((2U & Vtop__ConstPool__TABLE_h1f72a610_0[__Vtableidx1])) {
        vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo = 
            Vtop__ConstPool__TABLE_h02f8e7c9_0[__Vtableidx1];
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v0;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v1;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v2;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v3;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v4;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v5;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v6;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v7;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v8;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v9;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v10;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v11;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v12;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v13;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v14;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v15;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v16;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v17;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v18;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v19;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v20;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v21;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v22;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v23;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v24;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v25;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v26;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v27;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v28;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v29;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v30;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31) {
        vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31] 
            = __Vdlyvval__top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix__v31;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v0;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v1;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v2;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v3;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v4;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v5;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v6;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v7;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v8;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v9;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v10;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v11;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v12;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v13;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v14;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v15;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v16;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v17;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v18;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v19;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v20;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v21;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v22;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v23;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v24;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v25;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v26;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v27;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v28;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v29;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v30;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31) {
        vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31] 
            = __Vdlyvval__top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix__v31;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v0;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v1;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v2;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v3;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v4;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v5;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v6;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v7;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v8;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v9;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v10;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v11;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v12;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v13;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v14;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v15;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v16;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v17;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v18;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v19;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v20;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v21;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v22;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v23;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v24;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v25;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v26;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v27;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v28;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v29;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v30;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31) {
        vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31] 
            = __Vdlyvval__top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix__v31;
    }
    vlSelf->top__DOT__exe_ctrl__DOT__j = __Vdly__top__DOT__exe_ctrl__DOT__j;
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v0;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v1;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v2;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v3;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v4;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v5;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v6;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v7;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v8;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v9;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v10;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v11;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v12;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v13;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v14;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v15;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v16;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v17;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v18;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v19;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v20;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v21;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v22;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v23;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v24;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v25;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v26;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v27;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v28;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v29;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v30;
    }
    if (__Vdlyvset__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31) {
        vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[__Vdlyvdim0__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31] 
            = __Vdlyvval__top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix__v31;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v0) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v0] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v0;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v1) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v1] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v1;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v2) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v2] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v2;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v3) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v3] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v3;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v4) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v4] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v4;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v5) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v5] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v5;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v6) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v6] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v6;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v7) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v7] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v7;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v8) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v8] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v8;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v9) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v9] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v9;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v10) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v10] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v10;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v11) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v11] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v11;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v12) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v12] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v12;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v13) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v13] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v13;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v14) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v14] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v14;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v15) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v15] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v15;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v16) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v16] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v16;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v17) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v17] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v17;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v18) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v18] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v18;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v19) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v19] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v19;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v20) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v20] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v20;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v21) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v21] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v21;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v22) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v22] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v22;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v23) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v23] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v23;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v24) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v24] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v24;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v25) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v25] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v25;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v26) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v26] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v26;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v27) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v27] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v27;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v28) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v28] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v28;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v29) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v29] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v29;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v30) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v30] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v30;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff0__v31) {
        vlSelf->top__DOT__src_buf__DOT__buff0[__Vdlyvdim0__top__DOT__src_buf__DOT__buff0__v31] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff0__v31;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v0) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v0] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v0;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v1) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v1] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v1;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v2) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v2] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v2;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v3) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v3] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v3;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v4) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v4] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v4;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v5) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v5] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v5;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v6) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v6] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v6;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v7) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v7] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v7;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v8) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v8] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v8;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v9) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v9] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v9;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v10) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v10] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v10;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v11) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v11] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v11;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v12) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v12] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v12;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v13) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v13] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v13;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v14) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v14] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v14;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v15) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v15] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v15;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v16) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v16] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v16;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v17) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v17] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v17;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v18) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v18] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v18;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v19) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v19] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v19;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v20) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v20] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v20;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v21) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v21] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v21;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v22) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v22] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v22;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v23) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v23] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v23;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v24) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v24] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v24;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v25) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v25] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v25;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v26) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v26] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v26;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v27) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v27] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v27;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v28) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v28] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v28;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v29) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v29] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v29;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v30) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v30] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v30;
    }
    if (__Vdlyvset__top__DOT__src_buf__DOT__buff1__v31) {
        vlSelf->top__DOT__src_buf__DOT__buff1[__Vdlyvdim0__top__DOT__src_buf__DOT__buff1__v31] 
            = __Vdlyvval__top__DOT__src_buf__DOT__buff1__v31;
    }
    vlSelf->top__DOT__k_init = (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay) 
                                 | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__k_init_next)) 
                                & (~ (IData)(vlSelf->top__DOT__out_busy)));
    vlSelf->top__DOT__src_en = __Vdly__top__DOT__src_en;
    vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr 
        = (((IData)(vlSelf->top__DOT__p) << 8U) | (0xffU 
                                                   & (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                                                       << 6U) 
                                                      + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j))));
    vlSelf->top__DOT__exec = ((IData)(vlSelf->top__DOT__run) 
                              & (IData)(vlSelf->top__DOT__exe_ctrl__DOT____Vcellinp__d_exec__in));
    vlSelf->top__DOT__exe_ctrl__DOT__last_j = ((0x3fU 
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
    vlSelf->top__DOT__dst_ctrl__DOT__last_i = (((0U 
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
    vlSelf->top__DOT__src_ctrl__DOT__last_i = (((0xe0U 
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
