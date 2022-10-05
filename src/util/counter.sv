`default_nettype none

module counter
    #(
         parameter W = 32
     )
     (
         input wire			clk,
         input wire 		result_bit,
         input wire   		s_fin,
         input wire         k_fin,
         output logic 		sign_bit
     );

    // これは分散RAM
    // これがあかんと言われるのはわかる
    // 32bitあれば足りるでしょうと、20億くらい
    (* ram_style = "block" *)                reg signed [W-1:0] box;
    initial begin
        box = 0;
    end

    always_ff @(posedge clk) begin
                  if (s_fin) begin
                      box <= 0;
                  end
                  else if(k_fin) begin
                      if (result_bit == 1'b0) begin
                          box <= box + $signed(1);
                      end
                      else begin
                          box <= box - $signed(1);
                      end
                  end
              end;

    // 出力
    // 分散RAM
    always_comb begin
                    sign_bit = box[W-1];
                end;


endmodule

`default_nettype wire
