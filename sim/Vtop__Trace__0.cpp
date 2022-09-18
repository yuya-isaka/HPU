// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgCData(oldp+0,(vlSelf->top__DOT__mat_a),6);
        bufp->chgCData(oldp+1,(vlSelf->top__DOT__src_ctrl__DOT__i),8);
        bufp->chgCData(oldp+2,(vlSelf->top__DOT__src_en),2);
        bufp->chgBit(oldp+3,(vlSelf->top__DOT__p));
        bufp->chgBit(oldp+4,(vlSelf->top__DOT__s_init));
        bufp->chgBit(oldp+5,(vlSelf->top__DOT__s_fin));
        bufp->chgBit(oldp+6,(vlSelf->top__DOT__k_init));
        bufp->chgBit(oldp+7,(vlSelf->top__DOT__k_fin));
        bufp->chgBit(oldp+8,(vlSelf->top__DOT__exec));
        bufp->chgCData(oldp+9,((0xffU & (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                                          << 6U) + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j)))),8);
        bufp->chgCData(oldp+10,(vlSelf->top__DOT__exe_ctrl__DOT__j),6);
        bufp->chgBit(oldp+11,(vlSelf->top__DOT__out_busy));
        bufp->chgBit(oldp+12,(vlSelf->top__DOT__out_period));
        bufp->chgBit(oldp+13,(vlSelf->top__DOT__out_fin));
        bufp->chgCData(oldp+14,(vlSelf->top__DOT__out_addr),4);
        bufp->chgBit(oldp+15,(vlSelf->top__DOT__update));
        bufp->chgIData(oldp+16,(vlSelf->top__DOT__exec_src_data),32);
        bufp->chgCData(oldp+17,(vlSelf->top__DOT__dst_ctrl__DOT__i),3);
        bufp->chgIData(oldp+18,(vlSelf->top__DOT__acc[0]),32);
        bufp->chgIData(oldp+19,(vlSelf->top__DOT__acc[1]),32);
        bufp->chgIData(oldp+20,(vlSelf->top__DOT__acc[2]),32);
        bufp->chgIData(oldp+21,(vlSelf->top__DOT__acc[3]),32);
        bufp->chgIData(oldp+22,(vlSelf->top__DOT__acc[4]),32);
        bufp->chgIData(oldp+23,(vlSelf->top__DOT__acc
                                [0U]),32);
        bufp->chgCData(oldp+24,(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a),4);
        bufp->chgCData(oldp+25,(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr),5);
        bufp->chgWData(oldp+26,(vlSelf->top__DOT__dst_buf__DOT__stream_0),1024);
        bufp->chgWData(oldp+58,(vlSelf->top__DOT__dst_buf__DOT__stream_1),1024);
        bufp->chgIData(oldp+90,(vlSelf->top__DOT__dst_buf__DOT__buff0[0]),32);
        bufp->chgIData(oldp+91,(vlSelf->top__DOT__dst_buf__DOT__buff0[1]),32);
        bufp->chgIData(oldp+92,(vlSelf->top__DOT__dst_buf__DOT__buff0[2]),32);
        bufp->chgIData(oldp+93,(vlSelf->top__DOT__dst_buf__DOT__buff0[3]),32);
        bufp->chgIData(oldp+94,(vlSelf->top__DOT__dst_buf__DOT__buff0[4]),32);
        bufp->chgIData(oldp+95,(vlSelf->top__DOT__dst_buf__DOT__buff0[5]),32);
        bufp->chgIData(oldp+96,(vlSelf->top__DOT__dst_buf__DOT__buff0[6]),32);
        bufp->chgIData(oldp+97,(vlSelf->top__DOT__dst_buf__DOT__buff0[7]),32);
        bufp->chgIData(oldp+98,(vlSelf->top__DOT__dst_buf__DOT__buff1[0]),32);
        bufp->chgIData(oldp+99,(vlSelf->top__DOT__dst_buf__DOT__buff1[1]),32);
        bufp->chgIData(oldp+100,(vlSelf->top__DOT__dst_buf__DOT__buff1[2]),32);
        bufp->chgIData(oldp+101,(vlSelf->top__DOT__dst_buf__DOT__buff1[3]),32);
        bufp->chgIData(oldp+102,(vlSelf->top__DOT__dst_buf__DOT__buff1[4]),32);
        bufp->chgIData(oldp+103,(vlSelf->top__DOT__dst_buf__DOT__buff1[5]),32);
        bufp->chgIData(oldp+104,(vlSelf->top__DOT__dst_buf__DOT__buff1[6]),32);
        bufp->chgIData(oldp+105,(vlSelf->top__DOT__dst_buf__DOT__buff1[7]),32);
        bufp->chgIData(oldp+106,(vlSelf->top__DOT__dst_buf__DOT__buff2[0]),32);
        bufp->chgIData(oldp+107,(vlSelf->top__DOT__dst_buf__DOT__buff2[1]),32);
        bufp->chgIData(oldp+108,(vlSelf->top__DOT__dst_buf__DOT__buff2[2]),32);
        bufp->chgIData(oldp+109,(vlSelf->top__DOT__dst_buf__DOT__buff2[3]),32);
        bufp->chgIData(oldp+110,(vlSelf->top__DOT__dst_buf__DOT__buff2[4]),32);
        bufp->chgIData(oldp+111,(vlSelf->top__DOT__dst_buf__DOT__buff2[5]),32);
        bufp->chgIData(oldp+112,(vlSelf->top__DOT__dst_buf__DOT__buff2[6]),32);
        bufp->chgIData(oldp+113,(vlSelf->top__DOT__dst_buf__DOT__buff2[7]),32);
        bufp->chgIData(oldp+114,(vlSelf->top__DOT__dst_buf__DOT__buff3[0]),32);
        bufp->chgIData(oldp+115,(vlSelf->top__DOT__dst_buf__DOT__buff3[1]),32);
        bufp->chgIData(oldp+116,(vlSelf->top__DOT__dst_buf__DOT__buff3[2]),32);
        bufp->chgIData(oldp+117,(vlSelf->top__DOT__dst_buf__DOT__buff3[3]),32);
        bufp->chgIData(oldp+118,(vlSelf->top__DOT__dst_buf__DOT__buff3[4]),32);
        bufp->chgIData(oldp+119,(vlSelf->top__DOT__dst_buf__DOT__buff3[5]),32);
        bufp->chgIData(oldp+120,(vlSelf->top__DOT__dst_buf__DOT__buff3[6]),32);
        bufp->chgIData(oldp+121,(vlSelf->top__DOT__dst_buf__DOT__buff3[7]),32);
        bufp->chgBit(oldp+122,(vlSelf->top__DOT__dst_ctrl__DOT__start_check));
        bufp->chgBit(oldp+123,(vlSelf->top__DOT__dst_ctrl__DOT__stream_active));
        bufp->chgBit(oldp+124,(vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run));
        bufp->chgBit(oldp+125,(vlSelf->top__DOT__exe_ctrl__DOT__last_i));
        bufp->chgBit(oldp+126,(vlSelf->top__DOT__exe_ctrl__DOT__last_j));
        bufp->chgBit(oldp+127,(((IData)(vlSelf->top__DOT__s_init) 
                                | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre))));
        bufp->chgBit(oldp+128,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                                | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))));
        bufp->chgCData(oldp+129,(vlSelf->top__DOT__exe_ctrl__DOT__i),2);
        bufp->chgBit(oldp+130,(vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay));
        bufp->chgBit(oldp+131,(vlSelf->top__DOT__exe_ctrl__DOT__k_init_next));
        bufp->chgBit(oldp+132,(vlSelf->top__DOT__exe_ctrl__DOT__start));
        bufp->chgBit(oldp+133,(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period));
        bufp->chgBit(oldp+134,(((IData)(vlSelf->top__DOT__k_init) 
                                | ((IData)(vlSelf->top__DOT__exec) 
                                   & (~ (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j))))));
        bufp->chgBit(oldp+135,((((IData)(vlSelf->top__DOT__s_init) 
                                 | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre)) 
                                & (~ (IData)(vlSelf->top__DOT__s_init)))));
        bufp->chgBit(oldp+136,((1U & ((~ (IData)(vlSelf->top__DOT__out_busy)) 
                                      | ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                                         | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))))));
        bufp->chgBit(oldp+137,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period) 
                                & (IData)(vlSelf->top__DOT__out_fin))));
        bufp->chgBit(oldp+138,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_i) 
                                | (IData)(vlSelf->top__DOT__out_fin))));
        bufp->chgBit(oldp+139,(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre));
        bufp->chgBit(oldp+140,(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run));
        bufp->chgBit(oldp+141,(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre));
        bufp->chgBit(oldp+142,(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run));
        bufp->chgIData(oldp+143,(vlSelf->top__DOT__acc
                                 [1U]),32);
        bufp->chgIData(oldp+144,(((IData)(vlSelf->top__DOT__update)
                                   ? vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left
                                   : vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right)),32);
        bufp->chgIData(oldp+145,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data),32);
        bufp->chgIData(oldp+146,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right),32);
        bufp->chgIData(oldp+147,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left),32);
        bufp->chgBit(oldp+148,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next));
        bufp->chgBit(oldp+149,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next));
        bufp->chgBit(oldp+150,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next));
        bufp->chgBit(oldp+151,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next));
        bufp->chgIData(oldp+152,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2),32);
        bufp->chgIData(oldp+153,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2),32);
        bufp->chgIData(oldp+154,(vlSelf->top__DOT__acc
                                 [2U]),32);
        bufp->chgIData(oldp+155,(((IData)(vlSelf->top__DOT__update)
                                   ? vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left
                                   : vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right)),32);
        bufp->chgIData(oldp+156,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data),32);
        bufp->chgIData(oldp+157,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right),32);
        bufp->chgIData(oldp+158,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left),32);
        bufp->chgBit(oldp+159,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next));
        bufp->chgBit(oldp+160,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next));
        bufp->chgBit(oldp+161,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next));
        bufp->chgBit(oldp+162,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next));
        bufp->chgIData(oldp+163,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2),32);
        bufp->chgIData(oldp+164,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2),32);
        bufp->chgIData(oldp+165,(vlSelf->top__DOT__acc
                                 [3U]),32);
        bufp->chgIData(oldp+166,(((IData)(vlSelf->top__DOT__update)
                                   ? vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left
                                   : vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right)),32);
        bufp->chgIData(oldp+167,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data),32);
        bufp->chgIData(oldp+168,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right),32);
        bufp->chgIData(oldp+169,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left),32);
        bufp->chgBit(oldp+170,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next));
        bufp->chgBit(oldp+171,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next));
        bufp->chgBit(oldp+172,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next));
        bufp->chgBit(oldp+173,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next));
        bufp->chgIData(oldp+174,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2),32);
        bufp->chgIData(oldp+175,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2),32);
        bufp->chgIData(oldp+176,(vlSelf->top__DOT__acc
                                 [4U]),32);
        bufp->chgIData(oldp+177,(((IData)(vlSelf->top__DOT__update)
                                   ? vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left
                                   : vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right)),32);
        bufp->chgIData(oldp+178,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data),32);
        bufp->chgIData(oldp+179,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right),32);
        bufp->chgIData(oldp+180,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left),32);
        bufp->chgBit(oldp+181,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next));
        bufp->chgBit(oldp+182,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next));
        bufp->chgBit(oldp+183,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next));
        bufp->chgBit(oldp+184,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next));
        bufp->chgIData(oldp+185,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2),32);
        bufp->chgIData(oldp+186,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2),32);
        bufp->chgCData(oldp+187,(vlSelf->top__DOT__mat_ctrl__DOT__core_sel),2);
        bufp->chgCData(oldp+188,(vlSelf->top__DOT__out_ctrl__DOT__out_addr_pre),4);
        bufp->chgBit(oldp+189,((((3U == (IData)(vlSelf->top__DOT__out_ctrl__DOT__i)) 
                                 & ((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run) 
                                    | (IData)(vlSelf->top__DOT__s_init))) 
                                & (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))));
        bufp->chgBit(oldp+190,(vlSelf->top__DOT__out_ctrl__DOT__last_j));
        bufp->chgCData(oldp+191,(vlSelf->top__DOT__out_ctrl__DOT__i),2);
        bufp->chgCData(oldp+192,(vlSelf->top__DOT__out_ctrl__DOT__j),2);
        bufp->chgBit(oldp+193,(vlSelf->top__DOT__out_ctrl__DOT__last_j_next));
        bufp->chgBit(oldp+194,(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre));
        bufp->chgBit(oldp+195,(vlSelf->top__DOT__out_ctrl__DOT__update_after_start));
        bufp->chgBit(oldp+196,(vlSelf->top__DOT__out_ctrl__DOT__start));
        bufp->chgBit(oldp+197,(vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention));
        bufp->chgBit(oldp+198,(vlSelf->top__DOT__out_ctrl__DOT__j_period));
        bufp->chgBit(oldp+199,(((IData)(vlSelf->top__DOT__out_ctrl__DOT__start) 
                                | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))));
        bufp->chgBit(oldp+200,(((IData)(vlSelf->top__DOT__k_init) 
                                & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre))));
        bufp->chgBit(oldp+201,((((IData)(vlSelf->top__DOT__k_init) 
                                 & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre)) 
                                | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))));
        bufp->chgBit(oldp+202,(((IData)(vlSelf->top__DOT__k_fin) 
                                & (IData)(vlSelf->top__DOT__out_busy))));
        bufp->chgBit(oldp+203,((((IData)(vlSelf->top__DOT__k_fin) 
                                 & (IData)(vlSelf->top__DOT__out_busy)) 
                                | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))));
        bufp->chgBit(oldp+204,(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run));
        bufp->chgBit(oldp+205,(vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run));
        bufp->chgBit(oldp+206,(vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo));
        bufp->chgSData(oldp+207,(vlSelf->top__DOT____Vcellinp__src_buf__src_a),9);
        bufp->chgSData(oldp+208,(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr),9);
        bufp->chgBit(oldp+209,(vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run));
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgBit(oldp+210,(vlSelf->top__DOT__run));
        bufp->chgBit(oldp+211,(vlSelf->top__DOT__matw));
        bufp->chgBit(oldp+212,(vlSelf->top__DOT__last));
        bufp->chgCData(oldp+213,(vlSelf->top__DOT__state),4);
        bufp->chgSData(oldp+214,(vlSelf->top__DOT__write_addr),10);
        bufp->chgSData(oldp+215,(vlSelf->top__DOT__read_addr),10);
        bufp->chgIData(oldp+216,(vlSelf->top__DOT__write_data),32);
        bufp->chgBit(oldp+217,((0U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+218,((1U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+219,((2U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+220,((3U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+221,((4U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+222,((8U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgIData(oldp+223,(vlSelf->top__DOT__control),32);
        bufp->chgBit(oldp+224,(vlSelf->top__DOT__register_w));
        bufp->chgBit(oldp+225,((IData)(((4U == (IData)(vlSelf->top__DOT__state)) 
                                        & (0U == (0x300U 
                                                  & (IData)(vlSelf->top__DOT__read_addr)))))));
        bufp->chgBit(oldp+226,((1U & (~ (IData)(vlSelf->top__DOT__run)))));
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[3U])) {
        bufp->chgCData(oldp+227,(vlSelf->top__DOT__mat_v),4);
        bufp->chgBit(oldp+228,(vlSelf->top__DOT__src_ctrl__DOT__start));
        bufp->chgBit(oldp+229,(vlSelf->top__DOT__src_ctrl__DOT__last_i));
        bufp->chgBit(oldp+230,(vlSelf->top__DOT__s_fin_in));
        bufp->chgBit(oldp+231,(vlSelf->top__DOT__stream_v));
        bufp->chgBit(oldp+232,(vlSelf->top__DOT__dst_ctrl__DOT__last_i));
        bufp->chgBit(oldp+233,(vlSelf->top__DOT__dst_ctrl__DOT__start));
        bufp->chgBit(oldp+234,((1U & (IData)(vlSelf->top__DOT__mat_v))));
        bufp->chgBit(oldp+235,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                      >> 1U))));
        bufp->chgBit(oldp+236,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                      >> 2U))));
        bufp->chgBit(oldp+237,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                      >> 3U))));
        bufp->chgBit(oldp+238,(vlSelf->top__DOT__src_ctrl__DOT__sen));
    }
    bufp->chgBit(oldp+239,(vlSelf->S_AXI_ACLK));
    bufp->chgBit(oldp+240,(vlSelf->S_AXI_ARESETN));
    bufp->chgIData(oldp+241,(vlSelf->S_AXI_AWADDR),32);
    bufp->chgBit(oldp+242,(vlSelf->S_AXI_AWVALID));
    bufp->chgBit(oldp+243,(vlSelf->S_AXI_AWREADY));
    bufp->chgIData(oldp+244,(vlSelf->S_AXI_WDATA),32);
    bufp->chgCData(oldp+245,(vlSelf->S_AXI_WSTRB),4);
    bufp->chgBit(oldp+246,(vlSelf->S_AXI_WVALID));
    bufp->chgBit(oldp+247,(vlSelf->S_AXI_WREADY));
    bufp->chgCData(oldp+248,(vlSelf->S_AXI_BRESP),2);
    bufp->chgBit(oldp+249,(vlSelf->S_AXI_BVALID));
    bufp->chgBit(oldp+250,(vlSelf->S_AXI_BREADY));
    bufp->chgIData(oldp+251,(vlSelf->S_AXI_ARADDR),32);
    bufp->chgBit(oldp+252,(vlSelf->S_AXI_ARVALID));
    bufp->chgBit(oldp+253,(vlSelf->S_AXI_ARREADY));
    bufp->chgIData(oldp+254,(vlSelf->S_AXI_RDATA),32);
    bufp->chgCData(oldp+255,(vlSelf->S_AXI_RRESP),2);
    bufp->chgBit(oldp+256,(vlSelf->S_AXI_RVALID));
    bufp->chgBit(oldp+257,(vlSelf->S_AXI_RREADY));
    bufp->chgBit(oldp+258,(vlSelf->AXIS_ACLK));
    bufp->chgBit(oldp+259,(vlSelf->AXIS_ARESETN));
    bufp->chgBit(oldp+260,(vlSelf->M_AXIS_TVALID));
    bufp->chgWData(oldp+261,(vlSelf->M_AXIS_TDATA),1024);
    bufp->chgCData(oldp+293,(vlSelf->M_AXIS_TSTRB),8);
    bufp->chgBit(oldp+294,(vlSelf->M_AXIS_TLAST));
    bufp->chgBit(oldp+295,(vlSelf->M_AXIS_TREADY));
    bufp->chgBit(oldp+296,(vlSelf->S_AXIS_TREADY));
    bufp->chgWData(oldp+297,(vlSelf->S_AXIS_TDATA),1024);
    bufp->chgCData(oldp+329,(vlSelf->S_AXIS_TSTRB),8);
    bufp->chgBit(oldp+330,(vlSelf->S_AXIS_TLAST));
    bufp->chgBit(oldp+331,(vlSelf->S_AXIS_TVALID));
    bufp->chgBit(oldp+332,((((IData)(vlSelf->top__DOT__s_fin_in) 
                             | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__stream_active)) 
                            & (~ (IData)(vlSelf->top__DOT__dst_ctrl__DOT__last_i)))));
    bufp->chgBit(oldp+333,((1U & (~ (IData)(vlSelf->AXIS_ARESETN)))));
    bufp->chgBit(oldp+334,((1U & ((~ (IData)(vlSelf->S_AXIS_TREADY)) 
                                  | (~ (IData)(vlSelf->top__DOT__run))))));
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
