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


    always_comb begin
                    src_v = start;
                end;

endmodule

`default_nettype wire
