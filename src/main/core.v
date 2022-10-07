`default_nettype none

module core
    (
        input wire              clk,
        input wire              run,
        input wire              gen,
        input wire [15:0]       item_a,
        input wire [31:0]       rand_num,
        input wire              get_v,
        input wire [31:0]       get_d_1,
        input wire [31:0]       get_d_2,
        input wire [19:0]       addr_j,
        input wire              exec,
        input wire              update,

        output reg [31:0]     result_1,
        output reg [31:0]     result_2
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    (* ram_style = "block" *)
    reg [31:0]      item_memory [0:1023];


    reg [31:0]      hv_1;
    always @(posedge clk) begin
        if (gen) begin
            item_memory[item_a] <= rand_num;
            hv_1 <= 0;
        end
        else if (get_v) begin
            hv_1 <= item_memory[get_d_1];
        end
    end;

    reg [31:0]      hv_2;
    always @(posedge clk) begin
        if (gen) begin
            hv_2 <= 0;
        end
        else if (get_v) begin
            hv_2 <= item_memory[get_d_2];
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


    reg [31:0]      enc_1;
    reg [31:0]      enc_2;

    always @(posedge clk) begin
        if (~run) begin
            enc_1 <= 32'h0;
            enc_2 <= 32'h0;
        end
        else if (exec) begin
            if (update) begin
                enc_1 <= hv_1;
                enc_2 <= hv_2;
            end
            else begin
                enc_1 <= enc_1 ^ (hv_1 >> permutation | ( ( hv_1 & ((1'b1 << permutation) - 1'b1) ) << (32 - permutation) ) );
                enc_2 <= enc_2 ^ (hv_2 >> permutation | ( ( hv_2 & ((1'b1 << permutation) - 1'b1) ) << (32 - permutation) ) );
            end
        end
    end;


    //================================================================


    always @* begin
        result_1 = 0;
        result_2 = 0;

        if (update) begin
            result_1 = enc_1;
            result_2 = enc_2;
        end
    end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
