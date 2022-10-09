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
        //　バス幅可変
        output wire [1023:0]    M_AXIS_TDATA,
        output wire [7:0]       M_AXIS_TSTRB,
        output wire             M_AXIS_TLAST,
        input wire              M_AXIS_TREADY,

        // AXI Stream Slave Interface
        output wire             S_AXIS_TREADY,
        // バス幅可変
        input wire [1023:0]     S_AXIS_TDATA,
        input wire [7:0]        S_AXIS_TSTRB,
        input wire              S_AXIS_TLAST,
        input wire              S_AXIS_TVALID
    );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Parameter

    // N-gram
    reg [19:0]      addr_j;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            addr_j <= 19'd0;
        end
        else begin
            addr_j <= 19'd2;
        end
    end


    // アドレス数 / N-gram / コア数　(余る場合は+1)
    // 900 / 3gram / 32コア = 9  あまりを入れて 9 + 1 = 10
    reg [19:0]      addr_i;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            addr_i <= 19'd0;
        end
        else begin
            addr_i <= 19'd9;
        end
    end


    // 余りの数
    reg [4:0]       remainder;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            remainder <= 5'd0;
        end
        else begin
            remainder <= 5'd20;
        end
    end


    // item_memory数 (現状65536最大値, 16bitアドレスで指定)
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
                    // 次元数可変
                    .tmp_rand(tmp_rand[31:0]),
                    .remainder(remainder),
                    // コア数可変
                    .core_result_1(core_result[0]),
                    .core_result_2(core_result[1]),
                    .core_result_3(core_result[2]),
                    .core_result_4(core_result[3]),
                    .core_result_5(core_result[4]),
                    .core_result_6(core_result[5]),
                    .core_result_7(core_result[6]),
                    .core_result_8(core_result[7]),
                    .core_result_9(core_result[8]),
                    .core_result_10(core_result[9]),
                    .core_result_11(core_result[10]),
                    .core_result_12(core_result[11]),
                    .core_result_13(core_result[12]),
                    .core_result_14(core_result[13]),
                    .core_result_15(core_result[14]),
                    .core_result_16(core_result[15]),
                    .core_result_17(core_result[16]),
                    .core_result_18(core_result[17]),
                    .core_result_19(core_result[18]),
                    .core_result_20(core_result[19]),
                    .core_result_21(core_result[20]),
                    .core_result_22(core_result[21]),
                    .core_result_23(core_result[22]),
                    .core_result_24(core_result[23]),
                    .core_result_25(core_result[24]),
                    .core_result_26(core_result[25]),
                    .core_result_27(core_result[26]),
                    .core_result_28(core_result[27]),
                    .core_result_29(core_result[28]),
                    .core_result_30(core_result[29]),
                    .core_result_31(core_result[30]),
                    .core_result_32(core_result[31]),
                    .update(update),
                    .last_update(last_update),
                    .get_fin(get_fin),
                    .stream_v(stream_v),

                    // out
                    // バス幅可変
                    .stream_d(M_AXIS_TDATA[1023:0])
                );


    // M_AXIS_TVALID
    // M_AXIS_TLAST
    wire              stream_v;

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
                    .stream_v(stream_v)
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



    // 次元数可変
    wire [31:0]      rand_num;

    xorshift prng
             (
                 // in
                 .clk(AXIS_ACLK),
                 .gen(gen),

                 // out
                 .rand_num(rand_num[31:0])
             );



    // 次元数可変
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


    // コア数可変
    wire [31:0]         core_result [0:31];

    generate
        genvar      i;
        // コア数可変
        for (i = 0; i < 32; i = i + 1) begin
            core core
                 (
                     // in
                     .clk(AXIS_ACLK),
                     .run(run),
                     .gen(gen),
                     .item_a(item_a[15:0]),
                     .item_memory_num(item_memory_num[15:0]),
                     // 次元数可変
                     .rand_num(rand_num[31:0]),
                     .get_v(get_v),
                     // アドレス数可変
                     .get_d(S_AXIS_TDATA[31+32*i:32*i]),
                     .addr_j(addr_j[19:0]),
                     .exec(exec),
                     .update(update),

                     // out
                     .core_result(core_result[i])
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
