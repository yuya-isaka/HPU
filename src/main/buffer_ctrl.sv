
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
         //  input wire [ DIM:0 ]                   core_result_13,
         //  input wire [ DIM:0 ]                   core_result_14,
         //  input wire [ DIM:0 ]                   core_result_15,
         //  input wire [ DIM:0 ]                   core_result_16,
         // 1コア
         input wire [ CORENUM-1:0 ]             store,
         //  input wire                         store,
         input wire                             stream_v,


         // out
         output logic [ 1023:0 ]                stream_d,
         output wire  [ DIM:0 ]                 sign_bit

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 次元数分のカウンターを用意
    generate

        genvar i;

        for ( i = 0; i < DIM + 1; i = i + 1 ) begin

            // コア数可変
            // 計算数可変 (現状最大でACPポートがカバーできるのは１GBなので、30bitあれば十分)
            counter #( .W( 30 ), .CORENUM( 12 ) ) counter
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
                                // core_result_16[ i ],
                                // core_result_15[ i ],
                                // core_result_14[ i ],
                                // core_result_13[ i ],
                                core_result_12[ i ],
                                core_result_11[ i ],
                                core_result_10[ i ],
                                core_result_9[ i ],
                                core_result_8[ i ],
                                core_result_7[ i ],
                                core_result_6[ i ],
                                core_result_5[ i ],
                                core_result_4[ i ],
                                core_result_3[ i ],
                                core_result_2[ i ],
                                core_result_1[ i]
                            }
                        ),


                        // out
                        .sign_bit( sign_bit[ i ] )

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

                  // stream_vがたった次のタイミングに値を更新
                  // stram_vの次にdst_validが立つ設計
                  if ( stream_v ) begin
                      stream_d <= sign_bit;
                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
