`default_nettype none

module src_ctrl
    (
        input wire              clk,
        input wire              matw,
        input wire              run,
        input wire              src_valid,

        output wire             src_ready,
        output logic            src_v
    );

    always_comb begin
                    src_v = 1'b0;
                    if(src_valid & src_ready & run & ~matw)begin
                        src_v = 1'b1;
                    end
                end;

    assign src_ready = 1'b1;

endmodule

`default_nettype wire
