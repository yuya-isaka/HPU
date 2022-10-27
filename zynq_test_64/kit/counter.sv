
`default_nettype none


module counter
    #(
         // addr_iが10億以上になったら増やす必要あり
         parameter W = 30
     )
     (
         // in
         input wire			            clk,
         input wire                     rst,
         input wire                     tmp_even,
         input wire                     tmp_rand_bit,
         // コア数可変
         // 16コア
         //  input wire [15:0]              store,
         // 4コア
         //  input wire [3:0]               store,
         // 2コア
         input wire [1:0]               store,
         // コア数可変
         // 16コア
         //  input wire [15:0]              core_result,
         // 4コア
         //  input wire [3:0]               core_result,
         // 2コア
         input wire [1:0]               core_result,

         // out
         output logic 		            sign_bit
     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // コア数可変
    // 32コア
    // reg         store_n, store_nn, store_nnn;
    // always_ff @(posedge clk) begin
    //               store_n <= store;
    //               store_nn <= store_n;
    //               store_nnn <= store_nn;
    //           end;

    // コア数可変
    // 16コア
    reg         store_n, store_nn;
    always_ff @(posedge clk) begin
                  store_n <= store;
                  store_nn <= store_n;
              end;

    // コア数可変
    // 4コア
    // reg         store_n;
    // always_ff @(posedge clk) begin
    //               store_n <= store;
    //           end;


    // 分散RAM (符号付き)
    // (* ram_style = "block" *)
    reg signed [W-1:0]      box;

    // コア数可変
    // reg signed [W-1:0]      box_11;
    // reg signed [W-1:0]      box_22;

    // コア数可変
    reg signed [W-1:0]      box_1;
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
                      box_1 <= 0;
                      //   box_2 <= 0;
                      //   box_3 <= 0;
                      //   box_4 <= 0;
                      //   box_5 <= 0;
                      //   box_6 <= 0;
                      //   box_7 <= 0;
                      //   box_8 <= 0;
                  end

                  else if (store_n) begin
                      // コア数可変
                      // 2コア
                      box_1 <= select[0]
                            + select[1];
                      // 16コア
                      //   box_1 <= select[0]
                      //         + select[1]
                      //         + select[2]
                      //         + select[3];
                      //   box_2 <= select[4]
                      //         + select[5]
                      //         + select[6]
                      //         + select[7];
                      //   box_3 <= select[8]
                      //         + select[9]
                      //         + select[10]
                      //         + select[11];
                      //   box_4 <=
                      //         select[12]
                      //         + select[13]
                      //         + select[14]
                      //         + select[15];
                  end

                  else if (store_nn) begin
                      // コア数可変
                      // 16コア
                      //   box <= box + box_1 + box_2 + box_3 + box_4;
                      // 4コア
                      //   box <= box + select[0] + select[1] + select[2] + select[3];
                      // 2コア
                      box <= box + box_1;
                  end
              end;


    //================================================================


    // コア数可変
    // 16コア
    // wire signed [1:0]      select [0:15];
    // 4コア
    // wire signed [1:0]      select [0:3];
    // 2コア
    wire signed [1:0]      select [0:1];

    generate
        genvar      k;
        // コア数可変
        // 16コア
        // for (k = 0; k < 16; k = k + 1) begin
        // 4コア
        // for (k = 0; k < 4; k = k + 1) begin
        // 2コア
        for (k = 0; k < 2; k = k + 1) begin
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