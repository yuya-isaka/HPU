`default_nettype none

module counter
    #(
         parameter W = 32
     )
     (
         // in
         input wire			    clk,
         input wire             rst,
         input wire             tmp_addr_i,
         input wire             tmp_rand_bit,
         input wire 		    result_bit_1,
         input wire 		    result_bit_2,
         input wire             update,
         input wire             last_update,

         // out
         output logic 		    sign_bit
     );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 分散RAM (符号付き)
    // warning出る
    (* ram_style = "block" *)
    reg signed [W-1:0]      box;


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
                  end
                  else if (update) begin
                      // 多数決対象が奇数の時（addr_iは偶数）　&& 最後の更新
                      if (~tmp_addr_i & last_update) begin
                          box <= box + bit_1;
                      end
                      else begin
                          box <= box + bit_1 + bit_2;
                      end
                  end
              end;


    //================================================================


    // 1bitにするとbox+bit_1+bit_2で勝手に1bitとして符号拡張されて必ず-1される (教訓も込めて2bitで実装、暗黙の符号拡張に任せる)
    logic signed [1:0]        bit_1;
    always_comb begin
                    // -1
                    bit_1 = $signed(1'b1);

                    if (result_bit_1 == 1'b0) begin
                        // 1
                        bit_1 = $signed(1);
                    end
                end;

    logic signed [1:0]        bit_2;
    always_comb begin
                    // -1
                    bit_2 = $signed(1'b1);

                    if (result_bit_2 == 1'b0) begin
                        // 1
                        bit_2 = $signed(1);
                    end
                end;


    // 符号ビット
    assign sign_bit = box[W-1];


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
