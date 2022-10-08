`default_nettype none

module counter
    #(
         parameter W = 32
     )
     (
         // in
         input wire			        clk,
         input wire                 rst,
         input wire                 tmp_addr_i,
         input wire                 tmp_rand_bit,
         input wire [4:0]           remainder,
         input wire [31:0]          result,
         input wire                 update,
         input wire                 last_update,

         // out
         output logic 		        sign_bit
     );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg         update_n, update_nn;
    always_ff @(posedge clk) begin
                  update_n <= update;
                  update_nn <= update_n;
              end;


    // 分散RAM (符号付き)
    // warning出る
    (* ram_style = "block" *)
    reg signed [W-1:0]      box;

    reg signed [W-1:0]      box_1;
    reg signed [W-1:0]      box_2;
    reg signed [W-1:0]      box_3;
    reg signed [W-1:0]      box_4;

    // run == 1 にする前に設定する必要性あり
    // $signed(1'b1)にするとバグる
    always_ff @(posedge clk) begin
                  if (rst) begin
                      // 多数決対象が偶数の時（addr_iは奇数）
                      if (tmp_addr_i) begin
                          if (tmp_rand_bit == 1'b0) begin
                              // 1
                              box <= $signed(1);
                          end
                          else begin
                              // -1
                              box <= $signed(1'b1);
                          end
                      end
                      // 多数決対象が奇数の時（addr_iは偶数）
                      else begin
                          box <= 0;
                      end
                      box_1 <= 0;
                      box_2 <= 0;
                      box_3 <= 0;
                      box_4 <= 0;
                  end
                  else if (update_n) begin
                      box_1 <= select[0]
                            + select[1]
                            + select[2]
                            + select[3]
                            + select[4]
                            + select[5]
                            + select[6]
                            + select[7];
                      box_2 <= select[8]
                            + select[9]
                            + select[10]
                            + select[11]
                            + select[12]
                            + select[13]
                            + select[14]
                            + select[15];
                      box_3 <=
                            select[16]
                            + select[17]
                            + select[18]
                            + select[19]
                            + select[20]
                            + select[21]
                            + select[22]
                            + select[23];
                      box_4 <=
                            select[24]
                            + select[25]
                            + select[26]
                            + select[27]
                            + select[28]
                            + select[29]
                            + select[30]
                            + select[31];
                  end
                  else if (update_nn) begin
                      box <= box + box_1 + box_2 + box_3 + box_4;
                  end
              end;


    //================================================================


    wire signed [1:0]      select [0:31];

    generate
        genvar      k;
        for (k = 0; k < 32; k = k + 1) begin
            selector selector
                     (
                         // in
                         .clk(clk),
                         .update(update),
                         .last_update(last_update),
                         .remainder(remainder),
                         .result_bit(result[k]),
                         .constant(constant[k]),

                         // out
                         .sel_bit(select[k])
                     );
        end
    endgenerate



    // 符号ビット
    assign sign_bit = box[W-1];



    logic [4:0]         constant[0:31];

    always_comb begin
                    constant[0] = 0;
                    constant[1] = 1;
                    constant[2] = 2;
                    constant[3] = 3;
                    constant[4] = 4;
                    constant[5] = 5;
                    constant[6] = 6;
                    constant[7] = 7;
                    constant[8] = 8;
                    constant[9] = 9;
                    constant[10] = 10;
                    constant[11] = 11;
                    constant[12] = 12;
                    constant[13] = 13;
                    constant[14] = 14;
                    constant[15] = 15;
                    constant[16] = 16;
                    constant[17] = 17;
                    constant[18] = 18;
                    constant[19] = 19;
                    constant[20] = 20;
                    constant[21] = 21;
                    constant[22] = 22;
                    constant[23] = 23;
                    constant[24] = 24;
                    constant[25] = 25;
                    constant[26] = 26;
                    constant[27] = 27;
                    constant[28] = 28;
                    constant[29] = 29;
                    constant[30] = 30;
                    constant[31] = 31;
                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
