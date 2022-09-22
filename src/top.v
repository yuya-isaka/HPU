/**********************************************************************\
*      addrress range   access size   function                         *
* reg  0x000            32bit         [0] matw matrix write            *
*                                     [1] run  data input/ matrix mul/ *
*                                              data output             *
*                                     [2] last last cycle              *
* reg  0x010            32bit         control dummy register           *
\**********************************************************************/

// register_write -> matw -> mat_v
//                        -> mat_a

// register_w -> run -> src_v
//                   -> src_a
//                           -> src_fin -> s_init
//                                      -> p反転
//                                      -> src_en

// s_init -> k_init -> exec          -> k_fin -> k_init
//                  -> exec_mat_addr
//                  -> exec_src_addr
//                  -> exec_src_data

// k_fin -> out_period
//       -> out_busy
//       -> out_addr
//                     -> out_fin -> s_fin
// update -> result

// 最後のout_fin -> s_fin
//                 s_fin_in -> s_init
//                          -> src_en
//                          -> p反転（新しい計算）
//                          -> stream_v
//                          -> stream_a
`default_nettype none

module top
    (
        input wire         S_AXI_ACLK,
        input wire         S_AXI_ARESETN,

        ////////////////////////////////////////////////////////////////////////////
        // AXI Lite Slave Interface
        input wire [31:0]  S_AXI_AWADDR,
        input wire         S_AXI_AWVALID,
        output wire        S_AXI_AWREADY,
        input wire [31:0]  S_AXI_WDATA,
        input wire [3:0]   S_AXI_WSTRB, // ストローブ信号,wstrb は wdata のうち実際に書き込む部位をバイト単位で指定します
        input wire         S_AXI_WVALID,
        output wire        S_AXI_WREADY,
        output wire [1:0]  S_AXI_BRESP,
        output wire        S_AXI_BVALID,
        input wire         S_AXI_BREADY,

        input wire [31:0]  S_AXI_ARADDR,
        input wire         S_AXI_ARVALID,
        output wire        S_AXI_ARREADY,
        output reg [31:0]  S_AXI_RDATA,
        output wire [1:0]  S_AXI_RRESP,
        output wire        S_AXI_RVALID,
        input wire         S_AXI_RREADY,


        input wire         AXIS_ACLK,
        input wire         AXIS_ARESETN,

        ////////////////////////////////////////////////////////////////////////////
        // AXI Stream Master Interface
        output wire        M_AXIS_TVALID,
        output wire [63:0] M_AXIS_TDATA,
        output wire [7:0]  M_AXIS_TSTRB,
        output wire        M_AXIS_TLAST, // データの区切り、最後のデータの時に立たせる, // 必須らしい
        // https://www.acri.c.titech.ac.jp/wordpress/archives/11585
        // https://support.xilinx.com/s/article/60053?language=ja (Xilinxのアンサー)
        input wire         M_AXIS_TREADY,

        // tuserというデータの先頭を示す、オプショナルな信号もあるっぽい

        ////////////////////////////////////////////////////////////////////////////
        // AXI Stream Slave Interface
        output wire        S_AXIS_TREADY,
        input wire [63:0]  S_AXIS_TDATA,
        input wire [7:0]   S_AXIS_TSTRB,
        input wire         S_AXIS_TLAST, // データの区切り、最後のデータの時にたつ, 次のクロックにはデータがこない
        input wire         S_AXIS_TVALID
    );

    ///////////////////////////////////////////////////////////////////////////////


    assign M_AXIS_TSTRB = 8'hff;

    reg               run, matw, last;


    /////////////////////////////////////////////////////////////////////////////////


    wire              src_v;   // アドレス生成をしているか否か
    wire [8:0]        src_a;   // アドレス
    wire              src_fin; // アドレスの生成が最後か否か (s_init駆動、p変更, src_enを埋める)
    src_ctrl src_ctrl
             (
                 .clk(AXIS_ACLK),
                 .run(run),
                 .src_valid(S_AXIS_TVALID),
                 .src_en(src_en),

                 .src_ready(S_AXIS_TREADY),
                 .src_v(src_v),
                 .src_a(src_a[8:0]),
                 .src_fin(src_fin)
             );


    wire [1:0]     src_en;
    src_en_ctrl src_en_ctrl
                (
                    .clk(AXIS_ACLK),
                    .run(run),
                    .src_fin(src_fin),
                    .p(p),
                    .s_fin_in(s_fin_in),

                    .src_en(src_en)
                );


    wire              p;
    p_ctrl p_ctrl
           (
               .clk(AXIS_ACLK),
               .run(run),
               .src_fin(src_fin),
               .src_en(src_en),
               .s_fin_in(s_fin_in),

               .p(p)
           );


    wire              s_fin_in; // 次の計算するものがある or 最後
    wire              s_init; // srcの受信が終了した次(最初なら)　or 前の計算が終わった次（次のデータがあるなら）
    s_ctrl s_ctrl
           (
               .clk(AXIS_ACLK),
               .run(run),
               .last(last),
               .dst_ready(M_AXIS_TREADY),
               .s_fin(s_fin),
               .src_fin(src_fin),
               .src_en(src_en),
               .p(p),

               .s_fin_in(s_fin_in),
               .s_init(s_init)
           );



    ///////////////////////////////////////////////////////////////////////////////////


    wire              s_fin;
    wire              k_init;
    wire              k_fin;
    wire              exec;
    wire [9:0]        exec_src_addr;
    exe_ctrl exe_ctrl
             (
                 .clk(AXIS_ACLK),
                 .rst(~run),
                 .s_init(s_init),
                 .out_busy(out_busy),
                 .out_fin(out_fin),

                 .s_fin(s_fin),
                 .k_init(k_init),
                 .k_fin(k_fin),
                 .exec(exec),
                 .exec_src_addr(exec_src_addr[9:0])
             );


    wire              out_busy;
    wire              out_period;
    wire              out_fin;
    wire [5:0]        out_addr;
    wire              update;
    out_ctrl out_ctrl
             (
                 .clk(AXIS_ACLK),
                 .rst(~run),
                 .s_init(s_init),
                 .out_busy(out_busy),
                 .k_init(k_init),
                 .k_fin(k_fin),

                 .out_period(out_period),
                 .out_fin(out_fin),
                 .out_addr(out_addr[5:0]),
                 .update(update)
             );


    wire [31:0]       exec_src_data;
    src_buf src_buf
            (
                .clk(AXIS_ACLK),
                .src_v(src_v),
                .src_a(src_a[8:0]),
                .src_d(S_AXIS_TDATA),
                .exec(exec),
                .exec_src_addr(exec_src_addr[9:0]),
                .p(p),

                .exec_src_data(exec_src_data)
            );


    //////////////////////////////////////////////////////////////////////////////////


    wire              stream_v;
    wire [4:0]        stream_a;
    dst_ctrl dst_ctrl
             (
                 .clk(AXIS_ACLK),
                 .run(run),
                 .dst_ready(M_AXIS_TREADY),
                 .s_fin_in(s_fin_in),

                 .dst_valid(M_AXIS_TVALID),
                 .dst_last(M_AXIS_TLAST),
                 .stream_v(stream_v),
                 .stream_a(stream_a[4:0])
             );


    dst_buf dst_buf
            (
                .clk(AXIS_ACLK),
                .stream_v(stream_v),
                .stream_a(stream_a[4:0]), // 計算していない方なので~p
                .out_period(out_period),
                .out_addr(out_addr[5:0]), // 計算している方なのでp
                .result(result),
                .p(p),

                .stream_d(M_AXIS_TDATA)
            );


    //////////////////////////////////////////////////////////////////////////////////


    // wire [31:0] acc [0:1];
    wire [31:0] acc;
    // assign acc[1] = 0;

    // updateで一気に8個のコアのaccが更新される
    // 次のサイクルから, 各コアのaccが次のコアのaccで更新されていく
    // だから先頭のaccを見ていれば、８個のコアの結果が順にわかって、それをdst_bufに入れられる
    // wire [31:0] result = acc[0];
    wire [31:0] result = acc;

    generate
        genvar         i;
        for (i = 0; i < 1; i = i + 1)begin
            core core
                 (
                     .clk(AXIS_ACLK),
                     .init(k_init),

                     .mat_d(S_AXIS_TDATA),

                     .exec(exec),
                     .out_period(out_period),
                     .update(update),
                     .exec_src_data(exec_src_data),
                     //  .acc_next(acc[i+1]),

                     //  .acc(acc[i])
                     .acc(acc)
                 );
        end
    endgenerate


    ////////////////////////////////////////////////////////////////////////////

    // AXI Lite Slave State
    reg [3:0]         state;
    reg [11:2]        write_addr;
    reg [11:2]        read_addr;
    reg [31:0]        write_data;

    wire INI =  (state == 4'b0000);
    wire AW =   (state == 4'b0001);
    wire W =    (state == 4'b0010);
    wire AWW =  (state == 4'b0011);
    wire AR1 =  (state == 4'b0100);
    wire AR2 =  (state == 4'b1000);

    assign S_AXI_BRESP = 2'b00; // スレーブからの結果の成否
    // bresp[1:0] は上位１ビットがゼロなら成功、１なら失敗になります
    //         00 : OKAY
    //         01 : Exclusive Access OK
    //         10 : Slave Error
    //         11 : Decode Error
    assign S_AXI_RRESP = 2'b00; // スレーブからの結果の成否
    // rresp[1:0] は上位１ビットがゼロなら成功、１なら失敗になります
    //          00 : OKAY
    //          01 : Exclusive Access OK
    //          10 : Slave Error
    //          11 : Decode Error
    assign S_AXI_AWREADY = INI | W;
    assign S_AXI_WREADY  = INI | AW;
    assign S_AXI_ARREADY = INI;
    assign S_AXI_BVALID  = AWW;
    assign S_AXI_RVALID  = AR2;

    always @(posedge S_AXI_ACLK)begin
        if(~S_AXI_ARESETN)begin
            state<=4'b0000;
            write_addr<=0;
            write_data<=0;
        end
        // INI
        else if(INI)begin
            if(S_AXI_AWVALID & S_AXI_WVALID)begin
                state<=4'b0011; // go AWW
                write_addr[11:2]<=S_AXI_AWADDR[11:2];
                write_data<=S_AXI_WDATA;
            end
            else if(S_AXI_AWVALID)begin
                state<=4'b0001; // go AW
                write_addr[11:2]<=S_AXI_AWADDR[11:2];
            end
            else if(S_AXI_WVALID)begin
                state<=4'b0010; // go W
                write_data<=S_AXI_WDATA;
            end
            else if(S_AXI_ARVALID)begin
                state<=4'b0100; // go AR1
                read_addr[11:2]<=S_AXI_ARADDR[11:2];
            end
        end
        // AW
        else if(AW)begin
            if(S_AXI_WVALID)begin
                state<=4'b0011; // go AWW
                write_data<=S_AXI_WDATA;
            end
        end
        // W
        else if(W)begin
            if(S_AXI_AWVALID)begin
                state<=4'b0011; // go AWW
                write_addr[11:2]<=S_AXI_AWADDR[11:2];
            end
        end
        // AWW
        else if(AWW)begin
            if(S_AXI_BREADY)
                state<=4'b0000; // go INI
        end
        // AR1
        else if(AR1)begin
            state<=4'b1000;
        end
        // AR2
        else if(AR2)begin
            if(S_AXI_RREADY)
                state<=4'b0000; // go INI
        end
    end


    reg [31:0] control;

    wire       register_w = AWW & (write_addr[11:10]==2'b00);
    wire       register_r  = AR1 & (read_addr[11:10]==2'b00);

    ////////////////////////////////////////////////////////////////////////////

    // Register Write
    always @(posedge S_AXI_ACLK)begin
        if(~S_AXI_ARESETN)begin
            {last, run, matw} <= 3'b000;
            control <= 32'h0;
        end
        else if(register_w)begin
            case({write_addr[9:2],2'b00})
                10'h00:
                    {last, run, matw} <= write_data[2:0];
                10'h10:
                    control <= write_data;
                default:
                    ;
            endcase
        end
    end

    ////////////////////////////////////////////////////////////////////////////

    // Register Read
    always @(posedge S_AXI_ACLK)begin
        if(register_r)begin
            S_AXI_RDATA <= 0;
            case({read_addr[9:2],2'b00})
                10'h00:
                    S_AXI_RDATA[2:0] <= {last, run, matw};
                10'h10:
                    S_AXI_RDATA <= control;
                default:
                    ;
            endcase
        end
    end
endmodule

`default_nettype wire
