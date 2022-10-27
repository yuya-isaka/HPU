
`default_nettype none


module get_enable
    (
        // in
        input wire              clk,
        input wire              gen,
        input wire              run,
        input wire              get_valid,

        // out
        output wire             get_ready,
        output logic            get_v,
        output logic            exec
    );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    assign get_ready = 1'b1;


    always_comb begin
                    get_v = 1'b0;

                    if (get_valid & get_ready & run & ~gen) begin
                        get_v = 1'b1;
                    end
                end;


    always_ff @(posedge clk) begin
                  if (~run) begin
                      exec <= 1'b0;
                  end
                  else begin
                      exec <= get_v;
                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire