
`default_nettype none


module stream_ctrl
    #(

         // コア数 (デバッグ用)
         parameter CORENUM = 16

     )
     (

         // in
         input wire                             clk,
         input wire                             rst,
         input wire                             last,
         input wire                             dst_ready,


         // out
         output reg                             dst_valid,
         output reg                             dst_last,
         output logic                           stream_v,
         output wire [ 4:0 ]                    stream_i

     );


    //// last -> last_n -> last_nn ->  stream_ok_keep (stream_ok保持) -> dst_valid (stream_active引き金)
    ////                               start (stream_ok_keep引き金)       dst_last (stream_active & last_stream引き金)
    ////                               stream_active (sream_ok引き金)
    ////                               stream_v (stream_active引き金)
    ////                               last_stream (start引き金)


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // ラスト命令 (9命令) が実行された時、同時に他のコアでstore命令が実行されていることを考慮
    // sign_bitが更新されるまで3サイクル待つ
    reg         last_n;
    reg         last_nn;

    always_ff @( posedge clk ) begin

                  if ( rst ) begin

                      last_n <= 0;
                      last_nn <= 0;

                  end

                  else begin

                      last_n <= last;
                      last_nn <= last_n;

                  end

              end;



    // ラスト命令が発行された後に、dst_readyが落ちている場合を考慮
    // ラスト命令が発行された事実を保持
    reg         last_keep;

    always_ff @( posedge clk ) begin

                  if ( rst ) begin

                      last_keep <= 1'b0;

                  end

                  // 問題なく発行できそうなら、keepはしない
                  // stream_okを先に評価する
                  else if ( stream_ok ) begin

                      last_keep <= 1'b0;

                  end

                  else if ( last_nn ) begin

                      last_keep <= 1'b1;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 引き金: last_nn か last_keep
    logic       stream_ok;

    always_comb begin

                    stream_ok = 1'b0;

                    if ( ( last_nn | last_keep) & dst_ready ) begin

                        stream_ok = 1'b1;

                    end

                end;



    // stream_okが立った事実を保持
    reg         stream_ok_keep;

    always_ff @( posedge clk ) begin

                  if ( rst ) begin

                      stream_ok_keep <= 1'b0;

                  end

                  else if ( dst_ready ) begin

                      stream_ok_keep <= stream_ok;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 引き金: stream_ok
    // streamが続く限り1のまま
    reg         stream_active;

    always_ff @( posedge clk ) begin

                  if ( rst ) begin

                      stream_active <= 1'b0;

                  end

                  // 最後のストリームの時に落とす
                  // 最後のストリームが立っている時、再びstream_okが経つのは未定義動作（こっちが先に評価されるため）
                  else if ( last_stream ) begin

                      stream_active <= 1'b0;

                  end

                  // stream_active <= stream_okはだめ
                  // 一度stream_okが立ったら、stream_activeの値は保持する （last_streamが立った時に落とす）
                  else if ( dst_ready & stream_ok ) begin

                      stream_active <= 1'b1;

                  end

              end;



    // 引き金: stream_active
    // streamが続く限り1のまま
    // dst_valid(M_AXIS_TVALIDが立ったタイミングのstream_d(M_AXIS_TDATA)のデータが送信される
    always_ff @( posedge clk ) begin

                  if ( rst ) begin

                      dst_valid <= 1'b0;

                  end

                  else if ( dst_ready ) begin

                      dst_valid <= stream_active;

                  end

              end;


    // 引き金: stream_active
    assign stream_v = dst_ready & stream_active;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 引き金： stream_ok_keep
    logic       start;

    always_comb begin

                    start = 1'b0;

                    if ( dst_ready & stream_ok_keep ) begin

                        start = 1'b1;

                    end

                end;



    // 引き金: start
    wire                last_stream;

    // 各コアで違う結果を返したい時に使うかも？
    agu #( .W( 5 ) ) agu_stream_i
        (

            // in
            .ini( 5'd0 ),
            .fin( 5'd31 ),
            .start( start ),
            .clk( clk ),
            .rst( rst ),
            .en( dst_ready ),


            // out
            .data( stream_i ),
            .last( last_stream )

        );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 引き金: stream_activeとlast_stream
    // dst_validが立つ & 最後のストリームの時立たせる
    always_ff @( posedge clk ) begin

                  if ( rst ) begin

                      dst_last <= 1'b0;

                  end

                  else if ( dst_ready ) begin

                      dst_last <= stream_active & last_stream;

                  end

              end;


endmodule


`default_nettype wire
