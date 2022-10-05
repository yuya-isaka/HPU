`default_nettype none

module memoryInstruction #(parameter ADDR_SIZE = 32'd7)
(
  clk,
  rst,
  addr,
  inst
);

  // ポート
  input wire clk, rst;
  input wire [31:0] addr;
  output reg [31:0] inst; // always_ffで代入する先だから、reg??

  // MEM_SIZE = 1024
  // ADDR_SIZE = 9 (1024ならこれが最大？)

  // ROM (BRAM)
  // (* ram_style = "block" *) reg [31:0] mem [MEM_SIZE-1:0];
  (* ram_style = "block" *) reg [31:0] mem [2**(ADDR_SIZE-2+1)-1:0];

  initial begin
    // $readmemh("/home/isaka/hotate/test/fib.hex", mem);
    // $readmemh("/Users/yuyaisaka/workspace/project/project-riscv/hotate/test/fib.hex", mem);
    // $readmemh("/Users/yuyaisaka/workspace/project/project-riscv/hotate/test_mac/fib.hex", mem);
    // $readmemh("/Users/yuyaisaka/workspace/project/project-riscv/hotate/test_mac/factorial.hex", mem);
    $readmemh("/Users/yuyaisaka/workspace/project/project-zynq/zynq-project/src/sample/13_hdc/hotate/test_mac/fib.hex", mem);
  end

  // output (rstがfalseの時、クロックと同期して代入、最初のリセットだけ？)
  always_ff @(posedge clk) begin
    // リセットボタンが押されたときは、発動しなくて良い（readmemhで初期化されるから？）
    // 逆に常にクロックごとに代入する意味はなんだ？
    // if (!rst) begin
    inst <= mem[addr[ADDR_SIZE:2]];
      // ↓ verilatorに怒られて変更
      // inst <= mem[addr[ADDR_SIZE:0]];
    // end
  end

endmodule

`default_nettype wire
