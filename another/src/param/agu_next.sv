module agu_next
    #(
         parameter W = 32
     )
     (
         input wire [W-1:0] ini,
         input wire [W-1:0] fin,
         output reg [W-1:0] data,
         input wire         clk,
         input wire         rst,
         input wire         start,
         input wire         en,
         output wire        next,
         output wire        last
     );

    reg              next_pre;
    reg              run;
    assign next = start | next_pre;
    assign last = (data==fin)&(run|start)&en;

    always @(posedge clk)begin
        next_pre <= (run|start)&en&!last;
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
                    data <= data+1;
                end
            end
        end
    end;

endmodule
