`default_nettype none

module exe_ctrl
    (
        input wire              clk,
        input wire              rst,

        input wire              s_init,       // srcの受信が終了した次(最初なら)　or 前の計算が終わった次（次のデータがあるなら）
        input wire              out_busy,
        input wire              out_fin,

        output reg              s_fin,        // outrfの次。dst_buffに演算結果が全て入った時
        output logic            k_init,       // jループの始まりの前 (s_initの次)
        output reg              k_fin,        // jループが終わった次に駆動
        output reg              exec,         // 演算の始まり(jループの始まり)
        output logic [9:0]      exec_src_addr,    // src_buffから読み出すアドレス
        output logic [6:0]      exec_mat_addr // matrixから読み出すアドレス
    );

    wire                        last_i, last_j;
    wire                        next_i, next_j;
    wire [3:0]                  i;
    wire [6:0]                  j;
    reg                         s_init_delay, k_init_next;
    reg                         start;
    reg                         s_fin_period;

    // s_initの次にスタート //////////////////////////////////////////////////
    // s_init_delay
    always_ff @(posedge clk)begin
                  if(rst)begin
                      s_init_delay <= 1'b0;
                  end
                  else begin
                      s_init_delay <= s_init;
                  end
              end;
    // k_init (s_initの次に駆動, その後はk_init_nextが駆動)
    always_comb begin
                    k_init = 1'b0;

                    if((s_init_delay | k_init_next) & !out_busy)begin
                        k_init = 1'b1;
                    end
                end;
    //////////////////////////////////////////////////////////////////////

    // k_initの次にスタート ////////////////////////////////////////
    // exec // k_initの次に始まり、last_jまでで終わる
    always_ff @(posedge clk)begin
                  if(rst)begin
                      exec <= 1'b0;
                  end
                  else begin
                      exec <= k_init | exec & !last_j;
                  end
              end;

    // start
    always_ff @(posedge clk)begin
                  if(rst)begin
                      start <= 1'b0;
                  end
                  else begin
                      start <= k_init;
                  end
              end;
    ////////////////////////////////////////////////////////////


    // 32bitデータを64回出力
    // ってのを４回する

    // i loop
    agu_next #(.W(4)) l_i (.ini(2'd0), .fin(7), .start(s_init), .last(last_i), .clk(clk),  .rst(rst),
                           .next(next_i), .data(i), .en(last_j));

    // j loop
    agu_next #(.W(7)) l_j (.ini(3'd0), .fin(127),  .start(start), .last(last_j), .clk(clk),  .rst(rst),
                           .next(next_j), .data(j), .en(1'b1));

    always_comb begin
                    exec_src_addr = i*128 + j;
                end;

    always_comb begin
                    exec_mat_addr = j; // 最大127
                end;

    // last_jの次にスタート /////////////////////////////////////////////////
    // last_j -> next_i と k_fin -> k_init_next　と k_init -> exec と start
    // k_fin
    always_ff @(posedge clk)begin
                  if(rst)begin
                      k_fin <= 1'b0;
                  end
                  else begin
                      k_fin <= last_j;
                  end
              end;

    // k_init_next (最初以外のk_initを駆動)
    // そのためにnext_iが必要 (最初じゃないことの判断)
    // next_jで０にする
    always_ff @(posedge clk)begin
                  if(rst)begin
                      k_init_next <= 1'b0;
                  end
                  else if(~out_busy|next_j)begin
                      k_init_next <= next_i & ~s_init;
                  end
              end;
    //////////////////////////////////////////////////////////////////////

    // last_iの次にスタート /////////////////////////////////////////////////
    // last_i -> s_fin_period ... -> s_fin
    // s_fin_period // last_iの次に始まり、out_finまでで終わる
    always_ff @(posedge clk)begin
                  if(rst)begin
                      s_fin_period <= 1'b0;
                  end
                  else if(last_i)begin
                      s_fin_period <= 1'b1;
                  end
                  else if(out_fin) begin
                      s_fin_period <= 1'b0;
                  end
              end;
    // s_fin
    // outrfの次に駆動
    always_ff @(posedge clk)begin
                  if(rst)begin
                      s_fin <= 1'b0;
                  end
                  else begin
                      s_fin <= s_fin_period & out_fin;
                  end
              end;

endmodule

`default_nettype wire
