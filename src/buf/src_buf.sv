`default_nettype none

module src_buf
    (
        input wire          clk,
        input wire          src_v,
        input wire [63:0]   src_d,

        output reg [31:0]   exec_src_data
    );

    always @(posedge clk) begin
                  if(src_v) begin // 偶数
                      exec_src_data <= src_d[31:0];
                  end
              end;


endmodule

`default_nettype wire
