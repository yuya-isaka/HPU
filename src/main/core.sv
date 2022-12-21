
`default_nettype none


module core
    #(

         // ハイパーベクトルの次元数
         parameter DIM = 1023,
         parameter THREADS = 10,
         parameter WI = 31

     )
     (

         // in
         input wire                         clk,
         input wire                         run,
         input wire                         gen,
         input wire                         reset_item,
         input wire [ 9:0 ]                 item_memory_num,
         input wire                         get_v,
         // 16bit命令
         input wire [ 15:0 ]                get_d_tmp,
         input wire [ 15:0 ]                get_d_1,
         input wire                         exec,


         // out
         output logic                       finish_gen,
         output reg                         store,
         output logic [ DIM:0 ]             core_result

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic [ 15:0 ]      get_d;

    always_comb begin
                    if ( get_d_1[ 10 ] ) begin
                        get_d = get_d_1;
                    end
                    else begin
                        get_d = get_d_tmp;
                    end
                end;


    // ハイパーベクトルを保持するメモリ
    (* ram_style = "block" *)
    reg [ DIM:0 ]           item_memory [ 0:1023 ];

    // アイテムメモリーからロードしたデータの格納場所
    reg [ DIM:0 ]           reg_0;


    always_ff @( posedge clk ) begin

                  if ( update_item ) begin

                      item_memory[ item_a ] <= rand_num;

                  end

                  // 読み出し
                  // 常に垂れ流しで読み出しでOK
                  // (必要ない場合は使わない)
                  reg_0 <= item_memory[ get_d[ 9:0 ] ];

              end;


    // 命令
    reg [ 15:0 ]                inst;

    // マルチスレッド実行
    reg signed [ 3:0 ]          thread_count;

    always_ff @( posedge clk ) begin
                  if ( ~run ) begin

                      thread_count <= $signed( 1'b1 );

                  end

                  // データ受信時実行
                  else if ( get_v ) begin

                      // スレッド数可変
                      if ( thread_count == 4'd4 ) begin
                          thread_count <= 0;
                      end

                      else begin
                          thread_count <= thread_count + 4'd1;
                      end

                  end

              end;


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

                      inst <= 0;

                  end
              end;


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


    logic [ 3:0 ] thread_count_zure;

    always_comb begin
                    thread_count_zure = thread_count + 4'd1;

                    // スレッド数可変
                    // if ( thread_count == 4'd9 ) begin
                    if ( thread_count == 4'd4 ) begin
                        thread_count_zure = 0;
                    end
                end;

    // reg_1_thread, reg_2_threadsは値を保持
    // reg_0はその度にロードされるから保持しなくていい

    // レジスタ1
    reg [ DIM:0 ]         reg_1;

    // スレッド数可変
    (* ram_style = "block" *)
    reg [ DIM:0 ]           reg_1_threads [ THREADS-1:0 ];
    // reg [ DIM:0 ]           reg_1_threads_0;
    // reg [ DIM:0 ]           reg_1_threads_1;
    // reg [ DIM:0 ]           reg_1_threads_2;
    // reg [ DIM:0 ]           reg_1_threads_3;
    // reg [ DIM:0 ]           reg_1_threads_4;

    always_ff @( posedge clk ) begin

                  if ( exec & ~inst[ 15 ] & inst[ 11 ] ) begin

                      reg_1_threads[ thread_count ] <= reg_2_tmp;

                      //   if ( thread_count == 4'd0) begin
                      //       reg_1_threads_0 <= reg_2_tmp;
                      //   end
                      //   else if ( thread_count == 4'd1) begin
                      //       reg_1_threads_1 <= reg_2_tmp;
                      //   end
                      //   else if ( thread_count == 4'd2) begin
                      //       reg_1_threads_2 <= reg_2_tmp;
                      //   end
                      //   else if ( thread_count == 4'd3) begin
                      //       reg_1_threads_3 <= reg_2_tmp;
                      //   end
                      //   else if ( thread_count == 4'd4) begin
                      //       reg_1_threads_4 <= reg_2_tmp;
                      //   end

                  end

                  reg_1 <= reg_1_threads[ thread_count_zure ];

              end;

    // always_ff @( posedge clk ) begin

    //               if ( thread_count == 4'd0) begin
    //                   reg_1 <= reg_1_threads_1;
    //               end
    //               else if ( thread_count == 4'd1) begin
    //                   reg_1 <= reg_1_threads_2;
    //               end
    //               else if ( thread_count == 4'd2) begin
    //                   reg_1 <= reg_1_threads_3;
    //               end
    //               else if ( thread_count == 4'd3) begin
    //                   reg_1 <= reg_1_threads_4;
    //               end
    //               else if ( thread_count == 4'd4) begin
    //                   reg_1 <= reg_1_threads_0;
    //               end

    //           end;

    // always_ff @( posedge clk ) begin

    //               if ( exec & ~inst[ 15 ] & inst[ 11 ] ) begin

    //                   reg_1_threads[ thread_count ] <= reg_2_tmp;

    //               end

    //           end;

    // assign reg_1 = reg_1_threads[ thread_count ];



    reg [ DIM:0 ]         reg_2;

    // スレッド数可変
    (* ram_style = "block" *)
    reg [ DIM:0 ]           reg_2_threads [ THREADS-1:0 ];
    // reg [ DIM:0 ]           reg_2_threads_0;
    // reg [ DIM:0 ]           reg_2_threads_1;
    // reg [ DIM:0 ]           reg_2_threads_2;
    // reg [ DIM:0 ]           reg_2_threads_3;
    // reg [ DIM:0 ]           reg_2_threads_4;

    always_ff @( posedge clk ) begin

                  if ( exec & inst[ 13] ) begin

                      reg_2_threads[ thread_count] <= reg_for_inst_13;

                      //   if ( thread_count == 4'd0) begin
                      //       reg_2_threads_0 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd1) begin
                      //       reg_2_threads_1 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd2) begin
                      //       reg_2_threads_2 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd3) begin
                      //       reg_2_threads_3 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd4) begin
                      //       reg_2_threads_4 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd5) begin
                      //       reg_2_threads_5 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd6) begin
                      //       reg_2_threads_6 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd7) begin
                      //       reg_2_threads_7 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd8) begin
                      //       reg_2_threads_8 <= reg_for_inst_13;
                      //   end
                      //   else if ( thread_count == 4'd9) begin
                      //       reg_2_threads_9 <= reg_for_inst_13;
                      //   end

                  end

                  reg_2 <= reg_2_threads[ thread_count_zure ];
              end;

    // always_ff @( posedge clk ) begin

    //               if ( thread_count == 4'd0) begin
    //                   reg_2 <= reg_2_threads_1;
    //               end
    //               else if ( thread_count == 4'd1) begin
    //                   reg_2 <= reg_2_threads_2;
    //               end
    //               else if ( thread_count == 4'd2) begin
    //                   reg_2 <= reg_2_threads_3;
    //               end
    //               else if ( thread_count == 4'd3) begin
    //                   reg_2 <= reg_2_threads_4;
    //               end
    //               else if ( thread_count == 4'd4) begin
    //                   reg_2 <= reg_2_threads_0;
    //               end
    //               //   else if ( thread_count == 4'd5) begin
    //               //       reg_2 <= reg_2_threads_6;
    //               //   end
    //               //   else if ( thread_count == 4'd6) begin
    //               //       reg_2 <= reg_2_threads_7;
    //               //   end
    //               //   else if ( thread_count == 4'd7) begin
    //               //       reg_2 <= reg_2_threads_8;
    //               //   end
    //               //   else if ( thread_count == 4'd8) begin
    //               //       reg_2 <= reg_2_threads_9;
    //               //   end
    //               //   else if ( thread_count == 4'd9) begin
    //               //       reg_2 <= reg_2_threads_0;
    //               //   end

    //           end;

    logic [ DIM:0 ] reg_for_inst_13;

    always_comb begin
                    if ( inst[ 15 ] ) begin
                        reg_for_inst_13 = reg_0;
                    end
                    else begin
                        reg_for_inst_13 = reg_1 ^ reg_2_tmp;
                    end
                end;

    // always_ff @( posedge clk ) begin

    //               if ( exec ) begin

    //                   if ( inst[ 13 ] ) begin

    //                       if ( inst[ 15 ] ) begin

    //                           reg_2_threads[ thread_count ] <= reg_0;

    //                       end

    //                       else begin

    //                           reg_2_threads[ thread_count ] <= reg_1 ^ reg_2_tmp;

    //                       end

    //                   end

    //               end

    //           end;

    // assign reg_2 = reg_2_threads[ thread_count ];

    // レジスタ2

    logic [ DIM:0 ]      reg_2_tmp;

    always_comb begin
                    if ( inst[ 14 ] ) begin
                        reg_2_tmp = permute_reg_result;
                    end
                    else begin
                        reg_2_tmp = reg_2;
                    end
                end;


    // storeする値を蓄える変数
    reg [ DIM:0 ]           buff;

    always_ff @( posedge clk ) begin

                  // アクセラレータの動作終了と同時にリセット
                  // reg_1_threads　reg_2_threads は保持したいため、リセット時にしか0に戻さない
                  if ( ~run ) begin

                      buff <= 0;
                      store <= 0;

                  end

                  // アクセラレータ動作中実行
                  // 187MHzはexec->reg2がボトルネックだった
                  else if ( exec ) begin

                      // アドレス必要
                      if ( inst[ 15 ] ) begin

                          buff <= 0;
                          store <= 0;

                      end

                      // アドレスいらん
                      else begin

                          // store
                          if ( inst[ 12 ] ) begin

                              buff <= reg_2_tmp;
                              store <= 1;

                          end

                          // nop (すべて0のはず)
                          // (reg1やreg2の値は保持)
                          else begin

                              buff <= 0;
                              store <= 0;

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

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // コアの演算結果
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

                  if ( ~gen ) begin
                      update_item <= 0;
                  end

                  else if ( item_a_tmp == WI ) begin
                      update_item <= 1'd1;
                  end

                  else begin
                      update_item <= 0;
                  end

              end;


    reg [ 9:0 ]                 item_a;

    always_ff @( posedge clk ) begin

                  if ( ~gen ) begin
                      item_a <= 0;
                  end

                  else if ( update_item ) begin
                      item_a <= item_a + 10'd1;
                  end

              end;


    // 32bitのランダム値の生成数
    // (1024bitのハイパーベクトルが生成される場合、32個生成）
    // (現状最大で32個なので、5bit幅)
    reg [ 4:0 ]       item_a_tmp;

    always_ff @( posedge clk ) begin

                  if ( ~gen ) begin
                      item_a_tmp <= 0;
                  end

                  else begin
                      if ( item_a_tmp == WI ) begin
                          item_a_tmp <= 5'd0;
                      end

                      else begin
                          item_a_tmp <= item_a_tmp + 5'd1;
                      end
                  end
              end;




    // xorshiftモジュールから生成される32bitのランダム値
    wire [ 31:0 ]         rand_num_tmp;

    xorshift prng
             (

                 // in
                 .clk( clk ),
                 .gen( gen ),
                 .reset_item( reset_item ),

                 // out
                 .rand_num( rand_num_tmp[ 31:0 ] )

             );


    // xorshiftから生成されたランダム値(rand_num_tmp)の格納先
    // (ハイパーベクトル次元数が1024なら、31回別々に格納する)
    reg [ DIM:0 ]       rand_num;

    always_ff @( posedge clk ) begin

                  if ( ~gen ) begin
                      rand_num <= 0;
                  end

                  // 次元数可変
                  else if ( item_a_tmp == 0 ) begin
                      rand_num[ 31:0 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 1 ) begin
                      rand_num[ 63:32 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 2 ) begin
                      rand_num[ 95:64 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 3 ) begin
                      rand_num[ 127:96 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 4 ) begin
                      rand_num[ 159:128 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 5 ) begin
                      rand_num[ 191:160 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 6 ) begin
                      rand_num[ 223:192 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 7 ) begin
                      rand_num[ 255:224 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 8 ) begin
                      rand_num[ 287:256 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 9 ) begin
                      rand_num[ 319:288 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 10 ) begin
                      rand_num[ 351:320 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 11 ) begin
                      rand_num[ 383:352 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 12 ) begin
                      rand_num[ 415:384 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 13 ) begin
                      rand_num[ 447:416 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 14 ) begin
                      rand_num[ 479:448 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 15 ) begin
                      rand_num[ 511:480 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 16 ) begin
                      rand_num[ 543:512 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 17 ) begin
                      rand_num[ 575:544 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 18 ) begin
                      rand_num[ 607:576 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 19 ) begin
                      rand_num[ 639:608 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 20 ) begin
                      rand_num[ 671:640 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 21 ) begin
                      rand_num[ 703:672 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 22 ) begin
                      rand_num[ 735:704 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 23 ) begin
                      rand_num[ 767:736 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 24 ) begin
                      rand_num[ 799:768 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 25 ) begin
                      rand_num[ 831:800 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 26 ) begin
                      rand_num[ 863:832 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 27 ) begin
                      rand_num[ 895:864 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 28 ) begin
                      rand_num[ 927:896 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 29 ) begin
                      rand_num[ 959:928 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 30 ) begin
                      rand_num[ 991:960 ] <= rand_num_tmp;
                  end

                  else if ( item_a_tmp == 31 ) begin
                      rand_num[ 1023:992 ] <= rand_num_tmp;
                  end

              end;


    // ============================================================================================================================

    assign finish_gen = ( item_a == item_memory_num & update_item) ? 1'b1 : 1'b0;



endmodule


`default_nettype wire
