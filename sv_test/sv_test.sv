`default_nettype none

// xorshift
module sv_test
    (
        input   wire            clk,
        input   wire            rstn,
        output  logic [31:0]    rand_num
    );

    always_comb begin
                    rand_num = w;
                end;

    reg [31:0] x;
    reg [31:0] y;
    reg [31:0] z;
    reg [31:0] w;

    always_ff @(posedge clk) begin
                  if (!rstn | (x == 0 && y == 0 && z == 0 && w == 0))begin
                      // パターン１
                        // x <= 2380889285;
                        // y <= 1631889387;
                        // z <= 1698655726;
                        // w <= 2336862850;

                      // パターン２
                      x <= 123456789;
                      y <= 362436069;
                      z <= 521288629;
                      w <= 88675123;
                  end
                  else begin
                      x <= y;
                      y <= z;
                      z <= w;
                      w <= (w ^ (w >> 19)) ^ ((x ^ (x << 11)) ^ ((x ^ (x << 11)) >> 8));
                  end
              end;

endmodule

`default_nettype wire
