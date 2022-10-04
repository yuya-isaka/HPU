`default_nettype none

module p_ctrl
    (
        input wire          clk,
        input wire          run,
        input wire          src_fin, // srcから送られてくるのが終了したよ
        input wire          s_fin_in,

        output reg          p // 計算している方
    );

    always_ff @(posedge clk)begin
                  if(~run)begin
                      p <= 1'b1;
                  end
                  else if(src_fin)begin // 何もない時, 最初
                      p <= ~p;
                  end
                  else if(s_fin_in)begin // 一つ計算が終わって次に進んでいいとき
                      p <= ~p;
                  end
              end;

endmodule

`default_nettype wire
