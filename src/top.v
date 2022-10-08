`default_nettype none

module top
    (
        // AXI Lite Slave Interface
        input wire              S_AXI_ACLK,
        input wire              S_AXI_ARESETN,
        input wire [31:0]       S_AXI_AWADDR,
        input wire              S_AXI_AWVALID,
        output wire             S_AXI_AWREADY,
        input wire [31:0]       S_AXI_WDATA,
        input wire [3:0]        S_AXI_WSTRB,
        input wire              S_AXI_WVALID,
        output wire             S_AXI_WREADY,
        output wire [1:0]       S_AXI_BRESP,
        output wire             S_AXI_BVALID,
        input wire              S_AXI_BREADY,
        input wire [31:0]       S_AXI_ARADDR,
        input wire              S_AXI_ARVALID,
        output wire             S_AXI_ARREADY,
        output reg [31:0]       S_AXI_RDATA,
        output wire [1:0]       S_AXI_RRESP,
        output wire             S_AXI_RVALID,
        input wire              S_AXI_RREADY,

        // AXI Stream Master Interface
        input wire              AXIS_ACLK,
        input wire              AXIS_ARESETN,
        output wire             M_AXIS_TVALID,
        output wire [1023:0]    M_AXIS_TDATA,
        output wire [7:0]       M_AXIS_TSTRB,
        output wire             M_AXIS_TLAST,
        input wire              M_AXIS_TREADY,

        // AXI Stream Slave Interface
        output wire             S_AXIS_TREADY,
        input wire [1023:0]     S_AXIS_TDATA,
        input wire [7:0]        S_AXIS_TSTRB,
        input wire              S_AXIS_TLAST,
        input wire              S_AXIS_TVALID
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Parameter

    // 3
    reg [19:0]      addr_j;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            addr_j <= 19'd0;
        end
        else begin
            addr_j <= 19'd2;
        end
    end


    // 8
    reg [19:0]      addr_i;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            addr_i <= 19'd0;
        end
        else begin
            addr_i <= 19'd9; // 今回は900 / 3gram / 32コア = 9  あまりを入れて 9 + 1 = 10
            // addr_i <= 19'd7;
        end
    end


    reg [4:0]       remainder;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            remainder <= 5'd0;
        end
        else begin
            remainder <= 5'd0; // 今回の余りは20
        end
    end


    // item_memory数 (65536最大値)
    reg [15:0]      item_memory_num;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            item_memory_num <= 15'd0;
        end
        else begin
            item_memory_num <= 15'd1000;
        end
    end


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    wire        get_v;

    get_enable get_enable
               (
                   // in
                   .clk(AXIS_ACLK),
                   .gen(gen),
                   .run(run),
                   .get_valid(S_AXIS_TVALID),

                   // out
                   .get_ready(S_AXIS_TREADY),
                   .get_v(get_v)
               );



    wire        update;
    wire        exec;
    wire        last_update;
    wire        get_fin;

    get_ctrl get_ctrl
             (
                 // in
                 .clk(AXIS_ACLK),
                 .rst(~run),
                 .get_v(get_v),
                 .addr_i(addr_i[19:0]),
                 .addr_j(addr_j[19:0]),

                 // out
                 .update(update),
                 .exec(exec),
                 .last_update(last_update),
                 .get_fin(get_fin)
             );


    // M_AXIS_TDATA
    buffer_ctrl buffer_ctrl
                (
                    // in
                    .clk(AXIS_ACLK),
                    .rst(~run),
                    .tmp_addr_i(addr_i[0]),
                    .tmp_rand(tmp_rand[31:0]),
                    .remainder(remainder),
                    .result_1(result[0]),
                    .result_2(result[1]),
                    .result_3(result[2]),
                    .result_4(result[3]),
                    .result_5(result[4]),
                    .result_6(result[5]),
                    .result_7(result[6]),
                    .result_8(result[7]),
                    .result_9(result[8]),
                    .result_10(result[9]),
                    .result_11(result[10]),
                    .result_12(result[11]),
                    .result_13(result[12]),
                    .result_14(result[13]),
                    .result_15(result[14]),
                    .result_16(result[15]),
                    .result_17(result[16]),
                    .result_18(result[17]),
                    .result_19(result[18]),
                    .result_20(result[19]),
                    .result_21(result[20]),
                    .result_22(result[21]),
                    .result_23(result[22]),
                    .result_24(result[23]),
                    .result_25(result[24]),
                    .result_26(result[25]),
                    .result_27(result[26]),
                    .result_28(result[27]),
                    .result_29(result[28]),
                    .result_30(result[29]),
                    .result_31(result[30]),
                    .result_32(result[31]),
                    .update(update),
                    .last_update(last_update),
                    .get_fin(get_fin),
                    .stream_v(stream_v),
                    .stream_a(stream_a[7:0]),

                    // out
                    .stream_d(M_AXIS_TDATA[1023:0])
                );


    // M_AXIS_TVALID
    // M_AXIS_TLAST
    wire              stream_v;
    wire [7:0]        stream_a;

    stream_ctrl stream_ctrl
                (
                    // in
                    .clk(AXIS_ACLK),
                    .rst(~run),
                    .get_fin(get_fin),
                    .dst_ready(M_AXIS_TREADY),

                    // out
                    .dst_valid(M_AXIS_TVALID),
                    .dst_last(M_AXIS_TLAST),
                    .stream_v(stream_v),
                    .stream_a(stream_a[7:0])
                );


    //================================================================


    reg [15:0]      item_a;

    always @(posedge AXIS_ACLK) begin
        if (~gen) begin
            item_a <= 16'd0;
        end
        else begin
            item_a <= item_a + 16'd1;
        end
    end;



    wire [31:0]      rand_num;

    xorshift prng
             (
                 // in
                 .clk(AXIS_ACLK),
                 .gen(gen),

                 // out
                 .rand_num(rand_num[31:0])
             );



    reg [31:0]      tmp_rand;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            tmp_rand <= 32'd0;
        end
        else if (gen & addr_i[0] & (item_a == item_memory_num)) begin
            tmp_rand <= rand_num;
        end
    end


    //================================================================


    // 後々要改造（permutation == addr_j)
    reg [31:0]      permutation;

    always @(posedge AXIS_ACLK) begin
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



    wire [31:0]         result [0:31];

    generate
        genvar      i;
        for (i = 0; i < 32; i = i + 1) begin
            core core
                 (
                     // in
                     .clk(AXIS_ACLK),
                     .run(run),
                     .gen(gen),
                     .item_a(item_a[15:0]),
                     .item_memory_num(item_memory_num[15:0]),
                     .rand_num(rand_num[31:0]),
                     .get_v(get_v),
                     .get_d(S_AXIS_TDATA[31+32*i:32*i]),
                     .permutation(permutation),
                     .exec(exec),
                     .update(update),

                     // out
                     .result(result[i])
                 );
        end
    endgenerate


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    assign M_AXIS_TSTRB = 8'hff;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // AXI Lite Slave State
    reg [3:0]       state;
    reg [11:2]      write_addr;
    reg [11:2]      read_addr;
    reg [31:0]      write_data;


    wire INI = (state == 4'b0000);
    wire AW  = (state == 4'b0001);
    wire W   = (state == 4'b0010);
    wire AWW = (state == 4'b0011);
    wire AR1 = (state == 4'b0100);
    wire AR2 = (state == 4'b1000);


    //================================================================


    assign S_AXI_BRESP   = 2'b00;
    assign S_AXI_RRESP   = 2'b00;
    assign S_AXI_AWREADY = INI | W;
    assign S_AXI_WREADY  = INI | AW;
    assign S_AXI_ARREADY = INI;
    assign S_AXI_BVALID  = AWW;
    assign S_AXI_RVALID  = AR2;

    always @(posedge S_AXI_ACLK) begin
        if (~S_AXI_ARESETN) begin
            state <= 4'b0000;
            write_addr <= 0;
            write_data <= 0;
        end
        // INI
        else if (INI) begin
            if (S_AXI_AWVALID & S_AXI_WVALID) begin // go AWW
                state <= 4'b0011;
                write_addr[11:2] <= S_AXI_AWADDR[11:2];
                write_data <= S_AXI_WDATA;
            end
            else if (S_AXI_AWVALID) begin // go AW
                state <= 4'b0001;
                write_addr[11:2] <= S_AXI_AWADDR[11:2];
            end
            else if (S_AXI_WVALID) begin // go W
                state <= 4'b0010;
                write_data <= S_AXI_WDATA;
            end
            else if (S_AXI_ARVALID) begin // go AR1
                state <= 4'b0100;
                read_addr[11:2] <= S_AXI_ARADDR[11:2];
            end
        end
        // AW
        else if (AW) begin
            if (S_AXI_WVALID) begin // go AWW
                state <= 4'b0011;
                write_data <= S_AXI_WDATA;
            end
        end
        // W
        else if (W) begin
            if (S_AXI_AWVALID) begin // go AWW
                state <= 4'b0011;
                write_addr[11:2] <= S_AXI_AWADDR[11:2];
            end
        end
        // AWW
        else if (AWW) begin
            if (S_AXI_BREADY) begin // go INI
                state <= 4'b0000;
            end
        end
        // AR1
        else if (AR1) begin
            state <= 4'b1000;
        end
        // AR2
        else if (AR2) begin
            if (S_AXI_RREADY) begin // go INI
                state <= 4'b0000;
            end
        end
    end


    //================================================================


    wire register_w = AWW & (write_addr[11:10] == 2'b00);
    wire register_r = AR1 & (read_addr[11:10] == 2'b00);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    reg [31:0]      control;
    reg             run, gen;


    //================================================================


    // Register Write
    always @(posedge S_AXI_ACLK) begin
        if (~S_AXI_ARESETN) begin
            {run, gen} <= 2'b00;
            control <= 32'h0;
        end
        else if (register_w) begin
            case ({write_addr[9:2],2'b00})
                10'h00:
                    {run, gen} <= write_data[1:0];
                10'h10:
                    control <= write_data;
                default:
                    ;
            endcase
        end
        else if (gen & item_a == item_memory_num) begin
            gen <= 1'b0;
        end
    end


    //================================================================


    // Register Read
    always @(posedge S_AXI_ACLK) begin
        if (register_r) begin
            S_AXI_RDATA <= 0;
            case ({read_addr[9:2],2'b00})
                10'h00:
                    S_AXI_RDATA[1:0] <= {run, gen};
                10'h10:
                    S_AXI_RDATA <= control;
                default:
                    ;
            endcase
        end
    end


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
