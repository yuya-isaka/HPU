`default_nettype none

// xorshift
module sv_test
    (
        input   wire            clk,
        input   wire            rstn,
        input   wire [31:0]     in,
        input   wire [31:0]     permutation,

        output  logic [31:0]    out_1,
        output  logic [31:0]    out_2
    );

    always_ff @(posedge clk) begin
                  if (~rstn) begin
                      out_1 <= 0;
                      out_2 <= 0;
                  end
                  else begin
                      out_1 <= (in >> permutation | ( ( in & ((1'b1 << permutation) - 1'b1) ) << (32 - permutation) ) );
                      if (permutation == 1) begin
                        out_2 <= {in[0], in[31:1]};
                      end
                      else if (permutation == 2) begin
                        out_2 <= {in[1:0], in[31:2]};
                      end
                      else if (permutation == 3) begin
                        out_2 <= {in[2:0], in[31:3]};
                      end
                  end
              end;

endmodule

`default_nettype wire
