`default_nettype none

module selector
    (
        // in
        // コア数可変
        input wire                      clk,
        // コア数可変
        input wire                      update,
        input wire 						core_result_bit,
        input wire 				        core_enable_bit,

        // out
        // 1bitにするとbox+bit_1+bit_2で勝手に1bitとして符号拡張されて必ず-1される (教訓も込めて2bitで実装、暗黙の符号拡張に任せる)
        // コア数可変
        // output reg signed [1:0]		sel_bit
        output logic signed [1:0]		sel_bit
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // コア数可変（32コア）
    always_ff @(posedge clk) begin
                  if (update) begin
                      // -1
                      sel_bit <= $signed(1'b1);

                      if (core_enable_bit) begin
                          sel_bit <= 0;
                      end
                      else if (core_result_bit == 1'b0) begin
                          // 1
                          sel_bit <= $signed(1);
                      end
                  end
              end;


    // コア数可変（4コア）
    // always_comb begin
    //                 // -1
    //                 sel_bit = $signed(1'b1);

    //                 if (core_enable_bit) begin
    //                     sel_bit = 0;
    //                 end
    //                 else if (core_result_bit == 1'b0) begin
    //                     // 1
    //                     sel_bit = $signed(1);
    //                 end
    //             end;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
