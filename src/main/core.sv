`default_nettype none

module core
    #(
         parameter DIM = 1023
     )
     (
         input wire              clk,
         input wire              run,
         input wire              gen,
         input wire              update_item,
         input wire [15:0]       item_a,
         input wire [15:0]       item_memory_num,
         input wire [DIM:0]     rand_num,
         input wire              get_v,
         input wire [31:0]       get_d,
         input wire [19:0]       addr_j,
         input wire              exec,
         input wire              update,

         output logic [DIM:0]   core_result
     );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // BRAMになるはず
    (* ram_style = "block" *)
    reg [DIM:0]      item_memory [0:1023];


    reg [DIM:0]      hv;
    always_ff @(posedge clk) begin
                  if (gen & (item_a != item_memory_num) & update_item) begin
                      item_memory[item_a] <= rand_num;
                      hv <= 0;
                  end
                  else if (get_v) begin
                      hv <= item_memory[get_d];
                  end
              end;

    // integer i;
    // initial begin
    //     for (i=0; i < 100; i++) begin
    //         item_memory[i] = i;
    //     end
    // end


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 後々要改造（permutation == addr_j)
    reg [31:0]      permutation;

    always @(posedge clk) begin
        if (~run) begin
            permutation <= 32'h0;
        end
        else if (exec) begin
            if (permutation == addr_j) begin
                permutation <= 32'h0;
            end
            else begin
                permutation <= permutation + 1;
            end
        end
    end;



    reg [DIM:0]      enc;

    always_ff @(posedge clk) begin
                  if (~run) begin
                      enc <= 0;
                  end
                  else if (exec) begin
                      if (update) begin
                          enc <= hv;
                      end
                      else begin
                        // 次元数可変にするなら、これの左側（hv>>permutation)と右側に分けて、一番右の右側を一番左に持ってくる配線にしたら良いと
                          enc <= enc ^ (hv >> permutation | ( ( hv & ((1'b1 << permutation) - 1'b1) ) << (DIM+1 - permutation) ) );
                      end
                  end
              end;


    //================================================================


    always_comb begin
                    core_result = 0;

                    if (update) begin
                        core_result = enc;
                    end
                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
