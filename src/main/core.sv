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
                          //   enc <= enc ^ (hv >> permutation | ( ( hv & ((1'b1 << permutation) - 1'b1) ) << (DIM+1 - permutation) ) );
                          if (permutation == 10'd1) begin
                              enc <= enc ^ ({hv[0], hv[DIM:1]});
                          end
                          else if (permutation == 10'd2) begin
                              enc <= enc ^ ({hv[1:0], hv[DIM:2]});
                          end
                          else if (permutation == 10'd3) begin
                              enc <= enc ^ ({hv[2:0], hv[DIM:3]});
                          end
                          else if (permutation == 10'd4) begin
                              enc <= enc ^ ({hv[3:0], hv[DIM:4]});
                          end
                          else if (permutation == 10'd5) begin
                              enc <= enc ^ ({hv[4:0], hv[DIM:5]});
                          end
                          else if (permutation == 10'd6) begin
                              enc <= enc ^ ({hv[5:0], hv[DIM:6]});
                          end
                          else if (permutation == 10'd7) begin
                              enc <= enc ^ ({hv[6:0], hv[DIM:7]});
                          end
                          else if (permutation == 10'd8) begin
                              enc <= enc ^ ({hv[7:0], hv[DIM:8]});
                          end
                          else if (permutation == 10'd9) begin
                              enc <= enc ^ ({hv[8:0], hv[DIM:9]});
                          end
                          else if (permutation == 10'd10) begin
                              enc <= enc ^ ({hv[9:0], hv[DIM:10]});
                          end
                          else if (permutation == 10'd11) begin
                              enc <= enc ^ ({hv[10:0], hv[DIM:11]});
                          end
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
