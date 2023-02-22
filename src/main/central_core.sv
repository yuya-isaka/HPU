
`default_nettype none


module central_core
    #(

         // ハイパーベクトルの次元数
         parameter DIM = 1023,

         parameter THREADS = 5,

         parameter WI = 31

     )
     (

         // in
         input wire                         clk,
         input wire                         run,
         input wire                         com,
         input wire                         get_v,
         input wire                         get_c,
         // 16bit命令
         input wire [ 15:0 ]                get_d,
         input wire [ 31:0 ]                get_d_all,
         input wire                         exec,


         // out
         output reg                         store,
         output logic [ DIM:0 ]             core_result,
         output reg                         last

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // アイテムメモリ
    (* ram_style = "block" *)
    reg [ DIM:0 ]           item_memory [ 0:511 ];


    // アイテムメモリーからロードしたデータの一時格納場所
    reg [ DIM:0 ]           reg_0;

    always_ff @( posedge clk ) begin

                  // 書き込み
                  // 書き戻し | ランダム生成
                  if ( update_item ) begin

                      item_memory[ item_a ] <= rand_num;

                  end

                  // 読み出し
                  // 常に垂れ流しで読み出しでOK
                  // (必要ない場合は使わない)
                  reg_0 <= item_memory[ get_d[ 8:0 ] ];

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 命令
    reg [ 15:0 ]                inst;

    always_ff @( posedge clk ) begin

                  // thread_countは保持しておきたいので、実行終了時のみリセット
                  if ( ~run ) begin

                      inst <= 0;

                  end

                  // データ受信時実行
                  else if ( get_v ) begin

                      inst <= get_d[ 15:0 ];

                  end

                  // データを受信していないとき実行
                  // (リセットも兼ねる)
                  else begin

                      // instは保持しなくていい
                      // (たとえ、instを更新した後にget_vが落ちても、execはまだ続いているので、次サイクルで使われる)
                      inst <= 0;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    wire [ DIM:0 ]          permute_reg_result;

    // 次元数可変
    // permute #( .DIM( 31 ) ) permute

    permute #( .DIM( 1023 ) ) permute
            (

                // in
                .clk( clk ),
                .exec( exec ),
                .data( reg_2[ DIM:0 ] ),
                .permute_num( inst[ 9:0 ] ),


                // out
                .result( permute_reg_result[ DIM:0 ] )

            );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // reg_1_thread, reg_2_threadsは値を保持
    // reg_0はその度にロードされるから保持しなくていい


    reg [ DIM:0 ]         reg_1;

    always_ff @( posedge clk ) begin

                  if ( exec & ~inst[ 15 ] & inst[ 11 ] ) begin

                      reg_1 <= reg_2_tmp;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    logic [ DIM:0 ]         reg_2_tmp;

    always_comb begin

                    if ( inst[ 14 ] ) begin

                        reg_2_tmp = permute_reg_result;

                    end

                    else begin

                        reg_2_tmp = reg_2;

                    end

                end;



    logic [ DIM:0 ]         reg_for_inst_13;

    always_comb begin

                    if ( inst[ 15 ] ) begin

                        reg_for_inst_13 = reg_0;

                    end

                    else begin

                        reg_for_inst_13 = reg_1 ^ reg_2_tmp;

                    end

                end;



    reg [ DIM:0 ]           reg_2;

    always_ff @( posedge clk ) begin

                  if ( exec & inst[ 13 ] ) begin

                      reg_2 <= reg_for_inst_13;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg [ DIM:0 ]           buff;

    always_ff @( posedge clk ) begin

                  // スレッド数可変
                  // アクセラレータの動作終了と同時にリセット
                  // reg_1_threads　reg_2_threads は保持したいため、リセット時にしか0に戻さない
                  if ( ~run ) begin

                      buff <= 0;
                      store <= 0;
                      last <= 0;

                  end

                  // アクセラレータ動作中実行
                  // 187MHzはexec->reg2がボトルネックだった
                  else if ( exec ) begin

                      // アドレス必要
                      if ( inst[ 15 ] ) begin

                          buff <= 0;
                          store <= 0;
                          last <= 0;

                      end

                      // アドレスいらん
                      else begin

                          // store
                          if ( inst[ 12 ] ) begin

                              buff <= reg_2_tmp;
                              store <= 1;
                              last <= 0;

                          end

                          // last
                          else if ( inst[ 8 ] ) begin

                              last <= 1;
                              buff <= 0;
                              store <= 0;

                          end

                          // nop (すべて0のはず)
                          // (reg1やreg2の値は保持)
                          else begin

                              buff <= 0;
                              store <= 0;
                              last <= 0;

                          end

                      end

                  end

                  // execが落ちてる場合、その前にstore,last命令は実行されているので、リセットしてOK
                  // last命令が立つ時、execは落ちている設計 (last命令は必ず最後に実行する制限)
                  //   - もしlast命令をいつでも使えるようにするなら、if (exec)内のlast命令以外でlast <= 0 をしておかないとlastが落ちないでバグりそう
                  // (最後にstoreが実行された時、落としておかないと、正しくboxにstoreされない)
                  else begin

                      buff <= 0;
                      store <= 0;
                      last <= 0;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // コアの演算結果出力
    always_comb begin

                    core_result = 0;

                    // storeが立っている間buffで更新
                    if ( store ) begin

                        core_result = buff;

                    end

                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // ================================================== ランダム関連 ==============================================================
    // ランダム関連はgen信号によって駆動
    // ============================================================================================================================



    reg                         update_item;

    // 各コアのitem_memoryにランダム値を格納するタイミング
    // item_a_tmpの値から、更新タイミングを決定

    always_ff @( posedge clk ) begin

                  if ( ~com ) begin

                      update_item <= 0;

                  end

                  else if ( item_a_tmp == WI ) begin

                      update_item <= 1'd1;

                  end

                  else begin

                      update_item <= 0;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg [ 8:0 ]                 item_a;

    always_ff @( posedge clk ) begin

                  if ( ~com ) begin

                      item_a <= 0;

                  end

                  else if ( update_item ) begin

                      item_a <= item_a + 9'd1;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 32bitのランダム値の生成数
    // (1024bitのハイパーベクトルが生成される場合、32個生成）
    // (現状最大で32個なので、5bit幅)
    reg [ 4:0 ]       item_a_tmp;

    always_ff @( posedge clk ) begin

                  if ( ~com ) begin

                      item_a_tmp <= 0;

                  end

                  else if ( get_c ) begin

                      if ( item_a_tmp == WI ) begin

                          item_a_tmp <= 5'd0;

                      end

                      else begin

                          item_a_tmp <= item_a_tmp + 5'd1;

                      end

                  end

              end;



    // (ハイパーベクトル次元数が1024なら、31回別々に格納する)
    reg [ DIM:0 ]       rand_num;

    always_ff @( posedge clk ) begin

                  if ( ~com ) begin

                      rand_num <= 0;

                  end

                  else if ( com & get_c ) begin

                      // 次元数可変
                      if ( item_a_tmp == 0 ) begin

                          rand_num[ 31:0 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 1 ) begin

                          rand_num[ 63:32 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 2 ) begin

                          rand_num[ 95:64 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 3 ) begin

                          rand_num[ 127:96 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 4 ) begin

                          rand_num[ 159:128 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 5 ) begin

                          rand_num[ 191:160 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 6 ) begin

                          rand_num[ 223:192 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 7 ) begin

                          rand_num[ 255:224 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 8 ) begin

                          rand_num[ 287:256 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 9 ) begin

                          rand_num[ 319:288 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 10 ) begin

                          rand_num[ 351:320 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 11 ) begin

                          rand_num[ 383:352 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 12 ) begin

                          rand_num[ 415:384 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 13 ) begin

                          rand_num[ 447:416 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 14 ) begin

                          rand_num[ 479:448 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 15 ) begin

                          rand_num[ 511:480 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 16 ) begin

                          rand_num[ 543:512 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 17 ) begin

                          rand_num[ 575:544 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 18 ) begin

                          rand_num[ 607:576 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 19 ) begin

                          rand_num[ 639:608 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 20 ) begin

                          rand_num[ 671:640 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 21 ) begin

                          rand_num[ 703:672 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 22 ) begin

                          rand_num[ 735:704 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 23 ) begin

                          rand_num[ 767:736 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 24 ) begin

                          rand_num[ 799:768 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 25 ) begin

                          rand_num[ 831:800 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 26 ) begin

                          rand_num[ 863:832 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 27 ) begin

                          rand_num[ 895:864 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 28 ) begin

                          rand_num[ 927:896 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 29 ) begin

                          rand_num[ 959:928 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 30 ) begin

                          rand_num[ 991:960 ] <= get_d_all[ 31:0 ];

                      end

                      else if ( item_a_tmp == 31 ) begin

                          rand_num[ 1023:992 ] <= get_d_all[ 31:0 ];

                      end

                  end

              end;


endmodule


`default_nettype wire
