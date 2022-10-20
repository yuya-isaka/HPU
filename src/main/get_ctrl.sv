`default_nettype none

module get_ctrl
    (
        // in
        input wire              clk,
        input wire              rst,
        input wire              get_v,
        input wire [19:0]       addr_i,
        input wire [19:0]       addr_j,
        input wire [3:0]        step,

        // out
        output wire             update,
        output reg             tmp_tmp_update,
        output reg              exec,
        output wire             last_update,
        output reg              get_fin
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    wire [19:0] l;

    agu #(.W(20)) agu_new_2
        (
            // in
            .clk(clk),
            .rst(rst),
            .ini(0),
            .fin(step),
            .start((tmp_update & i == addr_i)),
            .en(1),

            // out
            .data(l),
            .last(last_update)
        );


    reg         get_v_n, get_v_nn, get_v_nnn;

    always_ff @(posedge clk) begin
                  get_v_n <= get_v;
                  get_v_nn <= get_v_n;
                  get_v_nnn <= get_v_nn;
              end;

    wire [19:0] k;
    wire tm_update;

    always_ff @(posedge clk) begin
        tmp_tmp_update <= tm_update;
    end;

    agu #(.W(20)) agu_new
        (
            // in
            .clk(clk),
            .rst(rst),
            .ini(0),
            .fin(step),
            .start(get_v_nnn),
            .en(1),

            // out
            .data(k),
            .last(tm_update)
        );


    // exec
    always_ff @(posedge clk) begin
                  if (rst) begin
                      exec <= 1'b0;
                  end
                  else begin
                      exec <= (get_v | get_v_nn);
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
    wire tmp_update;

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
            .last(tmp_update)
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
