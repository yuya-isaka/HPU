module src_ctrl
    (
        input wire        clk,          // AXIS_ACLK
        input wire        matw,         // これたってたらやらないで
        input wire        run,          // 開始
        input wire        src_valid,    // S_AXIS_TVALID
        input wire [1:0]  src_en,       // ソースバッファが空いているか否か

        output wire       src_ready,    // S_AXIS_TREADY
        output wire       src_v,        // アドレスが生成されているか否か
        output wire [7:0] src_a,        // アドレス
        output wire		  src_fin       // アドレスの生成が最後か否か
    );

    // 送っておっけい
    wire sen = src_valid & src_ready;
    // アドレス生成スタート
    wire start = sen & run & ~matw;

    assign src_ready = (src_en!=2'b11); // 両方埋まってる時はだめ

    wire              last_i;
    reg [7:0]         i;
    agu_param #(.W(8)) l_i (.ini(4'd0), .fin(224), .param(32), .data(i), .start(start),
                            .last(last_i), .clk(clk), .rst(~src_ready|~run), .en(sen));

    assign src_a = i;
    assign src_v = start;
    assign src_fin = last_i;

endmodule
