
`default_nettype none


module selector
    (

        // in
        input wire                              clk,
        input wire 				                store_bit,
        input wire 						        core_result_bit,


        // out
        // 1bitにするとbox+bit_1+bit_2で勝手に1bitとして符号拡張されて必ず-1される (教訓も込めて2bitで実装、暗黙の符号拡張に任せる)
        output reg signed [ 1:0 ] 		        sel_bit

    );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // sel_bit制御
    always_ff @( posedge clk ) begin

                  // ストアする場合
                  if ( store_bit ) begin

                      // 0の時は +1 (MSBを0に近づける)
                      if ( core_result_bit == 1'b0 ) begin

                          // 1
                          sel_bit <= $signed( 1 );

                      end

                      // 1の時は -1 (MSBを1に近づける)
                      else begin

                          // -1
                          sel_bit <= $signed( 1'b1 );

                      end

                  end

                  // ストアせん場合
                  else begin

                      // +0 で何もしないのと同じ
                      sel_bit <= 0;

                  end

              end;


endmodule


`default_nettype wire
