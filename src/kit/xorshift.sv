`default_nettype none

module xorshift
    (
        // in
        input wire              clk,
        input wire              gen,

        // out
        output logic [31:0]     rand_num
    );

    reg [31:0]      x;
    reg [31:0]      y;
    reg [31:0]      z;
    reg [31:0]      w;

    always_ff @(posedge clk) begin
                  if (~gen) begin
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

    //==============================================================

    assign rand_num = w;

endmodule

`default_nettype wire
