
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
    reg [ DIM:0 ]      item_memory [ 0:1023 ];

    // 書き戻し命令が発行されたか否かのフラグ
    reg                 wb_flag;
    // 書き戻し先のアドレス
    reg [ 9:0 ]         wb_addr;
    // ロードデータ
    reg [ DIM:0 ]       reg_0;
    // 命令
    reg [ 15:0 ]        inst;

    // 更新対象
    //  - item_memory
    //  - wb_flag
    //  - wb_addr
    //  - reg_0
    //  - inst
    always_ff @( posedge clk ) begin
                  // ランダム生成 | 書き戻し（命令12)
                  if ( ( gen & update_item) |  wb_flag  ) begin
                      // ランダム生成(gen)
                      if ( gen & update_item) begin
                          item_memory[ item_a ] <= rand_num;
                      end
                      // 書き戻し(命令12)
                      else begin
                          item_memory[ wb_addr ] <= reg_2;
                          // 書き戻し完了後にフラグを落とす
                          // ただし, wb→wbと命令が並んでいた場合を考慮
                          if ( ~( get_v & get_d[ 15 ] & get_d[ 10 ] ) ) begin
                              wb_flag <= 0;
                          end
                      end
                  end

                  // データを受信している時実行
                  if ( get_v ) begin
                      // アドレス必要
                      if ( get_d[ 15 ] ) begin
                          // 12. wb.item (特殊命令)
                          if ( get_d[ 10 ] ) begin
                              // 書き込みフラグを立てる
                              wb_flag <= 1'b1;
                              // 書き込み先アドレス格納
                              wb_addr <= get_d[ 9:0 ];
                              // データはロードされない, 命令は発行しない
                              reg_0 <= 0;
                              inst <= 0;
                          end
                          else begin
                              // フォワーディング処理 (wb直後のload関連の命令に対応)
                              if ( wb_flag ) begin
                                  reg_0 <= reg_2;
                              end
                              // ロード関連の命令に必要なロード
                              else begin
                                  reg_0 <= item_memory[ get_d[ 9:0 ] ];
                              end
                              inst <= get_d[ 15:0 ];
                          end
                      end
                      // アドレスいらん場合は、命令だけを更新
                      else begin
                          reg_0 <= 0;
                          inst <= get_d[ 15:0 ];
                      end
                  end
                  // データを受信していないとき実行
                  else begin
                      // reg_0とinstは保持しなくていい (たとえ、reg_0を更新した後にget_vが落ちても、execはまだ続いているので、次サイクルで使われる)
                      // wb_flagはwb_flagがたった次に必ず落ちる
                      // wb_addrは更新せず放置で良い
                      reg_0 <= 0;
                      inst <= 0;
                  end
              end;


    // reg_1, reg_2は値を保持しておく必要がある （reg_0はその度にロードされるから保持しなくていい）
    reg [ DIM:0 ]       reg_1;
    reg [ DIM:0 ]       reg_2;
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
                          // 1. load
                          if ( inst[ 14 ] ) begin
                              reg_2 <= reg_0;
                              buff <= 0;
                              store <= 0;
                          end
                          // 2. l.rshift
                          else if ( inst[ 13 ] ) begin
                              reg_2 <= { reg_0[ 0 ], reg_0[ DIM:1 ] };
                              buff <= 0;
                              store <= 0;
                          end
                          // 4. l.lshift
                          else if ( inst[ 12 ] ) begin
                              reg_2 <= { reg_0[ DIM-1:0 ], reg_0[ DIM ] };
                              buff <= 0;
                              store <= 0;
                          end
                          // 6. l.xor
                          else if ( inst[ 11 ] ) begin
                              reg_2 <= reg_0 ^ reg_2;
                              buff <= 0;
                              store <= 0;
                          end
                      end
                      // アドレスいらん
                      else begin
                          // 3. rshift
                          if ( inst[ 14 ] ) begin
                              reg_2 <= { reg_2[ 0 ], reg_2[ DIM:1 ] };
                              buff <= 0;
                              store <= 0;
                          end
                          // 5. lshift
                          else if ( inst[ 13 ] ) begin
                              reg_2 <= { reg_2[ DIM-1:0 ], reg_2[ DIM ] };
                              buff <= 0;
                              store <= 0;
                          end
                          // 7. xor
                          else if ( inst[ 12 ] ) begin
                              reg_2 <= reg_1 ^ reg_2;
                              buff <= 0;
                              store <= 0;
                          end
                          // 8. store
                          else if ( inst[ 11 ] ) begin
                              buff <= reg_2;
                              store <= 1;
                          end
                          // 9. last
                          else if ( inst[ 10 ] ) begin
                              last <= 1;
                              buff <= 0;
                              store <= 0;
                          end
                          // 10. move
                          else if ( inst[ 9 ] ) begin
                              reg_1 <= reg_2;
                              buff <= 0;
                              store <= 0;
                          end
                          // 11. wb
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
