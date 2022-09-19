`default_nettype none

module s_ctrl
    (
        input wire          clk,
        input wire          run,
        input wire          last,
        input wire          dst_ready,
        input wire          s_fin,    // outrfの次、dst_buffに演算結果がすべて入った時
        input wire          src_fin, // srcから送られてくるのが終了したよ
        input wire [1:0]    src_en, // 2種類格納
        input wire		    p,

        output logic	    s_fin_in, // wire
        output reg		    s_init
    );

    reg                s_fin_dayo;

    // 計算が終わった & srcのもう一方がある　＆　いつでも送っていい
    // 計算が終わった　＆ 最後 & いつでも送っていい
    // 計算終わって待っている状態（s_fin_dayo) & srcのもう一方がある & いつでも送っていい
    // 計算が終わって待っている状態(s_fin_dayo) & 最後 & いつでも送っていい

    always_comb begin
                    s_fin_in = 1'b0;

                    if((s_fin | s_fin_dayo) & (src_en[~p] | last) & dst_ready)begin
                        s_fin_in = 1'b1;
                    end
                end;

    // s_init ... srcの受信が終了した次(最初なら)　or 前の計算が終わった次（次のデータがあるなら）
    // s_fin_dayo ... 計算が終わったという情報を保持 (次のを駆動できそうなら０になる)
    always_ff @(posedge clk)begin
                  if(~run)begin
                      s_init <= 1'b0;
                      s_fin_dayo <= 1'b0;
                  end
                  else if(src_fin & src_en[1:0]==2'b00)begin // 何もない時、始める
                      s_init <= 1'b1;
                  end
                  else if(s_fin_in)begin // 計算が終わった時、次があるなら, もしくは最後なら
                      s_init <= ~last;
                      s_fin_dayo <= 1'b0;
                  end
                  else if(s_fin)begin
                      s_fin_dayo <= 1'b1; // 計算が終わってるよーってのを保持
                  end
                  else begin
                      s_init <= 1'b0;
                  end
              end;

endmodule

`default_nettype wire
