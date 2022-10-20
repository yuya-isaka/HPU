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

    // parameter DIM = 1023;    // DIM-1
    parameter DIM = 31;    // DIM-1
    // parameter WI = 31;      // 32が何個か-1
    parameter WI = 0;      // 32が何個か-1

    // 計算何をさせるか（0ならxor, 1ならpermutation)
    wire [3:0]  unit;
    assign unit = 4'b0101;
    // 0ユニットをperamutation
    // 1ユニットをxor
    // 2ユニットをpermutation
    // 3ユニットをxor

    // どっちの値を使うか (0ならitem, 1なら横のやつ)
    wire [3:0]  which;
    assign which = 4'b1010;


    wire [3:0]  core_en;
    assign core_en = 4'b0101;


    wire [3:0]  step;
    assign step = 4'd2;

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
    wire        tmp_tmp_update;
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
                 .step(step[3:0]),

                 // out
                 .update(update),
                 .tmp_tmp_update(tmp_tmp_update),
                 .exec(exec),
                 .last_update(last_update),
                 .get_fin(get_fin)
             );


    // M_AXIS_TDATA
    // buffer_ctrl #(.DIM(1023)) buffer_ctrl
    buffer_ctrl #(.DIM(31)) buffer_ctrl
                (
                    // in
                    .clk(AXIS_ACLK),
                    .rst(~run),
                    .tmp_even(even),
                    // 次元数可変
                    .tmp_rand(tmp_rand[DIM:0]),
                    .remainder(remainder),
                    .core_en(core_en[3:0]),
                    // コア数可変
                    .core_result_1(core_result_real[0]),
                    .core_result_2(core_result_real[1]),
                    .core_result_3(core_result_real[2]),
                    .core_result_4(core_result_real[3]),
                    // .core_result_5(core_result[4]),
                    // .core_result_6(core_result[5]),
                    // .core_result_7(core_result[6]),
                    // .core_result_8(core_result[7]),
                    // .core_result_9(core_result[8]),
                    // .core_result_10(core_result[9]),
                    // .core_result_11(core_result[10]),
                    // .core_result_12(core_result[11]),
                    // .core_result_13(core_result[12]),
                    // .core_result_14(core_result[13]),
                    // .core_result_15(core_result[14]),
                    // .core_result_16(core_result[15]),
                    // .core_result_17(core_result[16]),
                    // .core_result_18(core_result[17]),
                    // .core_result_19(core_result[18]),
                    // .core_result_20(core_result[19]),
                    // .core_result_21(core_result[20]),
                    // .core_result_22(core_result[21]),
                    // .core_result_23(core_result[22]),
                    // .core_result_24(core_result[23]),
                    // .core_result_25(core_result[24]),
                    // .core_result_26(core_result[25]),
                    // .core_result_27(core_result[26]),
                    // .core_result_28(core_result[27]),
                    // .core_result_29(core_result[28]),
                    // .core_result_30(core_result[29]),
                    // .core_result_31(core_result[30]),
                    // .core_result_32(core_result[31]),
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


    reg [4:0]       item_a_tmp;

    always @(posedge AXIS_ACLK) begin
        if (~gen) begin
            item_a_tmp <= 0;
        end
        else begin
            if (item_a_tmp == WI) begin
                item_a_tmp <= 5'd0;
            end
            else begin
                item_a_tmp <= item_a_tmp + 5'd1;
            end
        end
    end;


    reg             update_item;

    always @(posedge AXIS_ACLK) begin
        if (~gen) begin
            update_item <= 0;
        end
        else if (item_a_tmp == WI) begin
            update_item <= 1'd1;
        end
        else begin
            update_item <= 0;
        end
    end


    reg [15:0]      item_a;

    always @(posedge AXIS_ACLK) begin
        if (~gen) begin
            item_a <= 0;
        end
        else if (update_item) begin
            item_a <= item_a + 16'd1;
        end
    end


    wire [31:0]         rand_num_tmp;

    xorshift prng
             (
                 // in
                 .clk(AXIS_ACLK),
                 .gen(gen),

                 // out
                 .rand_num(rand_num_tmp[31:0])
             );


    // 次元数可変
    reg [DIM:0]       rand_num;

    always @(posedge AXIS_ACLK) begin
        if (~gen) begin
            rand_num <= 0;
        end
        else if (item_a_tmp == 0) begin
            rand_num[31:0] <= rand_num_tmp;
        end
        // else if (item_a_tmp == 1) begin
        //     rand_num[63:32] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 2) begin
        //     rand_num[95:64] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 3) begin
        //     rand_num[127:96] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 4) begin
        //     rand_num[159:128] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 5) begin
        //     rand_num[191:160] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 6) begin
        //     rand_num[223:192] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 7) begin
        //     rand_num[255:224] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 8) begin
        //     rand_num[287:256] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 9) begin
        //     rand_num[319:288] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 10) begin
        //     rand_num[351:320] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 11) begin
        //     rand_num[383:352] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 12) begin
        //     rand_num[415:384] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 13) begin
        //     rand_num[447:416] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 14) begin
        //     rand_num[479:448] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 15) begin
        //     rand_num[511:480] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 16) begin
        //     rand_num[543:512] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 17) begin
        //     rand_num[575:544] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 18) begin
        //     rand_num[607:576] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 19) begin
        //     rand_num[639:608] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 20) begin
        //     rand_num[671:640] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 21) begin
        //     rand_num[703:672] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 22) begin
        //     rand_num[735:704] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 23) begin
        //     rand_num[767:736] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 24) begin
        //     rand_num[799:768] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 25) begin
        //     rand_num[831:800] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 26) begin
        //     rand_num[863:832] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 27) begin
        //     rand_num[895:864] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 28) begin
        //     rand_num[927:896] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 29) begin
        //     rand_num[959:928] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 30) begin
        //     rand_num[991:960] <= rand_num_tmp;
        // end
        // else if (item_a_tmp == 31) begin
        //     rand_num[1023:992] <= rand_num_tmp;
        // end
    end



    // 次元数可変
    reg [DIM:0]      tmp_rand;

    always @(posedge AXIS_ACLK) begin
        if (~AXIS_ARESETN) begin
            tmp_rand <= 0;
        end
        else if (gen & (item_a == item_memory_num) & update_item) begin
            tmp_rand <= rand_num;
        end
    end


    //================================================================


    // コア数可変
    // wire [DIM:0]         core_result [0:31];
    // nextが必要なため＋１
    wire [DIM:0]         core_result [0:4];
    assign core_result[0] = 0;

    wire [DIM:0]         core_result_real [0:3];

    generate
        genvar      i;
        // コア数可変
        // for (i = 0; i < 32; i = i + 1) begin
        for (i = 0; i < 4; i = i + 1) begin
            // core #(.DIM(1023)) core
            core #(.DIM(31)) core
                 (
                     // in
                     .clk(AXIS_ACLK),
                     .run(run),
                     .gen(gen),
                     .update_item(update_item),
                     .item_a(item_a[15:0]),
                     .item_memory_num(item_memory_num[15:0]),
                     // 次元数可変
                     .rand_num(rand_num[DIM:0]),
                     .get_v(get_v),
                     // アドレス数可変
                     .get_d(S_AXIS_TDATA[31+32*i:32*i]),
                     .addr_j(addr_j[19:0]),
                     .exec(exec),
                     .update(update),
                     .core_en_bit(core_en[i]),
                     .tmp_tmp_update(tmp_tmp_update),
                     .unit_bit(unit[i]),
                     .which_bit(which[i]),
                     .core_result_next(core_result[i]),

                     // out
                     .core_result(core_result[i+1]),
                     .core_result_real(core_result_real[i])
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


    // 状態
    reg             run, gen;

    // N-gram
    reg [19:0]      addr_j;

    // アドレス数 / N-gram / コア数　(余る場合は+1)
    // 900 / 3gram / 32コア = 9  あまりを入れて 9 + 1 = 10
    reg [19:0]      addr_i;

    // 余りの数
    reg [4:0]       remainder;

    // item_memory数 (現状65536最大値, 16bitアドレスで指定)
    reg [15:0]      item_memory_num;

    // アドレス / N-gramが偶数か
    reg             even;

    //================================================================


    // Register Write
    always @(posedge S_AXI_ACLK) begin
        if (~S_AXI_ARESETN) begin
            {run, gen} <= 2'b00;
            item_memory_num <= 16'd0;
            addr_j <= 20'd0;
            addr_i <= 20'd0;
            remainder <= 5'd0;
            even <= 1'd0;
        end
        else if (register_w) begin
            case ({write_addr[9:2],2'b00})
                10'd00:
                    {run, gen} <= write_data[1:0];
                10'd04:
                    item_memory_num[15:0] <= write_data[15:0]; // 1000
                10'd08:
                    addr_j[19:0] <= write_data[19:0]; // 2
                10'd12:
                    addr_i[19:0] <= write_data[19:0]; // 9
                10'd16:
                    remainder[4:0] <= write_data[4:0]; // 20
                10'd20:
                    even <= write_data[0];
                default:
                    ;
            endcase
        end
        else if (gen & item_a == item_memory_num & update_item) begin
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
                10'd04:
                    S_AXI_RDATA[15:0] <= item_memory_num[15:0];
                10'd08:
                    S_AXI_RDATA[19:0] <= addr_j[19:0];
                10'd12:
                    S_AXI_RDATA[19:0] <= addr_i[19:0];
                10'd16:
                    S_AXI_RDATA[4:0] <= remainder[4:0];
                10'd20:
                    S_AXI_RDATA <= even;
                default:
                    ;
            endcase
        end
    end



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
