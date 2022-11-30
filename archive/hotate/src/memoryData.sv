`default_nettype none

// module memoryData #(parameter MEM_SIZE = 32'd1024, parameter ADDR_SIZE = 32'd7)
module memoryData #(parameter ADDR_SIZE = 32'd7)
(
  clk,
  rst,
  read_addr,
  read_data,
  write_addr,
  write_data,
  write_enable
);

  // ポート
  input wire clk, rst;
  input wire [31:0] read_addr, write_addr, write_data;
  input wire write_enable;
  output reg [31:0] read_data; // always_ffで代入する先だから、reg??

  // parameter DWIDTH=16,AWIDTH=12,WORDS=4096;
  // べき乗演算「**」が使えるので，WORDSの代わりに， 2**AWIDTHを用いることができる??

  // MEM_SIZE = 4096
  // ADDR_SIZE = 10 (4096なら11までいける？)

  // RAM (BRAM)
  // (* ram_style = "block" *) reg [31:0] mem [MEM_SIZE-1:0]; // 多分reg
  (* ram_style = "block" *) reg [31:0] mem [2**(ADDR_SIZE-2+1)-1:0]; // 多分reg

  // 命令メモリと違って、readmemhしないため、初期化する必要がある。
  // メモリ初期化(全要素初期化しないと初期化が無視される)
  task init_mem;
    begin
      for(int i=0; i<(2**(ADDR_SIZE-2+1)); i++) begin
        mem[i] = 32'd0;
      end
    end
  endtask

  initial begin
    init_mem();
  end

  always_ff @(posedge clk) begin
    // リセットのたびに初期化
    // if (rst) begin
    //   init_mem();
    // end else begin
      // read
      read_data <= mem[read_addr[ADDR_SIZE:2]];
      // ↓ verilatorに怒られて変更
      // read_data <= mem[read_addr[ADDR_SIZE:0]];
      // write
      if (write_enable) begin
        mem[write_addr[ADDR_SIZE:2]] <= write_data;
        // 下位２ビットを入れると、0->4->8となる。
        // これを避けるために、下位２ビットを無視して、0->1->2とする
        // データのサイズが32ビットだから！！！！！
        // 4バイトごとのアドレスになっているのは正しい。でもmemの中では番地は0->1->2でやりたいから、下位２ビットを無視する
        // ↓ verilatorに怒られて変更
        // mem[write_addr[ADDR_SIZE:0]] <= write_data;
      end
    // end
  end

endmodule

`default_nettype wire
