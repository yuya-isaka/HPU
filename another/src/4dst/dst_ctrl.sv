module dst_ctrl
    (
        input wire        clk,
        input wire        run,
        input wire        dst_ready,
        input wire        s_fin_in,

        output wire       dst_valid,
        output wire       stream_v,
        output wire [2:0] stream_a
    );

    reg [2:0]         i;
    wire              last_i;

    wire              start, start_check;

    wire              stream_active;

    // s_fin_inからlast_iがたつまで、アクティブ
    wire              stream_active_pre = (s_fin_in | stream_active) & !last_i;
    // dst_v0_inが立ったら次に立ち、落ちたら次に落ちる
    dff #(.W(1)) d_dst_v0 (.in(stream_active_pre), .data(stream_active), .clk(clk), .rst(~run), .en(dst_ready));


    dff #(.W(1)) d_dstart0 (.in(s_fin_in), .data(start_check), .clk(clk), .rst(~run), .en(dst_ready));

    assign start = dst_ready & start_check;

    agu #(.W(3)) l_da(.ini(3'd0), .fin(0),  .data(i), .start(start),  .last(last_i),
                      .clk(clk),   .rst(~run), .en(dst_ready) );

    assign stream_a = i;
    assign stream_v = stream_active & dst_ready;

    dff #(.W(1)) d_dst_valid (.in(stream_active), .data(dst_valid), .clk(clk), .rst(~run), .en(dst_ready));

    // s_fin_inが立つ（同時にstream_active_preもたつ） -> start_checkが立つ、startもたつ -> アドレス生成が始まる (実際はstartの時点で０だから既に始まっている『)
    //                                  -> stream_active, stream_vが始まる -> dst_validが立つ

    // last_i が立って、stream_active_preが落ちる -> stream_activeが落ちる, stream_vも落ちる -> dst_validが落ちる

endmodule
