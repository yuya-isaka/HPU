`default_nettype none


module stream_ctrl
    (
        // in
        input wire              clk,
        input wire              rst,
        input wire              get_fin,
        input wire              dst_ready,

        // out
        output reg              dst_valid,
        output reg              dst_last,
        output logic            stream_v
    );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // コア数可変
    // reg         get_fin_n, get_fin_nn;
    // always_ff @(posedge clk) begin
    //               get_fin_n <= get_fin;
    //               get_fin_nn <= get_fin_n;
    //           end;


    reg         get_fin_keep;
    always_ff @(posedge clk) begin
                  if (rst) begin
                      get_fin_keep <= 1'b0;
                  end
                  else if (stream_ok) begin
                      get_fin_keep <= 1'b0;
                  end
                  // コア数可変
                  //   else if (get_fin_nn) begin
                  else if (get_fin) begin
                      get_fin_keep <= 1'b1;
                  end
              end;


    reg         stream_ok_keep;
    always_ff @(posedge clk)begin
                  if (rst) begin
                      stream_ok_keep <= 1'b0;
                  end
                  else if (dst_ready) begin
                      stream_ok_keep <= stream_ok;
                  end
              end;


    //================================================================


    logic       stream_ok;
    always_comb begin
                    stream_ok = 1'b0;

                    // コア数可変
                    // if ((get_fin_nn | get_fin_keep) & dst_ready) begin
                    if ((get_fin | get_fin_keep) & dst_ready) begin
                        stream_ok = 1'b1;
                    end
                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // dst_valid
    always_ff @(posedge clk)begin
                  if (rst) begin
                      dst_valid <= 1'b0;
                  end
                  else if (dst_ready) begin
                      dst_valid <= stream_active;
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
            // in
            .ini(8'd0),
            .fin(8'd0),
            .start(start),
            .clk(clk),
            .rst(rst),
            .en(dst_ready),

            // out
            .data(i),
            .last(last_stream)
        );


    //================================================================


    logic       start;

    always_comb begin
                    start = 1'b0;

                    if (dst_ready & stream_ok_keep) begin
                        start = 1'b1;
                    end
                end;


    assign stream_v = stream_active & dst_ready;
    // assign stream_a = i;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // dst_last
    always_ff @(posedge clk)begin
                  if (rst) begin
                      dst_last <= 1'b0;
                  end
                  else if (dst_ready) begin
                      dst_last <= stream_active & last_stream;
                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
