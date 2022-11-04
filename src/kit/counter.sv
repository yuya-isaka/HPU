
`default_nettype none


module counter
    #(
         // addr_iが10億以上になったら増やす必要あり
         parameter W = 30,
         parameter CORENUM = 16
     )
     (
         // in
         input wire			            clk,
         input wire                     rst,
         input wire                     tmp_even,
         input wire                     tmp_rand_bit,
         // コア数可変
         input wire [CORENUM-1:0]              store,
         // 1コア
         //  input wire                store,
         // コア数可変
         input wire [CORENUM-1:0]              core_result,
         // 1コア
         //  input wire                core_result,

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
                      box_1 <= select[0] + select[1];
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
                      // 1コア
                      box <= box + box_1;
                  end
              end;


    //================================================================


    // コア数可変
    wire signed [1:0]      select [0:CORENUM-1];
    // 1コア
    // wire signed [1:0]      select;

    generate
        genvar      k;
        for (k = 0; k < CORENUM; k = k + 1) begin
            selector selector
                     (
                         // in
                         .clk(clk),
                         // コア数可変
                         .store_bit(store[k]),
                         //  .store_bit(store),
                         // コア数可変
                         .core_result_bit(core_result[k]),
                         //  .core_result_bit(core_result),

                         // out
                         // コア数可変
                         .sel_bit(select[k])
                         //  .sel_bit(select)
                     );
        end
    endgenerate



    // 符号ビット
    assign sign_bit = box[W-1];


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
