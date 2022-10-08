`default_nettype none

module buffer_ctrl
    (
        // in
        input wire              clk,
        input wire              rst,
        input wire              tmp_addr_i,
        input wire [31:0]       tmp_rand,
        input wire [4:0]        remainder,
        input wire [31:0]       result_1,
        input wire [31:0]       result_2,
        input wire [31:0]       result_3,
        input wire [31:0]       result_4,
        input wire [31:0]       result_5,
        input wire [31:0]       result_6,
        input wire [31:0]       result_7,
        input wire [31:0]       result_8,
        input wire [31:0]       result_9,
        input wire [31:0]       result_10,
        input wire [31:0]       result_11,
        input wire [31:0]       result_12,
        input wire [31:0]       result_13,
        input wire [31:0]       result_14,
        input wire [31:0]       result_15,
        input wire [31:0]       result_16,
        input wire [31:0]       result_17,
        input wire [31:0]       result_18,
        input wire [31:0]       result_19,
        input wire [31:0]       result_20,
        input wire [31:0]       result_21,
        input wire [31:0]       result_22,
        input wire [31:0]       result_23,
        input wire [31:0]       result_24,
        input wire [31:0]       result_25,
        input wire [31:0]       result_26,
        input wire [31:0]       result_27,
        input wire [31:0]       result_28,
        input wire [31:0]       result_29,
        input wire [31:0]       result_30,
        input wire [31:0]       result_31,
        input wire [31:0]       result_32,
        input wire              update,
        input wire              last_update,
        input wire              get_fin,
        input wire              stream_v,
        input wire [7:0]        stream_a,

        // out
        output logic [1023:0]     stream_d
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 次元数で可変になる、要改良
    wire [31:0]      sign_bit;

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
                        .remainder(remainder[4:0]),
                        .result(
                            {
                                result_32[i],
                                result_31[i],
                                result_30[i],
                                result_29[i],
                                result_28[i],
                                result_27[i],
                                result_26[i],
                                result_25[i],
                                result_24[i],
                                result_23[i],
                                result_22[i],
                                result_21[i],
                                result_20[i],
                                result_19[i],
                                result_18[i],
                                result_17[i],
                                result_16[i],
                                result_15[i],
                                result_14[i],
                                result_13[i],
                                result_12[i],
                                result_11[i],
                                result_10[i],
                                result_9[i],
                                result_8[i],
                                result_7[i],
                                result_6[i],
                                result_5[i],
                                result_4[i],
                                result_3[i],
                                result_2[i],
                                result_1[i]
                            }
                        ),
                        .update(update),
                        .last_update(last_update),

                        // out
                        .sign_bit(sign_bit[i])
                    );
        end
    endgenerate


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg [31:0]      encoded_hv;
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
