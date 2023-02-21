
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
         input wire                             store,
         // 各コアの結果
         input wire                             core_result,

         // out
         // 対応する次元のビット（符号ビットで判断）
         output wire 		                    sign_bit

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 0, 1, -1を格納
    wire signed [ 1:0 ]      select;


    selector selector
             (

                 // in
                 .clk( clk ),
                 .store_bit( store ),
                 // 各コアの結果ビット
                 .core_result_bit( core_result ),


                 // out
                 // 各コアの結果ビットから、0,1,-1を選択
                 .sel_bit( select )

             );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg         store_n;

    always_ff @( posedge clk ) begin

                  if ( ~rst ) begin

                      store_n <= store;

                  end

              end;



    reg signed [ W-1:0 ]        box;

    // TODO: 分けた方がいい？
    always_ff @( posedge clk ) begin

                  // 初期化
                  if ( rst ) begin

                      box <= 0;

                  end

                  // HDCプロセッサ起動中
                  else begin

                      // box更新
                      if ( store_n ) begin

                          box <= box + select;

                      end

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 符号ビット
    // 非同期読み出し
    assign sign_bit = box[ W-1 ];


endmodule


`default_nettype wire
