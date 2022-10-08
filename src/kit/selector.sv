`default_nettype none

module selector
    (
        // in
        input wire 						last_update,
        input wire 						remainder,
        input wire 						result_bit,
        input wire [4:0]				constant,

        // out
        // 1bitにするとbox+bit_1+bit_2で勝手に1bitとして符号拡張されて必ず-1される (教訓も込めて2bitで実装、暗黙の符号拡張に任せる)
        output logic signed [1:0]		sel_bit
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    always_comb begin
                    // -1
                    sel_bit = $signed(1'b1);

                    if (last_update && 1 <= remainder && remainder < constant) begin
                        sel_bit = 0;
                    end
                    else if (result_bit == 1'b0) begin
                        // 1
                        sel_bit = $signed(1);
                    end
                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
