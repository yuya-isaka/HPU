`default_nettype none

module get_ctrl
    (
        // in
        input wire              clk,
        input wire              rst,
        input wire              get_v,
        input wire [19:0]       addr_i,
        input wire [19:0]       addr_j,

        // out
        output wire             last_j,
        output reg              exec,
        output reg              get_fin
    );

    reg         get_v_n, get_v_nn;
    always_ff @(posedge clk) begin
                  get_v_n <= get_v;
                  get_v_nn <= get_v_n;
              end;

    always_ff @(posedge clk)begin
                  if (rst) begin
                      exec <= 1'b0;
                  end
                  else begin
                      exec <= get_v;
                  end
              end;

    always_ff @(posedge clk)begin
                  if (rst) begin
                      get_fin <= 1'b0;
                  end
                  else begin
                      get_fin <= last_i;
                  end
              end;

    wire [19:0]         i;
    wire [19:0]         j;
    wire                last_i;

    agu #(.W(20)) agu_get_i
        (
            // in
            .clk(clk),
            .rst(rst),
            .ini(0),
            .fin(addr_i),
            .start(get_v),
            .en(last_j),

            // out
            .data(i),
            .last(last_i)
        );

    agu #(.W(20)) agu_get_j
        (
            // in
            .clk(clk),
            .rst(rst),
            .ini(0),
            .fin(addr_j),
            .start(get_v_nn),
            .en(exec | (i == addr_i & j == addr_j)),

            // out
            .data(j),
            .last(last_j)
        );

endmodule

`default_nettype wire
