module dst_buf
    (
        input wire         clk,
        input wire         stream_v,
        input wire [3:0]   stream_a,
        input wire         out_period,
        input wire [4:0]   out_addr,
        input wire [31:0]  result,

        output wire [1023:0] stream_d
    );

    reg [1023:0]        stream_0;
    reg [1023:0]        stream_1;

    // steram_aの最上位ビットで、今計算していない方（送り出す方）がどちらかを判断
    assign stream_d = (stream_a[3]) ? stream_1 : stream_0;

    // out_addrの最上位ビットで、今計算している方がどちらかを判断

    // out_addrの最上位ビットが0
    ////////////////////////////////////////////////////////////////////////////

    // 32bitのデータを16個格納する
    // 送り出す時に書きやすいように(?本当に書きやすいか？) メモリバンク化している

    // この16個は4個ずつもとまって、out_ctrlによってわかる
    // exe(各コアで32bitの64個との積和演算、４個)  exe(同文)                       exe(同文)  exe(同文)
    //                                      out(各コアから算出された32bitの４個)  out(同文)  out(同文)  out(同文)

    // buff0とbuff1はoutの間に、下から２個ずつ格納されていく

    reg [31:0]        buff0 [0:7]; // アドレス偶数
    reg [31:0]        buff1 [0:7]; // アドレス奇数

    // out_addrの最下位ビットを見て、偶数か奇数か判断
    always_ff @(posedge clk) begin
                  if(out_period&~out_addr[0]&~out_addr[4]) begin
                      buff0[out_addr[3:1]] <= result;
                  end
              end;

    always_ff @(posedge clk) begin
                  if(out_period& out_addr[0]&~out_addr[4]) begin
                      buff1[out_addr[3:1]] <= result;
                  end
              end;

    generate
        genvar i;
        for (i = 0; i < 8; i = i + 1) begin
            always_ff @(posedge clk) begin
                          if (stream_v & ~stream_a[3]) begin
                              stream_0[i*64+32-1:i*64+32-1-31] <= buff0[stream_a[2:0]+i];
                          end
                      end;
        end
    endgenerate

    generate
        genvar j;
        for (j = 0; j < 8; j = j + 1) begin
            always_ff @(posedge clk) begin
                          if (stream_v & ~stream_a[3]) begin
                              stream_0[j*64+64-1:j*64+64-1-31] <= buff1[stream_a[2:0]+j];
                          end
                      end;
        end
    endgenerate

    always_ff @(posedge clk) begin
                  if (stream_v & ~stream_a[3]) begin
                      stream_0[1023:512] <= 0;
                  end
              end;

    // out_addrの最上位ビットが1
    ////////////////////////////////////////////////////////////////////////////

    reg [31:0]        buff2 [0:7]; // アドレス偶数
    reg [31:0]        buff3 [0:7]; // アドレス奇数

    always_ff @(posedge clk) begin
                  if(out_period&~out_addr[0]& out_addr[4]) begin
                      buff2[out_addr[3:1]] <= result;
                  end
              end;

    always_ff @(posedge clk) begin
                  if(out_period& out_addr[0]& out_addr[4]) begin
                      buff3[out_addr[3:1]] <= result;
                  end
              end;

    generate
        genvar k;
        for (k = 0; k < 8; k = k + 1) begin
            always_ff @(posedge clk) begin
                          if (stream_v & stream_a[3]) begin
                              stream_1[k*64+32-1:k*64+32-1-31] <= buff2[stream_a[2:0]+k];
                          end
                      end;
        end
    endgenerate

    generate
        genvar l;
        for (l = 0; l < 8; l = l + 1) begin
            always_ff @(posedge clk) begin
                          if (stream_v & stream_a[3]) begin
                              stream_1[l*64+64-1:l*64+64-1-31] <= buff3[stream_a[2:0]+l];
                          end
                      end;
        end
    endgenerate

    always_ff @(posedge clk) begin
                  if (stream_v & stream_a[3]) begin
                      stream_1[1023:512] <= 0;
                  end
              end;

endmodule