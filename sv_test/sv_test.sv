// module sv_test
//     (
//         input wire          clk,
//         input wire          rstn,
//         output reg [31:0]   rand_num
//     );

//     reg [31:0] x;
//     reg [31:0] y;
//     reg [31:0] z;
//     reg [31:0] w;
//     reg [31:0] t;

//     always_ff @(posedge clk) begin
//                   if (!rstn)begin
//                       x <= 123456789;
//                       y <= 362436069;
//                       z <= 521288629;
//                       w <= 88675123;
//                       t <= 0;
//                       rand_num <= 0;
//                   end
//                   else begin
//                       t <= x ^ (x << 11);
//                       x <= y;
//                       y <= z;
//                       z <= w;
//                       w <= (w ^ (w >> 19)) ^ (t ^ (t >> 8));
//                       rand_num <= w;
//                   end
//               end;

// endmodule

// xorshift
module sv_test
    (
        input   wire            clk,
        input   wire            rstn,
        output  wire [31:0]     rand_num
    );

    reg [31:0] x_q, y_q, z_q, w_q, x_d, y_d, z_d, w_d;
    // wire [127:0] seed = 128'h8de97cc56144a7eb653f6dee8b49b282;
    assign rand_num = w_q;

    always_comb begin
                    x_d = y_q;
                    y_d = z_q;
                    z_d = w_q;
                    w_d = w_q ^ (w_q >> 19) ^ (x_q ^ (x_q << 11)) ^ ((x_q ^ (x_q << 11)) >> 8);
                end;

    always_ff @(posedge clk) begin
                  // Auto-reset if we're in the all-zero state
                  if (x_q == 0 && y_q == 0 && z_q == 0 && w_q == 0) begin
                      //   x_q <= 32'h8de97cc5;
                      //   y_q <= 32'h6144a7eb;
                      //   z_q <= 32'h653f6dee;
                      //   w_q <= 32'h8b49b282;
                      x_q <= 32'd123456789;
                      y_q <= 32'd362436069;
                      z_q <= 32'd521288629;
                      w_q <= 32'd88675123;
                  end
                  else if (!rstn) begin
                      //   x_q <= 32'h8de97cc5;
                      //   y_q <= 32'h6144a7eb;
                      //   z_q <= 32'h653f6dee;
                      //   w_q <= 32'h8b49b282;
                      x_q <= 32'd123456789;
                      y_q <= 32'd362436069;
                      z_q <= 32'd521288629;
                      w_q <= 32'd88675123;
                  end
                  else begin
                      x_q <= x_d;
                      y_q <= y_d;
                      z_q <= z_d;
                      w_q <= w_d;
                  end
              end;

endmodule
