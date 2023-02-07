
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
         // 各コアのストア信号
         input wire [ CORENUM-1:0 ]             store,
         // ストアフラグ信号（どこかのコアがstoreならON）
         input wire                             store_flag,
         // 各コアの結果
         input wire [ CORENUM-1:0 ]             core_result,


         // out
         // 対応する次元のビット（符号ビットで判断）
         output wire 		                    sign_bit

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 0, 1, -1を格納
    wire signed [ 1:0 ]      select [ 0:CORENUM-1 ];


    // 各コアの結果をselectに格納（0, 1, -1）
    generate

        genvar      k;

        for ( k = 0; k < CORENUM; k = k + 1 ) begin

            selector selector
                     (

                         // in
                         .clk( clk ),
                         // ストア信号
                         .store_bit( store[ k ] ),
                         // 各コアの結果ビット
                         .core_result_bit( core_result[ k ] ),


                         // out
                         // 各コアの結果ビットから、0,1,-1を選択
                         .sel_bit( select[ k ] )

                     );

        end

    endgenerate


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
    reg signed [ 2:0 ]      box_1; // コア数可変

    // TODO: 分けた方がいい？
    always_ff @( posedge clk ) begin

                  // 初期化
                  if ( rst ) begin

                      box <= 0;
                      box_1 <= 0;

                  end

                  // HDCプロセッサ起動中
                  else begin

                      // box更新
                      if ( store_nn ) begin

                          box <=
                              box
                              + box_1;

                      end

                      // box_1更新
                      if ( store_n ) begin

                          // コア数可変
                          box_1 <=
                                select[ 0 ]
                                + select[ 1 ];
                          // + select[ 2 ]
                          // + select[ 3 ];
                          // + select[ 4 ]
                          // + select[ 5 ]
                          // + select[ 6 ]
                          // + select[ 7 ]
                          // + select[ 8 ]
                          // + select[ 9 ]
                          // + select[ 10 ]
                          // + select[ 11 ]
                          // + select[ 12 ]
                          // + select[ 13 ];
                          // + select[ 14 ];
                          // + select[ 15 ];

                      end

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 符号ビット
    // 非同期読み出し
    assign sign_bit = box[ W-1 ];


endmodule


`default_nettype wire
