`default_nettype none

module agu_param
    #(
         parameter W = 32
     )
     (
         input wire [W-1:0] ini,
         input wire [W-1:0] fin,
         input wire [W-1:0] param,
         output reg [W-1:0] data,
         input wire         clk,
         input wire         rst,
         input wire         start,
         input wire         en,
         output wire        last
     );

    reg              run;
    assign last = (data==fin)&(run|start)&en;

    always @(posedge clk)begin
        if(rst)begin
            run <= 1'b0;
            data <= ini;
        end
        else if(start|run)begin
            if(last)begin
                if(en)begin
                    data <= ini;
                    run <= 1'b0;
                end
            end
            else begin
                run <= 1'b1;
                if(en)begin
                    data <= data+param;
                end
            end
        end
    end;

endmodule

`default_nettype wire
