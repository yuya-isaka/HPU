module src_en_ctrl
    (

        input wire        clk,
        input wire        run,
        input wire        src_fin, // srcから送られてくるのが終了したよ
        input wire        p,
        input wire        s_fin_in,

        output reg [1:0] src_en
    );

    // src_en
    always_ff @(posedge clk) begin
                  if(~run)begin
                      src_en[1:0] <= 2'b00;
                  end
                  else if(src_fin)begin
                      src_en[~p] <= 1'b1; // 計算していない方を埋める
                  end
                  // 計算が終わって次に進んでいい時 // 最後の時は駆動しないってことを暗に示唆
                  else if(s_fin_in & src_en[~p])begin
                      src_en[p] <= 1'b0;
                  end
              end;

endmodule
