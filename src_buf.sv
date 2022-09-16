module src_buf
    (
        input wire        clk,
        input wire        src_v,
        input wire [4:0]  src_a,
        input wire [63:0] src_d,
        input wire        exec,
        input wire [5:0]  exec_src_addr,

        output reg [31:0] exec_src_data
    );

    reg [63:0]        buff0 [0:15];
    reg [63:0]        wd0;
    reg [63:0]        buff1 [0:15];
    reg [63:0]        wd1;
    reg [1:0]         ia_;

    always_ff @(posedge clk) begin
                  ia_ <= {exec_src_addr[5],exec_src_addr[0]};
              end;

    always_comb begin
                    case(ia_)
                        2'd0 :
                            exec_src_data = wd0[31:0];
                        2'd1 :
                            exec_src_data = wd0[63:32];
                        2'd2 :
                            exec_src_data = wd1[31:0];
                        2'd3 :
                            exec_src_data = wd1[63:32];
                    endcase
                end;

    always_ff @(posedge clk) begin
                  if(src_v&~src_a[4]) begin
                      buff0[src_a[3:0]] <= src_d;
                  end
                  else if(exec&~exec_src_addr[5]   ) begin
                      wd0 <= buff0[exec_src_addr[4:1]];
                  end
              end;

    always_ff @(posedge clk) begin
                  if(src_v& src_a[4]) begin
                      buff1[src_a[3:0]] <= src_d;
                  end
                  else if(exec& exec_src_addr[5]   ) begin
                      wd1 <= buff1[exec_src_addr[4:1]];
                  end
              end;

endmodule
