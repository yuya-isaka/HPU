module exe_ctrl
    (
        input wire        clk,
        input wire        rst,

        input wire        s_init,       // srcの受信が終了した次(最初なら)　or 前の計算が終わった次（次のデータがあるなら）
        input wire        out_busy,
        input wire        out_fin,

        output wire       s_fin,        // outrfの次。dst_buffに演算結果が全て入った時
        output wire       k_init,       // jループの始まりの前 (s_initの次)
        output wire       k_fin,        // jループが終わった次に駆動
        output wire       exec,         // 演算の始まり(jループの始まり)
        output wire [7:0] exec_src_addr,    // src_buffから読み出すアドレス
        output wire [5:0] exec_mat_addr // matrixから読み出すアドレス
    );

    wire                    last_i, last_j;
    wire                    next_i, next_j;
    wire [1:0]                           i;
    wire [5:0]                           j;
    wire         s_init_delay, k_init_next;
    wire                             start;
    wire                      s_fin_period;

    // s_initの次にスタート //////////////////////////////////////////////////
    // s_init_delay
    dff #(.W(1)) d_s_init_delay (.in(s_init), .data(s_init_delay), .clk(clk), .rst(rst), .en(1'b1));
    // k_init (s_initの次に駆動)
    assign k_init = (s_init_delay | k_init_next) & !out_busy;
    //////////////////////////////////////////////////////////////////////

    // k_initの次にスタート ////////////////////////////////////////
    // exec // k_initの次に始まり、last_jまでで終わる
    dff #(.W(1)) d_exec  (.in(k_init|exec&!last_j), .data(exec), .clk(clk), .rst(rst), .en(1'b1));
    // start
    dff #(.W(1)) d_start (.in(k_init), .data(start), .clk(clk), .rst(rst), .en(1'b1));
    ////////////////////////////////////////////////////////////


    // 32bitデータを64回出力
    // ってのを４回する

    // i loop
    agu_next #(.W(2)) l_i (.ini(2'd0), .fin(3), .data(i), .start(s_init), .last(last_i),
                           .clk(clk),  .rst(rst),  .next(next_i),  .en(last_j));

    // j loop
    agu_next #(.W(6)) l_j (.ini(3'd0), .fin(63), .data(j), .start(start), .last(last_j),
                           .clk(clk),  .rst(rst), .next(next_j), .en(1'b1));

    assign exec_src_addr = i*64 + j;
    assign exec_mat_addr = j;

    // last_jの次にスタート /////////////////////////////////////////////////
    // last_j -> next_i と k_fin -> k_init_next　と k_init -> exec と start
    // k_fin
    dff #(.W(1)) d_k_fin (.in(last_j), .data(k_fin), .clk(clk), .rst(rst), .en(1'b1));
    // k_init_next (最初以外のk_initを駆動)
    // そのためにnext_iが必要 (最初じゃないことの判断)
    // next_jで０にする
    dff #(.W(1)) d_k_init_next (.in(next_i&!s_init), .data(k_init_next), .clk(clk),
                                .rst(rst), .en(!out_busy|next_j));
    //////////////////////////////////////////////////////////////////////

    // last_iの次にスタート /////////////////////////////////////////////////
    // last_i -> s_fin_period ... -> s_fin
    // s_fin_period // last_iの次に始まり、outrfまでで終わる
    dff #(.W(1)) d_s_fin_period (.in(last_i), .data(s_fin_period), .clk(clk), .rst(rst), .en(last_i|out_fin));
    // s_fin
    // outrfの次に駆動
    dff #(.W(1)) d_s_fin (.in(s_fin_period&out_fin), .data(s_fin), .clk(clk), .rst(rst), .en(1'b1));

endmodule
