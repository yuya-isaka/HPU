
`default_nettype none


module core
    #(

         // ハイパーベクトルの次元数
         parameter DIM = 1023,
         parameter THREADS = 10

     )
     (

         // in
         input wire                         clk,
         input wire                         run,
         input wire                         gen,
         input wire                         update_item,
         input wire [ 9:0 ]                 item_a,
         input wire [ DIM:0 ]               rand_num,
         input wire                         get_v,
         // 16bit命令
         input wire [ 15:0 ]                get_d,
         input wire                         exec,
         input wire [ DIM:0 ]               sign_bit,


         // out
         output reg                         store,
         output logic [ DIM:0 ]             core_result,
         output reg                         last

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // ハイパーベクトルを保持するメモリ
    (* ram_style = "block" *)
    reg [ DIM:0 ]           item_memory [ 0:511 ];

    // アイテムメモリーからロードしたデータの格納場所
    reg [ DIM:0 ]           reg_0;


    always_ff @( posedge clk ) begin

                  // 書き込み
                  // 書き戻し | ランダム生成
                  if ( wb_flag | ( gen & update_item ) ) begin

                      // 書き戻し
                      if ( wb_flag ) begin
                          item_memory[ wb_addr ] <= reg_2;
                      end

                      // ランダム生成
                      else begin
                          item_memory[ item_a ] <= rand_num;
                      end
                  end

                  // 読み出し
                  // 常に垂れ流しで読み出しでOK
                  // (必要ない場合は使わない)
                  reg_0 <= item_memory[ get_d[ 9:0 ] ];
              end;


    // 書き戻し命令が発行されたか否かのフラグ
    reg                 wb_flag;

    // 書き戻し先のアドレス
    reg [ 9:0 ]         wb_addr;

    // 命令
    reg [ 15:0 ]        inst;

    // マルチスレッディング
    reg signed [ 4:0 ]         thread_count;


    always_ff @( posedge clk ) begin

                  // データ受信時実行
                  if ( get_v ) begin

                      // wb.item命令 (特殊)
                      if ( get_d[ 15 ] & get_d[ 12 ] ) begin
                          // 書き込みフラグを立てる
                          wb_flag <= 1'b1;
                          // 書き込み先アドレス格納
                          wb_addr <= get_d[ 9:0 ];

                          // 命令は発行しない (nop)
                          inst <= 0;
                      end

                      // wb.item命令以外はinstを更新
                      else begin
                          inst <= get_d[ 15:0 ];
                          wb_flag <= 0;
                          wb_addr <= 0;
                      end

                      // マルチスレッド（10）
                      // スレッド数可変
                      if ( thread_count == 4'd4 ) begin
                          thread_count <= 0;
                      end
                      else begin
                          thread_count <= thread_count + 4'd1;
                      end
                  end

                  // データを受信していないとき実行
                  // (リセットも兼ねる)
                  else begin
                      // instは保持しなくていい
                      // (たとえ、instを更新した後にget_vが落ちても、execはまだ続いているので、次サイクルで使われる)
                      inst <= 0;
                      wb_flag <= 0;
                      wb_addr <= 0;
                      // 初期値: -1
                      thread_count <= $signed( 1'b1 );
                  end
              end;


    wire [ DIM:0 ] permute_reg_after;

    // 次元数可変
    permute #( .DIM( 31 ) ) permute
            (
                // in
                .clk( clk ),
                .data( reg_2[ DIM:0] ),
                .permute_num( inst[ 9:0] ),

                // out
                .result( permute_reg_after[ DIM:0 ] )
            );


    // reg_1, reg_2は値を保持しておく必要がある （reg_0はその度にロードされるから保持しなくていい）

    // レジスタ1
    logic [ DIM:0] reg_1;
    reg [ DIM:0 ]       reg_1_threads [ THREADS-1:0 ];

    // スレッド数可変
    always_comb begin
                    case ( thread_count)
                        5'd0:
                            reg_1 = reg_1_threads[ 0 ];
                        5'd1:
                            reg_1 = reg_1_threads[ 1 ];
                        5'd2:
                            reg_1 = reg_1_threads[ 2 ];
                        5'd3:
                            reg_1 = reg_1_threads[ 3 ];
                        5'd4:
                            reg_1 = reg_1_threads[ 4 ];
                        // 5'd5:
                        //     reg_1 = reg_1_threads[ 5 ];
                        // 5'd6:
                        //     reg_1 = reg_1_threads[ 6 ];
                        // 5'd7:
                        //     reg_1 = reg_1_threads[ 7 ];
                        // 5'd8:
                        //     reg_1 = reg_1_threads[ 8 ];
                        // 5'd9:
                        //     reg_1 = reg_1_threads[ 9 ];
                        default:
                            reg_1 = 0;
                    endcase
                end;

    // レジスタ2
    logic [ DIM:0] reg_2;
    reg [ DIM:0 ]       reg_2_threads [ THREADS-1:0 ];

    always_comb begin
                    if ( inst[ 14] ) begin
                        reg_2 = permute_reg_after;
                    end
                    else begin
                        case ( thread_count)
                            5'd0:
                                reg_2 = reg_2_threads[ 0 ];
                            5'd1:
                                reg_2 = reg_2_threads[ 1 ];
                            5'd2:
                                reg_2 = reg_2_threads[ 2 ];
                            5'd3:
                                reg_2 = reg_2_threads[ 3 ];
                            5'd4:
                                reg_2 = reg_2_threads[ 4 ];
                            // 5'd5:
                            //     reg_2 = reg_2_threads[ 5 ];
                            // 5'd6:
                            //     reg_2 = reg_2_threads[ 6 ];
                            // 5'd7:
                            //     reg_2 = reg_2_threads[ 7 ];
                            // 5'd8:
                            //     reg_2 = reg_2_threads[ 8 ];
                            // 5'd9:
                            //     reg_2 = reg_2_threads[ 9 ];
                            default:
                                reg_2 = 0;
                        endcase
                    end
                end;

    // storeする値を蓄える変数
    reg [ DIM:0 ]       buff;

    // 更新対象
    //  - reg_1
    //  - reg_2
    //  - buff
    //  - store (port)
    //  - last  (port)
    always_ff @( posedge clk ) begin

                  // スレッド数可変
                  // アクセラレータの動作終了と同時にリセット
                  // reg_1　reg_2 は保持したいため、リセット時にしか0に戻さない
                  if ( ~run ) begin
                      reg_1_threads[ 0] <= 0;
                      reg_1_threads[ 1] <= 0;
                      reg_1_threads[ 2] <= 0;
                      reg_1_threads[ 3] <= 0;
                      reg_1_threads[ 4] <= 0;
                      //   reg_1_threads[ 5] <= 0;
                      //   reg_1_threads[ 6] <= 0;
                      //   reg_1_threads[ 7] <= 0;
                      //   reg_1_threads[ 8] <= 0;
                      //   reg_1_threads[ 9] <= 0;

                      reg_2_threads[ 0] <= 0;
                      reg_2_threads[ 1] <= 0;
                      reg_2_threads[ 2] <= 0;
                      reg_2_threads[ 3] <= 0;
                      reg_2_threads[ 4] <= 0;
                      //   reg_2_threads[ 5] <= 0;
                      //   reg_2_threads[ 6] <= 0;
                      //   reg_2_threads[ 7] <= 0;
                      //   reg_2_threads[ 8] <= 0;
                      //   reg_2_threads[ 9] <= 0;

                      buff <= 0;
                      store <= 0;
                      last <= 0;
                  end

                  // アクセラレータ動作中実行
                  // 187MHzはexec->reg2がボトルネックだった
                  else if ( exec ) begin

                      // アドレス必要
                      if ( inst[ 15 ] ) begin

                          // load
                          if ( inst[ 13 ] ) begin

                              // スレッド数可変
                              case ( thread_count)
                                  5'd0:
                                      reg_2_threads[ 0] <= reg_0;
                                  5'd1:
                                      reg_2_threads[ 1] <= reg_0;
                                  5'd2:
                                      reg_2_threads[ 2] <= reg_0;
                                  5'd3:
                                      reg_2_threads[ 3] <= reg_0;
                                  5'd4:
                                      reg_2_threads[ 4] <= reg_0;
                                  //   5'd5:
                                  //       reg_2_threads[ 5] <= reg_0;
                                  //   5'd6:
                                  //   reg_2_threads[ 6] <= reg_0;
                                  //   5'd7:
                                  //       reg_2_threads[ 7] <= reg_0;
                                  //   5'd8:
                                  //       reg_2_threads[ 8] <= reg_0;
                                  //   5'd9:
                                  //       reg_2_threads[ 9] <= reg_0;
                                  default:
                                      ;
                              endcase
                          end

                          buff <= 0;
                          store <= 0;

                      end

                      // アドレスいらん
                      else begin

                          // xor
                          if ( inst[ 13 ] ) begin
                              // スレッド数可変
                              case ( thread_count)
                                  5'd0:
                                      reg_2_threads[ 0] <= reg_1 ^ reg_2;
                                  5'd1:
                                      reg_2_threads[ 1] <= reg_1 ^ reg_2;
                                  5'd2:
                                      reg_2_threads[ 2] <= reg_1 ^ reg_2;
                                  5'd3:
                                      reg_2_threads[ 3] <= reg_1 ^ reg_2;
                                  5'd4:
                                      reg_2_threads[ 4] <= reg_1 ^ reg_2;
                                  //   5'd5:
                                  //       reg_2_threads[ 5] <= reg_1 ^ reg_2;
                                  //   5'd6:
                                  //   reg_2_threads[ 6] <= reg_1 ^ reg_2;
                                  //   5'd7:
                                  //       reg_2_threads[ 7] <= reg_1 ^ reg_2;
                                  //   5'd8:
                                  //       reg_2_threads[ 8] <= reg_1 ^ reg_2;
                                  //   5'd9:
                                  //       reg_2_threads[ 9] <= reg_1 ^ reg_2;
                                  default:
                                      ;
                              endcase
                              buff <= 0;
                              store <= 0;
                          end

                          // store
                          else if ( inst[ 12 ] ) begin
                              buff <= reg_2;
                              store <= 1;
                          end

                          // move
                          else if ( inst[ 11 ] ) begin
                              // スレッド数可変
                              case ( thread_count)
                                  5'd0:
                                      reg_1_threads[ 0] <= reg_2;
                                  5'd1:
                                      reg_1_threads[ 1] <= reg_2;
                                  5'd2:
                                      reg_1_threads[ 2] <= reg_2;
                                  5'd3:
                                      reg_1_threads[ 3] <= reg_2;
                                  5'd4:
                                      reg_1_threads[ 4] <= reg_2;
                                  //   5'd5:
                                  //       reg_1_threads[ 5] <= reg_2;
                                  //   5'd6:
                                  //   reg_1_threads[ 6] <= reg_2;
                                  //   5'd7:
                                  //       reg_1_threads[ 7] <= reg_2;
                                  //   5'd8:
                                  //       reg_1_threads[ 8] <= reg_2;
                                  //   5'd9:
                                  //       reg_1_threads[ 9] <= reg_2;
                                  default:
                                      ;
                              endcase
                              buff <= 0;
                              store <= 0;
                          end

                          // last
                          else if ( inst[ 10 ] ) begin
                              last <= 1;
                              buff <= 0;
                              store <= 0;
                          end

                          // wb
                          else if ( inst[ 9 ] ) begin
                              // スレッド数可変
                              case ( thread_count)
                                  5'd0:
                                      reg_2_threads[ 0] <= sign_bit;
                                  5'd1:
                                      reg_2_threads[ 1] <= sign_bit;
                                  5'd2:
                                      reg_2_threads[ 2] <= sign_bit;
                                  5'd3:
                                      reg_2_threads[ 3] <= sign_bit;
                                  5'd4:
                                      reg_2_threads[ 4] <= sign_bit;
                                  //   5'd5:
                                  //       reg_2_threads[ 5] <= sign_bit;
                                  //   5'd6:
                                  //   reg_2_threads[ 6] <= sign_bit;
                                  //   5'd7:
                                  //       reg_2_threads[ 7] <= sign_bit;
                                  //   5'd8:
                                  //       reg_2_threads[ 8] <= sign_bit;
                                  //   5'd9:
                                  //       reg_2_threads[ 9] <= sign_bit;
                                  default:
                                      ;
                              endcase
                              buff <= 0;
                              store <= 0;
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
                      last <= 0;
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


endmodule


`default_nettype wire
