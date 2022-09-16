module src_ctrl
    (
        input wire        clk,
        input wire        matw,
        input wire        run,
        input wire        src_valid,
        input wire [1:0]  src_en,

        output wire       src_ready,
        output wire       src_v,
        output wire [3:0] src_a,
        output wire		  src_fin
    );

    // 送っておっけい
    wire sen = src_valid & src_ready;
    // アドレス生成スタート
    wire start = sen & run & ~matw;

    assign src_ready = (src_en!=2'b11); // 両方埋まってる時はだめ

    wire              last_i;
    reg [3:0]         i;
    agu #(.W(4)) l_i (.ini(4'd0), .fin(15), .data(i), .start(start),
                      .last(last_i), .clk(clk), .rst(~src_ready|~run), .en(sen));

    assign src_a = i;
    assign src_v = start;
    assign src_fin = last_i;

endmodule
