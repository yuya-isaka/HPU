`default_nettype none

module core
    (
        input wire              clk,
        input wire              rst,
        input wire              matw,
        input wire [6:0]        mat_a,
        input wire [31:0]       rand_num,

        input wire [64:0]       mat_d,
        input wire src_v,
        input wire s_init,
        input wire last_j,

        input wire              exec,
        input wire              out_period,
        input wire              update,
        input wire [31:0]       exec_src_data,
        // input wire [31:0]       acc_next,

        output logic [31:0]     acc
    );

    // reg [31:0] exec_src_data_next;
    // always_ff @(posedge clk) begin
    //     exec_src_data_next <= exec_src_data;
    // end;

    reg src_v_next;
    always_ff @(posedge clk) begin
        src_v_next <= src_v;
    end;


    // 各コアにつき32bitのデータを128個集める
    // BRAMになっているよし
    (* ram_style = "block" *)         reg [31:0]        item_memory [0:99];

    always_ff @(posedge clk) begin
                //   if (matw) begin
                //       item_memory[mat_a] = rand_num;
                //   end
                  if (src_v_next) begin // 偶数
                      m2 <= item_memory[exec_src_data[8:0]];
                  end
              end;

    // integer i;
    // integer j;
    // initial begin
    //     j = 33215360;
    //     for (i=0; i < 100; i++) begin
    //         item_memory[i] = j;
    //         j += 18360;
    //     end
    // end
    integer i;
    initial begin
        for (i=0; i < 100; i++) begin
            item_memory[i] = i;
        end
    end

    // reg [31:0]        exec_mat_data;

    reg [31:0]        acc_right, acc_left;

    // updateで一気に8個のコアのaccが更新される
    // 次のサイクルから, 各コアのaccが次のコアのaccで更新されていく

    always_comb begin
                    acc = acc_right;

                    if (update) begin
                        acc = acc_left;
                    end
                end;

    // // initを適切なタイミングで１にする
    // reg               init_next, init_next_next;
    // always_ff @(posedge clk)begin
    //               init_next <= init;
    //               init_next_next <= init_next;
    //           end;

    // reg               exec_next, exec_next_next, exec_next_next_next;
    // always_ff @(posedge clk)begin
    //               exec_next <= exec;
    //               exec_next_next <= exec_next;
    //               exec_next_next_next <= exec_next_next;
    //           end;


    // 周波数をあげるためにレジスタを間に挟む (ここがクリティカルパスになるっぽい)
    reg [31:0]        m2;
    // always_ff @(posedge clk)begin
    //               if(exec_next_next)begin
    //                   m2 <= exec_mat_data;
    //               end
    //           end;

    reg [31:0]     permutation;
    always_ff @(posedge clk)begin
                  if(src_v & ~s_init | last_j)begin
                      permutation <= 32'h0;
                      acc_left <= 32'h0;
                      permutation <= 0;
                  end
                  else if(exec)begin
                      // クリティカルパスになりそう（なるなら分けてもいい）
                      //   acc_left <= acc_left ^ (m2 >> m2 | ( ( m2 & ((1'b1 << m2) - 1'b1) ) << (32 - m2) ) );
                      //   acc_left <= acc_left ^ (32'd33215360 >> m2 | ( ( 32'd33215360 & ((1'b1 << m2) - 1'b1) ) << (32 - m2) ) );
                      //   acc_left <= acc_left ^ (32'd33215360 >> permutation | ( ( 32'd33215360 & ((1'b1 << permutation) - 1'b1) ) << (32 - permutation) ) );
                    //   acc_left <= acc_left ^ (m2 >> permutation | ( ( m2 & ((1'b1 << permutation) - 1'b1) ) << (32 - permutation) ) );
                      acc_left <= acc_left + m2;
                      permutation <= permutation + 1;
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
