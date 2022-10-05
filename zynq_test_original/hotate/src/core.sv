`default_nettype none

module core (
  clk,
  rst,
  data_seg
);

  // ポート
  input wire clk, rst;
  output wire [31:0] data_seg;

  // パラメータ ---------------------------------------------------------------------

  // parameter INST_MEM_SIZE = 32'd64;
  parameter INST_ADDR_SIZE = 32'd7;
  // parameter DATA_MEM_SIZE = 32'd512;
  parameter DATA_ADDR_SIZE = 32'd10;

  // PC (WBで更新)  ---------------------------------------------------------------------------

  // Program counter (regだからalways_ffで代入)
  reg [31:0] pc;

  // Initialize pc
  // regは初期化必要？
  // task init_pc;
  //   begin
  //     pc = 32'd0;
  //   end
  // endtask

  // Update led
  // assign led = pc[31:0];

  // State machine --------------------------------------------------------------------------------------------------

  // State (always_ffで代入するからreg)
  // logicでも良い
  // enumにできない？？
  reg state_idle, state_if, state_de, state_ex, state_ma, state_wb;

  // Initialize state
  // regは初期化必要
  // task init_state;
  //   begin
  //     state_idle = 1'b1;
  //     {state_if, state_de, state_ex, state_ma, state_wb} = 5'b0;
  //   end
  // endtask

  // FSM
  always_ff @(posedge clk) begin
    if (rst) begin
      state_idle <= 1'b1;
      {state_if, state_de, state_ex, state_ma, state_wb} <= 5'b0;
    end
    else begin
      if (state_idle) begin
        state_idle <= 1'b0;
        state_if <= 1'b1;
      end
      else if (state_if) begin
        state_if <= 1'b0;
        state_de <= 1'b1;
      end
      else if (state_de) begin
        state_de <= 1'b0;
        state_ex <= 1'b1;
      end
      else if (state_ex) begin
        state_ex <= 1'b0;
        state_ma <= 1'b1;
      end
      else if (state_ma) begin
        state_ma <= 1'b0;
        state_wb <= 1'b1;
      end
      else begin
        state_wb <= 1'b0;
        state_if <= 1'b1;
      end
    end
  end

  // Instruction Fetch ----------------------------------------------------------------------------------------

  // Instruction memory
  // ↓ Verilatorはunpackな構造体をpackにする
  typedef struct packed {
  // typedef struct {
    logic [31:0]  addr; // wire
    reg [31:0]    inst;
  } instruction_memory;

  instruction_memory imem;

  assign imem.addr = pc;

  memoryInstruction #(.ADDR_SIZE(INST_ADDR_SIZE)) Imem (
    .clk(clk),
    .rst(rst),

    .addr(imem.addr),
    .inst(imem.inst)
  );

  // Instruction Decode --------------------------------------------------------------------------------------------

  typedef struct packed {
  // typedef struct {
    logic [4:0]   rs1, rs2;   // wire
    logic [4:0]   rd;         // wire
    logic [2:0]   funct3;     // wire
    logic [6:0]   funct7;     // wire
    logic [31:0]  imm;        // wire
    logic         _arithmetic, _arithmetic_imm, _load, _store, _branch, _jal, _jalr, _lui, _auipc; // wire
  } instruction_decode;

  instruction_decode de;

  instructionDecode Decode (
    .inst(imem.inst),

    .rs1(de.rs1),
    .rs2(de.rs2),
    .rd(de.rd),

    .funct3(de.funct3),
    .funct7(de.funct7),

    .imm(de.imm),

    .arithmetic(de._arithmetic),
    .arithmetic_imm(de._arithmetic_imm),
    .load(de._load),
    .store(de._store),
    .branch(de._branch),
    .jal(de._jal),
    .jalr(de._jalr),
    .lui(de._lui),
    .auipc(de._auipc)
  );

  // Register ----------------------------------------------------------------------------------------------------

  // typedef struct packed {
  //   logic [31:0] rs1_data, rs2_data; // wire
  //   logic [31:0] rd_data; // wire
  // } register_file;

  // register_file rf;
  // verilator
  logic [31:0] rs1_data, rs2_data; // wire
  logic [31:0] rd_data; // wire

  // Register (always_ffで代入するからreg)
  // (むしろ値を持っておきたいから、regで、regだからalways_ffって方が正しいか、因果関係が逆)
  reg [31:0] register [31:0];

  // regの配列は初期化が必要（レジスタは初期化必要？）
  task init_rf;
    begin
      for(int i=0; i<32; i++) begin
        register[i] = 32'd0;
      end
    end
  endtask

  assign rs1_data = (de.rs1 == 5'd0) ? 32'd0 : register[de.rs1];
  assign rs2_data = (de.rs2 == 5'd0) ? 32'd0 : register[de.rs2];
  assign data_seg = register[5'd10];
  // assign data_seg = imem.inst;

  always_ff @(posedge clk) begin
    if (rst) begin
      init_rf();
    end
    else if (state_wb) begin
      register[de.rd] <= rd_data;
    end
  end

  // Execute ----------------------------------------------------------------------------------------------

  logic [31:0] alu_out; // wire

  // 演算
  alu Alu (
    .rs1_data(rs1_data),
    .rs2_data(rs2_data),

    .imm_data(de.imm),

    .funct3(de.funct3),
    .funct7(de.funct7),

    .arithmetic(de._arithmetic),
    .arithmetic_imm(de._arithmetic_imm),
    .load(de._load),
    .store(de._store),
    .branch(de._branch),

    .alu_out(alu_out)
  );


  // Memory Access --------------------------------------------------------------------------------------------------

  typedef struct packed {
  // typedef struct {
    logic [31:0]  read_addr, read_data, write_addr, write_data; // read_addr, write_addr, write_data ... wire
    logic         write_enable;
  } data_memory;

  data_memory dmem;

  // データメモリ読み込み
  assign dmem.read_addr = alu_out;
  // データメモリ書き込み
  assign dmem.write_addr = alu_out;
  // ↓verilatorに怒られたので変
  assign dmem.write_data = (de.funct3 == 3'b000) ? {24'b0, rs2_data[7:0]} :
                           (de.funct3 == 3'b001) ? {16'b0, rs2_data[15:0]} :
                           rs2_data;
  assign dmem.write_enable = state_ma && de._store;

  // データメモリ読み込み/書き込み
  memoryData #(.ADDR_SIZE(DATA_ADDR_SIZE)) Dmem (
    .clk(clk),
    .rst(rst),

    .read_addr(dmem.read_addr),
    .read_data(dmem.read_data),

    .write_addr(dmem.write_addr),
    .write_data(dmem.write_data),
    .write_enable(dmem.write_enable)
  );

  // Write back ---------------------------------------------------------------------------------------------------------

  always_comb begin
    if (de._jal || de._jalr) begin
      rd_data = pc + 32'd4;
    end
    else if (de._load) begin
      rd_data = dmem.read_data;
    end
    else if (de._lui) begin
      rd_data = de.imm;
    end
    else if (de._auipc) begin
      rd_data = pc + de.imm;
    end
    else begin
      rd_data = alu_out;
    end
  end

  // Update pc
  always_ff @(posedge clk) begin
    if (rst) begin
      pc <= 32'd0;
    end
    else begin
      if (state_wb) begin
        if (de._branch) begin
          if (alu_out != 32'b0) begin // 怒られた
            pc <= pc + de.imm;
          end
          else begin
            pc <= pc + 32'd4;
          end
        end
        else if (de._jal) begin
          pc <= pc + de.imm;
        end
        else if (de._jalr) begin
          pc <= rs1_data + de.imm;
        end
        else if (de._lui) begin
          pc <= pc + 32'd4;
        end
        else if (de._auipc) begin
          pc <= pc + 32'd4;
        end
        else begin
          pc <= pc + 32'd4;
        end
      end
    end
  end

  // Initialize ------------------------------------------------------------------------------------------

  initial begin
    // init_pc();
    // init_state();
    state_idle = 1'b1;
    {state_if, state_de, state_ex, state_ma, state_wb} = 5'b0;
    pc = 32'd0;
    init_rf();
  end

endmodule

`default_nettype wire
