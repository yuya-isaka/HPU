
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
         //  input wire [ DIM:0 ]                   core_result_3,
         //  input wire [ DIM:0 ]                   core_result_4,
         //  input wire [ DIM:0 ]                   core_result_5,
         //  input wire [ DIM:0 ]                   core_result_6,
         //  input wire [ DIM:0 ]                   core_result_7,
         //  input wire [ DIM:0 ]                   core_result_8,
         //  input wire [ DIM:0 ]                   core_result_9,
         //  input wire [ DIM:0 ]                   core_result_10,
         //  input wire [ DIM:0 ]                   core_result_11,
         //  input wire [ DIM:0 ]                   core_result_12,
         //  input wire [ DIM:0 ]                   core_result_13,
         //  input wire [ DIM:0 ]                   core_result_14,
         //  input wire [ DIM:0 ]                   core_result_15,
         //  input wire [ DIM:0 ]                   core_result_16,
         input wire [ CORENUM-1:0 ]             store,
         input wire                             store_flag,
         input wire                             stream_v,
         input wire [ 4:0 ]                     stream_i,


         // out
         output logic [ 31:0 ]                  stream_d,
         output wire  [ DIM:0 ]                 sign_bit

     );


    // 『stream_vが立つタイミングのsign_bitが求めてた値』
    // last     ->   last_n      ->  last_nn    ->  stream_v
    //          ->   select      ->  box_1 ...  ->  box (sign_bit)


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 次元数分のカウンターを用意
    generate

        genvar      j;

        for ( j = 0; j < DIM + 1; j = j + 1 ) begin

            // コア数可変
            // 計算数可変 (現状最大でACPポートがカバーできるのは１GBなので、30bitあれば十分)

            counter #( .W( 26 ), .CORENUM( 2 ) ) counter
                    (

                        // in
                        .clk( clk ),
                        .rst( rst ),
                        // 1コア
                        // .store( store ),
                        .store( store[ CORENUM-1:0 ] ),
                        .store_flag( store_flag ),
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
                                // core_result_16[ j ],
                                // core_result_15[ j ],
                                // core_result_14[ j ],
                                // core_result_13[ j ],
                                // core_result_12[ j ],
                                // core_result_11[ j ],
                                // core_result_10[ j ],
                                // core_result_9[ j ],
                                // core_result_8[ j ],
                                // core_result_7[ j ],
                                // core_result_6[ j ],
                                // core_result_5[ j ],
                                // core_result_4[ j ],
                                // core_result_3[ j ],
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


    // stream_d
    always_ff @( posedge clk ) begin

                  // 次元数可変
                  // stream_vがたった次のタイミングに値を更新
                  // stram_vの次にdst_validが立つ設計
                  if ( stream_v ) begin

                      if ( stream_i == 5'd0 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 31:0 ];

                      end

                      else if ( stream_i == 5'd1 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 63:32 ];

                      end

                      else if ( stream_i == 5'd2 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 95:64 ];

                      end

                      else if ( stream_i == 5'd3 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 127:96 ];

                      end

                      else if ( stream_i == 5'd4 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 159:128 ];

                      end

                      else if ( stream_i == 5'd5 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 191:160 ];

                      end

                      else if ( stream_i == 5'd6 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 223:192 ];

                      end

                      else if ( stream_i == 5'd7 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 255:224 ];

                      end

                      else if ( stream_i == 5'd8 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 287:256 ];

                      end

                      else if ( stream_i == 5'd9 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 319:288 ];

                      end

                      else if ( stream_i == 5'd10 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 351:320 ];

                      end

                      else if ( stream_i == 5'd11 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 383:352 ];

                      end

                      else if ( stream_i == 5'd12 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 415:384 ];

                      end

                      else if ( stream_i == 5'd13 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 447:416 ];

                      end

                      else if ( stream_i == 5'd14 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 479:448 ];

                      end

                      else if ( stream_i == 5'd15 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 511:480 ];

                      end

                      else if ( stream_i == 5'd16 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 543:512 ];

                      end

                      else if ( stream_i == 5'd17 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 575:544 ];

                      end

                      else if ( stream_i == 5'd18 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 607:576 ];

                      end

                      else if ( stream_i == 5'd19 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 639:608 ];

                      end

                      else if ( stream_i == 5'd20 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 671:640 ];

                      end

                      else if ( stream_i == 5'd21 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 703:672 ];

                      end

                      else if ( stream_i == 5'd22 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 735:704 ];

                      end

                      else if ( stream_i == 5'd23 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 767:736 ];

                      end

                      else if ( stream_i == 5'd24 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 799:768 ];

                      end

                      else if ( stream_i == 5'd25 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 831:800 ];

                      end

                      else if ( stream_i == 5'd26 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 863:832 ];

                      end

                      else if ( stream_i == 5'd27 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 895:864 ];

                      end

                      else if ( stream_i == 5'd28 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 927:896 ];

                      end

                      else if ( stream_i == 5'd29 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 959:928 ];

                      end

                      else if ( stream_i == 5'd30 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 991:960 ];

                      end

                      else if ( stream_i == 5'd31 ) begin

                          stream_d[ 31:0 ] <= sign_bit[ 1023:992 ];

                      end

                  end

              end;


endmodule


`default_nettype wire
