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
         output logic [DIM:0]   core_result
     );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    (* ram_style = "block" *)
    reg [DIM:0]      item_memory [0:1023];


    reg [DIM:0]     data;
    reg [15:0]      inst;

    always_ff @(posedge clk) begin
                  if (gen & (item_a != item_memory_num) & update_item) begin
                      item_memory[item_a] <= rand_num;
                      data <= 0;
                      inst <= 0;
                      reg_1 <= 0;
                      reg_2 <= 0;
                  end
                  else if (get_v) begin
                      data <= item_memory[get_d[15:0]];
                      inst <= get_d[31:16];
                  end
              end;

    // inst
    // inst[3:0] = permutationの数
    // inst[4] = reg1, reg2を初期化
    // inst[5] = 外から入ってきたデータをPermしたものをreg1に格納
    // inst[6] = reg1とreg2をXorしたものをreg2に格納
    // inst[7] = reg2の値を吐き出す

    // アドレスx, reg1, reg2を初期化命令 (最初は初期化されているからこれいらない)
    // 上の命令を実行中、アドレス0, 外から入ってきたデータを、Permしたものをreg1に格納
    // 上の命令を実行中, アドレスx, reg1とreg2をXorしたものをreg2に格納
    // 上の命令を実行中、アドレス1、 外から入ってきたデータを,Permしたものをreg1に格納

    // 0. reg1, reg2を初期化
    // 1. 外から入ってきたデータをPermしたものをreg1に格納
    // 2. reg1とreg2をXorしたものをreg2に格納
    // 3. 外から入ってきたデータをPermしたものをreg1に格納
    // 4. reg1とreg2をXorしたものをreg2に格納
    // 5. 外から入ってきたデータをPermしたものをreg1に格納
    // 6. reg1とreg2をXorしたものをreg2に格納
    // 7. reg2の値を吐き出す
    // exec

    reg [DIM:0] reg_1;
    reg [DIM:0] reg_2;

    reg [DIM:0] buff;

    always_ff @(posedge clk) begin
                  if (~run) begin
                      reg_1 <= 0;
                      reg_2 <= 0;
                      buff <= 0;
                      store <= 0;
                  end
                  else if (exec) begin
                      if (inst[4]) begin
                          reg_1 <= 0;
                          reg_2 <= 0;
                          buff <= 0;
                          store <= 0;
                      end
                      else if (inst[5]) begin
                          if (inst[3:0] == 4'd0) begin
                              reg1 <= data;
                          end
                          else if (inst[3:0] == 4'd1) begin
                              reg1 <= {data[0:0], data[DIM:1]};
                          end
                          else if (inst[3:0] == 4'd2) begin
                              reg1 <= {data[1:0], data[DIM:2]};
                          end
                          else if (inst[3:0] == 4'd3) begin
                              reg1 <= {data[2:0], data[DIM:3]};
                          end
                          else if (inst[3:0] == 4'd4) begin
                              reg1 <= {data[3:0], data[DIM:4]};
                          end
                          else if (inst[3:0] == 4'd5) begin
                              reg1 <= {data[4:0], data[DIM:5]};
                          end
                          else if (inst[3:0] == 4'd6) begin
                              reg1 <= {data[5:0], data[DIM:6]};
                          end
                          else if (inst[3:0] == 4'd7) begin
                              reg1 <= {data[6:0], data[DIM:7]};
                          end
                          else if (inst[3:0] == 4'd8) begin
                              reg1 <= {data[7:0], data[DIM:8]};
                          end
                          else if (inst[3:0] == 4'd9) begin
                              reg1 <= {data[8:0], data[DIM:9]};
                          end
                          else if (inst[3:0] == 4'd10) begin
                              reg1 <= {data[9:0], data[DIM:10]};
                          end
                          buff <= 0;
                          store <= 0;
                      end
                      else if (inst[6]) begin
                          reg_2 <= reg_1 ^ reg_2;
                          buff <= 0;
                          store <= 0;
                      end
                      else if (inst[7]) begin
                          buff <= reg_2;
                          store <= 1;
                      end
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
