module top (
   clk,
   rst,
   led,
   anode,
   seg
);

   // ポート (トップのポートはwire??)
   input wire clk, rst;
   output wire [15:0] led;
   output logic [3:0] anode;     // wire
   output logic [6:0] seg;       // wire

   // CoreとSevenを繋ぐ架け橋
   wire [31:0] data_seg;
   assign led = data_seg[15:0];

//    // 同期クロック生成
//    // 1000分周
// 10万分周
   reg [31:0] count; // こいつinialの初期化いるかも？
   initial begin
      count = 32'd0;
   end
   always_ff @(posedge clk) begin
     if (rst) count <= 32'd0;
     else if (count == 32'd10) count <= 32'd0;
     else count <= count + 32'd1;
   end
   wire sysclk = (count > 32'd5) ? 1'b0 : 1'b1;
//    // CoreとSevenのclkをsysclkに変更

   // RISC-V core
   // input: clk, rst
   // output: data_seg
   core Core (
      .clk(sysclk),
      .rst(rst),

      .data_seg(data_seg)
   );

   // Dynamic display of 7 seg led
   // input: clk, rst, data_seg
   // output: anode, seg
   seven Seven (
      .clk(sysclk),
      .rst(rst),
      .data_seg(data_seg),

      .anode(anode),
      .seg(seg)
   );

endmodule
