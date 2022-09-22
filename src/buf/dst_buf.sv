`default_nettype none

module dst_buf
    (
        input wire              clk,
        input wire              stream_v,
        input wire [4:0]        stream_a,
        input wire              out_period,
        input wire [5:0]        out_addr,
        input wire              out_fin,
        input wire [31:0]       result,
        input wire              p,
        input wire              s_fin,

        output logic [63:0]     stream_d // M_AXIS_TDATA
    );

    reg [63:0]        stream_0;
    reg [63:0]        stream_1;

    // steram_aの最上位ビットで、今計算していない方（送り出す方）がどちらかを判断
    always_comb begin
                    stream_d = stream_1;

                    if (p) begin
                        stream_d = stream_0;
                    end
                end;

    // out_addrの最上位ビットで、今計算している方がどちらかを判断

    // out_addrの最上位ビットが0
    ////////////////////////////////////////////////////////////////////////////

    // 32bitのデータを16個格納する
    // 送り出す時に書きやすいように(?本当に書きやすいか？) メモリバンク化している

    // この16個は4個ずつもとまって、out_ctrlによってわかる
    // exe(各コアで32bitの64個との積和演算、４個)  exe(同文)                       exe(同文)  exe(同文)
    //                                      out(各コアから算出された32bitの４個)  out(同文)  out(同文)  out(同文)

    // buff0とbuff1はoutの間に、下から２個ずつ格納されていく

    //　一旦この方法で書いて、その後試してみようか

    // いやそもそもdualportメモリやからそれはないか
    // 32bitを64個格納（バンク化）
    reg [63:0]        buff0 [0:31]; // アドレス偶数
    // reg [31:0]        buff0 [0:31]; // アドレス偶数
    reg [31:0]        buff1 [0:31]; // アドレス奇数

    // out_addrの最下位ビットを見て、偶数か奇数か判断

    reg [63:0]      counter_1;
    initial begin
        counter_1 = 0;
    end

    always_ff @(posedge clk) begin
                  if (s_fin) begin
                      counter_1 <= 0;
                  end
                  else if(out_period & ~p & out_fin) begin
                      counter_1 <= counter_1 + result;
                  end
              end;

    always_ff @(posedge clk) begin
                  if (s_fin) begin
                      buff0[0] <= counter_1;
                  end
              end;

    // always_ff @(posedge clk) begin // 偶数
    //               if(out_period & ~p & ~out_addr[0]) begin
    //                   buff0[out_addr[5:1]] <= result;
    //               end
    //           end;

    // always_ff @(posedge clk) begin // 奇数
    //               if(out_period & ~p & out_addr[0]) begin
    //                   buff1[out_addr[5:1]] <= result;
    //               end
    //           end;

    // さっきまで計算してたやつを出力
    // s_fin_inでpが変わってるからこれでいける
    always_ff @(posedge clk) begin
                  if (stream_v & p) begin
                      //   stream_0[31:0] <= buff0[stream_a];
                      //   stream_0[63:32] <= buff1[stream_a];
                      stream_0 <= buff0[0];
                  end
              end;

    // out_addrの最上位ビットが1
    ////////////////////////////////////////////////////////////////////////////

    reg [63:0]        buff2 [0:31]; // アドレス偶数
    // reg [31:0]        buff2 [0:31]; // アドレス偶数
    reg [31:0]        buff3 [0:31]; // アドレス奇数

    reg [63:0]      counter_2;
    initial begin
        counter_2 = 0;
    end

    always_ff @(posedge clk) begin
                  if (s_fin) begin
                      counter_2 <= 0;
                  end
                  else if(out_period & p & out_fin) begin
                      counter_2 <= counter_2 + result;
                  end
              end;

    always_ff @(posedge clk) begin
                  if (s_fin) begin
                      buff2[0] <= counter_2;
                  end
              end;

    // always_ff @(posedge clk) begin // 偶数
    //               if(out_period & p & ~out_addr[0]) begin
    //                   buff2[out_addr[5:1]] <= result;
    //               end
    //           end;

    // always_ff @(posedge clk) begin // 奇数
    //               if(out_period & p & out_addr[0]) begin
    //                   buff3[out_addr[5:1]] <= result;
    //               end
    //           end;

    always_ff @(posedge clk) begin
                  if (stream_v & ~p) begin
                      //   stream_1[31:0] <= buff2[stream_a];
                      //   stream_1[63:32] <= buff3[stream_a];
                      stream_1 <= buff2[0];
                  end
              end;

endmodule

`default_nettype wire
