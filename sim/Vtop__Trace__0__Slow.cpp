// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+281,"S_AXI_ACLK", false,-1);
    tracep->declBit(c+282,"S_AXI_ARESETN", false,-1);
    tracep->declBus(c+283,"S_AXI_AWADDR", false,-1, 31,0);
    tracep->declBit(c+284,"S_AXI_AWVALID", false,-1);
    tracep->declBit(c+285,"S_AXI_AWREADY", false,-1);
    tracep->declBus(c+286,"S_AXI_WDATA", false,-1, 31,0);
    tracep->declBus(c+287,"S_AXI_WSTRB", false,-1, 3,0);
    tracep->declBit(c+288,"S_AXI_WVALID", false,-1);
    tracep->declBit(c+289,"S_AXI_WREADY", false,-1);
    tracep->declBus(c+290,"S_AXI_BRESP", false,-1, 1,0);
    tracep->declBit(c+291,"S_AXI_BVALID", false,-1);
    tracep->declBit(c+292,"S_AXI_BREADY", false,-1);
    tracep->declBus(c+293,"S_AXI_ARADDR", false,-1, 31,0);
    tracep->declBit(c+294,"S_AXI_ARVALID", false,-1);
    tracep->declBit(c+295,"S_AXI_ARREADY", false,-1);
    tracep->declBus(c+296,"S_AXI_RDATA", false,-1, 31,0);
    tracep->declBus(c+297,"S_AXI_RRESP", false,-1, 1,0);
    tracep->declBit(c+298,"S_AXI_RVALID", false,-1);
    tracep->declBit(c+299,"S_AXI_RREADY", false,-1);
    tracep->declBit(c+300,"AXIS_ACLK", false,-1);
    tracep->declBit(c+301,"AXIS_ARESETN", false,-1);
    tracep->declBit(c+302,"M_AXIS_TVALID", false,-1);
    tracep->declQuad(c+303,"M_AXIS_TDATA", false,-1, 63,0);
    tracep->declBus(c+305,"M_AXIS_TSTRB", false,-1, 7,0);
    tracep->declBit(c+306,"M_AXIS_TLAST", false,-1);
    tracep->declBit(c+307,"M_AXIS_TREADY", false,-1);
    tracep->declBit(c+308,"S_AXIS_TREADY", false,-1);
    tracep->declQuad(c+309,"S_AXIS_TDATA", false,-1, 63,0);
    tracep->declBus(c+311,"S_AXIS_TSTRB", false,-1, 7,0);
    tracep->declBit(c+312,"S_AXIS_TLAST", false,-1);
    tracep->declBit(c+313,"S_AXIS_TVALID", false,-1);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+281,"S_AXI_ACLK", false,-1);
    tracep->declBit(c+282,"S_AXI_ARESETN", false,-1);
    tracep->declBus(c+283,"S_AXI_AWADDR", false,-1, 31,0);
    tracep->declBit(c+284,"S_AXI_AWVALID", false,-1);
    tracep->declBit(c+285,"S_AXI_AWREADY", false,-1);
    tracep->declBus(c+286,"S_AXI_WDATA", false,-1, 31,0);
    tracep->declBus(c+287,"S_AXI_WSTRB", false,-1, 3,0);
    tracep->declBit(c+288,"S_AXI_WVALID", false,-1);
    tracep->declBit(c+289,"S_AXI_WREADY", false,-1);
    tracep->declBus(c+290,"S_AXI_BRESP", false,-1, 1,0);
    tracep->declBit(c+291,"S_AXI_BVALID", false,-1);
    tracep->declBit(c+292,"S_AXI_BREADY", false,-1);
    tracep->declBus(c+293,"S_AXI_ARADDR", false,-1, 31,0);
    tracep->declBit(c+294,"S_AXI_ARVALID", false,-1);
    tracep->declBit(c+295,"S_AXI_ARREADY", false,-1);
    tracep->declBus(c+296,"S_AXI_RDATA", false,-1, 31,0);
    tracep->declBus(c+297,"S_AXI_RRESP", false,-1, 1,0);
    tracep->declBit(c+298,"S_AXI_RVALID", false,-1);
    tracep->declBit(c+299,"S_AXI_RREADY", false,-1);
    tracep->declBit(c+300,"AXIS_ACLK", false,-1);
    tracep->declBit(c+301,"AXIS_ARESETN", false,-1);
    tracep->declBit(c+302,"M_AXIS_TVALID", false,-1);
    tracep->declQuad(c+303,"M_AXIS_TDATA", false,-1, 63,0);
    tracep->declBus(c+305,"M_AXIS_TSTRB", false,-1, 7,0);
    tracep->declBit(c+306,"M_AXIS_TLAST", false,-1);
    tracep->declBit(c+307,"M_AXIS_TREADY", false,-1);
    tracep->declBit(c+308,"S_AXIS_TREADY", false,-1);
    tracep->declQuad(c+309,"S_AXIS_TDATA", false,-1, 63,0);
    tracep->declBus(c+311,"S_AXIS_TSTRB", false,-1, 7,0);
    tracep->declBit(c+312,"S_AXIS_TLAST", false,-1);
    tracep->declBit(c+313,"S_AXIS_TVALID", false,-1);
    tracep->declBit(c+252,"run", false,-1);
    tracep->declBit(c+253,"matw", false,-1);
    tracep->declBit(c+254,"last", false,-1);
    tracep->declBus(c+269,"mat_v", false,-1, 3,0);
    tracep->declBus(c+1,"mat_a", false,-1, 2,0);
    tracep->declBit(c+270,"src_v", false,-1);
    tracep->declBus(c+2,"src_a", false,-1, 3,0);
    tracep->declBit(c+271,"src_fin", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->declBit(c+4,"p", false,-1);
    tracep->declBit(c+272,"s_fin_in", false,-1);
    tracep->declBit(c+5,"s_init", false,-1);
    tracep->declBit(c+6,"s_fin", false,-1);
    tracep->declBit(c+7,"k_init", false,-1);
    tracep->declBit(c+8,"k_fin", false,-1);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBus(c+10,"exec_src_addr", false,-1, 4,0);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 2,0);
    tracep->declBit(c+12,"out_busy", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+14,"out_fin", false,-1);
    tracep->declBus(c+15,"out_addr", false,-1, 3,0);
    tracep->declBit(c+16,"sum_update", false,-1);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBit(c+273,"stream_v", false,-1);
    tracep->declBus(c+18,"stream_a", false,-1, 2,0);
    for (int i = 0; i < 5; ++i) {
        tracep->declBus(c+19+i*1,"acc", true,(i+0), 31,0);
    }
    tracep->declBus(c+24,"result", false,-1, 31,0);
    tracep->declBus(c+255,"state", false,-1, 3,0);
    tracep->declBus(c+256,"write_addr", false,-1, 11,2);
    tracep->declBus(c+257,"read_addr", false,-1, 11,2);
    tracep->declBus(c+258,"write_data", false,-1, 31,0);
    tracep->declBit(c+259,"INI", false,-1);
    tracep->declBit(c+260,"AW", false,-1);
    tracep->declBit(c+261,"W", false,-1);
    tracep->declBit(c+262,"AWW", false,-1);
    tracep->declBit(c+263,"AR1", false,-1);
    tracep->declBit(c+264,"AR2", false,-1);
    tracep->declBus(c+265,"control", false,-1, 31,0);
    tracep->declBit(c+266,"register_w", false,-1);
    tracep->declBit(c+267,"register_r", false,-1);
    tracep->pushNamePrefix("dst_buf ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+273,"stream_v", false,-1);
    tracep->declBus(c+25,"stream_a", false,-1, 3,0);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBus(c+26,"out_addr", false,-1, 4,0);
    tracep->declBus(c+24,"result", false,-1, 31,0);
    tracep->declQuad(c+303,"stream_d", false,-1, 63,0);
    tracep->declQuad(c+27,"stream_0", false,-1, 63,0);
    tracep->declQuad(c+29,"stream_1", false,-1, 63,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+31+i*1,"buff0", true,(i+0), 31,0);
    }
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+39+i*1,"buff1", true,(i+0), 31,0);
    }
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+47+i*1,"buff2", true,(i+0), 31,0);
    }
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+55+i*1,"buff3", true,(i+0), 31,0);
    }
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("dst_ctrl ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+252,"run", false,-1);
    tracep->declBit(c+302,"dst_valid", false,-1);
    tracep->declBit(c+307,"dst_ready", false,-1);
    tracep->declBit(c+272,"s_fin_in", false,-1);
    tracep->declBit(c+273,"stream_v", false,-1);
    tracep->declBus(c+18,"stream_a", false,-1, 2,0);
    tracep->declBus(c+18,"i", false,-1, 2,0);
    tracep->declBit(c+274,"last_i", false,-1);
    tracep->declBit(c+275,"start", false,-1);
    tracep->declBit(c+63,"start_check", false,-1);
    tracep->declBit(c+64,"stream_active", false,-1);
    tracep->declBit(c+314,"stream_active_pre", false,-1);
    tracep->pushNamePrefix("d_dst_v0 ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+314,"in", false,-1, 0,0);
    tracep->declBus(c+64,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+307,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_dst_valid ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+64,"in", false,-1, 0,0);
    tracep->declBus(c+302,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+307,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_dstart0 ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+272,"in", false,-1, 0,0);
    tracep->declBus(c+63,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+307,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_da ");
    tracep->declBus(c+319,"W", false,-1, 31,0);
    tracep->declBus(c+320,"ini", false,-1, 2,0);
    tracep->declBus(c+321,"fin", false,-1, 2,0);
    tracep->declBus(c+18,"data", false,-1, 2,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+275,"start", false,-1);
    tracep->declBit(c+307,"en", false,-1);
    tracep->declBit(c+274,"last", false,-1);
    tracep->declBit(c+65,"run", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("exe_ctrl ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+5,"s_init", false,-1);
    tracep->declBit(c+12,"out_busy", false,-1);
    tracep->declBit(c+14,"out_fin", false,-1);
    tracep->declBit(c+6,"s_fin", false,-1);
    tracep->declBit(c+7,"k_init", false,-1);
    tracep->declBit(c+8,"k_fin", false,-1);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBus(c+10,"exec_src_addr", false,-1, 4,0);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 2,0);
    tracep->declBit(c+66,"last_i", false,-1);
    tracep->declBit(c+67,"last_j", false,-1);
    tracep->declBit(c+68,"next_i", false,-1);
    tracep->declBit(c+69,"next_j", false,-1);
    tracep->declBus(c+70,"i", false,-1, 1,0);
    tracep->declBus(c+11,"j", false,-1, 2,0);
    tracep->declBit(c+71,"s_init_delay", false,-1);
    tracep->declBit(c+72,"k_init_next", false,-1);
    tracep->declBit(c+73,"start", false,-1);
    tracep->declBit(c+74,"s_fin_period", false,-1);
    tracep->pushNamePrefix("d_exec ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+75,"in", false,-1, 0,0);
    tracep->declBus(c+9,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+322,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_k_fin ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+67,"in", false,-1, 0,0);
    tracep->declBus(c+8,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+322,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_k_init_next ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+76,"in", false,-1, 0,0);
    tracep->declBus(c+72,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+77,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_s_fin ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+78,"in", false,-1, 0,0);
    tracep->declBus(c+6,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+322,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_s_fin_period ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+66,"in", false,-1, 0,0);
    tracep->declBus(c+74,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+79,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_s_init_delay ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+5,"in", false,-1, 0,0);
    tracep->declBus(c+71,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+322,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_start ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+7,"in", false,-1, 0,0);
    tracep->declBus(c+73,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+322,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_i ");
    tracep->declBus(c+323,"W", false,-1, 31,0);
    tracep->declBus(c+324,"ini", false,-1, 1,0);
    tracep->declBus(c+325,"fin", false,-1, 1,0);
    tracep->declBus(c+70,"data", false,-1, 1,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+5,"start", false,-1);
    tracep->declBit(c+67,"en", false,-1);
    tracep->declBit(c+68,"next", false,-1);
    tracep->declBit(c+66,"last", false,-1);
    tracep->declBit(c+80,"next_pre", false,-1);
    tracep->declBit(c+81,"run", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_j ");
    tracep->declBus(c+319,"W", false,-1, 31,0);
    tracep->declBus(c+320,"ini", false,-1, 2,0);
    tracep->declBus(c+321,"fin", false,-1, 2,0);
    tracep->declBus(c+11,"data", false,-1, 2,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+73,"start", false,-1);
    tracep->declBit(c+322,"en", false,-1);
    tracep->declBit(c+69,"next", false,-1);
    tracep->declBit(c+67,"last", false,-1);
    tracep->declBit(c+82,"next_pre", false,-1);
    tracep->declBit(c+83,"run", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("genblk1[0] ");
    tracep->pushNamePrefix("core ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+7,"init", false,-1);
    tracep->declBit(c+276,"mat_v", false,-1);
    tracep->declBus(c+1,"mat_a", false,-1, 2,0);
    tracep->declBus(c+315,"mat_d", false,-1, 31,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 2,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBus(c+84,"acc_next", false,-1, 31,0);
    tracep->declBus(c+85,"acc", false,-1, 31,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+86+i*1,"matrix", true,(i+0), 31,0);
    }
    tracep->declBus(c+94,"exec_mat_data", false,-1, 31,0);
    tracep->declBus(c+95,"acc_right", false,-1, 31,0);
    tracep->declBus(c+96,"acc_left", false,-1, 31,0);
    tracep->declBit(c+97,"init_next", false,-1);
    tracep->declBit(c+98,"init_next_next", false,-1);
    tracep->declBit(c+99,"exec_next", false,-1);
    tracep->declBit(c+100,"exec_next_next", false,-1);
    tracep->declBus(c+101,"m2", false,-1, 31,0);
    tracep->declBus(c+102,"d2", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("genblk1[1] ");
    tracep->pushNamePrefix("core ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+7,"init", false,-1);
    tracep->declBit(c+277,"mat_v", false,-1);
    tracep->declBus(c+1,"mat_a", false,-1, 2,0);
    tracep->declBus(c+315,"mat_d", false,-1, 31,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 2,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBus(c+103,"acc_next", false,-1, 31,0);
    tracep->declBus(c+104,"acc", false,-1, 31,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+105+i*1,"matrix", true,(i+0), 31,0);
    }
    tracep->declBus(c+113,"exec_mat_data", false,-1, 31,0);
    tracep->declBus(c+114,"acc_right", false,-1, 31,0);
    tracep->declBus(c+115,"acc_left", false,-1, 31,0);
    tracep->declBit(c+116,"init_next", false,-1);
    tracep->declBit(c+117,"init_next_next", false,-1);
    tracep->declBit(c+118,"exec_next", false,-1);
    tracep->declBit(c+119,"exec_next_next", false,-1);
    tracep->declBus(c+120,"m2", false,-1, 31,0);
    tracep->declBus(c+121,"d2", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("genblk1[2] ");
    tracep->pushNamePrefix("core ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+7,"init", false,-1);
    tracep->declBit(c+278,"mat_v", false,-1);
    tracep->declBus(c+1,"mat_a", false,-1, 2,0);
    tracep->declBus(c+315,"mat_d", false,-1, 31,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 2,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBus(c+122,"acc_next", false,-1, 31,0);
    tracep->declBus(c+123,"acc", false,-1, 31,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+124+i*1,"matrix", true,(i+0), 31,0);
    }
    tracep->declBus(c+132,"exec_mat_data", false,-1, 31,0);
    tracep->declBus(c+133,"acc_right", false,-1, 31,0);
    tracep->declBus(c+134,"acc_left", false,-1, 31,0);
    tracep->declBit(c+135,"init_next", false,-1);
    tracep->declBit(c+136,"init_next_next", false,-1);
    tracep->declBit(c+137,"exec_next", false,-1);
    tracep->declBit(c+138,"exec_next_next", false,-1);
    tracep->declBus(c+139,"m2", false,-1, 31,0);
    tracep->declBus(c+140,"d2", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("genblk1[3] ");
    tracep->pushNamePrefix("core ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+7,"init", false,-1);
    tracep->declBit(c+279,"mat_v", false,-1);
    tracep->declBus(c+1,"mat_a", false,-1, 2,0);
    tracep->declBus(c+315,"mat_d", false,-1, 31,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 2,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBus(c+141,"acc_next", false,-1, 31,0);
    tracep->declBus(c+142,"acc", false,-1, 31,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+143+i*1,"matrix", true,(i+0), 31,0);
    }
    tracep->declBus(c+151,"exec_mat_data", false,-1, 31,0);
    tracep->declBus(c+152,"acc_right", false,-1, 31,0);
    tracep->declBus(c+153,"acc_left", false,-1, 31,0);
    tracep->declBit(c+154,"init_next", false,-1);
    tracep->declBit(c+155,"init_next_next", false,-1);
    tracep->declBit(c+156,"exec_next", false,-1);
    tracep->declBit(c+157,"exec_next_next", false,-1);
    tracep->declBus(c+158,"m2", false,-1, 31,0);
    tracep->declBus(c+159,"d2", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("mat_ctrl ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+316,"rst", false,-1);
    tracep->declBit(c+253,"matw", false,-1);
    tracep->declBit(c+313,"src_valid", false,-1);
    tracep->declBus(c+269,"mat_v", false,-1, 3,0);
    tracep->declBus(c+1,"mat_a", false,-1, 2,0);
    tracep->declBus(c+160,"core_sel", false,-1, 1,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("out_ctrl ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+5,"s_init", false,-1);
    tracep->declBit(c+7,"k_init", false,-1);
    tracep->declBit(c+8,"k_fin", false,-1);
    tracep->declBit(c+12,"out_busy", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+14,"out_fin", false,-1);
    tracep->declBus(c+15,"out_addr", false,-1, 3,0);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+161,"out_addr_pre", false,-1, 3,0);
    tracep->declBit(c+162,"last_i", false,-1);
    tracep->declBit(c+163,"last_j", false,-1);
    tracep->declBus(c+164,"i", false,-1, 1,0);
    tracep->declBus(c+165,"j", false,-1, 1,0);
    tracep->declBit(c+166,"last_j_next", false,-1);
    tracep->declBit(c+167,"out_period_pre", false,-1);
    tracep->declBit(c+168,"update_after_start", false,-1);
    tracep->declBit(c+169,"start", false,-1);
    tracep->declBit(c+170,"k_fin_retention", false,-1);
    tracep->declBit(c+171,"j_period", false,-1);
    tracep->pushNamePrefix("d_j_period ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+169,"in", false,-1, 0,0);
    tracep->declBus(c+171,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+172,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_out_busy ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+173,"in", false,-1, 0,0);
    tracep->declBus(c+12,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+174,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_out_busy1 ");
    tracep->declBus(c+318,"W", false,-1, 31,0);
    tracep->declBus(c+175,"in", false,-1, 0,0);
    tracep->declBus(c+170,"data", false,-1, 0,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+176,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_i ");
    tracep->declBus(c+323,"W", false,-1, 31,0);
    tracep->declBus(c+324,"ini", false,-1, 1,0);
    tracep->declBus(c+325,"fin", false,-1, 1,0);
    tracep->declBus(c+164,"data", false,-1, 1,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+5,"start", false,-1);
    tracep->declBit(c+163,"en", false,-1);
    tracep->declBit(c+162,"last", false,-1);
    tracep->declBit(c+177,"run", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_j ");
    tracep->declBus(c+323,"W", false,-1, 31,0);
    tracep->declBus(c+324,"ini", false,-1, 1,0);
    tracep->declBus(c+325,"fin", false,-1, 1,0);
    tracep->declBus(c+165,"data", false,-1, 1,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+268,"rst", false,-1);
    tracep->declBit(c+169,"start", false,-1);
    tracep->declBit(c+322,"en", false,-1);
    tracep->declBit(c+163,"last", false,-1);
    tracep->declBit(c+178,"run", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("p_ctrl ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+252,"run", false,-1);
    tracep->declBit(c+271,"src_fin", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->declBit(c+272,"s_fin_in", false,-1);
    tracep->declBit(c+4,"p", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("s_ctrl ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+252,"run", false,-1);
    tracep->declBit(c+254,"last", false,-1);
    tracep->declBit(c+307,"dst_ready", false,-1);
    tracep->declBit(c+6,"s_fin", false,-1);
    tracep->declBit(c+271,"src_fin", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->declBit(c+4,"p", false,-1);
    tracep->declBit(c+272,"s_fin_in", false,-1);
    tracep->declBit(c+5,"s_init", false,-1);
    tracep->declBit(c+179,"s_fin_dayo", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("src_buf ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+270,"src_v", false,-1);
    tracep->declBus(c+180,"src_a", false,-1, 4,0);
    tracep->declQuad(c+309,"src_d", false,-1, 63,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBus(c+181,"exec_src_addr", false,-1, 5,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    for (int i = 0; i < 16; ++i) {
        tracep->declQuad(c+182+i*2,"buff0", true,(i+0), 63,0);
    }
    tracep->declQuad(c+214,"wd0", false,-1, 63,0);
    for (int i = 0; i < 16; ++i) {
        tracep->declQuad(c+216+i*2,"buff1", true,(i+0), 63,0);
    }
    tracep->declQuad(c+248,"wd1", false,-1, 63,0);
    tracep->declBus(c+250,"ia_", false,-1, 1,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("src_ctrl ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+253,"matw", false,-1);
    tracep->declBit(c+252,"run", false,-1);
    tracep->declBit(c+313,"src_valid", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->declBit(c+308,"src_ready", false,-1);
    tracep->declBit(c+270,"src_v", false,-1);
    tracep->declBus(c+2,"src_a", false,-1, 3,0);
    tracep->declBit(c+271,"src_fin", false,-1);
    tracep->declBit(c+280,"sen", false,-1);
    tracep->declBit(c+270,"start", false,-1);
    tracep->declBit(c+271,"last_i", false,-1);
    tracep->declBus(c+2,"i", false,-1, 3,0);
    tracep->pushNamePrefix("l_i ");
    tracep->declBus(c+326,"W", false,-1, 31,0);
    tracep->declBus(c+327,"ini", false,-1, 3,0);
    tracep->declBus(c+328,"fin", false,-1, 3,0);
    tracep->declBus(c+2,"data", false,-1, 3,0);
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+317,"rst", false,-1);
    tracep->declBit(c+270,"start", false,-1);
    tracep->declBit(c+280,"en", false,-1);
    tracep->declBit(c+271,"last", false,-1);
    tracep->declBit(c+251,"run", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("src_en_ctrl ");
    tracep->declBit(c+300,"clk", false,-1);
    tracep->declBit(c+252,"run", false,-1);
    tracep->declBit(c+271,"src_fin", false,-1);
    tracep->declBit(c+4,"p", false,-1);
    tracep->declBit(c+272,"s_fin_in", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf, nullptr);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf, nullptr);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullCData(oldp+1,(vlSelf->top__DOT__mat_a),3);
    bufp->fullCData(oldp+2,(vlSelf->top__DOT__src_ctrl__DOT__i),4);
    bufp->fullCData(oldp+3,(vlSelf->top__DOT__src_en),2);
    bufp->fullBit(oldp+4,(vlSelf->top__DOT__p));
    bufp->fullBit(oldp+5,(vlSelf->top__DOT__s_init));
    bufp->fullBit(oldp+6,(vlSelf->top__DOT__s_fin));
    bufp->fullBit(oldp+7,(vlSelf->top__DOT__k_init));
    bufp->fullBit(oldp+8,(vlSelf->top__DOT__k_fin));
    bufp->fullBit(oldp+9,(vlSelf->top__DOT__exec));
    bufp->fullCData(oldp+10,((0x1fU & (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                                        << 3U) + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j)))),5);
    bufp->fullCData(oldp+11,(vlSelf->top__DOT__exe_ctrl__DOT__j),3);
    bufp->fullBit(oldp+12,(vlSelf->top__DOT__out_busy));
    bufp->fullBit(oldp+13,(vlSelf->top__DOT__out_period));
    bufp->fullBit(oldp+14,(vlSelf->top__DOT__out_fin));
    bufp->fullCData(oldp+15,(vlSelf->top__DOT__out_addr),4);
    bufp->fullBit(oldp+16,(vlSelf->top__DOT__sum_update));
    bufp->fullIData(oldp+17,(vlSelf->top__DOT__exec_src_data),32);
    bufp->fullCData(oldp+18,(vlSelf->top__DOT__dst_ctrl__DOT__i),3);
    bufp->fullIData(oldp+19,(vlSelf->top__DOT__acc[0]),32);
    bufp->fullIData(oldp+20,(vlSelf->top__DOT__acc[1]),32);
    bufp->fullIData(oldp+21,(vlSelf->top__DOT__acc[2]),32);
    bufp->fullIData(oldp+22,(vlSelf->top__DOT__acc[3]),32);
    bufp->fullIData(oldp+23,(vlSelf->top__DOT__acc[4]),32);
    bufp->fullIData(oldp+24,(vlSelf->top__DOT__acc[0U]),32);
    bufp->fullCData(oldp+25,(vlSelf->top__DOT____Vcellinp__dst_buf__stream_a),4);
    bufp->fullCData(oldp+26,(vlSelf->top__DOT____Vcellinp__dst_buf__out_addr),5);
    bufp->fullQData(oldp+27,(vlSelf->top__DOT__dst_buf__DOT__stream_0),64);
    bufp->fullQData(oldp+29,(vlSelf->top__DOT__dst_buf__DOT__stream_1),64);
    bufp->fullIData(oldp+31,(vlSelf->top__DOT__dst_buf__DOT__buff0[0]),32);
    bufp->fullIData(oldp+32,(vlSelf->top__DOT__dst_buf__DOT__buff0[1]),32);
    bufp->fullIData(oldp+33,(vlSelf->top__DOT__dst_buf__DOT__buff0[2]),32);
    bufp->fullIData(oldp+34,(vlSelf->top__DOT__dst_buf__DOT__buff0[3]),32);
    bufp->fullIData(oldp+35,(vlSelf->top__DOT__dst_buf__DOT__buff0[4]),32);
    bufp->fullIData(oldp+36,(vlSelf->top__DOT__dst_buf__DOT__buff0[5]),32);
    bufp->fullIData(oldp+37,(vlSelf->top__DOT__dst_buf__DOT__buff0[6]),32);
    bufp->fullIData(oldp+38,(vlSelf->top__DOT__dst_buf__DOT__buff0[7]),32);
    bufp->fullIData(oldp+39,(vlSelf->top__DOT__dst_buf__DOT__buff1[0]),32);
    bufp->fullIData(oldp+40,(vlSelf->top__DOT__dst_buf__DOT__buff1[1]),32);
    bufp->fullIData(oldp+41,(vlSelf->top__DOT__dst_buf__DOT__buff1[2]),32);
    bufp->fullIData(oldp+42,(vlSelf->top__DOT__dst_buf__DOT__buff1[3]),32);
    bufp->fullIData(oldp+43,(vlSelf->top__DOT__dst_buf__DOT__buff1[4]),32);
    bufp->fullIData(oldp+44,(vlSelf->top__DOT__dst_buf__DOT__buff1[5]),32);
    bufp->fullIData(oldp+45,(vlSelf->top__DOT__dst_buf__DOT__buff1[6]),32);
    bufp->fullIData(oldp+46,(vlSelf->top__DOT__dst_buf__DOT__buff1[7]),32);
    bufp->fullIData(oldp+47,(vlSelf->top__DOT__dst_buf__DOT__buff2[0]),32);
    bufp->fullIData(oldp+48,(vlSelf->top__DOT__dst_buf__DOT__buff2[1]),32);
    bufp->fullIData(oldp+49,(vlSelf->top__DOT__dst_buf__DOT__buff2[2]),32);
    bufp->fullIData(oldp+50,(vlSelf->top__DOT__dst_buf__DOT__buff2[3]),32);
    bufp->fullIData(oldp+51,(vlSelf->top__DOT__dst_buf__DOT__buff2[4]),32);
    bufp->fullIData(oldp+52,(vlSelf->top__DOT__dst_buf__DOT__buff2[5]),32);
    bufp->fullIData(oldp+53,(vlSelf->top__DOT__dst_buf__DOT__buff2[6]),32);
    bufp->fullIData(oldp+54,(vlSelf->top__DOT__dst_buf__DOT__buff2[7]),32);
    bufp->fullIData(oldp+55,(vlSelf->top__DOT__dst_buf__DOT__buff3[0]),32);
    bufp->fullIData(oldp+56,(vlSelf->top__DOT__dst_buf__DOT__buff3[1]),32);
    bufp->fullIData(oldp+57,(vlSelf->top__DOT__dst_buf__DOT__buff3[2]),32);
    bufp->fullIData(oldp+58,(vlSelf->top__DOT__dst_buf__DOT__buff3[3]),32);
    bufp->fullIData(oldp+59,(vlSelf->top__DOT__dst_buf__DOT__buff3[4]),32);
    bufp->fullIData(oldp+60,(vlSelf->top__DOT__dst_buf__DOT__buff3[5]),32);
    bufp->fullIData(oldp+61,(vlSelf->top__DOT__dst_buf__DOT__buff3[6]),32);
    bufp->fullIData(oldp+62,(vlSelf->top__DOT__dst_buf__DOT__buff3[7]),32);
    bufp->fullBit(oldp+63,(vlSelf->top__DOT__dst_ctrl__DOT__start_check));
    bufp->fullBit(oldp+64,(vlSelf->top__DOT__dst_ctrl__DOT__stream_active));
    bufp->fullBit(oldp+65,(vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run));
    bufp->fullBit(oldp+66,(vlSelf->top__DOT__exe_ctrl__DOT__last_i));
    bufp->fullBit(oldp+67,(vlSelf->top__DOT__exe_ctrl__DOT__last_j));
    bufp->fullBit(oldp+68,(((IData)(vlSelf->top__DOT__s_init) 
                            | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre))));
    bufp->fullBit(oldp+69,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                            | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))));
    bufp->fullCData(oldp+70,(vlSelf->top__DOT__exe_ctrl__DOT__i),2);
    bufp->fullBit(oldp+71,(vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay));
    bufp->fullBit(oldp+72,(vlSelf->top__DOT__exe_ctrl__DOT__k_init_next));
    bufp->fullBit(oldp+73,(vlSelf->top__DOT__exe_ctrl__DOT__start));
    bufp->fullBit(oldp+74,(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period));
    bufp->fullBit(oldp+75,(((IData)(vlSelf->top__DOT__k_init) 
                            | ((IData)(vlSelf->top__DOT__exec) 
                               & (~ (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j))))));
    bufp->fullBit(oldp+76,((((IData)(vlSelf->top__DOT__s_init) 
                             | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre)) 
                            & (~ (IData)(vlSelf->top__DOT__s_init)))));
    bufp->fullBit(oldp+77,((1U & ((~ (IData)(vlSelf->top__DOT__out_busy)) 
                                  | ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                                     | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))))));
    bufp->fullBit(oldp+78,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period) 
                            & (IData)(vlSelf->top__DOT__out_fin))));
    bufp->fullBit(oldp+79,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_i) 
                            | (IData)(vlSelf->top__DOT__out_fin))));
    bufp->fullBit(oldp+80,(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre));
    bufp->fullBit(oldp+81,(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run));
    bufp->fullBit(oldp+82,(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre));
    bufp->fullBit(oldp+83,(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run));
    bufp->fullIData(oldp+84,(vlSelf->top__DOT__acc[1U]),32);
    bufp->fullIData(oldp+85,(((IData)(vlSelf->top__DOT__sum_update)
                               ? vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left
                               : vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right)),32);
    bufp->fullIData(oldp+86,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[0]),32);
    bufp->fullIData(oldp+87,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[1]),32);
    bufp->fullIData(oldp+88,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[2]),32);
    bufp->fullIData(oldp+89,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[3]),32);
    bufp->fullIData(oldp+90,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[4]),32);
    bufp->fullIData(oldp+91,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[5]),32);
    bufp->fullIData(oldp+92,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[6]),32);
    bufp->fullIData(oldp+93,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__matrix[7]),32);
    bufp->fullIData(oldp+94,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data),32);
    bufp->fullIData(oldp+95,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right),32);
    bufp->fullIData(oldp+96,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left),32);
    bufp->fullBit(oldp+97,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next));
    bufp->fullBit(oldp+98,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next));
    bufp->fullBit(oldp+99,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next));
    bufp->fullBit(oldp+100,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next));
    bufp->fullIData(oldp+101,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2),32);
    bufp->fullIData(oldp+102,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2),32);
    bufp->fullIData(oldp+103,(vlSelf->top__DOT__acc
                              [2U]),32);
    bufp->fullIData(oldp+104,(((IData)(vlSelf->top__DOT__sum_update)
                                ? vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left
                                : vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right)),32);
    bufp->fullIData(oldp+105,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[0]),32);
    bufp->fullIData(oldp+106,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[1]),32);
    bufp->fullIData(oldp+107,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[2]),32);
    bufp->fullIData(oldp+108,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[3]),32);
    bufp->fullIData(oldp+109,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[4]),32);
    bufp->fullIData(oldp+110,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[5]),32);
    bufp->fullIData(oldp+111,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[6]),32);
    bufp->fullIData(oldp+112,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__matrix[7]),32);
    bufp->fullIData(oldp+113,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data),32);
    bufp->fullIData(oldp+114,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right),32);
    bufp->fullIData(oldp+115,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left),32);
    bufp->fullBit(oldp+116,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next));
    bufp->fullBit(oldp+117,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next));
    bufp->fullBit(oldp+118,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next));
    bufp->fullBit(oldp+119,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next));
    bufp->fullIData(oldp+120,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2),32);
    bufp->fullIData(oldp+121,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2),32);
    bufp->fullIData(oldp+122,(vlSelf->top__DOT__acc
                              [3U]),32);
    bufp->fullIData(oldp+123,(((IData)(vlSelf->top__DOT__sum_update)
                                ? vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left
                                : vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right)),32);
    bufp->fullIData(oldp+124,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[0]),32);
    bufp->fullIData(oldp+125,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[1]),32);
    bufp->fullIData(oldp+126,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[2]),32);
    bufp->fullIData(oldp+127,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[3]),32);
    bufp->fullIData(oldp+128,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[4]),32);
    bufp->fullIData(oldp+129,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[5]),32);
    bufp->fullIData(oldp+130,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[6]),32);
    bufp->fullIData(oldp+131,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__matrix[7]),32);
    bufp->fullIData(oldp+132,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data),32);
    bufp->fullIData(oldp+133,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right),32);
    bufp->fullIData(oldp+134,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left),32);
    bufp->fullBit(oldp+135,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next));
    bufp->fullBit(oldp+136,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next));
    bufp->fullBit(oldp+137,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next));
    bufp->fullBit(oldp+138,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next));
    bufp->fullIData(oldp+139,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2),32);
    bufp->fullIData(oldp+140,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2),32);
    bufp->fullIData(oldp+141,(vlSelf->top__DOT__acc
                              [4U]),32);
    bufp->fullIData(oldp+142,(((IData)(vlSelf->top__DOT__sum_update)
                                ? vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left
                                : vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right)),32);
    bufp->fullIData(oldp+143,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[0]),32);
    bufp->fullIData(oldp+144,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[1]),32);
    bufp->fullIData(oldp+145,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[2]),32);
    bufp->fullIData(oldp+146,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[3]),32);
    bufp->fullIData(oldp+147,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[4]),32);
    bufp->fullIData(oldp+148,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[5]),32);
    bufp->fullIData(oldp+149,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[6]),32);
    bufp->fullIData(oldp+150,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__matrix[7]),32);
    bufp->fullIData(oldp+151,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data),32);
    bufp->fullIData(oldp+152,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right),32);
    bufp->fullIData(oldp+153,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left),32);
    bufp->fullBit(oldp+154,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next));
    bufp->fullBit(oldp+155,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next));
    bufp->fullBit(oldp+156,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next));
    bufp->fullBit(oldp+157,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next));
    bufp->fullIData(oldp+158,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2),32);
    bufp->fullIData(oldp+159,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2),32);
    bufp->fullCData(oldp+160,(vlSelf->top__DOT__mat_ctrl__DOT__core_sel),2);
    bufp->fullCData(oldp+161,(vlSelf->top__DOT__out_ctrl__DOT__out_addr_pre),4);
    bufp->fullBit(oldp+162,((((3U == (IData)(vlSelf->top__DOT__out_ctrl__DOT__i)) 
                              & ((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run) 
                                 | (IData)(vlSelf->top__DOT__s_init))) 
                             & (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))));
    bufp->fullBit(oldp+163,(vlSelf->top__DOT__out_ctrl__DOT__last_j));
    bufp->fullCData(oldp+164,(vlSelf->top__DOT__out_ctrl__DOT__i),2);
    bufp->fullCData(oldp+165,(vlSelf->top__DOT__out_ctrl__DOT__j),2);
    bufp->fullBit(oldp+166,(vlSelf->top__DOT__out_ctrl__DOT__last_j_next));
    bufp->fullBit(oldp+167,(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre));
    bufp->fullBit(oldp+168,(vlSelf->top__DOT__out_ctrl__DOT__update_after_start));
    bufp->fullBit(oldp+169,(vlSelf->top__DOT__out_ctrl__DOT__start));
    bufp->fullBit(oldp+170,(vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention));
    bufp->fullBit(oldp+171,(vlSelf->top__DOT__out_ctrl__DOT__j_period));
    bufp->fullBit(oldp+172,(((IData)(vlSelf->top__DOT__out_ctrl__DOT__start) 
                             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))));
    bufp->fullBit(oldp+173,(((IData)(vlSelf->top__DOT__k_init) 
                             & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre))));
    bufp->fullBit(oldp+174,((((IData)(vlSelf->top__DOT__k_init) 
                              & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre)) 
                             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))));
    bufp->fullBit(oldp+175,(((IData)(vlSelf->top__DOT__k_fin) 
                             & (IData)(vlSelf->top__DOT__out_busy))));
    bufp->fullBit(oldp+176,((((IData)(vlSelf->top__DOT__k_fin) 
                              & (IData)(vlSelf->top__DOT__out_busy)) 
                             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))));
    bufp->fullBit(oldp+177,(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run));
    bufp->fullBit(oldp+178,(vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run));
    bufp->fullBit(oldp+179,(vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo));
    bufp->fullCData(oldp+180,(vlSelf->top__DOT____Vcellinp__src_buf__src_a),5);
    bufp->fullCData(oldp+181,(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr),6);
    bufp->fullQData(oldp+182,(vlSelf->top__DOT__src_buf__DOT__buff0[0]),64);
    bufp->fullQData(oldp+184,(vlSelf->top__DOT__src_buf__DOT__buff0[1]),64);
    bufp->fullQData(oldp+186,(vlSelf->top__DOT__src_buf__DOT__buff0[2]),64);
    bufp->fullQData(oldp+188,(vlSelf->top__DOT__src_buf__DOT__buff0[3]),64);
    bufp->fullQData(oldp+190,(vlSelf->top__DOT__src_buf__DOT__buff0[4]),64);
    bufp->fullQData(oldp+192,(vlSelf->top__DOT__src_buf__DOT__buff0[5]),64);
    bufp->fullQData(oldp+194,(vlSelf->top__DOT__src_buf__DOT__buff0[6]),64);
    bufp->fullQData(oldp+196,(vlSelf->top__DOT__src_buf__DOT__buff0[7]),64);
    bufp->fullQData(oldp+198,(vlSelf->top__DOT__src_buf__DOT__buff0[8]),64);
    bufp->fullQData(oldp+200,(vlSelf->top__DOT__src_buf__DOT__buff0[9]),64);
    bufp->fullQData(oldp+202,(vlSelf->top__DOT__src_buf__DOT__buff0[10]),64);
    bufp->fullQData(oldp+204,(vlSelf->top__DOT__src_buf__DOT__buff0[11]),64);
    bufp->fullQData(oldp+206,(vlSelf->top__DOT__src_buf__DOT__buff0[12]),64);
    bufp->fullQData(oldp+208,(vlSelf->top__DOT__src_buf__DOT__buff0[13]),64);
    bufp->fullQData(oldp+210,(vlSelf->top__DOT__src_buf__DOT__buff0[14]),64);
    bufp->fullQData(oldp+212,(vlSelf->top__DOT__src_buf__DOT__buff0[15]),64);
    bufp->fullQData(oldp+214,(vlSelf->top__DOT__src_buf__DOT__wd0),64);
    bufp->fullQData(oldp+216,(vlSelf->top__DOT__src_buf__DOT__buff1[0]),64);
    bufp->fullQData(oldp+218,(vlSelf->top__DOT__src_buf__DOT__buff1[1]),64);
    bufp->fullQData(oldp+220,(vlSelf->top__DOT__src_buf__DOT__buff1[2]),64);
    bufp->fullQData(oldp+222,(vlSelf->top__DOT__src_buf__DOT__buff1[3]),64);
    bufp->fullQData(oldp+224,(vlSelf->top__DOT__src_buf__DOT__buff1[4]),64);
    bufp->fullQData(oldp+226,(vlSelf->top__DOT__src_buf__DOT__buff1[5]),64);
    bufp->fullQData(oldp+228,(vlSelf->top__DOT__src_buf__DOT__buff1[6]),64);
    bufp->fullQData(oldp+230,(vlSelf->top__DOT__src_buf__DOT__buff1[7]),64);
    bufp->fullQData(oldp+232,(vlSelf->top__DOT__src_buf__DOT__buff1[8]),64);
    bufp->fullQData(oldp+234,(vlSelf->top__DOT__src_buf__DOT__buff1[9]),64);
    bufp->fullQData(oldp+236,(vlSelf->top__DOT__src_buf__DOT__buff1[10]),64);
    bufp->fullQData(oldp+238,(vlSelf->top__DOT__src_buf__DOT__buff1[11]),64);
    bufp->fullQData(oldp+240,(vlSelf->top__DOT__src_buf__DOT__buff1[12]),64);
    bufp->fullQData(oldp+242,(vlSelf->top__DOT__src_buf__DOT__buff1[13]),64);
    bufp->fullQData(oldp+244,(vlSelf->top__DOT__src_buf__DOT__buff1[14]),64);
    bufp->fullQData(oldp+246,(vlSelf->top__DOT__src_buf__DOT__buff1[15]),64);
    bufp->fullQData(oldp+248,(vlSelf->top__DOT__src_buf__DOT__wd1),64);
    bufp->fullCData(oldp+250,(vlSelf->top__DOT__src_buf__DOT__ia_),2);
    bufp->fullBit(oldp+251,(vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run));
    bufp->fullBit(oldp+252,(vlSelf->top__DOT__run));
    bufp->fullBit(oldp+253,(vlSelf->top__DOT__matw));
    bufp->fullBit(oldp+254,(vlSelf->top__DOT__last));
    bufp->fullCData(oldp+255,(vlSelf->top__DOT__state),4);
    bufp->fullSData(oldp+256,(vlSelf->top__DOT__write_addr),10);
    bufp->fullSData(oldp+257,(vlSelf->top__DOT__read_addr),10);
    bufp->fullIData(oldp+258,(vlSelf->top__DOT__write_data),32);
    bufp->fullBit(oldp+259,((0U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+260,((1U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+261,((2U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+262,((3U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+263,((4U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+264,((8U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullIData(oldp+265,(vlSelf->top__DOT__control),32);
    bufp->fullBit(oldp+266,(vlSelf->top__DOT__register_w));
    bufp->fullBit(oldp+267,((IData)(((4U == (IData)(vlSelf->top__DOT__state)) 
                                     & (0U == (0x300U 
                                               & (IData)(vlSelf->top__DOT__read_addr)))))));
    bufp->fullBit(oldp+268,((1U & (~ (IData)(vlSelf->top__DOT__run)))));
    bufp->fullCData(oldp+269,(vlSelf->top__DOT__mat_v),4);
    bufp->fullBit(oldp+270,(vlSelf->top__DOT__src_ctrl__DOT__start));
    bufp->fullBit(oldp+271,(vlSelf->top__DOT__src_ctrl__DOT__last_i));
    bufp->fullBit(oldp+272,(vlSelf->top__DOT__s_fin_in));
    bufp->fullBit(oldp+273,(vlSelf->top__DOT__stream_v));
    bufp->fullBit(oldp+274,(vlSelf->top__DOT__dst_ctrl__DOT__last_i));
    bufp->fullBit(oldp+275,(vlSelf->top__DOT__dst_ctrl__DOT__start));
    bufp->fullBit(oldp+276,((1U & (IData)(vlSelf->top__DOT__mat_v))));
    bufp->fullBit(oldp+277,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                   >> 1U))));
    bufp->fullBit(oldp+278,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                   >> 2U))));
    bufp->fullBit(oldp+279,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                   >> 3U))));
    bufp->fullBit(oldp+280,(vlSelf->top__DOT__src_ctrl__DOT__sen));
    bufp->fullBit(oldp+281,(vlSelf->S_AXI_ACLK));
    bufp->fullBit(oldp+282,(vlSelf->S_AXI_ARESETN));
    bufp->fullIData(oldp+283,(vlSelf->S_AXI_AWADDR),32);
    bufp->fullBit(oldp+284,(vlSelf->S_AXI_AWVALID));
    bufp->fullBit(oldp+285,(vlSelf->S_AXI_AWREADY));
    bufp->fullIData(oldp+286,(vlSelf->S_AXI_WDATA),32);
    bufp->fullCData(oldp+287,(vlSelf->S_AXI_WSTRB),4);
    bufp->fullBit(oldp+288,(vlSelf->S_AXI_WVALID));
    bufp->fullBit(oldp+289,(vlSelf->S_AXI_WREADY));
    bufp->fullCData(oldp+290,(vlSelf->S_AXI_BRESP),2);
    bufp->fullBit(oldp+291,(vlSelf->S_AXI_BVALID));
    bufp->fullBit(oldp+292,(vlSelf->S_AXI_BREADY));
    bufp->fullIData(oldp+293,(vlSelf->S_AXI_ARADDR),32);
    bufp->fullBit(oldp+294,(vlSelf->S_AXI_ARVALID));
    bufp->fullBit(oldp+295,(vlSelf->S_AXI_ARREADY));
    bufp->fullIData(oldp+296,(vlSelf->S_AXI_RDATA),32);
    bufp->fullCData(oldp+297,(vlSelf->S_AXI_RRESP),2);
    bufp->fullBit(oldp+298,(vlSelf->S_AXI_RVALID));
    bufp->fullBit(oldp+299,(vlSelf->S_AXI_RREADY));
    bufp->fullBit(oldp+300,(vlSelf->AXIS_ACLK));
    bufp->fullBit(oldp+301,(vlSelf->AXIS_ARESETN));
    bufp->fullBit(oldp+302,(vlSelf->M_AXIS_TVALID));
    bufp->fullQData(oldp+303,(vlSelf->M_AXIS_TDATA),64);
    bufp->fullCData(oldp+305,(vlSelf->M_AXIS_TSTRB),8);
    bufp->fullBit(oldp+306,(vlSelf->M_AXIS_TLAST));
    bufp->fullBit(oldp+307,(vlSelf->M_AXIS_TREADY));
    bufp->fullBit(oldp+308,(vlSelf->S_AXIS_TREADY));
    bufp->fullQData(oldp+309,(vlSelf->S_AXIS_TDATA),64);
    bufp->fullCData(oldp+311,(vlSelf->S_AXIS_TSTRB),8);
    bufp->fullBit(oldp+312,(vlSelf->S_AXIS_TLAST));
    bufp->fullBit(oldp+313,(vlSelf->S_AXIS_TVALID));
    bufp->fullBit(oldp+314,((((IData)(vlSelf->top__DOT__s_fin_in) 
                              | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__stream_active)) 
                             & (~ (IData)(vlSelf->top__DOT__dst_ctrl__DOT__last_i)))));
    bufp->fullIData(oldp+315,((IData)(vlSelf->S_AXIS_TDATA)),32);
    bufp->fullBit(oldp+316,((1U & (~ (IData)(vlSelf->AXIS_ARESETN)))));
    bufp->fullBit(oldp+317,((1U & ((~ (IData)(vlSelf->S_AXIS_TREADY)) 
                                   | (~ (IData)(vlSelf->top__DOT__run))))));
    bufp->fullIData(oldp+318,(1U),32);
    bufp->fullIData(oldp+319,(3U),32);
    bufp->fullCData(oldp+320,(0U),3);
    bufp->fullCData(oldp+321,(7U),3);
    bufp->fullBit(oldp+322,(1U));
    bufp->fullIData(oldp+323,(2U),32);
    bufp->fullCData(oldp+324,(0U),2);
    bufp->fullCData(oldp+325,(3U),2);
    bufp->fullIData(oldp+326,(4U),32);
    bufp->fullCData(oldp+327,(0U),4);
    bufp->fullCData(oldp+328,(0xfU),4);
}
