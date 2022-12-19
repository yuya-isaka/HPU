
`default_nettype none


module counter
    #(

         // 現状最大でACPポートがカバーできるのは１GBなので、30bitあれば十分
         // counterで数える上限
         parameter W = 30,

         // コア数 (デバッグ用)
         parameter CORENUM = 32

     )
     (

         // in
         input wire			                    clk,
         input wire                             rst,
         // 1コア
         input wire [ CORENUM-1:0 ]             store,
         //  input wire                         store,
         input wire                             store_flag,
         // 1コア
         input wire [ CORENUM-1:0 ]             core_result,
         //  input wire                         core_result,


         // out
         output wire 		                    sign_bit

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    reg         store_n;
    reg         store_nn;

    always_ff @( posedge clk ) begin

                  if ( ~rst ) begin
                      store_n <= store_flag;
                      store_nn <= store_n;
                  end

              end;


    reg signed [ W-1:0 ]      box;

    // コア数可変
    reg signed [ 4:0 ]      box_1;

    always_ff @( posedge clk ) begin

                  if ( rst ) begin

                      box <= 0;
                      box_1 <= 0;

                  end

                  else begin

                      if ( store_nn ) begin
                          box <=
                              box
                              + box_1;
                      end

                      // コア数可変
                      box_1 <=
                            select[ 0 ]
                            + select[ 1 ]
                            + select[ 2 ]
                            + select[ 3 ]
                            + select[ 4 ]
                            + select[ 5 ]
                            + select[ 6 ]
                            + select[ 7 ]
                            + select[ 8 ]
                            + select[ 9 ]
                            + select[ 10 ]
                            + select[ 11 ]
                            + select[ 12 ]
                            + select[ 13 ];
                      // + select[ 14 ];
                      // + select[ 15 ];
                      // + select[ 16 ]
                      // + select[ 17 ]
                      // + select[ 18 ]
                      // + select[ 19 ]
                      // + select[ 20 ]
                      // + select[ 21 ]
                      // + select[ 22 ]
                      // + select[ 23 ]
                      // + select[ 24 ]
                      // + select[ 25 ]
                      // + select[ 26 ]
                      // + select[ 27 ]
                      // + select[ 28 ]
                      // + select[ 29 ]
                      // + select[ 30 ]
                      // + select[ 31 ];
                      //   box_2 <=
                      //   box_3 <=
                      //   box_4 <=
                      // box_4 <=

                  end

              end;


    //================================================================


    // 0, 1, -1を格納
    // 1コア
    wire signed [ 1:0 ]      select [ 0:CORENUM-1 ];
    // wire signed [ 1:0 ]      select;

    // 各コアの結果をselectに格納　（0, 1, -1）
    generate

        genvar      k;

        for ( k = 0; k < CORENUM; k = k + 1 ) begin

            selector selector
                     (

                         // in
                         .clk( clk ),
                         // 1コア
                         .store_bit( store[ k ] ),
                         //  .store_bit( store ),
                         // 1コア
                         .core_result_bit( core_result[ k ] ),
                         //  .core_result_bit( core_result ),


                         // out
                         // 1コア
                         .sel_bit( select[ k ] )
                         //  .sel_bit( select)

                     );

        end
    endgenerate


    // 符号ビット
    // 非同期読み出し
    assign sign_bit = box[ W-1 ];


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
