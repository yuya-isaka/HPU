module src_buf
    (
        input wire        clk,
        input wire        src_v,
        input wire [8:0]  src_a,
        input wire [1023:0] src_d,
        input wire        exec,
        input wire [8:0]  exec_src_addr,

        output reg [31:0] exec_src_data
    );

    reg [31:0]        buff0 [0:255];
    reg [31:0]        buff1 [0:255];

    generate
        genvar i;
        for (i = 0; i < 32; i = i + 1) begin
            always_ff @(posedge clk) begin
                          if(src_v&~src_a[8]) begin
                              buff0[src_a+i] <= src_d[((i+1)*32)-1:0+(i*32)];
                          end
                      end;
        end
    endgenerate

    always_ff @(posedge clk) begin
                  if(exec & ~exec_src_addr[8]) begin
                      exec_src_data <= buff0[exec_src_addr[7:0]];
                  end
              end;

    generate
        genvar j;
        for (j = 0; j < 32; j = j + 1) begin
            always_ff @(posedge clk) begin
                          if(src_v& src_a[8]) begin
                              buff1[src_a+j] <= src_d[((j+1)*32)-1:0+(j*32)];
                          end
                      end;
        end
    endgenerate

    always_ff @(posedge clk) begin
                  if(exec & exec_src_addr[8]) begin
                      exec_src_data <= buff1[exec_src_addr[7:0]];
                  end
              end;

endmodule
