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
        bufp->chgCData(oldp+0,(vlSelf->top__DOT__mat_a),3);
        bufp->chgCData(oldp+1,(vlSelf->top__DOT__src_ctrl__DOT__i),4);
        bufp->chgCData(oldp+2,(vlSelf->top__DOT__src_en),2);
        bufp->chgBit(oldp+3,(vlSelf->top__DOT__p));
        bufp->chgBit(oldp+4,(vlSelf->top__DOT__s_init));
        bufp->chgBit(oldp+5,(vlSelf->top__DOT__s_fin));
        bufp->chgBit(oldp+6,(vlSelf->top__DOT__k_init));
        bufp->chgBit(oldp+7,(vlSelf->top__DOT__k_fin));
        bufp->chgBit(oldp+8,(vlSelf->top__DOT__exec));
        bufp->chgCData(oldp+9,((0x1fU & (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                                          << 3U) + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j)))),5);
        bufp->chgCData(oldp+10,(vlSelf->top__DOT__exe_ctrl__DOT__j),3);
        bufp->chgBit(oldp+11,(vlSelf->top__DOT__out_busy));
        bufp->chgBit(oldp+12,(vlSelf->top__DOT__out_period));
        bufp->chgBit(oldp+13,(vlSelf->top__DOT__out_fin));
        bufp->chgCData(oldp+14,(vlSelf->top__DOT__out_addr),4);
        bufp->chgBit(oldp+15,(vlSelf->top__DOT__sum_update));
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
        bufp->chgQData(oldp+26,(vlSelf->top__DOT__dst_buf__DOT__stream_0),64);
        bufp->chgQData(oldp+28,(vlSelf->top__DOT__dst_buf__DOT__stream_1),64);
        bufp->chgIData(oldp+30,(vlSelf->top__DOT__dst_buf__DOT__buff0[0]),32);
        bufp->chgIData(oldp+31,(vlSelf->top__DOT__dst_buf__DOT__buff0[1]),32);
        bufp->chgIData(oldp+32,(vlSelf->top__DOT__dst_buf__DOT__buff0[2]),32);
        bufp->chgIData(oldp+33,(vlSelf->top__DOT__dst_buf__DOT__buff0[3]),32);
        bufp->chgIData(oldp+34,(vlSelf->top__DOT__dst_buf__DOT__buff0[4]),32);
        bufp->chgIData(oldp+35,(vlSelf->top__DOT__dst_buf__DOT__buff0[5]),32);
        bufp->chgIData(oldp+36,(vlSelf->top__DOT__dst_buf__DOT__buff0[6]),32);
        bufp->chgIData(oldp+37,(vlSelf->top__DOT__dst_buf__DOT__buff0[7]),32);
        bufp->chgIData(oldp+38,(vlSelf->top__DOT__dst_buf__DOT__buff1[0]),32);
        bufp->chgIData(oldp+39,(vlSelf->top__DOT__dst_buf__DOT__buff1[1]),32);
        bufp->chgIData(oldp+40,(vlSelf->top__DOT__dst_buf__DOT__buff1[2]),32);
        bufp->chgIData(oldp+41,(vlSelf->top__DOT__dst_buf__DOT__buff1[3]),32);
        bufp->chgIData(oldp+42,(vlSelf->top__DOT__dst_buf__DOT__buff1[4]),32);
        bufp->chgIData(oldp+43,(vlSelf->top__DOT__dst_buf__DOT__buff1[5]),32);
        bufp->chgIData(oldp+44,(vlSelf->top__DOT__dst_buf__DOT__buff1[6]),32);
        bufp->chgIData(oldp+45,(vlSelf->top__DOT__dst_buf__DOT__buff1[7]),32);
        bufp->chgIData(oldp+46,(vlSelf->top__DOT__dst_buf__DOT__buff2[0]),32);
        bufp->chgIData(oldp+47,(vlSelf->top__DOT__dst_buf__DOT__buff2[1]),32);
        bufp->chgIData(oldp+48,(vlSelf->top__DOT__dst_buf__DOT__buff2[2]),32);
        bufp->chgIData(oldp+49,(vlSelf->top__DOT__dst_buf__DOT__buff2[3]),32);
        bufp->chgIData(oldp+50,(vlSelf->top__DOT__dst_buf__DOT__buff2[4]),32);
        bufp->chgIData(oldp+51,(vlSelf->top__DOT__dst_buf__DOT__buff2[5]),32);
        bufp->chgIData(oldp+52,(vlSelf->top__DOT__dst_buf__DOT__buff2[6]),32);
        bufp->chgIData(oldp+53,(vlSelf->top__DOT__dst_buf__DOT__buff2[7]),32);
        bufp->chgIData(oldp+54,(vlSelf->top__DOT__dst_buf__DOT__buff3[0]),32);
        bufp->chgIData(oldp+55,(vlSelf->top__DOT__dst_buf__DOT__buff3[1]),32);
        bufp->chgIData(oldp+56,(vlSelf->top__DOT__dst_buf__DOT__buff3[2]),32);
        bufp->chgIData(oldp+57,(vlSelf->top__DOT__dst_buf__DOT__buff3[3]),32);
        bufp->chgIData(oldp+58,(vlSelf->top__DOT__dst_buf__DOT__buff3[4]),32);
        bufp->chgIData(oldp+59,(vlSelf->top__DOT__dst_buf__DOT__buff3[5]),32);
        bufp->chgIData(oldp+60,(vlSelf->top__DOT__dst_buf__DOT__buff3[6]),32);
        bufp->chgIData(oldp+61,(vlSelf->top__DOT__dst_buf__DOT__buff3[7]),32);
        bufp->chgBit(oldp+62,(vlSelf->top__DOT__dst_ctrl__DOT__start_check));
        bufp->chgBit(oldp+63,(vlSelf->top__DOT__dst_ctrl__DOT__stream_active));
        bufp->chgBit(oldp+64,(vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run));
        bufp->chgBit(oldp+65,(vlSelf->top__DOT__exe_ctrl__DOT__last_i));
        bufp->chgBit(oldp+66,(vlSelf->top__DOT__exe_ctrl__DOT__last_j));
        bufp->chgBit(oldp+67,(((IData)(vlSelf->top__DOT__s_init) 
                               | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre))));
        bufp->chgBit(oldp+68,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                               | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))));
        bufp->chgCData(oldp+69,(vlSelf->top__DOT__exe_ctrl__DOT__i),2);
        bufp->chgBit(oldp+70,(vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay));
        bufp->chgBit(oldp+71,(vlSelf->top__DOT__exe_ctrl__DOT__k_init_next));
        bufp->chgBit(oldp+72,(vlSelf->top__DOT__exe_ctrl__DOT__start));
        bufp->chgBit(oldp+73,(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period));
        bufp->chgBit(oldp+74,(((IData)(vlSelf->top__DOT__k_init) 
                               | ((IData)(vlSelf->top__DOT__exec) 
                                  & (~ (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j))))));
        bufp->chgBit(oldp+75,((((IData)(vlSelf->top__DOT__s_init) 
                                | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre)) 
                               & (~ (IData)(vlSelf->top__DOT__s_init)))));
        bufp->chgBit(oldp+76,((1U & ((~ (IData)(vlSelf->top__DOT__out_busy)) 
                                     | ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                                        | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))))));
        bufp->chgBit(oldp+77,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period) 
                               & (IData)(vlSelf->top__DOT__out_fin))));
        bufp->chgBit(oldp+78,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_i) 
                               | (IData)(vlSelf->top__DOT__out_fin))));
        bufp->chgBit(oldp+79,(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre));
        bufp->chgBit(oldp+80,(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run));
        bufp->chgBit(oldp+81,(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre));
        bufp->chgBit(oldp+82,(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run));
        bufp->chgIData(oldp+83,(vlSelf->top__DOT__acc
                                [1U]),32);
        bufp->chgIData(oldp+84,(((IData)(vlSelf->top__DOT__sum_update)
                                  ? vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left
                                  : vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right)),32);
        bufp->chgIData(oldp+85,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[0]),32);
        bufp->chgIData(oldp+86,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[1]),32);
        bufp->chgIData(oldp+87,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[2]),32);
        bufp->chgIData(oldp+88,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[3]),32);
        bufp->chgIData(oldp+89,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[4]),32);
        bufp->chgIData(oldp+90,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[5]),32);
        bufp->chgIData(oldp+91,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[6]),32);
        bufp->chgIData(oldp+92,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[7]),32);
        bufp->chgIData(oldp+93,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data),32);
        bufp->chgIData(oldp+94,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right),32);
        bufp->chgIData(oldp+95,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left),32);
        bufp->chgBit(oldp+96,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next));
        bufp->chgBit(oldp+97,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next));
        bufp->chgBit(oldp+98,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next));
        bufp->chgBit(oldp+99,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next));
        bufp->chgIData(oldp+100,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2),32);
        bufp->chgIData(oldp+101,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2),32);
        bufp->chgIData(oldp+102,(vlSelf->top__DOT__acc
                                 [2U]),32);
        bufp->chgIData(oldp+103,(((IData)(vlSelf->top__DOT__sum_update)
                                   ? vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left
                                   : vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right)),32);
        bufp->chgIData(oldp+104,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[0]),32);
        bufp->chgIData(oldp+105,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[1]),32);
        bufp->chgIData(oldp+106,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[2]),32);
        bufp->chgIData(oldp+107,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[3]),32);
        bufp->chgIData(oldp+108,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[4]),32);
        bufp->chgIData(oldp+109,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[5]),32);
        bufp->chgIData(oldp+110,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[6]),32);
        bufp->chgIData(oldp+111,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[7]),32);
        bufp->chgIData(oldp+112,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data),32);
        bufp->chgIData(oldp+113,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right),32);
        bufp->chgIData(oldp+114,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left),32);
        bufp->chgBit(oldp+115,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next));
        bufp->chgBit(oldp+116,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next));
        bufp->chgBit(oldp+117,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next));
        bufp->chgBit(oldp+118,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next));
        bufp->chgIData(oldp+119,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2),32);
        bufp->chgIData(oldp+120,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2),32);
        bufp->chgIData(oldp+121,(vlSelf->top__DOT__acc
                                 [3U]),32);
        bufp->chgIData(oldp+122,(((IData)(vlSelf->top__DOT__sum_update)
                                   ? vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left
                                   : vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right)),32);
        bufp->chgIData(oldp+123,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[0]),32);
        bufp->chgIData(oldp+124,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[1]),32);
        bufp->chgIData(oldp+125,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[2]),32);
        bufp->chgIData(oldp+126,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[3]),32);
        bufp->chgIData(oldp+127,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[4]),32);
        bufp->chgIData(oldp+128,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[5]),32);
        bufp->chgIData(oldp+129,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[6]),32);
        bufp->chgIData(oldp+130,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[7]),32);
        bufp->chgIData(oldp+131,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data),32);
        bufp->chgIData(oldp+132,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right),32);
        bufp->chgIData(oldp+133,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left),32);
        bufp->chgBit(oldp+134,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next));
        bufp->chgBit(oldp+135,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next));
        bufp->chgBit(oldp+136,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next));
        bufp->chgBit(oldp+137,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next));
        bufp->chgIData(oldp+138,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2),32);
        bufp->chgIData(oldp+139,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2),32);
        bufp->chgIData(oldp+140,(vlSelf->top__DOT__acc
                                 [4U]),32);
        bufp->chgIData(oldp+141,(((IData)(vlSelf->top__DOT__sum_update)
                                   ? vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left
                                   : vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right)),32);
        bufp->chgIData(oldp+142,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[0]),32);
        bufp->chgIData(oldp+143,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[1]),32);
        bufp->chgIData(oldp+144,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[2]),32);
        bufp->chgIData(oldp+145,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[3]),32);
        bufp->chgIData(oldp+146,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[4]),32);
        bufp->chgIData(oldp+147,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[5]),32);
        bufp->chgIData(oldp+148,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[6]),32);
        bufp->chgIData(oldp+149,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[7]),32);
        bufp->chgIData(oldp+150,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data),32);
        bufp->chgIData(oldp+151,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right),32);
        bufp->chgIData(oldp+152,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left),32);
        bufp->chgBit(oldp+153,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next));
        bufp->chgBit(oldp+154,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next));
        bufp->chgBit(oldp+155,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next));
        bufp->chgBit(oldp+156,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next));
        bufp->chgIData(oldp+157,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2),32);
        bufp->chgIData(oldp+158,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2),32);
        bufp->chgCData(oldp+159,(vlSelf->top__DOT__mat_ctrl__DOT__core_sel),2);
        bufp->chgCData(oldp+160,(vlSelf->top__DOT__out_ctrl__DOT__out_addr_pre),4);
        bufp->chgBit(oldp+161,((((3U == (IData)(vlSelf->top__DOT__out_ctrl__DOT__i)) 
                                 & ((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run) 
                                    | (IData)(vlSelf->top__DOT__s_init))) 
                                & (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))));
        bufp->chgBit(oldp+162,(vlSelf->top__DOT__out_ctrl__DOT__last_j));
        bufp->chgCData(oldp+163,(vlSelf->top__DOT__out_ctrl__DOT__i),2);
        bufp->chgCData(oldp+164,(vlSelf->top__DOT__out_ctrl__DOT__j),2);
        bufp->chgBit(oldp+165,(vlSelf->top__DOT__out_ctrl__DOT__last_j_next));
        bufp->chgBit(oldp+166,(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre));
        bufp->chgBit(oldp+167,(vlSelf->top__DOT__out_ctrl__DOT__update_after_start));
        bufp->chgBit(oldp+168,(vlSelf->top__DOT__out_ctrl__DOT__start));
        bufp->chgBit(oldp+169,(vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention));
        bufp->chgBit(oldp+170,(vlSelf->top__DOT__out_ctrl__DOT__j_period));
        bufp->chgBit(oldp+171,(((IData)(vlSelf->top__DOT__out_ctrl__DOT__start) 
                                | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))));
        bufp->chgBit(oldp+172,(((IData)(vlSelf->top__DOT__k_init) 
                                & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre))));
        bufp->chgBit(oldp+173,((((IData)(vlSelf->top__DOT__k_init) 
                                 & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre)) 
                                | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))));
        bufp->chgBit(oldp+174,(((IData)(vlSelf->top__DOT__k_fin) 
                                & (IData)(vlSelf->top__DOT__out_busy))));
        bufp->chgBit(oldp+175,((((IData)(vlSelf->top__DOT__k_fin) 
                                 & (IData)(vlSelf->top__DOT__out_busy)) 
                                | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))));
        bufp->chgBit(oldp+176,(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run));
        bufp->chgBit(oldp+177,(vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run));
        bufp->chgBit(oldp+178,(vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo));
        bufp->chgCData(oldp+179,(vlSelf->top__DOT____Vcellinp__src_buf__src_a),5);
        bufp->chgCData(oldp+180,(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr),6);
        bufp->chgQData(oldp+181,(vlSelf->top__DOT__src_buf__DOT__buff0[0]),64);
        bufp->chgQData(oldp+183,(vlSelf->top__DOT__src_buf__DOT__buff0[1]),64);
        bufp->chgQData(oldp+185,(vlSelf->top__DOT__src_buf__DOT__buff0[2]),64);
        bufp->chgQData(oldp+187,(vlSelf->top__DOT__src_buf__DOT__buff0[3]),64);
        bufp->chgQData(oldp+189,(vlSelf->top__DOT__src_buf__DOT__buff0[4]),64);
        bufp->chgQData(oldp+191,(vlSelf->top__DOT__src_buf__DOT__buff0[5]),64);
        bufp->chgQData(oldp+193,(vlSelf->top__DOT__src_buf__DOT__buff0[6]),64);
        bufp->chgQData(oldp+195,(vlSelf->top__DOT__src_buf__DOT__buff0[7]),64);
        bufp->chgQData(oldp+197,(vlSelf->top__DOT__src_buf__DOT__buff0[8]),64);
        bufp->chgQData(oldp+199,(vlSelf->top__DOT__src_buf__DOT__buff0[9]),64);
        bufp->chgQData(oldp+201,(vlSelf->top__DOT__src_buf__DOT__buff0[10]),64);
        bufp->chgQData(oldp+203,(vlSelf->top__DOT__src_buf__DOT__buff0[11]),64);
        bufp->chgQData(oldp+205,(vlSelf->top__DOT__src_buf__DOT__buff0[12]),64);
        bufp->chgQData(oldp+207,(vlSelf->top__DOT__src_buf__DOT__buff0[13]),64);
        bufp->chgQData(oldp+209,(vlSelf->top__DOT__src_buf__DOT__buff0[14]),64);
        bufp->chgQData(oldp+211,(vlSelf->top__DOT__src_buf__DOT__buff0[15]),64);
        bufp->chgQData(oldp+213,(vlSelf->top__DOT__src_buf__DOT__wd0),64);
        bufp->chgQData(oldp+215,(vlSelf->top__DOT__src_buf__DOT__buff1[0]),64);
        bufp->chgQData(oldp+217,(vlSelf->top__DOT__src_buf__DOT__buff1[1]),64);
        bufp->chgQData(oldp+219,(vlSelf->top__DOT__src_buf__DOT__buff1[2]),64);
        bufp->chgQData(oldp+221,(vlSelf->top__DOT__src_buf__DOT__buff1[3]),64);
        bufp->chgQData(oldp+223,(vlSelf->top__DOT__src_buf__DOT__buff1[4]),64);
        bufp->chgQData(oldp+225,(vlSelf->top__DOT__src_buf__DOT__buff1[5]),64);
        bufp->chgQData(oldp+227,(vlSelf->top__DOT__src_buf__DOT__buff1[6]),64);
        bufp->chgQData(oldp+229,(vlSelf->top__DOT__src_buf__DOT__buff1[7]),64);
        bufp->chgQData(oldp+231,(vlSelf->top__DOT__src_buf__DOT__buff1[8]),64);
        bufp->chgQData(oldp+233,(vlSelf->top__DOT__src_buf__DOT__buff1[9]),64);
        bufp->chgQData(oldp+235,(vlSelf->top__DOT__src_buf__DOT__buff1[10]),64);
        bufp->chgQData(oldp+237,(vlSelf->top__DOT__src_buf__DOT__buff1[11]),64);
        bufp->chgQData(oldp+239,(vlSelf->top__DOT__src_buf__DOT__buff1[12]),64);
        bufp->chgQData(oldp+241,(vlSelf->top__DOT__src_buf__DOT__buff1[13]),64);
        bufp->chgQData(oldp+243,(vlSelf->top__DOT__src_buf__DOT__buff1[14]),64);
        bufp->chgQData(oldp+245,(vlSelf->top__DOT__src_buf__DOT__buff1[15]),64);
        bufp->chgQData(oldp+247,(vlSelf->top__DOT__src_buf__DOT__wd1),64);
        bufp->chgCData(oldp+249,(vlSelf->top__DOT__src_buf__DOT__ia_),2);
        bufp->chgBit(oldp+250,(vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run));
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgBit(oldp+251,(vlSelf->top__DOT__run));
        bufp->chgBit(oldp+252,(vlSelf->top__DOT__matw));
        bufp->chgBit(oldp+253,(vlSelf->top__DOT__last));
        bufp->chgCData(oldp+254,(vlSelf->top__DOT__state),4);
        bufp->chgSData(oldp+255,(vlSelf->top__DOT__write_addr),10);
        bufp->chgSData(oldp+256,(vlSelf->top__DOT__read_addr),10);
        bufp->chgIData(oldp+257,(vlSelf->top__DOT__write_data),32);
        bufp->chgBit(oldp+258,((0U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+259,((1U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+260,((2U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+261,((3U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+262,((4U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgBit(oldp+263,((8U == (IData)(vlSelf->top__DOT__state))));
        bufp->chgIData(oldp+264,(vlSelf->top__DOT__control),32);
        bufp->chgBit(oldp+265,(vlSelf->top__DOT__register_w));
        bufp->chgBit(oldp+266,((IData)(((4U == (IData)(vlSelf->top__DOT__state)) 
                                        & (0U == (0x300U 
                                                  & (IData)(vlSelf->top__DOT__read_addr)))))));
        bufp->chgBit(oldp+267,((1U & (~ (IData)(vlSelf->top__DOT__run)))));
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[3U])) {
        bufp->chgCData(oldp+268,(vlSelf->top__DOT__mat_v),4);
        bufp->chgBit(oldp+269,(vlSelf->top__DOT__src_ctrl__DOT__start));
        bufp->chgBit(oldp+270,(vlSelf->top__DOT__src_ctrl__DOT__last_i));
        bufp->chgBit(oldp+271,(vlSelf->top__DOT__s_fin_in));
        bufp->chgBit(oldp+272,(vlSelf->top__DOT__stream_v));
        bufp->chgBit(oldp+273,(vlSelf->top__DOT__dst_ctrl__DOT__last_i));
        bufp->chgBit(oldp+274,(vlSelf->top__DOT__dst_ctrl__DOT__start));
        bufp->chgBit(oldp+275,((1U & (IData)(vlSelf->top__DOT__mat_v))));
        bufp->chgBit(oldp+276,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                      >> 1U))));
        bufp->chgBit(oldp+277,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                      >> 2U))));
        bufp->chgBit(oldp+278,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                      >> 3U))));
        bufp->chgBit(oldp+279,(vlSelf->top__DOT__src_ctrl__DOT__sen));
    }
    bufp->chgBit(oldp+280,(vlSelf->S_AXI_ACLK));
    bufp->chgBit(oldp+281,(vlSelf->S_AXI_ARESETN));
    bufp->chgIData(oldp+282,(vlSelf->S_AXI_AWADDR),32);
    bufp->chgBit(oldp+283,(vlSelf->S_AXI_AWVALID));
    bufp->chgBit(oldp+284,(vlSelf->S_AXI_AWREADY));
    bufp->chgIData(oldp+285,(vlSelf->S_AXI_WDATA),32);
    bufp->chgCData(oldp+286,(vlSelf->S_AXI_WSTRB),4);
    bufp->chgBit(oldp+287,(vlSelf->S_AXI_WVALID));
    bufp->chgBit(oldp+288,(vlSelf->S_AXI_WREADY));
    bufp->chgCData(oldp+289,(vlSelf->S_AXI_BRESP),2);
    bufp->chgBit(oldp+290,(vlSelf->S_AXI_BVALID));
    bufp->chgBit(oldp+291,(vlSelf->S_AXI_BREADY));
    bufp->chgIData(oldp+292,(vlSelf->S_AXI_ARADDR),32);
    bufp->chgBit(oldp+293,(vlSelf->S_AXI_ARVALID));
    bufp->chgBit(oldp+294,(vlSelf->S_AXI_ARREADY));
    bufp->chgIData(oldp+295,(vlSelf->S_AXI_RDATA),32);
    bufp->chgCData(oldp+296,(vlSelf->S_AXI_RRESP),2);
    bufp->chgBit(oldp+297,(vlSelf->S_AXI_RVALID));
    bufp->chgBit(oldp+298,(vlSelf->S_AXI_RREADY));
    bufp->chgBit(oldp+299,(vlSelf->AXIS_ACLK));
    bufp->chgBit(oldp+300,(vlSelf->AXIS_ARESETN));
    bufp->chgBit(oldp+301,(vlSelf->M_AXIS_TVALID));
    bufp->chgQData(oldp+302,(vlSelf->M_AXIS_TDATA),64);
    bufp->chgCData(oldp+304,(vlSelf->M_AXIS_TSTRB),8);
    bufp->chgBit(oldp+305,(vlSelf->M_AXIS_TLAST));
    bufp->chgBit(oldp+306,(vlSelf->M_AXIS_TREADY));
    bufp->chgBit(oldp+307,(vlSelf->S_AXIS_TREADY));
    bufp->chgQData(oldp+308,(vlSelf->S_AXIS_TDATA),64);
    bufp->chgCData(oldp+310,(vlSelf->S_AXIS_TSTRB),8);
    bufp->chgBit(oldp+311,(vlSelf->S_AXIS_TLAST));
    bufp->chgBit(oldp+312,(vlSelf->S_AXIS_TVALID));
    bufp->chgBit(oldp+313,((((IData)(vlSelf->top__DOT__s_fin_in) 
                             | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__stream_active)) 
                            & (~ (IData)(vlSelf->top__DOT__dst_ctrl__DOT__last_i)))));
    bufp->chgIData(oldp+314,((IData)(vlSelf->S_AXIS_TDATA)),32);
    bufp->chgBit(oldp+315,((1U & (~ (IData)(vlSelf->AXIS_ARESETN)))));
    bufp->chgBit(oldp+316,((1U & ((~ (IData)(vlSelf->S_AXIS_TREADY)) 
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
