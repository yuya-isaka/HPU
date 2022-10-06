`default_nettype none

module buffer
    (
        // in
        input wire              clk,
        input wire              rst,
        input wire              stream_v,
        input wire [7:0]        stream_a,
        input wire [31:0]       result,
        input wire              get_fin,
        input wire              update,

        // out
        output logic [63:0]     stream_d
    );

    wire [63:0]      sign_bit;

    // 次元数で可変になる、要改良
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

    reg [63:0]      encoded_hv;

    always_ff @(posedge clk) begin
                  if (get_fin) begin
                      encoded_hv <= sign_bit;
                  end
                  else if (stream_v) begin
                      stream_d <= encoded_hv;
                  end
              end;

endmodule

`default_nettype wire
