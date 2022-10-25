`default_nettype none


module core
    #(
         parameter DIM = 1023
     )
     (
         input wire              clk,
         input wire              run,
         input wire              gen,
         input wire              update_item,
         input wire [15:0]       item_a,
         input wire [15:0]       item_memory_num,
         input wire [DIM:0]      rand_num,
         input wire              get_v,
         input wire [31:0]       get_d,
         input wire              exec,

         output reg             store,
         output logic [DIM:0]   core_result,
         output reg             last
     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    (* ram_style = "block" *)
    reg [DIM:0]      item_memory [0:1023];


    reg [DIM:0]     reg_0;
    reg [15:0]      inst;

    always_ff @(posedge clk) begin
                  if (gen & (item_a != item_memory_num) & update_item) begin
                      item_memory[item_a] <= rand_num;
                      reg_0 <= 0;
                      inst <= 0;
                  end
                  else if (get_v) begin
                      reg_0 <= item_memory[get_d[15:0]];
                      inst <= get_d[31:16];
                  end
                  //   else begin
                  //       reg_0 <= 0;
                  //       inst <= 0;
                  //   end
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

    //  inst[31:15]の16ビットで指定
    //      a. 2進数
    //      b. 10進数

    // ロード
    //  0. ロードデータをreg2に格納 (reg0 → reg2)
    //      a. 0000000000000001
    //      b. 1

    // Permutation
    //  1. ロードデータを1Permしたものをreg2に格納 (reg0 → Perm → reg2)
    //      a. 0000000000000010
    //      b. 2
    //  2. reg2をPermしたものをreg2に格納 (reg2 → Perm → reg2)
    //      a. 0000000000000100
    //      b. 4

    // Xor
    //  3. ロードデータとreg2をXorしたものをreg2に格納（reg0 Xor reg2 → reg2）
    //      a. 0000000000001000
    //      b. 8
    //  4. reg1とreg2をXorしたものをreg2に格納（reg1 Xor reg2 → reg2）
    //      a. 0000000000010000
    //      b. 16

    // ストア
    //  5. reg2の値を吐き出す
    //      a. 0000000000100000
    //      b. 32

    // Copy
    //  6. reg2 → reg1
    //      a. 0000000001000000
    //      b. 64

    // ラストストア
    //  7. reg2の値を最後に吐き出す
    //      a. 0000000010000000
    //      b. 128



    reg [DIM:0] reg_1;
    reg [DIM:0] reg_2;

    reg [DIM:0] buff;

    always_ff @(posedge clk) begin
                  if (~run) begin
                      reg_1 <= 0;
                      reg_2 <= 0;
                      buff <= 0;
                      store <= 0;
                      last <= 0;
                  end
                  else if (exec & get_v) begin
                      // ロード
                      if (inst[0]) begin
                          reg_2 <= reg_0;
                          buff <= 0;
                          store <= 0;
                      end
                      // Perm
                      else if (inst[1]) begin
                          reg_2 <= {reg_0[0], reg_0[DIM:1]};
                          buff <= 0;
                          store <= 0;
                      end
                      // Perm
                      else if (inst[2]) begin
                          reg_2 <= {reg_2[0], reg_2[DIM:1]};
                          buff <= 0;
                          store <= 0;
                      end
                      // Xor
                      else if (inst[3]) begin
                          reg_2 <= reg_0 ^ reg_2;
                          buff <= 0;
                          store <= 0;
                      end
                      // Xor
                      else if (inst[4]) begin
                          reg_2 <= reg_1 ^ reg_2;
                          buff <= 0;
                          store <= 0;
                      end
                      // ストア
                      else if (inst[5]) begin
                          buff <= reg_2;
                          store <= 1;
                      end
                      // コピー
                      else if (inst[6]) begin
                          reg_1 <= reg_2;
                          buff <= 0;
                          store <= 0;
                      end
                      // ありえない命令 (reg_1とかが不自然に０になったりしたらおかしい), デバッグ用に使える
                    //   else begin
                    //       reg_1 <= 0;
                    //       reg_2 <= 0;
                    //       buff <= 0;
                    //       store <= 0;
                    //   end
                  end
                  else if (exec) begin
                      // ラストストア
                      if (inst[7]) begin
                          buff <= reg_2;
                          store <= 1;
                          last <= 1;
                      end
                  end
                //   else if (last) begin
                //       buff <= 0;
                //       store <= 0;
                //       last <= 0;
                //   end
                  //   else begin
                  //       //   reg_1 <= 0;
                  //       //   reg_2 <= 0;
                  //     //   buff <= 0;
                  //     //   store <= 0;
                  //     //   last <= 0;
                  //   end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    always_comb begin
                    core_result = 0;

                    if (store) begin
                        core_result = buff;
                    end
                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
