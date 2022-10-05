`default_nettype none

module s_ctrl
    (
        input wire          clk,
        input wire          run,
        input wire          dst_ready,
        input wire          s_fin,
        input wire          src_v,

        output logic	    stream_ok,
        output reg		    s_init
    );

    reg s_fin_keep;
    always_ff @(posedge clk)begin
                  if(~run)begin
                      s_fin_keep <= 1'b0;
                  end
                  else if(stream_ok)begin
                      s_fin_keep <= 1'b0;
                  end
                  else if(s_fin)begin
                      s_fin_keep <= 1'b1;
                  end
              end;

    always_comb begin
                    stream_ok = 1'b0;
                    if((s_fin | s_fin_keep) & dst_ready)begin
                        stream_ok = 1'b1;
                    end
                end;

    always_ff @(posedge clk)begin
                  if(~run)begin
                      s_init <= 1'b0;
                  end
                  else if(src_v)begin
                      s_init <= 1'b1;
                  end
                  else begin
                      s_init <= 1'b0;
                  end
              end;


endmodule

`default_nettype wire
