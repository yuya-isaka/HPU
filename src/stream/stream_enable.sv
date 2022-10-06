`default_nettype none

module stream_enable
    (
        // in
        input wire          clk,
        input wire          rst,
        input wire          dst_ready,
        input wire          get_fin,

        // out
        output logic	    stream_ok
    );

    reg get_fin_keep;
    always_ff @(posedge clk) begin
                  if (rst) begin
                      get_fin_keep <= 1'b0;
                  end
                  else if (stream_ok) begin
                      get_fin_keep <= 1'b0;
                  end
                  else if (get_fin) begin
                      get_fin_keep <= 1'b1;
                  end
              end;

    //==============================================================

    always_comb begin
                    stream_ok = 1'b0;

                    if ((get_fin | get_fin_keep) & dst_ready) begin
                        stream_ok = 1'b1;
                    end
                end;

endmodule

`default_nettype wire
