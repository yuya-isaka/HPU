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
        output wire             update,
        output reg              exec,
        output reg              get_fin
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg         get_v_n, get_v_nn;

    always_ff @(posedge clk) begin
                  get_v_n <= get_v;
                  get_v_nn <= get_v_n;
              end;


    // exec
    always_ff @(posedge clk) begin
                  if (rst) begin
                      exec <= 1'b0;
                  end
                  else begin
                      exec <= get_v;
                  end
              end;


    // get_fin
    always_ff @(posedge clk) begin
                  if (rst) begin
                      get_fin <= 1'b0;
                  end
                  else begin
                      get_fin <= last_update;
                  end
              end;


    wire [19:0]         i;
    wire                last_update;

    agu #(.W(20)) agu_get_i
        (
            // in
            .clk(clk),
            .rst(rst),
            .ini(20'd0),
            .fin(addr_i),
            .start(get_v),
            .en(update),

            // out
            .data(i),
            .last(last_update)
        );


    // update
    wire [19:0]         j;

    agu #(.W(20)) agu_get_j
        (
            // in
            .clk(clk),
            .rst(rst),
            .ini(20'd0),
            .fin(addr_j),
            .start(get_v_nn),
            .en(exec | (i == addr_i & j == addr_j)),

            // out
            .data(j),
            .last(update)
        );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
