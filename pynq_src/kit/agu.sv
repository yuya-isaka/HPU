
`default_nettype none


// アドレス生成ユニット
//      iniからfinまで
//      startで一度始まると止まらない (run == 1)
//      enが１の時＋１する
module agu
    #(

         // アドレス生成数の制限
         parameter W = 32

     )
     (

         // in
         input wire                     clk,
         input wire                     rst,
         // 初期値
         input wire [ W-1:0 ]           ini,
         // 終了値
         input wire [ W-1:0 ]           fin,
         // 起動信号
         input wire                     start,
         // イネーブル信号
         input wire                     en,


         // out
         // カウンタ
         output reg [ W-1:0 ]           data,
         // ラスト信号
         output logic                   last

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 実行中か否か
    reg              run;

    // TODO: last & en → lastだけでいい
    // TODO: start | runをまとめた信号があった方がいい？
    // 実行制御
    always_ff @( posedge clk ) begin

                  // reset
                  if ( rst ) begin

                      run <= 1'b0;

                  end

                  // 一度始まったらlastまで止まらない
                  else if ( start | run ) begin

                      // 初期化
                      if ( last & en ) begin

                          run <= 1'b0;

                      end

                      else begin

                          run <= 1'b1;

                      end

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // データ制御 (カウンタ)
    always_ff @( posedge clk ) begin

                  // reset
                  if ( rst ) begin

                      data <= ini;

                  end

                  // 一度始まったらlastまで止まらない
                  else if ( start | run ) begin

                      // 初期化
                      if ( last & en ) begin

                          data <= ini;

                      end

                      // イネーブル信号がONならカウント
                      else if ( en ) begin

                          data <= data + 1'b1;

                      end

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // ラスト信号制御
    always_comb begin

                    last = 1'b0;

                    if ( ( data == fin ) & ( run | start ) & en ) begin

                        last = 1'b1;

                    end

                end;


endmodule


`default_nettype wire
