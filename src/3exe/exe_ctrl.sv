`default_nettype none

module exe_ctrl
    (
        input wire              clk,
        input wire              rst,
        input wire              src_v,
        input wire [19:0]       addr_i,
        input wire [19:0]       addr_j,

        output wire last_j,
        output reg              s_fin,        // outrfの次。dst_buffに演算結果が全て入った時
        output reg              k_fin,        // jループが終わった次に駆動
        output reg              exec         // 演算の始まり(jループの始まり)
    );

    wire last_i;
    wire next_i, next_j;
    wire [19:0] i;
    wire [19:0] j;
    reg s_fin_period;

    always_ff @(posedge clk)begin
                  if(rst)begin
                      exec <= 1'b0;
                  end
                  else begin
                      exec <= src_v | exec & !last_j;
                  end
              end;

    reg src_v_n, src_v_nn;
    always_ff @(posedge clk) begin
                  src_v_n <= src_v;
                  src_v_nn <= src_v_n;
              end;

    ////////////////////////////////////////////////////////////

    agu_next #(.W(20)) l_i (.ini(2'd0), .fin(addr_i), .start(src_v), .last(last_i), .clk(clk),  .rst(rst),
                            .next(next_i), .data(i), .en(last_j));

    agu_next #(.W(20)) l_j (.ini(3'd0), .fin(addr_j),  .start(src_v_nn), .last(last_j), .clk(clk),  .rst(rst),
                            .next(next_j), .data(j), .en(1'b1));

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

    reg out_fin;
    always_ff @(posedge clk) begin
                  out_fin <= last_i;
              end

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
