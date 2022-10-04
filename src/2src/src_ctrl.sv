`default_nettype none

module src_ctrl
    (
        input wire              clk,          // AXIS_ACLK
        input wire              matw,
        input wire              run,          // 開始
        input wire              src_valid,    // S_AXIS_TVALID
        input wire [18:0]       addr_num,  // アドレスの数

        output logic            src_ready,    // S_AXIS_TREADY
        output logic            src_v,        // アドレスが生成されているか否か
        output logic [18:0]      src_a,        // アドレス
        output logic		    src_fin       // アドレスの生成が最後か否か
    );

    // 送っておっけい
    logic sen; // wire
    always_comb begin
                    sen = 1'b0;
                    if(src_valid & src_ready)begin
                        sen = 1'b1;
                    end
                end;

    // アドレス生成スタート
    logic start;
    always_comb begin
                    start = 1'b0;
                    if(sen & run & ~matw)begin
                        start = 1'b1;
                    end
                end;

    // 両方埋まってる時はダメ
    always_comb begin
                    src_ready = 1'b1;
                end;

    // 今回は24個
    wire              last_i;

    // 合計が何個かをfin内に指定
    // 16bitの範囲だとする(アイテムメモリーの量)
    // で今回は偶数と奇数で分けて保存するので、8bitでいい
    reg [18:0]         i;
    agu #(.W(19)) l_i (.ini(4'd0), .fin(addr_num), .start(start), .last(last_i), .clk(clk), .rst(~src_ready|~run),
                       .data(i), .en(sen));

    always_comb begin
                    src_a = i;
                    src_v = start;
                    src_fin = last_i;
                end;

endmodule

`default_nettype wire
