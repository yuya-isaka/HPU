
module dff
    #(
         parameter W = 32
     )
     (
         input wire [W-1:0] in,
         output reg [W-1:0] data,
         input wire         clk,
         input wire         rst,
         input wire         en
     );

    always @(posedge clk)begin
        if(rst)begin
            data <= 'h0;
        end
        else if(en)begin
            data <= in;
        end
    end;

endmodule
