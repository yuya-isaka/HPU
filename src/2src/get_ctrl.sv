`default_nettype none

module get_ctrl
    (
        input wire              clk,
        input wire              matw,
        input wire              run,
        input wire              get_valid,

        output wire             get_ready,
        output logic            get_v
    );

    always_comb begin
                    get_v = 1'b0;
                    if(get_valid & get_ready & run & ~matw)begin
                        get_v = 1'b1;
                    end
                end;

    assign get_ready = 1'b1;

endmodule

`default_nettype wire
