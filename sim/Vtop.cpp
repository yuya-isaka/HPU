// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtop.h"
#include "Vtop__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vtop::Vtop(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtop__Syms(contextp(), _vcname__, this)}
    , S_AXI_ACLK{vlSymsp->TOP.S_AXI_ACLK}
    , AXIS_ACLK{vlSymsp->TOP.AXIS_ACLK}
    , S_AXI_ARESETN{vlSymsp->TOP.S_AXI_ARESETN}
    , S_AXI_AWVALID{vlSymsp->TOP.S_AXI_AWVALID}
    , S_AXI_AWREADY{vlSymsp->TOP.S_AXI_AWREADY}
    , S_AXI_WSTRB{vlSymsp->TOP.S_AXI_WSTRB}
    , S_AXI_WVALID{vlSymsp->TOP.S_AXI_WVALID}
    , S_AXI_WREADY{vlSymsp->TOP.S_AXI_WREADY}
    , S_AXI_BRESP{vlSymsp->TOP.S_AXI_BRESP}
    , S_AXI_BVALID{vlSymsp->TOP.S_AXI_BVALID}
    , S_AXI_BREADY{vlSymsp->TOP.S_AXI_BREADY}
    , S_AXI_ARVALID{vlSymsp->TOP.S_AXI_ARVALID}
    , S_AXI_ARREADY{vlSymsp->TOP.S_AXI_ARREADY}
    , S_AXI_RRESP{vlSymsp->TOP.S_AXI_RRESP}
    , S_AXI_RVALID{vlSymsp->TOP.S_AXI_RVALID}
    , S_AXI_RREADY{vlSymsp->TOP.S_AXI_RREADY}
    , AXIS_ARESETN{vlSymsp->TOP.AXIS_ARESETN}
    , M_AXIS_TVALID{vlSymsp->TOP.M_AXIS_TVALID}
    , M_AXIS_TSTRB{vlSymsp->TOP.M_AXIS_TSTRB}
    , M_AXIS_TLAST{vlSymsp->TOP.M_AXIS_TLAST}
    , M_AXIS_TREADY{vlSymsp->TOP.M_AXIS_TREADY}
    , S_AXIS_TREADY{vlSymsp->TOP.S_AXIS_TREADY}
    , S_AXIS_TSTRB{vlSymsp->TOP.S_AXIS_TSTRB}
    , S_AXIS_TLAST{vlSymsp->TOP.S_AXIS_TLAST}
    , S_AXIS_TVALID{vlSymsp->TOP.S_AXIS_TVALID}
    , S_AXI_AWADDR{vlSymsp->TOP.S_AXI_AWADDR}
    , S_AXI_WDATA{vlSymsp->TOP.S_AXI_WDATA}
    , S_AXI_ARADDR{vlSymsp->TOP.S_AXI_ARADDR}
    , S_AXI_RDATA{vlSymsp->TOP.S_AXI_RDATA}
    , M_AXIS_TDATA{vlSymsp->TOP.M_AXIS_TDATA}
    , S_AXIS_TDATA{vlSymsp->TOP.S_AXIS_TDATA}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtop::Vtop(const char* _vcname__)
    : Vtop(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtop::~Vtop() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vtop___024root___eval_initial(Vtop___024root* vlSelf);
void Vtop___024root___eval_settle(Vtop___024root* vlSelf);
void Vtop___024root___eval(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
void Vtop___024root___final(Vtop___024root* vlSelf);

static void _eval_initial_loop(Vtop__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vtop___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vtop___024root___eval_settle(&(vlSymsp->TOP));
        Vtop___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void Vtop::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtop___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vtop___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

const char* Vtop::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vtop::final() {
    Vtop___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtop::hierName() const { return vlSymsp->name(); }
const char* Vtop::modelName() const { return "Vtop"; }
unsigned Vtop::threads() const { return 1; }
std::unique_ptr<VerilatedTraceConfig> Vtop::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->scopeEscape(' ');
    tracep->pushNamePrefix(std::string{vlSymsp->name()} + ' ');
    Vtop___024root__trace_init_top(vlSelf, tracep);
    tracep->popNamePrefix();
    tracep->scopeEscape('.');
}

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vtop::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vtop___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
