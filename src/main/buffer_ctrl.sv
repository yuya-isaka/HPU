`default_nettype none


module buffer_ctrl
    (
        // in
        input wire              clk,
        input wire              rst,
        input wire              tmp_even,
        input wire [31:0]       tmp_rand,
        input wire [4:0]        remainder,
        // コア数可変
        input wire [31:0]       core_result_1,
        input wire [31:0]       core_result_2,
        input wire [31:0]       core_result_3,
        input wire [31:0]       core_result_4,
        // input wire [31:0]       core_result_5,
        // input wire [31:0]       core_result_6,
        // input wire [31:0]       core_result_7,
        // input wire [31:0]       core_result_8,
        // input wire [31:0]       core_result_9,
        // input wire [31:0]       core_result_10,
        // input wire [31:0]       core_result_11,
        // input wire [31:0]       core_result_12,
        // input wire [31:0]       core_result_13,
        // input wire [31:0]       core_result_14,
        // input wire [31:0]       core_result_15,
        // input wire [31:0]       core_result_16,
        // input wire [31:0]       core_result_17,
        // input wire [31:0]       core_result_18,
        // input wire [31:0]       core_result_19,
        // input wire [31:0]       core_result_20,
        // input wire [31:0]       core_result_21,
        // input wire [31:0]       core_result_22,
        // input wire [31:0]       core_result_23,
        // input wire [31:0]       core_result_24,
        // input wire [31:0]       core_result_25,
        // input wire [31:0]       core_result_26,
        // input wire [31:0]       core_result_27,
        // input wire [31:0]       core_result_28,
        // input wire [31:0]       core_result_29,
        // input wire [31:0]       core_result_30,
        // input wire [31:0]       core_result_31,
        // input wire [31:0]       core_result_32,
        input wire              update,
        input wire              last_update,
        input wire              get_fin,
        input wire              stream_v,

        // out
        output logic [1023:0]     stream_d
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 次元数可変
    wire [31:0]      sign_bit;

    generate
        genvar i;
        // 次元数可変
        for (i = 0; i < 32; i = i + 1) begin
            counter counter
                    (
                        // in
                        .clk(clk),
                        .rst(rst),
                        .tmp_even(tmp_even),
                        .tmp_rand_bit(tmp_rand[i]),
                        // コア数可変
                        // .core_enable(core_enable[31:0]),
                        .core_enable(core_enable[3:0]),
                        // コア数可変
                        .core_result(
                            {
                                // core_result_32[i],
                                // core_result_31[i],
                                // core_result_30[i],
                                // core_result_29[i],
                                // core_result_28[i],
                                // core_result_27[i],
                                // core_result_26[i],
                                // core_result_25[i],
                                // core_result_24[i],
                                // core_result_23[i],
                                // core_result_22[i],
                                // core_result_21[i],
                                // core_result_20[i],
                                // core_result_19[i],
                                // core_result_18[i],
                                // core_result_17[i],
                                // core_result_16[i],
                                // core_result_15[i],
                                // core_result_14[i],
                                // core_result_13[i],
                                // core_result_12[i],
                                // core_result_11[i],
                                // core_result_10[i],
                                // core_result_9[i],
                                // core_result_8[i],
                                // core_result_7[i],
                                // core_result_6[i],
                                // core_result_5[i],
                                core_result_4[i],
                                core_result_3[i],
                                core_result_2[i],
                                core_result_1[i]
                            }
                        ),
                        .update(update),

                        // out
                        .sign_bit(sign_bit[i])
                    );
        end
    endgenerate


    //================================================================


    // コア数可変
    // 立っていたら無視
    // logic [31:0]        core_enable;
    logic [3:0]        core_enable;

    always_comb begin
                    // コア数可変
                    // core_enable = 32'd0;
                    core_enable = 4'd0;
                    // コア数可変
                    if (last_update & (remainder != 0)) begin
                        core_enable[0] = remainder < 1;
                        core_enable[1] = remainder < 2;
                        core_enable[2] = remainder < 3;
                        core_enable[3] = remainder < 4;
                        // core_enable[4] = remainder < 5;
                        // core_enable[5] = remainder < 6;
                        // core_enable[6] = remainder < 7;
                        // core_enable[7] = remainder < 8;
                        // core_enable[8] = remainder < 9;
                        // core_enable[9] = remainder < 10;
                        // core_enable[10] = remainder < 11;
                        // core_enable[11] = remainder < 12;
                        // core_enable[12] = remainder < 13;
                        // core_enable[13] = remainder < 14;
                        // core_enable[14] = remainder < 15;
                        // core_enable[15] = remainder < 16;
                        // core_enable[16] = remainder < 17;
                        // core_enable[17] = remainder < 18;
                        // core_enable[18] = remainder < 19;
                        // core_enable[19] = remainder < 20;
                        // core_enable[20] = remainder < 21;
                        // core_enable[21] = remainder < 22;
                        // core_enable[22] = remainder < 23;
                        // core_enable[23] = remainder < 24;
                        // core_enable[24] = remainder < 25;
                        // core_enable[25] = remainder < 26;
                        // core_enable[26] = remainder < 27;
                        // core_enable[27] = remainder < 28;
                        // core_enable[28] = remainder < 29;
                        // core_enable[29] = remainder < 30;
                        // core_enable[30] = remainder < 31;
                        // core_enable[31] = remainder < 32;
                    end
                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 4コア
    // 『stream_vが立つタイミングのencoded_hvが求めてた値』
    // update  ->   get_fin         ->   stream_v
    //         ->   sign_bit(最新値) ->   encoded_hv
    //         ->   box ↑(sign_bit), update前にselectが組み合わせ回路で求まっている前提

    // コア数可変（32ならいらない）
    // reg [31:0]      encoded_hv;
    // always_ff @(posedge clk) begin
    //               if (get_fin) begin
    //                   encoded_hv <= sign_bit;
    //               end
    //           end;


    // 32コア
    // 『stream_vが立つタイミングのsign_bitが求めてた値』
    // update  ->   get_fin      ->  get_fin_n  ->  get_fin_nn   ->  stream_v
    //         ->   update_n     ->  update_nn  ->  update_nnn   ->  sign_bit(最新値)
    //         ->   select       ->  box_1 ...  ->  box_11       ->  box ↑ sign_bitも最新値


    // stream_d
    always_ff @(posedge clk) begin
                  if (stream_v) begin
                      // コア数可変

                      // 32コア
                      stream_d <= sign_bit;

                      // 4コア
                      //   stream_d <= encoded_hv;
                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule


`default_nettype wire
