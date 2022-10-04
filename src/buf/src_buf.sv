`default_nettype none

module src_buf
    (
        input wire          clk,
        input wire          src_v,
        input wire [18:0]    src_a,
        input wire [63:0]   src_d,
        input wire          exec,
        input wire [19:0]    exec_src_addr,
        input wire          p,

        output reg [31:0]   exec_src_data
    );

    // 32bitのデータを128個 各コアに格納
    // つまり128*8=1024確保

    // buff0とbuff1はp_ctrlで選択するやつ


    // buff0----------------------------------------------------------
    // アドレスが入ってくる
    // 2^20 = 1048576
    // １個当たり 524288
    // reg [31:0]        buff0even [0:524287];
    // reg [31:0]        buff0odd [0:524287];
    (* ram_style = "block" *) reg [31:0]        buff0even [0:1023];
    (* ram_style = "block" *) reg [31:0]        buff0odd [0:1023];


    // buff1----------------------------------------------------------
    (* ram_style = "block" *) reg [31:0]        buff1even [0:524287];
    (* ram_style = "block" *) reg [31:0]        buff1odd [0:524287];

    always_ff @(posedge clk) begin
                  if(src_v & ~p) begin
                      buff1even[src_a] <= src_d[31:0];
                      buff1odd[src_a] <= src_d[63:32];
                  end
                  if(src_v & p) begin
                      buff0even[src_a] <= src_d[31:0];
                      buff0odd[src_a] <= src_d[63:32];
                  end
                  if(exec & ~p) begin
                      if (~exec_src_addr[0]) begin // 偶数
                          exec_src_data <= buff0even[exec_src_addr[19:1]];
                      end
                      if (exec_src_addr[0]) begin // 奇数
                          exec_src_data <= buff0odd[exec_src_addr[19:1]];
                      end
                  end
                  if(exec & p) begin
                      if (~exec_src_addr[0]) begin // 偶数
                          exec_src_data <= buff1even[exec_src_addr[19:1]];
                      end
                      if (exec_src_addr[0]) begin // 奇数
                          exec_src_data <= buff1odd[exec_src_addr[19:1]];
                      end
                  end
              end;

endmodule

`default_nettype wire
