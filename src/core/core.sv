`default_nettype none

module core
    (
        input wire        clk,
        input wire        init,

        input wire        mat_v,
        input wire [5:0]  mat_a,
        input wire [64:0] mat_d,

        input wire        exec,
        input wire        out_period,
        input wire        update,
        input wire [6:0]  exec_mat_addr,
        input wire [31:0] exec_src_data,
        input wire [31:0] acc_next,

        output reg [31:0] acc
    );

    // 各コアにつき32bitのデータを128個集める
    reg [31:0]        matrix_even [0:63];
    reg [31:0]        matrix_odd [0:63];

    reg [31:0]        exec_mat_data;

    reg [31:0]        acc_right, acc_left;

    // updateで一気に8個のコアのaccが更新される
    // 次のサイクルから, 各コアのaccが次のコアのaccで更新されていく
    assign acc  = (update) ? acc_left  : acc_right;

    always_ff @(posedge clk)begin
                  if(mat_v)begin
                      matrix_even[mat_a] <= mat_d[31:0];
                  end
                  if (~exec_mat_addr[0]) begin // 偶数
                      exec_mat_data <= matrix_even[exec_mat_addr[6:1]];
                  end
              end;

    always_ff @(posedge clk)begin
                  if(mat_v)begin
                      matrix_odd[mat_a] <= mat_d[63:32];
                  end
                  if (exec_mat_addr[0]) begin // 奇数
                      exec_mat_data <= matrix_odd[exec_mat_addr[6:1]];
                  end
              end;

    reg               init_next, init_next_next;
    reg               exec_next, exec_next_next;

    always_ff @(posedge clk)begin
                  init_next <= init;
                  init_next_next <= init_next;
                  exec_next <= exec;
                  exec_next_next <= exec_next;
              end;

    // 周波数をあげるためにレジスタを間に挟む (ここがクリティカルパスになるっぽい)
    reg [31:0]        m2,d2;
    always_ff @(posedge clk)begin
                  if(exec_next)begin
                      m2 <= exec_mat_data;
                      d2 <= exec_src_data;
                  end
              end;

    always_ff @(posedge clk)begin
                  if(init_next_next)begin
                      acc_left <= 32'h0;
                  end
                  else if(exec_next_next)begin
                      acc_left <= acc_left + m2 * d2;
                  end
                  if(out_period)begin
                      acc_right <= acc_next;
                  end
              end;

endmodule

`default_nettype wire
