`default_nettype none

module dst_buf
    (
        input wire              clk,
        input wire              stream_v,
        input wire [4:0]        stream_a,
        input wire [31:0]       result,
        input wire              s_fin,
        input wire last_j,

        output logic [63:0]     stream_d // M_AXIS_TDATA
    );

    reg [63:0]        stream_0;

    // steram_aの最上位ビットで、今計算していない方（送り出す方）がどちらかを判断
    always_comb begin
                    stream_d = stream_0;
                end;

    // いやそもそもdualportメモリやからそれはないか
    // これは分散RAM
    // そもそもあれかな、フリップフロップでええやんってなってる？
    (* ram_style = "block" *)                          reg [63:0]        buff0; // アドレス偶数
    // reg [31:0]        buff0 [0:31]; // アドレス偶数
    // reg [31:0]        buff1 [0:31]; // アドレス奇数

    // out_addrの最下位ビットを見て、偶数か奇数か判断

    wire [63:0]      sign_bit_1;

    // ここが次元数で可変になる
    generate
        genvar i;
        for (i = 0; i < 32; i = i + 1) begin
            counter counter
                    (
                        .clk(clk),
                        .result_bit(result[i]),
                        .s_fin(s_fin),
                        .last_j(last_j),
                        .sign_bit(sign_bit_1[i])
                    );
        end
    endgenerate


    always_ff @(posedge clk) begin
                  if (s_fin) begin
                      buff0 <= sign_bit_1;
                  end
                  // s_fin_inでpが変わってるからこれでいける
                  else if (stream_v) begin
                      stream_0 <= buff0;
                  end
              end;


endmodule

`default_nettype wire
