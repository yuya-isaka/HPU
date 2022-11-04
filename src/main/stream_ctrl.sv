
`default_nettype none


module stream_ctrl
    #(
         parameter CORENUM = 16
     )
     (
         // in
         input wire                  clk,
         input wire                  rst,
         input wire                  get_v,
         // コア数可変
         input wire [CORENUM-1:0]           last,
         // 1コア
         // input wire            last,
         input wire                  dst_ready,

         // out
         output reg                  dst_valid,
         output reg                  dst_last,
         output logic                stream_v
     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // コア数可変
    // 32コア
    // reg         last_n, last_nn, last_nnn;
    // always_ff @(posedge clk) begin
    //               get_fin_n <= get_fin;
    //               get_fin_nn <= get_fin_n;
    //               last_nnn <= get_fin_nn;
    //           end;

    reg         last_n, last_nn;
    always_ff @(posedge clk) begin
                  if (rst) begin
                      last_n <= 1'b0;
                      last_nn <= 1'b0;
                  end
                  else begin
                      if (last != 0) begin
                          last_n <= 1'b1;
                      end
                      else begin
                          last_n <= 1'b0;
                      end
                      last_nn <= last_n;
                  end
              end;


    reg         last_keep;
    always_ff @(posedge clk) begin
                  if (rst) begin
                      last_keep <= 1'b0;
                  end
                  else if (stream_ok) begin
                      last_keep <= 1'b0;
                  end
                  // コア数可変
                  // 32コア
                  //   else if (lst_nnn) begin
                  // 4コア
                  //   else if (last) begin
                  // 16コア
                  else if (last_nn) begin
                      last_keep <= 1'b1;
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
                    // 32コア
                    // if ((last_nnn | last_keep) & dst_ready) begin
                    // 4コア
                    // if ((last | last_keep) & dst_ready) begin
                    // 16コア
                    if ((last_nn | last_keep) & dst_ready) begin
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


    wire [1:0]      i;
    wire            last_stream;

    // 各コアで違う結果を返したい時に使うかも？
    agu #(.W(2)) agu_stream_i
        (
            // in
            .ini(2'd0),
            .fin(2'd0),
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
