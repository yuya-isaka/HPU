`default_nettype none

module out_ctrl
    (
        input wire       clk,
        input wire       rst,

        // srcの受信が終了した次(最初なら)　or前の計算が終わった次（次のデータがあるなら）
        input wire       k_init,   // exeの jループの始まりの前 (s_initの次)
        input wire       k_fin,    // exeの jループが終わった次に駆動
        input wire [19:0] addr_i,
        input wire s_init,

        output reg       out_busy,
        output reg       out_period,
        output reg       out_fin,
        output reg       update
    );


    wire              last_i, last_j;
    wire [19:0]        i, j;
    reg               last_j_next;
    reg               out_period_pre;

    // outが先に終わってて、kが終わった次 or kが先に終わってて、outが終わった次


    logic start;
    always_comb begin
                    start = 1'b0;
                    if( (k_fin&!j_period) | (last_j_next&k_fin_retention) )begin
                        start = 1'b1;
                    end
                end;

    // out_busy
    // k_init & out_period_pre の次から、last_j_nextが終わるまで立ち続ける
    // out_period_preの次からout_periodが始まるからそれに合わせる形か。
    always_ff @(posedge clk)begin
                  if(rst)begin
                      out_busy <= 1'b0;
                  end
                  else if(k_init&out_period_pre)begin
                      out_busy <= 1'b1;
                  end
                  else if(last_j_next) begin
                      out_busy <= 1'b0;
                  end
              end;


    // k_fin_retention
    // k_fin & out_busy の次から、last_j_nextが終わるまで立ち続ける
    reg               k_fin_retention;
    always_ff @(posedge clk)begin
                  if(rst)begin
                      k_fin_retention <= 1'b0;
                  end
                  else if(k_fin&out_busy)begin
                      k_fin_retention <= 1'b1;
                  end
                  else if (last_j_next) begin
                      k_fin_retention <= 1'b0;
                  end
              end;

    // j_period
    // startの次から、last_jが終わるまで続ける
    reg               j_period;
    always_ff @(posedge clk)begin
                  if(rst)begin
                      j_period <= 1'b0;
                  end
                  else if(start)begin
                      j_period <= 1'b1;
                  end
                  else if (last_j) begin
                      j_period <= 1'b0;
                  end
              end;


    // jの終わりに更新される
    agu #(.W(20)) l_i (.ini(0), .fin(addr_i),  .start(s_init), .last(last_i), .clk(clk), .rst(rst),
                      .data(i), .en(last_j));

    // kが終わるたびに新しいのが始まる
    agu #(.W(3)) l_j (.ini(0), .fin(1),  .start(start), .last(last_j), .clk(clk), .rst(rst),
                      .data(j), .en(1'b1));

    always_ff @(posedge clk)begin
                  if(rst)begin
                      out_period_pre <= 1'b0;

                      out_period <= 1'b0;
                      out_fin <= 1'b0;
                  end
                  else begin
                      out_period_pre <= j_period|start; // startの次に始まり、j_periodの次まで生き残る

                      out_period <= out_period_pre;
                      out_fin <= out_period_pre&~j_period; // jが終わっていて、out_period_preが立っている時間の次にout_periodは終わる
                  end
              end;

    // k_finの何回後にupdateしたいか
    // 例外
    // 2段FF start → update
    reg               update_after_start;
    always_ff @(posedge clk)begin
                  if(rst)begin
                      update_after_start <= 1'b0;
                      update <= 1'b0;
                  end
                  else begin
                      update_after_start <= start;
                      update <= update_after_start;
                  end
              end;

    always_ff @(posedge clk)begin
                  if(rst)begin
                      last_j_next <= 1'b0;
                  end
                  else begin
                      last_j_next <= last_j;
                  end
              end;


endmodule

`default_nettype wire
