`default_nettype none

module exe_ctrl
    (
        input wire              clk,
        input wire              rst,
        input wire              get_v,
        input wire [19:0]       addr_i,
        input wire [19:0]       addr_j,

        output wire             last_j,
        output reg              get_fin,
        output reg              exec
    );

    wire last_i;
    wire [19:0] i;
    wire [19:0] j;

    // 要改良
    always_ff @(posedge clk)begin
                  if(rst)begin
                      exec <= 1'b0;
                  end
                  else begin
                      exec <= get_v;
                  end
              end;

    reg get_v_n, get_v_nn;
    always_ff @(posedge clk) begin
                  get_v_n <= get_v;
                  get_v_nn <= get_v_n;
              end;

    agu #(.W(20)) l_i
             (
                 .ini(2'd0),
                 .fin(addr_i),
                 .start(get_v),
                 .last(last_i),
                 .clk(clk),
                 .rst(rst),
                 .data(i),
                 .en(last_j)
             );

    agu #(.W(20)) l_j
             (
                 .ini(3'd0),
                 .fin(addr_j),
                 .start(get_v_nn),
                 .last(last_j),
                 .clk(clk),
                 .rst(rst),
                 .data(j),
                 .en(exec | (i == addr_i & j == addr_j))
             );

    always_ff @(posedge clk)begin
                  if(rst)begin
                      get_fin <= 1'b0;
                  end
                  else begin
                      get_fin <= last_i;
                  end
              end;

endmodule

`default_nettype wire
