`default_nettype none

module buffer_ctrl
    (
        // in
        input wire              clk,
        input wire              rst,
        input wire [31:0]       result,
        input wire              update,
        input wire              get_fin,
        input wire              stream_v,
        input wire [7:0]        stream_a,

        // out
        output logic [63:0]     stream_d
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 次元数で可変になる、要改良
    wire [63:0]      sign_bit;

    generate
        genvar i;
        for (i = 0; i < 32; i = i + 1) begin
            counter counter
                    (
                        // in
                        .clk(clk),
                        .rst(rst),
                        .result_bit(result[i]),
                        .update(update),

                        // out
                        .sign_bit(sign_bit[i])
                    );
        end
    endgenerate


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg [63:0]      encoded_hv;
    always_ff @(posedge clk) begin
                  if (get_fin) begin
                      encoded_hv <= sign_bit;
                  end
              end;


    // stream_d
    always_ff @(posedge clk) begin
                  if (stream_v) begin
                      stream_d <= encoded_hv;
                  end
              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
