`default_nettype none

module dst_ctrl
    (
        input wire          clk,
        input wire          run,
        input wire          dst_ready,
        input wire          s_fin_in, // 次のsrcがあるなら、もしくは最後なら送り返す (送る側を完全に信用、まあ今回のCGRAなら問題ないね)

        output reg          dst_valid,
        output reg          dst_last,
        output logic        stream_v,
        output logic [4:0]  stream_a
    );


    // dst_v0_inが立ったら次に立ち、落ちたら次に落ちる
    reg              stream_active;
    always_ff @(posedge clk)begin
                  if(~run)begin
                      stream_active <= 1'b0;
                  end
                  else if(dst_ready & s_fin_in & !last_i)begin // !last_iは正直いらんけど、念の為
                      stream_active <= 1'b1;
                  end
                  else if(last_i) begin
                      stream_active <= 1'b0;
                  end
              end;


    // startを保持する
    reg             start_check;
    always_ff @(posedge clk)begin
                  if(~run)begin
                      start_check <= 1'b0;
                  end
                  else if(dst_ready)begin
                      start_check <= s_fin_in;
                  end
              end;


    // dst_readyが落とされている可能性もある
    logic start;
    always_comb begin
                    start = 1'b0;

                    if (dst_ready & start_check) begin
                        start = 1'b1;
                    end
                end;


    wire [4:0]         i;
    wire              last_i;
    agu #(.W(5)) l_da(.ini(3'd0), .fin(0), .start(start), .last(last_i), .clk(clk), .rst(~run),
                      .data(i), .en(dst_ready) );


    always_comb begin
                    stream_a = i;
                    stream_v = stream_active & dst_ready;
                end;


    always_ff @(posedge clk)begin
                  if(~run)begin
                      dst_valid <= 1'b0;
                  end
                  else if(dst_ready)begin
                      dst_valid <= stream_active;
                  end
              end;

    always_ff @(posedge clk)begin
                  if(~run)begin
                      dst_last <= 1'b0;
                  end
                  else if(dst_ready)begin
                      dst_last <= stream_active & last_i;
                  end
              end;

    // s_fin_inが立つ -> start_checkが立つ、startもたつ -> アドレス生成が始まる (実際はstartの時点で０だから既に始まっている『)
    //               -> stream_active, stream_vが始まる -> dst_validが立つ

    // last_i が立つ -> stream_activeが落ちる, stream_vも落ちる -> dst_validが落ちる

endmodule

`default_nettype wire
