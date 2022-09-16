module mat_ctrl
    (
        input wire clk,
        input wire rst,
        input wire matw,
        input wire src_valid,

        output wire [3:0] mat_v, // コアの選択
        output reg [2:0]  mat_a // アドレス
    );

    // 一回最初送って終わりだからsrc_readyはあまりつかわない？
    // matwを１にして送って０にしてリセット
    // またmatwを１にしたら新しくセットできる？（その場合はsrc_readyの考慮が必要？）　src_readyをどう設定するべきなのかがいまいちわかっていない

    reg [1:0]         core_sel;

    assign mat_v = (src_valid & matw) ? 1<<(core_sel) : 4'h0;

    always_ff @(posedge clk)begin
                  if(rst|~matw)begin
                      core_sel <= 2'h0;
                      mat_a <= 3'h0;
                  end
                  else if(src_valid)begin
                      mat_a <= mat_a + 1;
                      if(mat_a == 3'h7)begin
                          core_sel <= core_sel + 1;
                      end
                  end
              end;

endmodule
