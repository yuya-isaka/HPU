`default_nettype none

module counter
    #(
         parameter W = 32
     )
     (
         // in
         input wire			clk,
         input wire         rst,
         input wire 		result_bit,
         input wire         update,

         // out
         output logic 		sign_bit
     );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 分散RAM (符号付き)
    // warning出る
    (* ram_style = "block" *)
    reg signed [W-1:0]      box;

    // $signed(1'b1)にするとバグる
    always_ff @(posedge clk) begin
                  if (rst) begin
                      box <= 0;
                  end
                  else if(update) begin
                      if (result_bit == 1'b0) begin
                          box <= box + $signed(1);
                      end
                      else begin
                          box <= box - $signed(1);
                      end
                  end
              end;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 符号ビット
    assign sign_bit = box[W-1];


endmodule

`default_nettype wire
