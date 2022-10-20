`default_nettype none

// xorshift
module sv_test
    (
        input   wire            clk,
        input   wire            rstn,
        input   wire [31:0]     in,
        input   wire [31:0]     permutation,

        output  logic [31:0]    out_1,
        output  logic [31:0]    out_2,
        output  logic [31:0]    out_3
    );

    wire  [63:0] tmp;

    // always_comb begin
    //                 tmp = 
    //             end;
    assign tmp = {in & ((1'b1 << permutation) - 1'b1), in >> permutation};
    // 右も左も余計なものが生まれるのでダメ

    always_ff @(posedge clk) begin
                  if (~rstn) begin
                      out_1 <= 0;
                      out_2 <= 0;
                  end
                  else begin
                      out_1 <= (in >> permutation | ( ( in & ((1'b1 << permutation) - 1'b1) ) << (32 - permutation) ) );
                      out_2 <= tmp[31:0];
                      out_3 <= tmp[63:32];
                  end
              end;

endmodule

`default_nettype wire
