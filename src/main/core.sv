
`default_nettype none


module core
    #(
         parameter DIM = 1023
     )
     (
         input wire                     clk,
         input wire                     run,
         input wire                     gen,
         input wire                     update_item,
         input wire [ 9:0]               item_a,
         input wire [ DIM:0]             rand_num,
         input wire                     get_v,
         // アドレス幅可変
         //  input wire [31:0]              get_d,
         input wire [ 15:0]              get_d,
         input wire                     exec,
         input wire                     wb_en,
         input wire [ DIM:0]             wb_data,

         output reg                     store,
         output logic [ DIM:0]           core_result,
         output reg                     last
     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    (* ram_style = "block" *)
    reg [ DIM:0]      item_memory [ 0:1023 ];


    reg             wb_ok;

    always_ff @(posedge clk) begin
                  if (wb) begin
                      wb_ok <= 1;
                  end
                  else if (wb_en) begin
                      wb_ok <= 0;
                  end
              end

              reg [ 9:0]       addr;
    reg [ DIM:0]     reg_0;
    // 16bit保持
    reg [ 15:0]      inst;

    always_ff @( posedge clk ) begin
                  if ( gen & update_item ) begin
                      item_memory[ item_a] <= rand_num;
                      addr <= 0;
                      reg_0 <= 0;
                      inst <= 0;
                  end
                  else if ( wb_ok & wb_en) begin
                      item_memory[ wb_addr] <= wb_data;
                  end
                  else if ( get_v ) begin
                      // アドレスが必要か否か
                      if ( get_d[ 15 ] ) begin
                          addr <= get_d[ 9:0 ];
                          reg_0 <= item_memory[ get_d[ 9:0 ] ];
                          inst <= get_d[ 15:0 ];
                      end
                      else begin
                          inst <= get_d[ 15:0 ];
                      end
                  end
                  // これのおかげで、Gtktermで見た時のデータ→命令の並びができて嬉しい
                  else begin
                      // reg_0は保持しなくていい
                      addr <= 0;
                      reg_0 <= 0;
                      inst <= 0;
                  end
              end;


    // N-gram流れ
    // 0. reg1, reg2を初期化
    // 1. 外から入ってきたデータをPermしたものをreg1に格納
    // 2. reg1とreg2をXorしたものをreg2に格納
    // 3. 外から入ってきたデータをPermしたものをreg1に格納
    // 4. reg1とreg2をXorしたものをreg2に格納
    // 5. 外から入ってきたデータをPermしたものをreg1に格納
    // 6. reg1とreg2をXorしたものをreg2に格納
    // 7. reg2の値を吐き出す
    // exec

    // 1. ロードデータをreg2に格納 (reg0 → reg2) load

    // 2. ロードデータをPermしたものをreg2に格納 (reg0 → Perm → reg2) l.rshift
    // 3. reg2をPermしたものをreg2に格納 (reg2 → Perm → reg2) rshift

    // 4. ロードデータをPermしたものをreg2に格納 (reg0 → Perm → reg2) l.lshift
    // 5. reg2をPermしたものをreg2に格納 (reg2 → Perm → reg2) lshift

    // 6. ロードデータとreg2をXorしたものをreg2に格納（reg0 Xor reg2 → reg2）l.xor
    // 7. reg1とreg2をXorしたものをreg2に格納（reg1 Xor reg2 → reg2) xor

    // 8. reg2の値を吐き出す store
    // 9. ラストストア lastore

    // 10. reg2 → reg1 move
    // 11. sign_bit → item_memory



    reg [ DIM:0] reg_1;
    reg [ DIM:0] reg_2;

    reg [ DIM:0] buff;
    reg [ 9:0]   wb_addr;
    reg            wb;

    // reg_1, reg_2は値を保持しておく必要がある（reg_0はその度にロードされるから保持しなくていい）
    always_ff @( posedge clk ) begin
                  if ( ~run ) begin
                      reg_1 <= 0;
                      reg_2 <= 0;
                      wb <= 0;
                      wb_addr <= 0;
                      buff <= 0;
                      store <= 0;
                      last <= 0;
                  end
                  else if ( exec ) begin
                      // アドレス必要
                      if ( inst[ 15 ] ) begin
                          // load
                          if ( inst[ 14 ] ) begin
                              reg_2 <= reg_0;
                              buff <= 0;
                              store <= 0;
                          end
                          // l.rshift
                          else if ( inst[ 13 ] ) begin
                              reg_2 <= { reg_0[ 0 ], reg_0[ DIM:1 ] };
                              buff <= 0;
                              store <= 0;
                          end
                          // l.lshift
                          else if ( inst[ 12 ] ) begin
                              reg_2 <= { reg_0[ DIM-1:0 ], reg_0[ DIM ] };
                              buff <= 0;
                              store <= 0;
                          end
                          // l.xor
                          else if ( inst[ 11 ] ) begin
                              reg_2 <= reg_0 ^ reg_2;
                              buff <= 0;
                              store <= 0;
                          end
                          // wb
                          else if ( inst[ 10 ] ) begin
                              // wb
                              wb <= 1;
                              wb_addr <= addr;
                              buff <= 0;
                              store <= 0;
                              // last
                              last <= 1;
                          end
                      end
                      // アドレスいらん
                      else begin
                          // rshift
                          if ( inst[ 14 ] ) begin
                              reg_2 <= { reg_2[ 0 ], reg_2[ DIM:1 ] };
                              buff <= 0;
                              store <= 0;
                          end
                          // lshift
                          else if ( inst[ 13 ] ) begin
                              reg_2 <= { reg_2[ DIM-1:0 ], reg_2[ DIM ] };
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
                          // lastore
                          else if ( inst[ 10 ] ) begin
                              buff <= reg_2;
                              store <= 1;
                              last <= 1;
                          end
                          // move
                          else if ( inst[ 9 ] ) begin
                              reg_1 <= reg_2;
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
                  // ラストビットが立ってたら落とす→counterのstore_nnが綺麗に動く
                  // lastが立つ前にget_vとexecが落ちてるはず(そういう設計じゃないとおかしい, ラストの命令は最後に使わないとエラー)
                  else if ( last ) begin
                      wb <= 0;
                      buff <= 0;
                      store <= 0;
                      last <= 0;
                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    logic            wb_active;
    always_comb begin
                    wb_active = 0;

                    if ( wb ) begin
                        wb_active = 1'b1;
                    end
                    else if ( wb_active ) begin
                        wb_active = 1'b1;
                    end
                end;


    always_comb begin
                    core_result = 0;

                    if ( store ) begin
                        core_result = buff;
                    end
                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
