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
        output wire [63:0]      M_AXIS_TDATA,
        output wire [7:0]       M_AXIS_TSTRB,
        output wire             M_AXIS_TLAST,
        input wire              M_AXIS_TREADY,

        // AXI Stream Slave Interface
        output wire             S_AXIS_TREADY,
        input wire [63:0]       S_AXIS_TDATA,
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
            addr_i <= 19'd149;
            // addr_i <= 19'd7;
        end
    end

    // item_memory数 (65536最大値)
    reg [15:0]      random_num;
    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            random_num <= 15'd0;
        end
        else begin
            random_num <= 15'd1000;
            // random_num <= 15'd100;
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
                 .get_fin(get_fin)
             );

    // M_AXIS_TDATA
    buffer_ctrl buffer_ctrl
                (
                    // in
                    .clk(AXIS_ACLK),
                    .rst(~run),
                    .result_1(result_1[31:0]),
                    .result_2(result_2[31:0]),
                    .update(update),
                    .get_fin(get_fin),
                    .stream_v(stream_v),
                    .stream_a(stream_a[7:0]),

                    // out
                    .stream_d(M_AXIS_TDATA[63:0])
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


    //================================================================


    wire [31:0]         result_1;
    wire [31:0]         result_2;

    generate
        genvar         i;
        for (i = 0; i < 1; i = i + 1) begin
            core core
                 (
                     // in
                     .clk(AXIS_ACLK),
                     .run(run),
                     .gen(gen),
                     .item_a(item_a[15:0]),
                     .rand_num(rand_num[31:0]),
                     .get_v(get_v),
                     .get_d_1(S_AXIS_TDATA[31:0]),
                     .get_d_2(S_AXIS_TDATA[63:32]),
                     .addr_j(addr_j[19:0]),
                     .exec(exec),
                     .update(update),

                     // out
                     .result_1(result_1[31:0]),
                     .result_2(result_2[31:0])
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
        else if (gen & item_a == random_num) begin
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
