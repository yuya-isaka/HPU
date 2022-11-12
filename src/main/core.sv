
`default_nettype none


module core
    #(

         // ハイパーベクトルの次元数
         parameter DIM = 1023

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
    reg [ DIM:0 ]           item_memory [ 0:1023 ];

    // アイテムメモリーからロードしたデータの格納場所
    reg [ DIM:0 ]           reg_tmp;

    // フォワーディング処理フラグ
    reg                     forward_flag;


    // 更新対象
    //  - item_memory
    //  - reg_tmp
    //  - forward_flag

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
                  reg_tmp <= item_memory[ get_d[ 9:0 ] ];

                  // フォワーディングフラグ
                  forward_flag <= ( wb_flag & ( wb_addr == get_d[ 9:0 ] ) );

              end;



    // 命令で使われるロードデータ
    logic [ DIM:0 ]         reg_0;

    // reg_tmpを使うかreg_2の値を使うか
    // reg2の保持しておきつつ続けてreg2を使って更新したいとき、write_back命令を直前に発行
    // (たぶん意外に便利に使える。write_backしたあとreg0にロードしてそのままreg2の値と計算するとかもできる)
    always_comb begin
                    // 通常はアイテムメモリーからロードした値を格納
                    reg_0 = reg_tmp;

                    // フォワーディングフラグが立っている場合、reg_2の値をフォワーディング
                    if ( forward_flag ) begin
                        reg_0 = reg_2;
                    end
                end;



    // 書き戻し命令が発行されたか否かのフラグ
    reg                 wb_flag;

    // 書き戻し先のアドレス
    reg [ 9:0 ]         wb_addr;

    // 命令
    reg [ 15:0 ]        inst;


    // 更新対象
    //  - inst
    //  - wb_flag
    //  - wb_addr
    always_ff @( posedge clk ) begin

                  // データ受信時実行
                  if ( get_v ) begin

                      // wb.item命令 (特殊)
                      if ( get_d[ 15 ] & get_d[ 13 ] ) begin
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
                  end

                  // データを受信していないとき実行
                  // (リセットも兼ねる)
                  else begin
                      // instは保持しなくていい
                      // (たとえ、instを更新した後にget_vが落ちても、execはまだ続いているので、次サイクルで使われる)
                      inst <= 0;
                      wb_flag <= 0;
                      wb_addr <= 0;
                  end
              end;



    // reg_1, reg_2は値を保持しておく必要がある （reg_0はその度にロードされるから保持しなくていい）

    // レジスタ1
    reg [ DIM:0 ]       reg_1;

    // レジスタ2
    reg [ DIM:0 ]       reg_2;

    // storeする値を蓄える変数
    reg [ DIM:0 ]       buff;

    // 更新対象
    //  - reg_1
    //  - reg_2
    //  - buff
    //  - store (port)
    //  - last  (port)
    always_ff @( posedge clk ) begin

                  // アクセラレータの動作終了と同時にリセット
                  // reg_1　reg_2 は保持したいため、リセット時にしか0に戻さない
                  if ( ~run ) begin
                      reg_1 <= 0;
                      reg_2 <= 0;
                      buff <= 0;
                      store <= 0;
                      last <= 0;
                  end

                  // アクセラレータ動作中実行
                  else if ( exec ) begin

                      // アドレス必要
                      if ( inst[ 15 ] ) begin

                          // load
                          if ( inst[ 14 ] ) begin
                              reg_2 <= reg_0;
                              buff <= 0;
                              store <= 0;
                          end

                      end

                      // アドレスいらん
                      else begin

                          // rshift
                          if ( inst[ 14 ] ) begin

                              // 1
                              if ( inst[ 12 ] ) begin
                                  reg_2 <= { reg_2[ 0 ], reg_2[ DIM:1 ] };
                              end

                              // 2
                              else if ( inst[ 11 ] ) begin
                                  reg_2 <= { reg_2[ 1:0 ], reg_2[ DIM:2 ] };
                              end

                              // 4
                              else if ( inst[ 10 ] ) begin
                                  reg_2 <= { reg_2[ 3:0 ], reg_2[ DIM:4 ] };
                              end

                              // 8
                              else if ( inst[ 9 ] ) begin
                                  reg_2 <= { reg_2[ 7:0 ], reg_2[ DIM:8 ] };
                              end

                              // 16
                              else if ( inst[ 8 ] ) begin
                                  reg_2 <= { reg_2[ 15:0 ], reg_2[ DIM:16 ] };
                              end

                              // 32
                              else if ( inst[ 7 ] ) begin
                                  reg_2 <= { reg_2[ 31:0 ], reg_2[ DIM:32 ] };
                              end

                              // 64
                              else if ( inst[ 6 ] ) begin
                                  reg_2 <= { reg_2[ 63:0 ], reg_2[ DIM:64 ] };
                              end

                              // 128
                              else if ( inst[ 5 ] ) begin
                                  reg_2 <= { reg_2[ 127:0 ], reg_2[ DIM:128 ] };
                              end

                              // 256
                              else if ( inst[ 4 ] ) begin
                                  reg_2 <= { reg_2[ 255:0 ], reg_2[ DIM:256 ] };
                              end

                              // 512
                              else if ( inst[ 3 ] ) begin
                                  reg_2 <= { reg_2[ 511:0 ], reg_2[ DIM:512 ] };
                              end

                              buff <= 0;
                              store <= 0;
                          end

                          // lshift
                          else if ( inst [ 13 ] ) begin

                              // 1
                              if ( inst[ 12 ] ) begin
                                  reg_2 <= { reg_2[ DIM-1:0 ], reg_2[ DIM ] };
                              end

                              // 2
                              else if ( inst[ 11 ] ) begin
                                  reg_2 <= { reg_2[ DIM-2:0 ], reg_2[ DIM:DIM-1 ] };
                              end

                              // 4
                              else if ( inst[ 10 ] ) begin
                                  reg_2 <= { reg_2[ DIM-4:0 ], reg_2[ DIM:DIM-3 ] };
                              end

                              // 8
                              else if ( inst[ 9 ] ) begin
                                  reg_2 <= { reg_2[ DIM-8:0 ], reg_2[ DIM:DIM-7 ] };
                              end

                              // 16
                              else if ( inst[ 8 ] ) begin
                                  reg_2 <= { reg_2[ DIM-16:0 ], reg_2[ DIM:DIM-15 ] };
                              end

                              // 32
                              else if ( inst[ 7 ] ) begin
                                  reg_2 <= { reg_2[ DIM-32:0 ], reg_2[ DIM:DIM-31 ] };
                              end

                              // 64
                              else if ( inst[ 6 ] ) begin
                                  reg_2 <= { reg_2[ DIM-64:0 ], reg_2[ DIM:DIM-63 ] };
                              end

                              // 128
                              else if ( inst[ 5 ] ) begin
                                  reg_2 <= { reg_2[ DIM-128:0 ], reg_2[ DIM:DIM-127 ] };
                              end

                              // 256
                              else if ( inst[ 4 ] ) begin
                                  reg_2 <= { reg_2[ DIM-256:0 ], reg_2[ DIM:DIM-255 ] };
                              end

                              // 512
                              else if ( inst[ 3 ] ) begin
                                  reg_2 <= { reg_2[ DIM-512:0 ], reg_2[ DIM:DIM-511 ] };
                              end

                              buff <= 0;
                              store <= 0;
                          end

                          // xor
                          else if ( inst[ 12 ] ) begin
                              reg_2 <= reg_1 ^ reg_2;
                              buff <= 0;
                              store <= 0;
                          end

                          // store
                          else if ( inst[ 11 ] ) begin
                              buff <= reg_2;
                              store <= 1;
                          end

                          // last
                          else if ( inst[ 10 ] ) begin
                              last <= 1;
                              buff <= 0;
                              store <= 0;
                          end

                          // move
                          else if ( inst[ 9 ] ) begin
                              reg_1 <= reg_2;
                              buff <= 0;
                              store <= 0;
                          end

                          // wb
                          else if ( inst[ 8 ] ) begin
                              reg_2 <= sign_bit;
                              buff <= 0;
                              store <= 0;
                          end

                          // nop (すべて0のはず)
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
