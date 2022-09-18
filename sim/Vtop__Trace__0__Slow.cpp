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
    tracep->declBit(c+240,"S_AXI_ACLK", false,-1);
    tracep->declBit(c+241,"S_AXI_ARESETN", false,-1);
    tracep->declBus(c+242,"S_AXI_AWADDR", false,-1, 31,0);
    tracep->declBit(c+243,"S_AXI_AWVALID", false,-1);
    tracep->declBit(c+244,"S_AXI_AWREADY", false,-1);
    tracep->declBus(c+245,"S_AXI_WDATA", false,-1, 31,0);
    tracep->declBus(c+246,"S_AXI_WSTRB", false,-1, 3,0);
    tracep->declBit(c+247,"S_AXI_WVALID", false,-1);
    tracep->declBit(c+248,"S_AXI_WREADY", false,-1);
    tracep->declBus(c+249,"S_AXI_BRESP", false,-1, 1,0);
    tracep->declBit(c+250,"S_AXI_BVALID", false,-1);
    tracep->declBit(c+251,"S_AXI_BREADY", false,-1);
    tracep->declBus(c+252,"S_AXI_ARADDR", false,-1, 31,0);
    tracep->declBit(c+253,"S_AXI_ARVALID", false,-1);
    tracep->declBit(c+254,"S_AXI_ARREADY", false,-1);
    tracep->declBus(c+255,"S_AXI_RDATA", false,-1, 31,0);
    tracep->declBus(c+256,"S_AXI_RRESP", false,-1, 1,0);
    tracep->declBit(c+257,"S_AXI_RVALID", false,-1);
    tracep->declBit(c+258,"S_AXI_RREADY", false,-1);
    tracep->declBit(c+259,"AXIS_ACLK", false,-1);
    tracep->declBit(c+260,"AXIS_ARESETN", false,-1);
    tracep->declBit(c+261,"M_AXIS_TVALID", false,-1);
    tracep->declArray(c+262,"M_AXIS_TDATA", false,-1, 1023,0);
    tracep->declBus(c+294,"M_AXIS_TSTRB", false,-1, 7,0);
    tracep->declBit(c+295,"M_AXIS_TLAST", false,-1);
    tracep->declBit(c+296,"M_AXIS_TREADY", false,-1);
    tracep->declBit(c+297,"S_AXIS_TREADY", false,-1);
    tracep->declArray(c+298,"S_AXIS_TDATA", false,-1, 1023,0);
    tracep->declBus(c+330,"S_AXIS_TSTRB", false,-1, 7,0);
    tracep->declBit(c+331,"S_AXIS_TLAST", false,-1);
    tracep->declBit(c+332,"S_AXIS_TVALID", false,-1);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+240,"S_AXI_ACLK", false,-1);
    tracep->declBit(c+241,"S_AXI_ARESETN", false,-1);
    tracep->declBus(c+242,"S_AXI_AWADDR", false,-1, 31,0);
    tracep->declBit(c+243,"S_AXI_AWVALID", false,-1);
    tracep->declBit(c+244,"S_AXI_AWREADY", false,-1);
    tracep->declBus(c+245,"S_AXI_WDATA", false,-1, 31,0);
    tracep->declBus(c+246,"S_AXI_WSTRB", false,-1, 3,0);
    tracep->declBit(c+247,"S_AXI_WVALID", false,-1);
    tracep->declBit(c+248,"S_AXI_WREADY", false,-1);
    tracep->declBus(c+249,"S_AXI_BRESP", false,-1, 1,0);
    tracep->declBit(c+250,"S_AXI_BVALID", false,-1);
    tracep->declBit(c+251,"S_AXI_BREADY", false,-1);
    tracep->declBus(c+252,"S_AXI_ARADDR", false,-1, 31,0);
    tracep->declBit(c+253,"S_AXI_ARVALID", false,-1);
    tracep->declBit(c+254,"S_AXI_ARREADY", false,-1);
    tracep->declBus(c+255,"S_AXI_RDATA", false,-1, 31,0);
    tracep->declBus(c+256,"S_AXI_RRESP", false,-1, 1,0);
    tracep->declBit(c+257,"S_AXI_RVALID", false,-1);
    tracep->declBit(c+258,"S_AXI_RREADY", false,-1);
    tracep->declBit(c+259,"AXIS_ACLK", false,-1);
    tracep->declBit(c+260,"AXIS_ARESETN", false,-1);
    tracep->declBit(c+261,"M_AXIS_TVALID", false,-1);
    tracep->declArray(c+262,"M_AXIS_TDATA", false,-1, 1023,0);
    tracep->declBus(c+294,"M_AXIS_TSTRB", false,-1, 7,0);
    tracep->declBit(c+295,"M_AXIS_TLAST", false,-1);
    tracep->declBit(c+296,"M_AXIS_TREADY", false,-1);
    tracep->declBit(c+297,"S_AXIS_TREADY", false,-1);
    tracep->declArray(c+298,"S_AXIS_TDATA", false,-1, 1023,0);
    tracep->declBus(c+330,"S_AXIS_TSTRB", false,-1, 7,0);
    tracep->declBit(c+331,"S_AXIS_TLAST", false,-1);
    tracep->declBit(c+332,"S_AXIS_TVALID", false,-1);
    tracep->declBit(c+211,"run", false,-1);
    tracep->declBit(c+212,"matw", false,-1);
    tracep->declBit(c+213,"last", false,-1);
    tracep->declBus(c+228,"mat_v", false,-1, 3,0);
    tracep->declBus(c+1,"mat_a", false,-1, 5,0);
    tracep->declBit(c+229,"src_v", false,-1);
    tracep->declBus(c+2,"src_a", false,-1, 7,0);
    tracep->declBit(c+230,"src_fin", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->declBit(c+4,"p", false,-1);
    tracep->declBit(c+231,"s_fin_in", false,-1);
    tracep->declBit(c+5,"s_init", false,-1);
    tracep->declBit(c+6,"s_fin", false,-1);
    tracep->declBit(c+7,"k_init", false,-1);
    tracep->declBit(c+8,"k_fin", false,-1);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBus(c+10,"exec_src_addr", false,-1, 7,0);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 5,0);
    tracep->declBit(c+12,"out_busy", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+14,"out_fin", false,-1);
    tracep->declBus(c+15,"out_addr", false,-1, 3,0);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBit(c+232,"stream_v", false,-1);
    tracep->declBus(c+18,"stream_a", false,-1, 2,0);
    for (int i = 0; i < 5; ++i) {
        tracep->declBus(c+19+i*1,"acc", true,(i+0), 31,0);
    }
    tracep->declBus(c+24,"result", false,-1, 31,0);
    tracep->declBus(c+214,"state", false,-1, 3,0);
    tracep->declBus(c+215,"write_addr", false,-1, 11,2);
    tracep->declBus(c+216,"read_addr", false,-1, 11,2);
    tracep->declBus(c+217,"write_data", false,-1, 31,0);
    tracep->declBit(c+218,"INI", false,-1);
    tracep->declBit(c+219,"AW", false,-1);
    tracep->declBit(c+220,"W", false,-1);
    tracep->declBit(c+221,"AWW", false,-1);
    tracep->declBit(c+222,"AR1", false,-1);
    tracep->declBit(c+223,"AR2", false,-1);
    tracep->declBus(c+224,"control", false,-1, 31,0);
    tracep->declBit(c+225,"register_w", false,-1);
    tracep->declBit(c+226,"register_r", false,-1);
    tracep->pushNamePrefix("dst_buf ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+232,"stream_v", false,-1);
    tracep->declBus(c+25,"stream_a", false,-1, 3,0);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBus(c+26,"out_addr", false,-1, 4,0);
    tracep->declBus(c+24,"result", false,-1, 31,0);
    tracep->declArray(c+262,"stream_d", false,-1, 1023,0);
    tracep->declArray(c+27,"stream_0", false,-1, 1023,0);
    tracep->declArray(c+59,"stream_1", false,-1, 1023,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+91+i*1,"buff0", true,(i+0), 31,0);
    }
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+99+i*1,"buff1", true,(i+0), 31,0);
    }
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+107+i*1,"buff2", true,(i+0), 31,0);
    }
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+115+i*1,"buff3", true,(i+0), 31,0);
    }
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("dst_ctrl ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+211,"run", false,-1);
    tracep->declBit(c+296,"dst_ready", false,-1);
    tracep->declBit(c+231,"s_fin_in", false,-1);
    tracep->declBit(c+261,"dst_valid", false,-1);
    tracep->declBit(c+232,"stream_v", false,-1);
    tracep->declBus(c+18,"stream_a", false,-1, 2,0);
    tracep->declBus(c+18,"i", false,-1, 2,0);
    tracep->declBit(c+233,"last_i", false,-1);
    tracep->declBit(c+234,"start", false,-1);
    tracep->declBit(c+123,"start_check", false,-1);
    tracep->declBit(c+124,"stream_active", false,-1);
    tracep->declBit(c+333,"stream_active_pre", false,-1);
    tracep->pushNamePrefix("d_dst_v0 ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+333,"in", false,-1, 0,0);
    tracep->declBus(c+124,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+296,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_dst_valid ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+124,"in", false,-1, 0,0);
    tracep->declBus(c+261,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+296,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_dstart0 ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+231,"in", false,-1, 0,0);
    tracep->declBus(c+123,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+296,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_da ");
    tracep->declBus(c+337,"W", false,-1, 31,0);
    tracep->declBus(c+338,"ini", false,-1, 2,0);
    tracep->declBus(c+338,"fin", false,-1, 2,0);
    tracep->declBus(c+18,"data", false,-1, 2,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+234,"start", false,-1);
    tracep->declBit(c+296,"en", false,-1);
    tracep->declBit(c+233,"last", false,-1);
    tracep->declBit(c+125,"run", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("exe_ctrl ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+5,"s_init", false,-1);
    tracep->declBit(c+12,"out_busy", false,-1);
    tracep->declBit(c+14,"out_fin", false,-1);
    tracep->declBit(c+6,"s_fin", false,-1);
    tracep->declBit(c+7,"k_init", false,-1);
    tracep->declBit(c+8,"k_fin", false,-1);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBus(c+10,"exec_src_addr", false,-1, 7,0);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 5,0);
    tracep->declBit(c+126,"last_i", false,-1);
    tracep->declBit(c+127,"last_j", false,-1);
    tracep->declBit(c+128,"next_i", false,-1);
    tracep->declBit(c+129,"next_j", false,-1);
    tracep->declBus(c+130,"i", false,-1, 1,0);
    tracep->declBus(c+11,"j", false,-1, 5,0);
    tracep->declBit(c+131,"s_init_delay", false,-1);
    tracep->declBit(c+132,"k_init_next", false,-1);
    tracep->declBit(c+133,"start", false,-1);
    tracep->declBit(c+134,"s_fin_period", false,-1);
    tracep->pushNamePrefix("d_exec ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+135,"in", false,-1, 0,0);
    tracep->declBus(c+9,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+339,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_k_fin ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+127,"in", false,-1, 0,0);
    tracep->declBus(c+8,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+339,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_k_init_next ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+136,"in", false,-1, 0,0);
    tracep->declBus(c+132,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+137,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_s_fin ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+138,"in", false,-1, 0,0);
    tracep->declBus(c+6,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+339,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_s_fin_period ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+126,"in", false,-1, 0,0);
    tracep->declBus(c+134,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+139,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_s_init_delay ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+5,"in", false,-1, 0,0);
    tracep->declBus(c+131,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+339,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_start ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+7,"in", false,-1, 0,0);
    tracep->declBus(c+133,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+339,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_i ");
    tracep->declBus(c+340,"W", false,-1, 31,0);
    tracep->declBus(c+341,"ini", false,-1, 1,0);
    tracep->declBus(c+342,"fin", false,-1, 1,0);
    tracep->declBus(c+130,"data", false,-1, 1,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+5,"start", false,-1);
    tracep->declBit(c+127,"en", false,-1);
    tracep->declBit(c+128,"next", false,-1);
    tracep->declBit(c+126,"last", false,-1);
    tracep->declBit(c+140,"next_pre", false,-1);
    tracep->declBit(c+141,"run", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_j ");
    tracep->declBus(c+343,"W", false,-1, 31,0);
    tracep->declBus(c+344,"ini", false,-1, 5,0);
    tracep->declBus(c+345,"fin", false,-1, 5,0);
    tracep->declBus(c+11,"data", false,-1, 5,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+133,"start", false,-1);
    tracep->declBit(c+339,"en", false,-1);
    tracep->declBit(c+129,"next", false,-1);
    tracep->declBit(c+127,"last", false,-1);
    tracep->declBit(c+142,"next_pre", false,-1);
    tracep->declBit(c+143,"run", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("genblk1[0] ");
    tracep->pushNamePrefix("core ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+7,"init", false,-1);
    tracep->declBit(c+235,"mat_v", false,-1);
    tracep->declBus(c+1,"mat_a", false,-1, 5,0);
    tracep->declArray(c+298,"mat_d", false,-1, 1023,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 5,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBus(c+144,"acc_next", false,-1, 31,0);
    tracep->declBus(c+145,"acc", false,-1, 31,0);
    tracep->declBus(c+146,"exec_mat_data", false,-1, 31,0);
    tracep->declBus(c+147,"acc_right", false,-1, 31,0);
    tracep->declBus(c+148,"acc_left", false,-1, 31,0);
    tracep->declBit(c+149,"init_next", false,-1);
    tracep->declBit(c+150,"init_next_next", false,-1);
    tracep->declBit(c+151,"exec_next", false,-1);
    tracep->declBit(c+152,"exec_next_next", false,-1);
    tracep->declBus(c+153,"m2", false,-1, 31,0);
    tracep->declBus(c+154,"d2", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("genblk1[1] ");
    tracep->pushNamePrefix("core ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+7,"init", false,-1);
    tracep->declBit(c+236,"mat_v", false,-1);
    tracep->declBus(c+1,"mat_a", false,-1, 5,0);
    tracep->declArray(c+298,"mat_d", false,-1, 1023,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 5,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBus(c+155,"acc_next", false,-1, 31,0);
    tracep->declBus(c+156,"acc", false,-1, 31,0);
    tracep->declBus(c+157,"exec_mat_data", false,-1, 31,0);
    tracep->declBus(c+158,"acc_right", false,-1, 31,0);
    tracep->declBus(c+159,"acc_left", false,-1, 31,0);
    tracep->declBit(c+160,"init_next", false,-1);
    tracep->declBit(c+161,"init_next_next", false,-1);
    tracep->declBit(c+162,"exec_next", false,-1);
    tracep->declBit(c+163,"exec_next_next", false,-1);
    tracep->declBus(c+164,"m2", false,-1, 31,0);
    tracep->declBus(c+165,"d2", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("genblk1[2] ");
    tracep->pushNamePrefix("core ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+7,"init", false,-1);
    tracep->declBit(c+237,"mat_v", false,-1);
    tracep->declBus(c+1,"mat_a", false,-1, 5,0);
    tracep->declArray(c+298,"mat_d", false,-1, 1023,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 5,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBus(c+166,"acc_next", false,-1, 31,0);
    tracep->declBus(c+167,"acc", false,-1, 31,0);
    tracep->declBus(c+168,"exec_mat_data", false,-1, 31,0);
    tracep->declBus(c+169,"acc_right", false,-1, 31,0);
    tracep->declBus(c+170,"acc_left", false,-1, 31,0);
    tracep->declBit(c+171,"init_next", false,-1);
    tracep->declBit(c+172,"init_next_next", false,-1);
    tracep->declBit(c+173,"exec_next", false,-1);
    tracep->declBit(c+174,"exec_next_next", false,-1);
    tracep->declBus(c+175,"m2", false,-1, 31,0);
    tracep->declBus(c+176,"d2", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("genblk1[3] ");
    tracep->pushNamePrefix("core ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+7,"init", false,-1);
    tracep->declBit(c+238,"mat_v", false,-1);
    tracep->declBus(c+1,"mat_a", false,-1, 5,0);
    tracep->declArray(c+298,"mat_d", false,-1, 1023,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+11,"exec_mat_addr", false,-1, 5,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->declBus(c+177,"acc_next", false,-1, 31,0);
    tracep->declBus(c+178,"acc", false,-1, 31,0);
    tracep->declBus(c+179,"exec_mat_data", false,-1, 31,0);
    tracep->declBus(c+180,"acc_right", false,-1, 31,0);
    tracep->declBus(c+181,"acc_left", false,-1, 31,0);
    tracep->declBit(c+182,"init_next", false,-1);
    tracep->declBit(c+183,"init_next_next", false,-1);
    tracep->declBit(c+184,"exec_next", false,-1);
    tracep->declBit(c+185,"exec_next_next", false,-1);
    tracep->declBus(c+186,"m2", false,-1, 31,0);
    tracep->declBus(c+187,"d2", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("mat_ctrl ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+334,"rst", false,-1);
    tracep->declBit(c+212,"matw", false,-1);
    tracep->declBit(c+332,"src_valid", false,-1);
    tracep->declBus(c+228,"mat_v", false,-1, 3,0);
    tracep->declBus(c+1,"mat_a", false,-1, 5,0);
    tracep->declBus(c+188,"core_sel", false,-1, 1,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("out_ctrl ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+5,"s_init", false,-1);
    tracep->declBit(c+7,"k_init", false,-1);
    tracep->declBit(c+8,"k_fin", false,-1);
    tracep->declBit(c+12,"out_busy", false,-1);
    tracep->declBit(c+13,"out_period", false,-1);
    tracep->declBit(c+14,"out_fin", false,-1);
    tracep->declBus(c+15,"out_addr", false,-1, 3,0);
    tracep->declBit(c+16,"update", false,-1);
    tracep->declBus(c+189,"out_addr_pre", false,-1, 3,0);
    tracep->declBit(c+190,"last_i", false,-1);
    tracep->declBit(c+191,"last_j", false,-1);
    tracep->declBus(c+192,"i", false,-1, 1,0);
    tracep->declBus(c+193,"j", false,-1, 1,0);
    tracep->declBit(c+194,"last_j_next", false,-1);
    tracep->declBit(c+195,"out_period_pre", false,-1);
    tracep->declBit(c+196,"update_after_start", false,-1);
    tracep->declBit(c+197,"start", false,-1);
    tracep->declBit(c+198,"k_fin_retention", false,-1);
    tracep->declBit(c+199,"j_period", false,-1);
    tracep->pushNamePrefix("d_j_period ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+197,"in", false,-1, 0,0);
    tracep->declBus(c+199,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+200,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_out_busy ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+201,"in", false,-1, 0,0);
    tracep->declBus(c+12,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+202,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("d_out_busy1 ");
    tracep->declBus(c+336,"W", false,-1, 31,0);
    tracep->declBus(c+203,"in", false,-1, 0,0);
    tracep->declBus(c+198,"data", false,-1, 0,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+204,"en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_i ");
    tracep->declBus(c+340,"W", false,-1, 31,0);
    tracep->declBus(c+341,"ini", false,-1, 1,0);
    tracep->declBus(c+342,"fin", false,-1, 1,0);
    tracep->declBus(c+192,"data", false,-1, 1,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+5,"start", false,-1);
    tracep->declBit(c+191,"en", false,-1);
    tracep->declBit(c+190,"last", false,-1);
    tracep->declBit(c+205,"run", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("l_j ");
    tracep->declBus(c+340,"W", false,-1, 31,0);
    tracep->declBus(c+341,"ini", false,-1, 1,0);
    tracep->declBus(c+342,"fin", false,-1, 1,0);
    tracep->declBus(c+193,"data", false,-1, 1,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+227,"rst", false,-1);
    tracep->declBit(c+197,"start", false,-1);
    tracep->declBit(c+339,"en", false,-1);
    tracep->declBit(c+191,"last", false,-1);
    tracep->declBit(c+206,"run", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("p_ctrl ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+211,"run", false,-1);
    tracep->declBit(c+230,"src_fin", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->declBit(c+231,"s_fin_in", false,-1);
    tracep->declBit(c+4,"p", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("s_ctrl ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+211,"run", false,-1);
    tracep->declBit(c+213,"last", false,-1);
    tracep->declBit(c+296,"dst_ready", false,-1);
    tracep->declBit(c+6,"s_fin", false,-1);
    tracep->declBit(c+230,"src_fin", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->declBit(c+4,"p", false,-1);
    tracep->declBit(c+231,"s_fin_in", false,-1);
    tracep->declBit(c+5,"s_init", false,-1);
    tracep->declBit(c+207,"s_fin_dayo", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("src_buf ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+229,"src_v", false,-1);
    tracep->declBus(c+208,"src_a", false,-1, 8,0);
    tracep->declArray(c+298,"src_d", false,-1, 1023,0);
    tracep->declBit(c+9,"exec", false,-1);
    tracep->declBus(c+209,"exec_src_addr", false,-1, 8,0);
    tracep->declBus(c+17,"exec_src_data", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("src_ctrl ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+212,"matw", false,-1);
    tracep->declBit(c+211,"run", false,-1);
    tracep->declBit(c+332,"src_valid", false,-1);
    tracep->declBus(c+3,"src_en", false,-1, 1,0);
    tracep->declBit(c+297,"src_ready", false,-1);
    tracep->declBit(c+229,"src_v", false,-1);
    tracep->declBus(c+2,"src_a", false,-1, 7,0);
    tracep->declBit(c+230,"src_fin", false,-1);
    tracep->declBit(c+239,"sen", false,-1);
    tracep->declBit(c+229,"start", false,-1);
    tracep->declBit(c+230,"last_i", false,-1);
    tracep->declBus(c+2,"i", false,-1, 7,0);
    tracep->pushNamePrefix("l_i ");
    tracep->declBus(c+346,"W", false,-1, 31,0);
    tracep->declBus(c+347,"ini", false,-1, 7,0);
    tracep->declBus(c+348,"fin", false,-1, 7,0);
    tracep->declBus(c+349,"param", false,-1, 7,0);
    tracep->declBus(c+2,"data", false,-1, 7,0);
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+335,"rst", false,-1);
    tracep->declBit(c+229,"start", false,-1);
    tracep->declBit(c+239,"en", false,-1);
    tracep->declBit(c+230,"last", false,-1);
    tracep->declBit(c+210,"run", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("src_en_ctrl ");
    tracep->declBit(c+259,"clk", false,-1);
    tracep->declBit(c+211,"run", false,-1);
    tracep->declBit(c+230,"src_fin", false,-1);
    tracep->declBit(c+4,"p", false,-1);
    tracep->declBit(c+231,"s_fin_in", false,-1);
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
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
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
    bufp->fullCData(oldp+1,(vlSelf->top__DOT__mat_a),6);
    bufp->fullCData(oldp+2,(vlSelf->top__DOT__src_ctrl__DOT__i),8);
    bufp->fullCData(oldp+3,(vlSelf->top__DOT__src_en),2);
    bufp->fullBit(oldp+4,(vlSelf->top__DOT__p));
    bufp->fullBit(oldp+5,(vlSelf->top__DOT__s_init));
    bufp->fullBit(oldp+6,(vlSelf->top__DOT__s_fin));
    bufp->fullBit(oldp+7,(vlSelf->top__DOT__k_init));
    bufp->fullBit(oldp+8,(vlSelf->top__DOT__k_fin));
    bufp->fullBit(oldp+9,(vlSelf->top__DOT__exec));
    bufp->fullCData(oldp+10,((0xffU & (((IData)(vlSelf->top__DOT__exe_ctrl__DOT__i) 
                                        << 6U) + (IData)(vlSelf->top__DOT__exe_ctrl__DOT__j)))),8);
    bufp->fullCData(oldp+11,(vlSelf->top__DOT__exe_ctrl__DOT__j),6);
    bufp->fullBit(oldp+12,(vlSelf->top__DOT__out_busy));
    bufp->fullBit(oldp+13,(vlSelf->top__DOT__out_period));
    bufp->fullBit(oldp+14,(vlSelf->top__DOT__out_fin));
    bufp->fullCData(oldp+15,(vlSelf->top__DOT__out_addr),4);
    bufp->fullBit(oldp+16,(vlSelf->top__DOT__update));
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
    bufp->fullWData(oldp+27,(vlSelf->top__DOT__dst_buf__DOT__stream_0),1024);
    bufp->fullWData(oldp+59,(vlSelf->top__DOT__dst_buf__DOT__stream_1),1024);
    bufp->fullIData(oldp+91,(vlSelf->top__DOT__dst_buf__DOT__buff0[0]),32);
    bufp->fullIData(oldp+92,(vlSelf->top__DOT__dst_buf__DOT__buff0[1]),32);
    bufp->fullIData(oldp+93,(vlSelf->top__DOT__dst_buf__DOT__buff0[2]),32);
    bufp->fullIData(oldp+94,(vlSelf->top__DOT__dst_buf__DOT__buff0[3]),32);
    bufp->fullIData(oldp+95,(vlSelf->top__DOT__dst_buf__DOT__buff0[4]),32);
    bufp->fullIData(oldp+96,(vlSelf->top__DOT__dst_buf__DOT__buff0[5]),32);
    bufp->fullIData(oldp+97,(vlSelf->top__DOT__dst_buf__DOT__buff0[6]),32);
    bufp->fullIData(oldp+98,(vlSelf->top__DOT__dst_buf__DOT__buff0[7]),32);
    bufp->fullIData(oldp+99,(vlSelf->top__DOT__dst_buf__DOT__buff1[0]),32);
    bufp->fullIData(oldp+100,(vlSelf->top__DOT__dst_buf__DOT__buff1[1]),32);
    bufp->fullIData(oldp+101,(vlSelf->top__DOT__dst_buf__DOT__buff1[2]),32);
    bufp->fullIData(oldp+102,(vlSelf->top__DOT__dst_buf__DOT__buff1[3]),32);
    bufp->fullIData(oldp+103,(vlSelf->top__DOT__dst_buf__DOT__buff1[4]),32);
    bufp->fullIData(oldp+104,(vlSelf->top__DOT__dst_buf__DOT__buff1[5]),32);
    bufp->fullIData(oldp+105,(vlSelf->top__DOT__dst_buf__DOT__buff1[6]),32);
    bufp->fullIData(oldp+106,(vlSelf->top__DOT__dst_buf__DOT__buff1[7]),32);
    bufp->fullIData(oldp+107,(vlSelf->top__DOT__dst_buf__DOT__buff2[0]),32);
    bufp->fullIData(oldp+108,(vlSelf->top__DOT__dst_buf__DOT__buff2[1]),32);
    bufp->fullIData(oldp+109,(vlSelf->top__DOT__dst_buf__DOT__buff2[2]),32);
    bufp->fullIData(oldp+110,(vlSelf->top__DOT__dst_buf__DOT__buff2[3]),32);
    bufp->fullIData(oldp+111,(vlSelf->top__DOT__dst_buf__DOT__buff2[4]),32);
    bufp->fullIData(oldp+112,(vlSelf->top__DOT__dst_buf__DOT__buff2[5]),32);
    bufp->fullIData(oldp+113,(vlSelf->top__DOT__dst_buf__DOT__buff2[6]),32);
    bufp->fullIData(oldp+114,(vlSelf->top__DOT__dst_buf__DOT__buff2[7]),32);
    bufp->fullIData(oldp+115,(vlSelf->top__DOT__dst_buf__DOT__buff3[0]),32);
    bufp->fullIData(oldp+116,(vlSelf->top__DOT__dst_buf__DOT__buff3[1]),32);
    bufp->fullIData(oldp+117,(vlSelf->top__DOT__dst_buf__DOT__buff3[2]),32);
    bufp->fullIData(oldp+118,(vlSelf->top__DOT__dst_buf__DOT__buff3[3]),32);
    bufp->fullIData(oldp+119,(vlSelf->top__DOT__dst_buf__DOT__buff3[4]),32);
    bufp->fullIData(oldp+120,(vlSelf->top__DOT__dst_buf__DOT__buff3[5]),32);
    bufp->fullIData(oldp+121,(vlSelf->top__DOT__dst_buf__DOT__buff3[6]),32);
    bufp->fullIData(oldp+122,(vlSelf->top__DOT__dst_buf__DOT__buff3[7]),32);
    bufp->fullBit(oldp+123,(vlSelf->top__DOT__dst_ctrl__DOT__start_check));
    bufp->fullBit(oldp+124,(vlSelf->top__DOT__dst_ctrl__DOT__stream_active));
    bufp->fullBit(oldp+125,(vlSelf->top__DOT__dst_ctrl__DOT__l_da__DOT__run));
    bufp->fullBit(oldp+126,(vlSelf->top__DOT__exe_ctrl__DOT__last_i));
    bufp->fullBit(oldp+127,(vlSelf->top__DOT__exe_ctrl__DOT__last_j));
    bufp->fullBit(oldp+128,(((IData)(vlSelf->top__DOT__s_init) 
                             | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre))));
    bufp->fullBit(oldp+129,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                             | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))));
    bufp->fullCData(oldp+130,(vlSelf->top__DOT__exe_ctrl__DOT__i),2);
    bufp->fullBit(oldp+131,(vlSelf->top__DOT__exe_ctrl__DOT__s_init_delay));
    bufp->fullBit(oldp+132,(vlSelf->top__DOT__exe_ctrl__DOT__k_init_next));
    bufp->fullBit(oldp+133,(vlSelf->top__DOT__exe_ctrl__DOT__start));
    bufp->fullBit(oldp+134,(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period));
    bufp->fullBit(oldp+135,(((IData)(vlSelf->top__DOT__k_init) 
                             | ((IData)(vlSelf->top__DOT__exec) 
                                & (~ (IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_j))))));
    bufp->fullBit(oldp+136,((((IData)(vlSelf->top__DOT__s_init) 
                              | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre)) 
                             & (~ (IData)(vlSelf->top__DOT__s_init)))));
    bufp->fullBit(oldp+137,((1U & ((~ (IData)(vlSelf->top__DOT__out_busy)) 
                                   | ((IData)(vlSelf->top__DOT__exe_ctrl__DOT__start) 
                                      | (IData)(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre))))));
    bufp->fullBit(oldp+138,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__s_fin_period) 
                             & (IData)(vlSelf->top__DOT__out_fin))));
    bufp->fullBit(oldp+139,(((IData)(vlSelf->top__DOT__exe_ctrl__DOT__last_i) 
                             | (IData)(vlSelf->top__DOT__out_fin))));
    bufp->fullBit(oldp+140,(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__next_pre));
    bufp->fullBit(oldp+141,(vlSelf->top__DOT__exe_ctrl__DOT__l_i__DOT__run));
    bufp->fullBit(oldp+142,(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__next_pre));
    bufp->fullBit(oldp+143,(vlSelf->top__DOT__exe_ctrl__DOT__l_j__DOT__run));
    bufp->fullIData(oldp+144,(vlSelf->top__DOT__acc
                              [1U]),32);
    bufp->fullIData(oldp+145,(((IData)(vlSelf->top__DOT__update)
                                ? vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left
                                : vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right)),32);
    bufp->fullIData(oldp+146,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_mat_data),32);
    bufp->fullIData(oldp+147,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_right),32);
    bufp->fullIData(oldp+148,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__acc_left),32);
    bufp->fullBit(oldp+149,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next));
    bufp->fullBit(oldp+150,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__init_next_next));
    bufp->fullBit(oldp+151,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next));
    bufp->fullBit(oldp+152,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__exec_next_next));
    bufp->fullIData(oldp+153,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__m2),32);
    bufp->fullIData(oldp+154,(vlSelf->top__DOT__genblk1__BRA__0__KET____DOT__core__DOT__d2),32);
    bufp->fullIData(oldp+155,(vlSelf->top__DOT__acc
                              [2U]),32);
    bufp->fullIData(oldp+156,(((IData)(vlSelf->top__DOT__update)
                                ? vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left
                                : vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right)),32);
    bufp->fullIData(oldp+157,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_mat_data),32);
    bufp->fullIData(oldp+158,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_right),32);
    bufp->fullIData(oldp+159,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__acc_left),32);
    bufp->fullBit(oldp+160,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next));
    bufp->fullBit(oldp+161,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__init_next_next));
    bufp->fullBit(oldp+162,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next));
    bufp->fullBit(oldp+163,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__exec_next_next));
    bufp->fullIData(oldp+164,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__m2),32);
    bufp->fullIData(oldp+165,(vlSelf->top__DOT__genblk1__BRA__1__KET____DOT__core__DOT__d2),32);
    bufp->fullIData(oldp+166,(vlSelf->top__DOT__acc
                              [3U]),32);
    bufp->fullIData(oldp+167,(((IData)(vlSelf->top__DOT__update)
                                ? vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left
                                : vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right)),32);
    bufp->fullIData(oldp+168,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_mat_data),32);
    bufp->fullIData(oldp+169,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_right),32);
    bufp->fullIData(oldp+170,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__acc_left),32);
    bufp->fullBit(oldp+171,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next));
    bufp->fullBit(oldp+172,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__init_next_next));
    bufp->fullBit(oldp+173,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next));
    bufp->fullBit(oldp+174,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__exec_next_next));
    bufp->fullIData(oldp+175,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__m2),32);
    bufp->fullIData(oldp+176,(vlSelf->top__DOT__genblk1__BRA__2__KET____DOT__core__DOT__d2),32);
    bufp->fullIData(oldp+177,(vlSelf->top__DOT__acc
                              [4U]),32);
    bufp->fullIData(oldp+178,(((IData)(vlSelf->top__DOT__update)
                                ? vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left
                                : vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right)),32);
    bufp->fullIData(oldp+179,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_mat_data),32);
    bufp->fullIData(oldp+180,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_right),32);
    bufp->fullIData(oldp+181,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__acc_left),32);
    bufp->fullBit(oldp+182,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next));
    bufp->fullBit(oldp+183,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__init_next_next));
    bufp->fullBit(oldp+184,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next));
    bufp->fullBit(oldp+185,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__exec_next_next));
    bufp->fullIData(oldp+186,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__m2),32);
    bufp->fullIData(oldp+187,(vlSelf->top__DOT__genblk1__BRA__3__KET____DOT__core__DOT__d2),32);
    bufp->fullCData(oldp+188,(vlSelf->top__DOT__mat_ctrl__DOT__core_sel),2);
    bufp->fullCData(oldp+189,(vlSelf->top__DOT__out_ctrl__DOT__out_addr_pre),4);
    bufp->fullBit(oldp+190,((((3U == (IData)(vlSelf->top__DOT__out_ctrl__DOT__i)) 
                              & ((IData)(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run) 
                                 | (IData)(vlSelf->top__DOT__s_init))) 
                             & (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))));
    bufp->fullBit(oldp+191,(vlSelf->top__DOT__out_ctrl__DOT__last_j));
    bufp->fullCData(oldp+192,(vlSelf->top__DOT__out_ctrl__DOT__i),2);
    bufp->fullCData(oldp+193,(vlSelf->top__DOT__out_ctrl__DOT__j),2);
    bufp->fullBit(oldp+194,(vlSelf->top__DOT__out_ctrl__DOT__last_j_next));
    bufp->fullBit(oldp+195,(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre));
    bufp->fullBit(oldp+196,(vlSelf->top__DOT__out_ctrl__DOT__update_after_start));
    bufp->fullBit(oldp+197,(vlSelf->top__DOT__out_ctrl__DOT__start));
    bufp->fullBit(oldp+198,(vlSelf->top__DOT__out_ctrl__DOT__k_fin_retention));
    bufp->fullBit(oldp+199,(vlSelf->top__DOT__out_ctrl__DOT__j_period));
    bufp->fullBit(oldp+200,(((IData)(vlSelf->top__DOT__out_ctrl__DOT__start) 
                             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j))));
    bufp->fullBit(oldp+201,(((IData)(vlSelf->top__DOT__k_init) 
                             & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre))));
    bufp->fullBit(oldp+202,((((IData)(vlSelf->top__DOT__k_init) 
                              & (IData)(vlSelf->top__DOT__out_ctrl__DOT__out_period_pre)) 
                             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))));
    bufp->fullBit(oldp+203,(((IData)(vlSelf->top__DOT__k_fin) 
                             & (IData)(vlSelf->top__DOT__out_busy))));
    bufp->fullBit(oldp+204,((((IData)(vlSelf->top__DOT__k_fin) 
                              & (IData)(vlSelf->top__DOT__out_busy)) 
                             | (IData)(vlSelf->top__DOT__out_ctrl__DOT__last_j_next))));
    bufp->fullBit(oldp+205,(vlSelf->top__DOT__out_ctrl__DOT__l_i__DOT__run));
    bufp->fullBit(oldp+206,(vlSelf->top__DOT__out_ctrl__DOT__l_j__DOT__run));
    bufp->fullBit(oldp+207,(vlSelf->top__DOT__s_ctrl__DOT__s_fin_dayo));
    bufp->fullSData(oldp+208,(vlSelf->top__DOT____Vcellinp__src_buf__src_a),9);
    bufp->fullSData(oldp+209,(vlSelf->top__DOT____Vcellinp__src_buf__exec_src_addr),9);
    bufp->fullBit(oldp+210,(vlSelf->top__DOT__src_ctrl__DOT__l_i__DOT__run));
    bufp->fullBit(oldp+211,(vlSelf->top__DOT__run));
    bufp->fullBit(oldp+212,(vlSelf->top__DOT__matw));
    bufp->fullBit(oldp+213,(vlSelf->top__DOT__last));
    bufp->fullCData(oldp+214,(vlSelf->top__DOT__state),4);
    bufp->fullSData(oldp+215,(vlSelf->top__DOT__write_addr),10);
    bufp->fullSData(oldp+216,(vlSelf->top__DOT__read_addr),10);
    bufp->fullIData(oldp+217,(vlSelf->top__DOT__write_data),32);
    bufp->fullBit(oldp+218,((0U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+219,((1U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+220,((2U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+221,((3U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+222,((4U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+223,((8U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullIData(oldp+224,(vlSelf->top__DOT__control),32);
    bufp->fullBit(oldp+225,(vlSelf->top__DOT__register_w));
    bufp->fullBit(oldp+226,((IData)(((4U == (IData)(vlSelf->top__DOT__state)) 
                                     & (0U == (0x300U 
                                               & (IData)(vlSelf->top__DOT__read_addr)))))));
    bufp->fullBit(oldp+227,((1U & (~ (IData)(vlSelf->top__DOT__run)))));
    bufp->fullCData(oldp+228,(vlSelf->top__DOT__mat_v),4);
    bufp->fullBit(oldp+229,(vlSelf->top__DOT__src_ctrl__DOT__start));
    bufp->fullBit(oldp+230,(vlSelf->top__DOT__src_ctrl__DOT__last_i));
    bufp->fullBit(oldp+231,(vlSelf->top__DOT__s_fin_in));
    bufp->fullBit(oldp+232,(vlSelf->top__DOT__stream_v));
    bufp->fullBit(oldp+233,(vlSelf->top__DOT__dst_ctrl__DOT__last_i));
    bufp->fullBit(oldp+234,(vlSelf->top__DOT__dst_ctrl__DOT__start));
    bufp->fullBit(oldp+235,((1U & (IData)(vlSelf->top__DOT__mat_v))));
    bufp->fullBit(oldp+236,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                   >> 1U))));
    bufp->fullBit(oldp+237,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                   >> 2U))));
    bufp->fullBit(oldp+238,((1U & ((IData)(vlSelf->top__DOT__mat_v) 
                                   >> 3U))));
    bufp->fullBit(oldp+239,(vlSelf->top__DOT__src_ctrl__DOT__sen));
    bufp->fullBit(oldp+240,(vlSelf->S_AXI_ACLK));
    bufp->fullBit(oldp+241,(vlSelf->S_AXI_ARESETN));
    bufp->fullIData(oldp+242,(vlSelf->S_AXI_AWADDR),32);
    bufp->fullBit(oldp+243,(vlSelf->S_AXI_AWVALID));
    bufp->fullBit(oldp+244,(vlSelf->S_AXI_AWREADY));
    bufp->fullIData(oldp+245,(vlSelf->S_AXI_WDATA),32);
    bufp->fullCData(oldp+246,(vlSelf->S_AXI_WSTRB),4);
    bufp->fullBit(oldp+247,(vlSelf->S_AXI_WVALID));
    bufp->fullBit(oldp+248,(vlSelf->S_AXI_WREADY));
    bufp->fullCData(oldp+249,(vlSelf->S_AXI_BRESP),2);
    bufp->fullBit(oldp+250,(vlSelf->S_AXI_BVALID));
    bufp->fullBit(oldp+251,(vlSelf->S_AXI_BREADY));
    bufp->fullIData(oldp+252,(vlSelf->S_AXI_ARADDR),32);
    bufp->fullBit(oldp+253,(vlSelf->S_AXI_ARVALID));
    bufp->fullBit(oldp+254,(vlSelf->S_AXI_ARREADY));
    bufp->fullIData(oldp+255,(vlSelf->S_AXI_RDATA),32);
    bufp->fullCData(oldp+256,(vlSelf->S_AXI_RRESP),2);
    bufp->fullBit(oldp+257,(vlSelf->S_AXI_RVALID));
    bufp->fullBit(oldp+258,(vlSelf->S_AXI_RREADY));
    bufp->fullBit(oldp+259,(vlSelf->AXIS_ACLK));
    bufp->fullBit(oldp+260,(vlSelf->AXIS_ARESETN));
    bufp->fullBit(oldp+261,(vlSelf->M_AXIS_TVALID));
    bufp->fullWData(oldp+262,(vlSelf->M_AXIS_TDATA),1024);
    bufp->fullCData(oldp+294,(vlSelf->M_AXIS_TSTRB),8);
    bufp->fullBit(oldp+295,(vlSelf->M_AXIS_TLAST));
    bufp->fullBit(oldp+296,(vlSelf->M_AXIS_TREADY));
    bufp->fullBit(oldp+297,(vlSelf->S_AXIS_TREADY));
    bufp->fullWData(oldp+298,(vlSelf->S_AXIS_TDATA),1024);
    bufp->fullCData(oldp+330,(vlSelf->S_AXIS_TSTRB),8);
    bufp->fullBit(oldp+331,(vlSelf->S_AXIS_TLAST));
    bufp->fullBit(oldp+332,(vlSelf->S_AXIS_TVALID));
    bufp->fullBit(oldp+333,((((IData)(vlSelf->top__DOT__s_fin_in) 
                              | (IData)(vlSelf->top__DOT__dst_ctrl__DOT__stream_active)) 
                             & (~ (IData)(vlSelf->top__DOT__dst_ctrl__DOT__last_i)))));
    bufp->fullBit(oldp+334,((1U & (~ (IData)(vlSelf->AXIS_ARESETN)))));
    bufp->fullBit(oldp+335,((1U & ((~ (IData)(vlSelf->S_AXIS_TREADY)) 
                                   | (~ (IData)(vlSelf->top__DOT__run))))));
    bufp->fullIData(oldp+336,(1U),32);
    bufp->fullIData(oldp+337,(3U),32);
    bufp->fullCData(oldp+338,(0U),3);
    bufp->fullBit(oldp+339,(1U));
    bufp->fullIData(oldp+340,(2U),32);
    bufp->fullCData(oldp+341,(0U),2);
    bufp->fullCData(oldp+342,(3U),2);
    bufp->fullIData(oldp+343,(6U),32);
    bufp->fullCData(oldp+344,(0U),6);
    bufp->fullCData(oldp+345,(0x3fU),6);
    bufp->fullIData(oldp+346,(8U),32);
    bufp->fullCData(oldp+347,(0U),8);
    bufp->fullCData(oldp+348,(0xe0U),8);
    bufp->fullCData(oldp+349,(0x20U),8);
}
