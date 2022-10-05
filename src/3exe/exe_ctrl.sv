`default_nettype none

module exe_ctrl
    (
        input wire              clk,
        input wire              rst,
        input wire              src_v,
        input wire [19:0]       addr_i,
        input wire [19:0]       addr_j,

        output wire             last_j,
        output reg              s_fin,
        output reg              exec
    );

    wire last_i;
    wire next_i, next_j;
    wire [19:0] i;
    wire [19:0] j;

    // 要改良
    always_ff @(posedge clk)begin
                  if(rst)begin
                      exec <= 1'b0;
                  end
                  else begin
                      exec <= src_v;
                  end
              end;

    reg src_v_n, src_v_nn;
    always_ff @(posedge clk) begin
                  src_v_n <= src_v;
                  src_v_nn <= src_v_n;
              end;

    agu_next #(.W(20)) l_i (.ini(2'd0), .fin(addr_i), .start(src_v), .last(last_i), .clk(clk),  .rst(rst),
                            .next(next_i), .data(i), .en(last_j));

    agu_next #(.W(20)) l_j (.ini(3'd0), .fin(addr_j),  .start(src_v_nn), .last(last_j), .clk(clk),  .rst(rst),
                            .next(next_j), .data(j), .en(exec | (i == addr_i & j == addr_j)));

    always_ff @(posedge clk)begin
                  if(rst)begin
                      s_fin <= 1'b0;
                  end
                  else begin
                      s_fin <= last_i;
                  end
              end;

endmodule

`default_nettype wire
