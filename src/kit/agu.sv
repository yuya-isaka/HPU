`default_nettype none

// アドレス生成ユニット
//      iniからfinまで
//      startで始まると止まらない
//      enが１の時＋１する
module agu
    #(
         parameter W = 32
     )
     (
         // in
         input wire             clk,
         input wire             rst,
         input wire [W-1:0]     ini,
         input wire [W-1:0]     fin,
         input wire             start,
         input wire             en,

         // out
         output reg [W-1:0]     data,
         output logic           last
     );

    // start もしくは既にアドレス生成が始まっている場合
    //      最後に０にする
    //      それまでは１
    reg              run;
    always_ff @(posedge clk) begin
                  if (rst) begin
                      run <= 1'b0;
                  end
                  else if (start | run) begin
                      if (last & en) begin
                          run <= 1'b0;
                      end
                      else begin
                          run <= 1'b1;
                      end
                  end
              end;

    // startもしくは既にアドレス生成が始まっている場合
    //      最後に初期化
    //      それまでは +1
    always_ff @(posedge clk) begin
                  if (rst) begin
                      data <= ini;
                  end
                  else if (start | run) begin
                      if (last & en) begin
                          data <= ini;
                      end
                      else if (en) begin
                          data <= data + 1'b1;
                      end
                  end
              end;

    //==============================================================

    // データが最後　&&
    // startもしくは既にアドレス生成が始まっている　&&
    // enable
    always_comb begin
                    last = 1'b0;

                    if ((data==fin) & (run|start) & en) begin
                        last = 1'b1;
                    end
                end;

endmodule

`default_nettype wire
