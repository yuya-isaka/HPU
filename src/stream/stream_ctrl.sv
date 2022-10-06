`default_nettype none

module stream_ctrl
    (
        // in
        input wire          clk,
        input wire          rst,
        input wire          dst_ready,
        input wire          stream_ok,

        // out
        output reg          dst_valid,
        output reg          dst_last,
        output logic        stream_v,
        output logic [7:0]  stream_a
    );

    reg         stream_ok_keep;
    always_ff @(posedge clk)begin
                  if (rst) begin
                      stream_ok_keep <= 1'b0;
                  end
                  else if (dst_ready) begin
                      stream_ok_keep <= stream_ok;
                  end
              end;

    reg         stream_active;
    always_ff @(posedge clk)begin
                  if (rst) begin
                      stream_active <= 1'b0;
                  end
                  else if (last_stream) begin
                      stream_active <= 1'b0;
                  end
                  else if (dst_ready & stream_ok) begin
                      stream_active <= 1'b1;
                  end
              end;

    wire [7:0]      i;
    wire            last_stream;
    agu #(.W(8)) agu_stream_i
        (
            .ini(8'd0),
            .fin(8'd0),
            .start(start),
            .clk(clk),
            .rst(rst),
            .en(dst_ready),

            .data(i),
            .last(last_stream)
        );

    always_ff @(posedge clk)begin
                  if (rst) begin
                      dst_valid <= 1'b0;
                  end
                  else if (dst_ready) begin
                      dst_valid <= stream_active;
                  end
              end;

    always_ff @(posedge clk)begin
                  if (rst) begin
                      dst_last <= 1'b0;
                  end
                  else if (dst_ready) begin
                      dst_last <= stream_active & last_stream;
                  end
              end;

    //==============================================================

    logic       start;
    always_comb begin
                    start = 1'b0;

                    if (dst_ready & stream_ok_keep) begin
                        start = 1'b1;
                    end
                end;

    always_comb begin
                    stream_a = i;
                    stream_v = stream_active & dst_ready;
                end;

endmodule

`default_nettype wire
