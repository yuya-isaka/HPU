
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
         input wire [ DIM:0 ]                   core_result,
         input wire                             store,
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

            // 計算数可変 (現状最大でACPポートがカバーできるのは１GBなので、30bitあれば十分)
            counter #( .W( 26 ), .CORENUM( 1 ) ) counter
                    (

                        // in
                        .clk( clk ),
                        .rst( rst ),
                        .store( store ),
                        .core_result( core_result[ j ] ),

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
