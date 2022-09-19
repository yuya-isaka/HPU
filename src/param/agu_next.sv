`default_nettype none

module agu_next
    #(
         parameter W = 32
     )
     (
         input wire [W-1:0]     ini,
         input wire [W-1:0]     fin,
         input wire             clk,
         input wire             rst,
         input wire             start,
         input wire             en,

         output reg [W-1:0]     data,
         output logic           next,
         output logic           last
     );

    always_comb begin
                    next = 1'b0;

                    if (start | next_pre) begin
                        next = 1'b1;
                    end
                end;

    always_comb begin
                    last = 1'b0;

                    if ((data==fin)&(run|start)&en) begin
                        last = 1'b1;
                    end
                end;

    reg              next_pre;
    always @(posedge clk)begin
        next_pre <= (run|start)&en&!last;
    end;

    reg              run;
    always_ff @(posedge clk)begin
                  if(rst)begin
                      run <= 1'b0;
                  end
                  else if(start|run)begin
                      if(last & en)begin
                          run <= 1'b0;
                      end
                      else begin
                          run <= 1'b1;
                      end
                  end
              end;

    always_ff @(posedge clk)begin
                  if(rst)begin
                      data <= ini;
                  end
                  else if(start|run)begin
                      if(last & en)begin
                          data <= ini;
                      end
                      else if(en)begin
                          data <= data+1;
                      end
                  end
              end;

endmodule

`default_nettype wire
