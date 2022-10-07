`default_nettype none

module buffer_ctrl
    (
        // in
        input wire              clk,
        input wire              rst,
        input wire              tmp_addr_i,
        input wire [31:0]       tmp_rand,
        input wire [31:0]       result_1,
        input wire [31:0]       result_2,
        input wire              update,
        input wire              last_update,
        input wire              get_fin,
        input wire              stream_v,
        input wire [7:0]        stream_a,

        // out
        output logic [127:0]     stream_d
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 次元数で可変になる、要改良
    wire [127:0]      sign_bit;

    generate
        genvar i;
        for (i = 0; i < 32; i = i + 1) begin
            counter counter
                    (
                        // in
                        .clk(clk),
                        .rst(rst),
                        .tmp_addr_i(tmp_addr_i),
                        .tmp_rand_bit(tmp_rand[i]),
                        .result_bit_1(result_1[i]),
                        .result_bit_2(result_2[i]),
                        .update(update),
                        .last_update(last_update),

                        // out
                        .sign_bit(sign_bit[i])
                    );
        end
    endgenerate


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg [127:0]      encoded_hv;
    always_ff @(posedge clk) begin
                  if (get_fin) begin
                      encoded_hv <= sign_bit;
                  end
              end;


    // stream_d
    always_ff @(posedge clk) begin
                  if (stream_v) begin
                      stream_d <= encoded_hv;
                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
