`default_nettype none

module core
    (
        input wire              clk,
        input wire              run,
        input wire              gen,
        input wire [15:0]       item_a,
        input wire [15:0]       item_memory_num,
        input wire [31:0]       rand_num,
        input wire              get_v,
        input wire [31:0]       get_d,
        input wire [31:0]       permutation,
        input wire              exec,
        input wire              update,

        output logic [31:0]     core_result
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // BRAMになるはず
    (* ram_style = "block" *)
    reg [31:0]      item_memory [0:1023];


    reg [31:0]      hv;
    always_ff @(posedge clk) begin
                  if (gen & (item_a != item_memory_num)) begin
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


    reg [31:0]      enc;

    always_ff @(posedge clk) begin
                  if (~run) begin
                      enc <= 32'h0;
                  end
                  else if (exec) begin
                      if (update) begin
                          enc <= hv;
                      end
                      else begin
                          enc <= enc ^ (hv >> permutation | ( ( hv & ((1'b1 << permutation) - 1'b1) ) << (32 - permutation) ) );
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
