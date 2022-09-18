`default_nettype none

module src_buf
    (
        input wire        clk,
        input wire        src_v,
        input wire [10:0]  src_a,
        input wire [63:0] src_d,
        input wire        exec,
        input wire [10:0]  exec_src_addr,

        output reg [31:0] exec_src_data
    );

    // 32bitのデータを128個 各コアに格納
    // つまり128*8=1024確保

    // buff0とbuff1はp_ctrlで選択するやつ

    // buff0----------------------------------------------------------
    reg [31:0]        buff0 [0:1023];

    always_ff @(posedge clk) begin
                  if(src_v & ~src_a[10]) begin
                      buff0[src_a[9:0]] <= src_d[31:0];
                  end
              end;

    always_ff @(posedge clk) begin
                  if(src_v & ~src_a[10]) begin
                      buff0[src_a[9:0]+1'b1] <= src_d[63:32];
                  end
                  if(exec & ~exec_src_addr[10]) begin
                      exec_src_data <= buff0[exec_src_addr[9:0]];
                  end
              end;

    // buff1----------------------------------------------------------
    reg [31:0]        buff1 [0:1023];

    always_ff @(posedge clk) begin
                  if(src_v & src_a[10]) begin
                      buff1[src_a[9:0]] <= src_d[31:0];
                  end
              end;

    always_ff @(posedge clk) begin
                  if(src_v & src_a[10]) begin
                      buff1[src_a[9:0]+1'b1] <= src_d[63:32];
                  end
                  if(exec & exec_src_addr[10]) begin
                      exec_src_data <= buff1[exec_src_addr[9:0]];
                  end
              end;

endmodule

`default_nettype wire
