`default_nettype none

module src_ctrl
    (
        input wire              clk,          // AXIS_ACLK
        input wire              matw,         // これたってたらやらないで
        input wire              run,          // 開始
        input wire              src_valid,    // S_AXIS_TVALID
        input wire [1:0]        src_en,       // ソースバッファが空いているか否か

        output logic            src_ready,    // S_AXIS_TREADY
        output logic            src_v,        // アドレスが生成されているか否か
        output logic [8:0]      src_a,        // アドレス
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

                    if(src_en == 2'b11)begin
                        src_ready = 1'b0;
                    end
                end;

    wire              last_i;
    reg [8:0]         i;
    agu #(.W(9)) l_i (.ini(4'd0), .fin(511), .start(start), .last(last_i), .clk(clk), .rst(~src_ready|~run),
                      .data(i), .en(sen));

    always_comb begin
                    src_a = i;
                    src_v = start;
                    src_fin = last_i;
                end;

endmodule

`default_nettype wire
