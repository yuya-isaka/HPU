module dst_buf
    (
        input wire         clk,
        input wire         stream_v,
        input wire [3:0]   stream_a,
        input wire         out_period,
        input wire [4:0]   out_addr,
        input wire [31:0]  result,

        output wire [63:0] stream_d
    );

    reg [63:0]        stream_0;
    reg [63:0]        stream_1;

    assign stream_d = (stream_a[3]) ? stream_1 : stream_0;

    // 0
    ////////////////////////////////////////////////////////////////////////////

    reg [31:0]        buff0 [0:7]; // アドレス偶数
    reg [31:0]        buff1 [0:7]; // アドレス奇数

    always_ff @(posedge clk) begin
                  if(out_period&~out_addr[0]&~out_addr[4]) begin
                      buff0[out_addr[3:1]] <= result;
                  end
                  else if(stream_v&~stream_a[3]) begin
                      stream_0[31:0] <= buff0[stream_a[2:0]];
                  end
              end;

    always_ff @(posedge clk) begin
                  if(out_period& out_addr[0]&~out_addr[4]) begin
                      buff1[out_addr[3:1]] <= result;
                  end
                  else if(stream_v&~stream_a[3]) begin
                      stream_0[63:32] <= buff1[stream_a[2:0]];
                  end
              end;

    // 1
    ////////////////////////////////////////////////////////////////////////////

    reg [31:0]        buff2 [0:7]; // アドレス偶数
    reg [31:0]        buff3 [0:7]; // アドレス奇数

    always_ff @(posedge clk) begin
                  if(out_period&~out_addr[0]& out_addr[4]) begin
                      buff2[out_addr[3:1]] <= result;
                  end
                  else if(stream_v& stream_a[3]) begin
                      stream_1[31:0] <= buff2[stream_a[2:0]];
                  end
              end;

    always_ff @(posedge clk) begin
                  if(out_period& out_addr[0]& out_addr[4]) begin
                      buff3[out_addr[3:1]] <= result;
                  end
                  else if(stream_v& stream_a[3]) begin
                      stream_1[63:32] <= buff3[stream_a[2:0]];
                  end
              end;

endmodule
