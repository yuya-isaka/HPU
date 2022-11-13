
`default_nettype none


module counter
    #(

         // 現状最大でACPポートがカバーできるのは１GBなので、30bitあれば十分
         // counterで数える上限
         parameter W = 30,
         // コア数 (デバッグ用)
         parameter CORENUM = 16

     )
     (

         // in
         input wire			                    clk,
         input wire                             rst,
         // 1コア
         input wire [ CORENUM-1:0 ]             store,
         //  input wire                         store,
         // 1コア
         input wire [ CORENUM-1:0 ]             core_result,
         //  input wire                         core_result,


         // out
         output logic 		                    sign_bit

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg         store_n;
    reg         store_nn;

    reg signed [ W-1:0 ]      box;

    // コア数可変
    // 3bitあれば十分
    reg signed [ 2:0 ]      box_1;
    reg signed [ 2:0 ]      box_2;
    reg signed [ 2:0 ]      box_3;
    reg signed [ 2:0 ]      box_4;


    always_ff @( posedge clk ) begin

                  store_n <= store;
                  store_nn <= store_n;

                  if ( rst ) begin
                      // コア数可変
                      box_1 <= 0;
                      box_2 <= 0;
                      box_3 <= 0;
                      box_4 <= 0;
                  end

                  else if ( store_n ) begin
                      // コア数可変
                      // 1コア
                      //   box_1 <= select;
                      // 2コア
                      //   box_1 <= select[ 0 ] + select[ 1 ];
                      box_1 <=
                            select[ 0 ]
                            + select[ 1 ]
                            + select[ 2 ];
                      box_2 <=
                            select[ 3 ]
                            + select[ 4 ]
                            + select[ 5 ];
                      box_3 <=
                            select[ 6 ]
                            + select[ 7 ]
                            + select[ 8 ];
                      box_4 <=
                            select[ 9 ]
                            + select[ 10 ]
                            + select[ 11 ];
                      // box_4 <=
                      //       select[ 12 ]
                      //       + select[ 13 ]
                      //       + select[ 14 ]
                      //       + select[ 15 ];
                  end


                  // 現状アクセラレータの動作を止めることで、counterの値をフラッシュ（将来命令セットにフラッシュを加えるかも）
                  if ( rst) begin
                      box <= 0;
                  end

                  // store_nと分離することで、storeが連続で実行されても対応可能にした
                  else if ( store_nn ) begin
                      // コア数可変
                      // 16コア
                      box <=
                          box
                          + box_1
                          + box_2
                          + box_3
                          + box_4;
                      // 1-4コア
                      //   box <= box + box_1;
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
