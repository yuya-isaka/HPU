
`default_nettype none


module buffer_ctrl
    #(

         // ハイパーベクトルの次元数
         parameter DIM = 1023,

         // コア数 (デバッグ用)
         parameter CORENUM = 16

     )
     (

         // in
         input wire                             clk,
         input wire                             rst,
         // コア数可変
         input wire [ DIM:0 ]                   core_result_1,
         input wire [ DIM:0 ]                   core_result_2,
         input wire [ DIM:0 ]                   core_result_3,
         input wire [ DIM:0 ]                   core_result_4,
         input wire [ DIM:0 ]                   core_result_5,
         input wire [ DIM:0 ]                   core_result_6,
         input wire [ DIM:0 ]                   core_result_7,
         input wire [ DIM:0 ]                   core_result_8,
         input wire [ DIM:0 ]                   core_result_9,
         input wire [ DIM:0 ]                   core_result_10,
         input wire [ DIM:0 ]                   core_result_11,
         input wire [ DIM:0 ]                   core_result_12,
         input wire [ DIM:0 ]                   core_result_13,
         input wire [ DIM:0 ]                   core_result_14,
         input wire [ DIM:0 ]                   core_result_15,
         input wire [ DIM:0 ]                   core_result_16,
         //  input wire [ DIM:0 ]                   core_result_17,
         //  input wire [ DIM:0 ]                   core_result_18,
         //  input wire [ DIM:0 ]                   core_result_19,
         //  input wire [ DIM:0 ]                   core_result_20,
         //  input wire [ DIM:0 ]                   core_result_21,
         //  input wire [ DIM:0 ]                   core_result_22,
         //  input wire [ DIM:0 ]                   core_result_23,
         //  input wire [ DIM:0 ]                   core_result_24,
         //  input wire [ DIM:0 ]                   core_result_25,
         //  input wire [ DIM:0 ]                   core_result_26,
         //  input wire [ DIM:0 ]                   core_result_27,
         //  input wire [ DIM:0 ]                   core_result_28,
         //  input wire [ DIM:0 ]                   core_result_29,
         //  input wire [ DIM:0 ]                   core_result_30,
         //  input wire [ DIM:0 ]                   core_result_31,
         //  input wire [ DIM:0 ]                   core_result_32,
         // 1コア
         input wire [ CORENUM-1:0 ]             store,
         //  input wire                         store,
         input wire                             stream_v,
         input wire [ 1:0 ]                     stream_i,


         // out
         output logic [ 255:0 ]                 stream_d,
         output wire  [ DIM:0 ]                 sign_bit

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 次元数分のカウンターを用意
    generate

        genvar      j;

        for ( j = 0; j < DIM + 1; j = j + 1 ) begin

            // コア数可変
            // 計算数可変 (現状最大でACPポートがカバーできるのは１GBなので、30bitあれば十分)
            counter #( .W( 26 ), .CORENUM( 16 ) ) counter
                    (

                        // in
                        .clk( clk ),
                        .rst( rst ),
                        // 1コア
                        // .store( store ),
                        .store( store[ CORENUM-1:0 ] ),
                        // コア数可変
                        // この順番で渡す必要がある
                        .core_result(
                            {
                                // core_result_32[ j ],
                                // core_result_31[ j ],
                                // core_result_30[ j ],
                                // core_result_29[ j ],
                                // core_result_28[ j ],
                                // core_result_27[ j ],
                                // core_result_26[ j ],
                                // core_result_25[ j ],
                                // core_result_24[ j ],
                                // core_result_23[ j ],
                                // core_result_22[ j ],
                                // core_result_21[ j ],
                                // core_result_20[ j ],
                                // core_result_19[ j ],
                                // core_result_18[ j ],
                                // core_result_17[ j ],
                                core_result_16[ j ],
                                core_result_15[ j ],
                                core_result_14[ j ],
                                core_result_13[ j ],
                                core_result_12[ j ],
                                core_result_11[ j ],
                                core_result_10[ j ],
                                core_result_9[ j ],
                                core_result_8[ j ],
                                core_result_7[ j ],
                                core_result_6[ j ],
                                core_result_5[ j ],
                                core_result_4[ j ],
                                core_result_3[ j ],
                                core_result_2[ j ],
                                core_result_1[ j ]
                            }
                        ),


                        // out
                        .sign_bit( sign_bit[ j ] )

                    );

        end
    endgenerate


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 16コア
    // 『stream_vが立つタイミングのsign_bitが求めてた値』
    // last     ->   last_n      ->  last_nn    ->  stream_v
    //          ->   select      ->  box_1 ...  ->  box (sign_bit)


    // stream_d
    always_ff @( posedge clk ) begin

                  // 次元数可変
                  // stream_vがたった次のタイミングに値を更新
                  // stram_vの次にdst_validが立つ設計
                  if ( stream_v ) begin

                      if ( stream_i == 2'd0 ) begin

                          stream_d[ 255:0 ] <= sign_bit[ 255:0 ];
                          //   stream_d[ 511:0 ] <= sign_bit[ 1023:512 ];
                          //   stream_d[ 31:0 ] <= sign_bit[ 31:0 ];
                          //   stream_d[ 511:32 ] <= 0;

                      end

                      else if ( stream_i == 2'd1 ) begin

                          stream_d[ 255:0 ] <= sign_bit[ 511:256 ];

                      end

                      else if ( stream_i == 2'd2) begin

                          stream_d[ 255:0 ] <= sign_bit[ 767:512 ];

                      end

                      else begin

                          stream_d[ 255:0 ] <= sign_bit[ 1023:768 ];
                          //   stream_d[ 511:0 ] <= sign_bit[ 511:0 ];
                          //   stream_d[ 511:0 ] <= 0;

                      end

                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
