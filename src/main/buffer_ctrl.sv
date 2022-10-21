`default_nettype none


module buffer_ctrl
    #(
         parameter DIM = 1023
     )
     (
         // in
         input wire              clk,
         input wire              rst,
         input wire              tmp_even,
         input wire [DIM:0]       tmp_rand,
         // コア数可変
         input wire [DIM:0]       core_result_1,
         input wire [DIM:0]       core_result_2,
         input wire [DIM:0]       core_result_3,
         input wire [DIM:0]       core_result_4,
         //  input wire [DIM:0]       core_result_5,
         //  input wire [DIM:0]       core_result_6,
         //  input wire [DIM:0]       core_result_7,
         //  input wire [DIM:0]       core_result_8,
         //  input wire [DIM:0]       core_result_9,
         //  input wire [DIM:0]       core_result_10,
         //  input wire [DIM:0]       core_result_11,
         //  input wire [DIM:0]       core_result_12,
         //  input wire [DIM:0]       core_result_13,
         //  input wire [DIM:0]       core_result_14,
         //  input wire [DIM:0]       core_result_15,
         //  input wire [DIM:0]       core_result_16,
         //  input wire [DIM:0]       core_result_17,
         //  input wire [DIM:0]       core_result_18,
         //  input wire [DIM:0]       core_result_19,
         //  input wire [DIM:0]       core_result_20,
         //  input wire [DIM:0]       core_result_21,
         //  input wire [DIM:0]       core_result_22,
         //  input wire [DIM:0]       core_result_23,
         //  input wire [DIM:0]       core_result_24,
         //  input wire [DIM:0]       core_result_25,
         //  input wire [DIM:0]       core_result_26,
         //  input wire [DIM:0]       core_result_27,
         //  input wire [DIM:0]       core_result_28,
         //  input wire [DIM:0]       core_result_29,
         //  input wire [DIM:0]       core_result_30,
         //  input wire [DIM:0]       core_result_31,
         //  input wire [DIM:0]       core_result_32,
         // コア数可変
         input wire [3:0]           store,
         input wire                 stream_v,

         // out
         output logic [1023:0]      stream_d
     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    wire [DIM:0]      sign_bit;

    generate
        genvar i;
        for (i = 0; i < DIM+1; i = i + 1) begin

            // 計算数可変
            counter #(.W(30)) counter
                    (
                        // in
                        .clk(clk),
                        .rst(rst),
                        .tmp_even(tmp_even),
                        .tmp_rand_bit(tmp_rand[i]),
                        // コア数可変
                        // .store(store[31:0]),
                        .store(store[3:0]),
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

                        // out
                        .sign_bit(sign_bit[i])
                    );

        end
    endgenerate


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 4コア
    // 『stream_vが立つタイミングのencoded_hvが求めてた値』
    //         ->   get_fin         ->   stream_v
    //                              ->   sign_bit(最新値)
    //         ->   select          ->   box ↑(sign_bit), update前にselectが組み合わせ回路で求まっている前提


    // 32コア
    // 『stream_vが立つタイミングのsign_bitが求めてた値』
    // update  ->   get_fin      ->  get_fin_n  ->  get_fin_nn   ->  stream_v
    //         ->   update_n     ->  update_nn  ->  update_nnn   ->  sign_bit(最新値)
    //         ->   select       ->  box_1 ...  ->  box_11       ->  box ↑ sign_bitも最新値


    // stream_d
    always_ff @(posedge clk) begin
                  if (stream_v) begin
                      stream_d <= sign_bit;
                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
