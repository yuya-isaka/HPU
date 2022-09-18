// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VTOP_H_
#define VERILATED_VTOP_H_  // guard

#include "verilated.h"

class Vtop__Syms;
class Vtop___024root;
class VerilatedVcdC;

// This class is the main interface to the Verilated model
class Vtop VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vtop__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&S_AXI_ACLK,0,0);
    VL_IN8(&AXIS_ACLK,0,0);
    VL_IN8(&S_AXI_ARESETN,0,0);
    VL_IN8(&S_AXI_AWVALID,0,0);
    VL_OUT8(&S_AXI_AWREADY,0,0);
    VL_IN8(&S_AXI_WSTRB,3,0);
    VL_IN8(&S_AXI_WVALID,0,0);
    VL_OUT8(&S_AXI_WREADY,0,0);
    VL_OUT8(&S_AXI_BRESP,1,0);
    VL_OUT8(&S_AXI_BVALID,0,0);
    VL_IN8(&S_AXI_BREADY,0,0);
    VL_IN8(&S_AXI_ARVALID,0,0);
    VL_OUT8(&S_AXI_ARREADY,0,0);
    VL_OUT8(&S_AXI_RRESP,1,0);
    VL_OUT8(&S_AXI_RVALID,0,0);
    VL_IN8(&S_AXI_RREADY,0,0);
    VL_IN8(&AXIS_ARESETN,0,0);
    VL_OUT8(&M_AXIS_TVALID,0,0);
    VL_OUT8(&M_AXIS_TSTRB,7,0);
    VL_OUT8(&M_AXIS_TLAST,0,0);
    VL_IN8(&M_AXIS_TREADY,0,0);
    VL_OUT8(&S_AXIS_TREADY,0,0);
    VL_IN8(&S_AXIS_TSTRB,7,0);
    VL_IN8(&S_AXIS_TLAST,0,0);
    VL_IN8(&S_AXIS_TVALID,0,0);
    VL_IN(&S_AXI_AWADDR,31,0);
    VL_IN(&S_AXI_WDATA,31,0);
    VL_IN(&S_AXI_ARADDR,31,0);
    VL_OUT(&S_AXI_RDATA,31,0);
    VL_OUTW(&M_AXIS_TDATA,1023,0,32);
    VL_INW(&S_AXIS_TDATA,1023,0,32);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vtop___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vtop(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vtop(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vtop();
  private:
    VL_UNCOPYABLE(Vtop);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    std::unique_ptr<VerilatedTraceConfig> traceConfig() const override final;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
