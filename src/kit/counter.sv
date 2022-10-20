`default_nettype none

module counter
    #(
         // addr_iが100万以上になったら増やす必要あり
         //  parameter W = 20
         parameter W = 30
     )
     (
         // in
         input wire			        clk,
         input wire                 rst,
         input wire                 tmp_even,
         input wire                 tmp_rand_bit,
         // コア数可変
         //  input wire [31:0]          store,
         input wire [3:0]           store,
         // コア数可変
         //  input wire [31:0]          core_result,
         input wire [3:0]           core_result,

         // out
         output logic 		        sign_bit
     );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // コア数可変
    // reg         update_n, update_nn, update_nnn;
    // always_ff @(posedge clk) begin
    //               update_n <= update;
    //               update_nn <= update_n;
    //               update_nnn <= update_nn;
    //           end;

    // コア数可変
    reg         store_n;
    always_ff @(posedge clk) begin
                  store_n <= store;
              end;


    // 分散RAM (符号付き)
    // warning出る
    (* ram_style = "block" *)
    reg signed [W-1:0]      box;

    // コア数可変
    // reg signed [W-1:0]      box_11;
    // reg signed [W-1:0]      box_22;

    // コア数可変
    // reg signed [W-1:0]      box_1;
    // reg signed [W-1:0]      box_2;
    // reg signed [W-1:0]      box_3;
    // reg signed [W-1:0]      box_4;
    // reg signed [W-1:0]      box_5;
    // reg signed [W-1:0]      box_6;
    // reg signed [W-1:0]      box_7;
    // reg signed [W-1:0]      box_8;

    // run == 1 にする前に設定する必要性あり
    // $signed(1'b1)にするとバグる
    always_ff @(posedge clk) begin
                  if (rst) begin
                      // 偶数なら一個たす
                      if (tmp_even) begin
                          if (tmp_rand_bit == 1'b0) begin
                              // 1
                              box <= $signed(1);
                          end
                          else begin
                              // -1
                              box <= $signed(1'b1);
                          end
                      end
                      else begin
                          box <= 0;
                      end
                      // コア数可変
                      //   box_1 <= 0;
                      //   box_2 <= 0;
                      //   box_3 <= 0;
                      //   box_4 <= 0;
                      //   box_5 <= 0;
                      //   box_6 <= 0;
                      //   box_7 <= 0;
                      //   box_8 <= 0;
                  end
                  //   else if (update_n) begin
                  //       // コア数可変
                  //       box_1 <= select[0]
                  //             + select[1]
                  //             + select[2]
                  //             + select[3];
                  //       box_2 <= select[4]
                  //             + select[5]
                  //             + select[6]
                  //             + select[7];
                  //       box_3 <= select[8]
                  //             + select[9]
                  //             + select[10]
                  //             + select[11];
                  //       box_4 <=
                  //             select[12]
                  //             + select[13]
                  //             + select[14]
                  //             + select[15];
                  //       box_5 <=
                  //             select[16]
                  //             + select[17]
                  //             + select[18]
                  //             + select[19];
                  //       box_6 <=
                  //             select[20]
                  //             + select[21]
                  //             + select[22]
                  //             + select[23];
                  //       box_7 <=
                  //             select[24]
                  //             + select[25]
                  //             + select[26]
                  //             + select[27];
                  //       box_8 <=
                  //             select[28]
                  //             + select[29]
                  //             + select[30]
                  //             + select[31];
                  //   end
                  //   else if (update_nn) begin
                  //       // コア数可変
                  //       box_11 <= box_1 + box_2 + box_3 + box_4;
                  //       box_22 <= box_5 + box_6 + box_7 + box_8;
                  //   end
                  //   else if (update_nnn) begin
                  else if (store_n) begin
                      // コア数可変
                      //   box <= box + box_11 + box_22;
                      box <= box + select[0] + select[1] + select[2] + select[3];
                  end
              end;


    //================================================================


    // コア数可変
    // wire signed [1:0]      select [0:31];
    wire signed [1:0]      select [0:3];

    generate
        genvar      k;
        // コア数可変
        // for (k = 0; k < 32; k = k + 1) begin
        for (k = 0; k < 4; k = k + 1) begin
            selector selector
                     (
                         // in
                         .clk(clk),
                         .store_bit(store[k]),
                         .core_result_bit(core_result[k]),

                         // out
                         .sel_bit(select[k])
                     );
        end
    endgenerate



    // 符号ビット
    assign sign_bit = box[W-1];


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
