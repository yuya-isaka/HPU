module sv_test
    (
        input wire          clk,
        input wire          rstn,
        output reg [63:0]   rand_num
    );

    initial begin
        rand_num = 0;
    end

    reg [63:0] x;
    reg [63:0] y;
    reg [63:0] z;
    reg [63:0] w;
    reg [63:0] t;

    always_ff @(posedge clk) begin
                  if (!rstn)begin
                      x <= 123456789;
                      y <= 362436069;
                      z <= 521288629;
                      w <= 88675123;
                      t <= 0;
                      rand_num <= 0;
                  end
                  else begin
                      t <= x ^ (x << 11);
                      x <= y;
                      y <= z;
                      z <= w;
                      //   w <= (w ^ (w >> 19)) ^ (t ^ (t >> 8));
                      //   rand_num <= w;
                      rand_num <= (w ^ (w >> 19)) ^ (t ^ (t >> 8));
                  end
              end;

endmodule
