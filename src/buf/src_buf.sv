`default_nettype none

module src_buf
    (
        input wire        clk,
        input wire        src_v,
        input wire [9:0]  src_a,
        input wire [63:0] src_d,
        input wire        exec,
        input wire [10:0]  exec_src_addr,

        output reg [31:0] exec_src_data
    );

    // 32bitのデータを128個 各コアに格納
    // つまり128*8=1024確保

    // buff0とbuff1はp_ctrlで選択するやつ

    always_ff @(posedge clk) begin
                  if(exec & ~exec_src_addr[10] & ~exec_src_addr[0]) begin // 偶数
                      exec_src_data <= buff0even[exec_src_addr[9:1]];
                  end
                  if(exec & ~exec_src_addr[10] & exec_src_addr[0]) begin // 奇数
                      exec_src_data <= buff0odd[exec_src_addr[9:1]];
                  end
                  if(exec & exec_src_addr[10]) begin
                      if (~exec_src_addr[0]) begin // 偶数
                          exec_src_data <= buff1even[exec_src_addr[9:1]];
                      end
                      if (exec_src_addr[0]) begin // 奇数
                          exec_src_data <= buff1odd[exec_src_addr[9:1]];
                      end
                  end
              end;

    // buff0----------------------------------------------------------
    reg [31:0]        buff0even [0:511];
    reg [31:0]        buff0odd [0:511];

    always_ff @(posedge clk) begin
                  if(src_v & ~src_a[9]) begin
                      buff0even[src_a[8:0]] <= src_d[31:0];
                      buff0odd[src_a[8:0]] <= src_d[63:32];
                  end
              end;

    // buff1----------------------------------------------------------
    reg [31:0]        buff1even [0:511];
    reg [31:0]        buff1odd [0:511];

    always_ff @(posedge clk) begin
                  if(src_v & src_a[9]) begin
                      buff1even[src_a[8:0]] <= src_d[31:0];
                      buff1odd[src_a[8:0]] <= src_d[63:32];
                  end
              end;

endmodule

`default_nettype wire
