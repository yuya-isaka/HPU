`default_nettype none

module core
    (
        input wire              clk,
        input wire              init, // k_init

        input wire [64:0]       mat_d,

        input wire              exec,
        input wire              out_period,
        input wire              update,
        input wire [31:0]       exec_src_data,
        // input wire [31:0]       acc_next,

        output logic [31:0]     acc
    );

    // 各コアにつき32bitのデータを128個集める
    reg [31:0]        item_memory [0:100];

    integer i;
    integer j = 33215360;
    initial begin
        for (i=0; i < 100; i++) begin
            item_memory[i] = j;
            j = j + 180038;
        end
    end

    reg [31:0]        exec_mat_data;

    reg [31:0]        acc_right, acc_left;

    // updateで一気に8個のコアのaccが更新される
    // 次のサイクルから, 各コアのaccが次のコアのaccで更新されていく

    always_comb begin
                    acc = acc_right;

                    if (update) begin
                        acc = acc_left;
                    end
                end;

    always_ff @(posedge clk)begin
                  if (exec_next) begin // 偶数
                      exec_mat_data <= item_memory[exec_src_data[8:0]];
                  end
              end;

    // initを適切なタイミングで１にする
    reg               init_next, init_next_next;
    always_ff @(posedge clk)begin
                  init_next <= init;
                  init_next_next <= init_next;
              end;

    reg               exec_next, exec_next_next, exec_next_next_next;
    always_ff @(posedge clk)begin
                  exec_next <= exec;
                  exec_next_next <= exec_next;
                  exec_next_next_next <= exec_next_next;
              end;


    // 周波数をあげるためにレジスタを間に挟む (ここがクリティカルパスになるっぽい)
    reg [31:0]        m2;
    always_ff @(posedge clk)begin
                  if(exec_next_next)begin
                      m2 <= exec_mat_data;
                  end
              end;

    reg [2:0]         permutation; // 3-gramを想定
    initial begin
        permutation = 0;
    end
    always_ff @(posedge clk)begin
                  if(init_next_next)begin
                      acc_left <= 32'h0;
                      permutation <= 0;
                  end
                  else if(exec_next_next_next)begin
                      permutation <= permutation + 1;
                      // クリティカルパスになりそう（なるなら分けてもいい）
                        // acc_left <= acc_left ^ (m2 >> m2 | ( ( m2 & ((1'b1 << m2) - 1'b1) ) << (32 - m2) ) );
                      acc_left <= acc_left ^ (m2 >> permutation | ( ( m2 & ((1'b1 << permutation) - 1'b1) ) << (32 - permutation) ) );
                  end
              end;

    always_ff @(posedge clk) begin
                  if(out_period)begin
                      //   acc_right <= acc_next;
                      acc_right <= acc_left;
                  end
              end;

endmodule

`default_nettype wire
