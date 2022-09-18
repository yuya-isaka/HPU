`default_nettype none

module mat_ctrl
    (
        input wire clk,             // AXIS_ACLK
        input wire rst,             // ~AXIS_ARESETN
        input wire matw,            // 開始
        input wire src_valid,       // S_AXIS_TVALID

        output wire [7:0] mat_v,    // 8個のコアの選択
        output reg [5:0]  mat_a     // アドレス
    );

    // 一回最初送って終わりだからsrc_readyはあまりつかわない？
    // matwを１にして送って０にしてリセット
    // またmatwを１にしたら新しくセットできる？（その場合はsrc_readyの考慮が必要？）　src_readyをどう設定するべきなのかがいまいちわかっていない

    // 8個を選択
    reg [3:0]         core_sel;

    // コアの選択
    assign mat_v = (src_valid & matw) ? 1<<(core_sel) : 7'h0;

    // koko
    // ここの０とか１とか直したい
    // 32bitが32個ずつ送信されるので、２回ぽんぽんとしたら、コアをシフト
    always_ff @(posedge clk)begin
                  if(rst|~matw)begin
                      core_sel <= 4'h0;
                      mat_a <= 0;
                  end
                  else if(src_valid)begin
                      mat_a <= mat_a + 1;
                      if(mat_a == 63)begin
                          core_sel <= core_sel + 1;
                      end
                  end
              end;

endmodule

`default_nettype wire
