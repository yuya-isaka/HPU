
`default_nettype none


// 可変 (デバッグ用)

// ------------------------------------------
// アドレス数可変
// 計算数可変
// バス幅可変

// コア数可変 (1コア専用の部分は、『1コア』とコメント。)
// 次元数可変 (topだけ)
// ------------------------------------------

module top
    (

        // AXI Lite Slave Interface ----------------------
        input wire                      S_AXI_ACLK,
        input wire                      S_AXI_ARESETN,

        input wire [ 31:0 ]             S_AXI_AWADDR,
        input wire                      S_AXI_AWVALID,
        output wire                     S_AXI_AWREADY,

        input wire [ 31:0 ]             S_AXI_WDATA,
        input wire [ 3:0 ]              S_AXI_WSTRB,
        input wire                      S_AXI_WVALID,
        output wire                     S_AXI_WREADY,

        input wire                      S_AXI_BREADY,
        output wire [ 1:0 ]             S_AXI_BRESP,
        output wire                     S_AXI_BVALID,

        input wire [ 31:0 ]             S_AXI_ARADDR,
        input wire                      S_AXI_ARVALID,
        output wire                     S_AXI_ARREADY,

        input wire                      S_AXI_RREADY,
        output reg [ 31:0 ]             S_AXI_RDATA,
        output wire [ 1:0 ]             S_AXI_RRESP,
        output wire                     S_AXI_RVALID,
        // -----------------------------------------------


        // AXI Strem Interface ---------------------------
        input wire                      AXIS_ACLK,
        input wire                      AXIS_ARESETN,
        // -----------------------------------------------


        // AXI Stream Master Interface -------------------
        input wire                      M_AXIS_TREADY,
        output wire [ 31:0 ]            M_AXIS_TDATA,
        output wire                     M_AXIS_TVALID,
        output wire [ 7:0 ]             M_AXIS_TSTRB,
        output wire                     M_AXIS_TLAST,
        // -----------------------------------------------


        // AXI Stream Slave Interface --------------------
        input wire [ 31:0 ]             S_AXIS_TDATA,
        input wire [ 7:0 ]              S_AXIS_TSTRB,
        input wire                      S_AXIS_TLAST,
        input wire                      S_AXIS_TVALID,
        output wire                     S_AXIS_TREADY
        // -----------------------------------------------

    );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 次元数可変
    // 32次元 -----------------
    // parameter DIM = 31;
    // -----------------------

    // 1024次元 ---------------
    parameter DIM = 1023;
    // -----------------------


    // 次元数可変
    // 32次元 -----------------
    // parameter WI = 0;
    // -----------------------

    // 1024次元 ---------------
    // parameter WI = 31;
    // -----------------------


    // コア数可変
    // 2コア -------------------
    parameter CORENUM = 2;
    // ------------------------


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    wire        get_v;
    wire        exec;
    wire        get_c;
    wire        communicate;
    wire        get_c_tmp;

    get_enable get_enable
               (

                   // in
                   .clk( AXIS_ACLK ),
                   .run( run ),
                   .com( com ),
                   .get_valid( S_AXIS_TVALID ),


                   // out
                   .get_ready( S_AXIS_TREADY ),
                   .get_v( get_v ),
                   .exec( exec ),
                   .get_c( get_c )

               );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 現時点のcounterの値
    wire [ DIM:0 ]      sign_bit;

    // コア数可変
    // 次元数可変
    // buffer_ctrl #( .DIM( 31 ), .CORENUM( 8 ) ) buffer_ctrl
    buffer_ctrl #( .DIM( 1023 ), .CORENUM( 2 ) ) buffer_ctrl
                (

                    // in
                    .clk( AXIS_ACLK ),
                    .rst( ~run ),
                    // 1コア
                    // .core_result_1( core_result ),
                    // コア数可変
                    .core_result_1( core_result[ 0 ] ),
                    .core_result_2( core_result[ 1 ] ),
                    // .core_result_3( core_result[ 2 ] ),
                    // .core_result_4( core_result[ 3 ] ),
                    // .core_result_5( core_result[ 4 ] ),
                    // .core_result_6( core_result[ 5 ] ),
                    // .core_result_7( core_result[ 6 ] ),
                    // .core_result_8( core_result[ 7 ] ),
                    // .core_result_9( core_result[ 8 ] ),
                    // .core_result_10( core_result[ 9 ] ),
                    // .core_result_11( core_result[ 10 ] ),
                    // .core_result_12( core_result[ 11 ] ),
                    // .core_result_13( core_result[ 12 ] ),
                    // .core_result_14( core_result[ 13 ] ),
                    // .core_result_15( core_result[ 14 ] ),
                    // .core_result_16( core_result[ 15 ] ),
                    // .core_result_17( core_result[ 16 ] ),
                    // .core_result_18( core_result[ 17 ] ),
                    // .core_result_19( core_result[ 18 ] ),
                    // .core_result_20( core_result[ 19 ] ),
                    // .core_result_21( core_result[ 20 ] ),
                    // .core_result_22( core_result[ 21 ] ),
                    // .core_result_23( core_result[ 22 ] ),
                    // .core_result_24( core_result[ 23 ] ),
                    // .core_result_25( core_result[ 24 ] ),
                    // .core_result_26( core_result[ 25 ] ),
                    // .core_result_27( core_result[ 26 ] ),
                    // .core_result_28( core_result[ 27 ] ),
                    // .core_result_29( core_result[ 28 ] ),
                    // .core_result_30( core_result[ 29 ] ),
                    // .core_result_31( core_result[ 30 ] ),
                    // .core_result_32( core_result[ 31 ] ),
                    // 1コア
                    .store( store[ CORENUM-1:0 ] ),
                    .store_flag( store_flag ),
                    .stream_v( stream_v ),
                    .stream_i( stream_i[ 4:0 ] ),


                    // out
                    // バス幅可変
                    .stream_d( M_AXIS_TDATA[ 31:0 ] ),
                    .sign_bit( sign_bit[ DIM:0 ] )

                );



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    // 計算結果を送るタイミングの１クロック前に立つ
    // counterの値(sign_bit)をM_AXIS_TDATAに格納するタイミングを知らせる役割
    wire                stream_v;

    wire [ 4:0 ]          stream_i;

    // コア数可変
    stream_ctrl #( .CORENUM( 2 ) ) stream_ctrl
                (

                    // in
                    .clk( AXIS_ACLK ),
                    .rst( ~run ),
                    // 1コア
                    .last( last ),
                    // .last( last ),
                    .dst_ready( M_AXIS_TREADY ),


                    // out
                    .dst_valid( M_AXIS_TVALID ),
                    .dst_last( M_AXIS_TLAST ),
                    .stream_v( stream_v ),
                    .stream_i( stream_i[ 4:0 ] )

                );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 各コアのストア信号
    wire [ CORENUM-1:0 ]            store;
    wire                            store_flag;

    assign store_flag = ( store != 0 ) ? 1'b1 : 1'b0;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 各コアの演算結果
    wire [ DIM:0 ]                      core_result [ 0:CORENUM-1 ];

    // 各コアでエンコーディング
    generate

        genvar      i;

        for ( i = 1; i < CORENUM; i = i + 1 ) begin

            // 次元数可変
            // スレッド数可変
            // core #( .DIM( 31 ), .THREADS( 5 ) ) core
            core #( .DIM( 1023 ), .THREADS( 5 ), .WI( 31 ) ) core
                 (

                     // in
                     .clk( AXIS_ACLK ),
                     .run( run ),
                     .com( com ),
                     .get_v( get_v ),
                     .get_c( get_c ),
                     // 16bit命令
                     .get_d_tmp( S_AXIS_TDATA[ 15+16*i:16*i ] ),
                     .get_d_all( S_AXIS_TDATA[ 31:0 ] ),
                     .exec( exec ),


                     // out
                     // 1コア
                     .store( store[ i ] ),
                     //  .store( store ),
                     // 1コア
                     .core_result( core_result[ i ] )
                     //  .core_result( core_result ),
                 );

        end

    endgenerate


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 各コアのラスト信号
    wire                            last;


    central_core #( .DIM( 1023 ), .THREADS( 5 ), .WI( 31 ) ) central_core
                 (

                     // in
                     .clk( AXIS_ACLK ),
                     .run( run ),
                     .com( com ),
                     .get_v( get_v ),
                     .get_c( get_c ),
                     // 16bit命令
                     .get_d( S_AXIS_TDATA[ 15:0 ] ),
                     .get_d_all( S_AXIS_TDATA[ 31:0 ] ),
                     .exec( exec ),


                     // out
                     // 1コア
                     .store( store[ 0 ] ),
                     //  .store( store ),
                     // 1コア
                     .core_result( core_result[ 0 ] ),
                     //  .core_result( core_result ),
                     // 1コア
                     .last( last )
                     //  .last( last)

                 );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    assign M_AXIS_TSTRB = 8'hff;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // AXI Lite Slave State --------------

    reg [ 3:0 ]           state;

    wire INI = ( state == 4'b0000 );

    wire AW  = ( state == 4'b0001 );

    wire W   = ( state == 4'b0010 );

    wire AWW = ( state == 4'b0011 );

    wire AR1 = ( state == 4'b0100 );

    wire AR2 = ( state == 4'b1000 );

    // -----------------------------------


    // アドレスは4の倍数で指定

    // UIOの書き込み先アドレス
    reg [ 11:2 ]          write_addr;

    // UIOの書き込みデータ
    reg [ 31:0 ]          write_data;

    // UIOの読み込み先アドレス
    reg [ 11:2 ]          read_addr;


    //================================================================


    assign S_AXI_BRESP   = 2'b00;

    assign S_AXI_RRESP   = 2'b00;

    assign S_AXI_AWREADY = INI | W;

    assign S_AXI_WREADY  = INI | AW;

    assign S_AXI_ARREADY = INI;

    assign S_AXI_BVALID  = AWW;

    assign S_AXI_RVALID  = AR2;


    always @( posedge S_AXI_ACLK ) begin

        // リセット
        if ( ~S_AXI_ARESETN ) begin

            state <= 4'b0000;
            write_addr <= 0;
            write_data <= 0;
            read_addr <= 0;

        end

        // INI
        else if ( INI ) begin

            if ( S_AXI_AWVALID & S_AXI_WVALID ) begin

                // go AWW
                state <= 4'b0011;
                write_addr[ 11:2 ] <= S_AXI_AWADDR[ 11:2 ];
                write_data[ 1:0 ] <= S_AXI_WDATA[ 1:0 ];

            end

            else if ( S_AXI_AWVALID ) begin

                // go AW
                state <= 4'b0001;
                write_addr[ 11:2 ] <= S_AXI_AWADDR[ 11:2 ];

            end

            else if ( S_AXI_WVALID ) begin

                // go W
                state <= 4'b0010;
                write_data[ 1:0 ] <= S_AXI_WDATA[ 1:0 ];

            end

            else if ( S_AXI_ARVALID ) begin

                // go AR1
                state <= 4'b0100;
                read_addr[ 11:2 ] <= S_AXI_ARADDR[ 11:2 ];

            end

        end

        // AW
        else if ( AW ) begin

            if ( S_AXI_WVALID ) begin

                // go AWW
                state <= 4'b0011;
                write_data[ 1:0 ] <= S_AXI_WDATA[ 1:0 ];

            end

        end

        // W
        else if ( W ) begin

            if ( S_AXI_AWVALID ) begin

                // go AWW
                state <= 4'b0011;
                write_addr[ 11:2 ] <= S_AXI_AWADDR[ 11:2 ];

            end

        end

        // AWW
        else if ( AWW ) begin

            if ( S_AXI_BREADY ) begin

                // go INI
                state <= 4'b0000;

            end

        end

        // AR1
        else if ( AR1 ) begin

            // go AR2
            state <= 4'b1000;

        end

        // AR2
        else if ( AR2 ) begin

            if ( S_AXI_RREADY ) begin

                // go INI
                state <= 4'b0000;

            end

        end

    end


    //================================================================


    // 書き込み可能フラグ
    wire    register_wflag;

    assign register_wflag = AWW & ( write_addr[ 11:10 ] == 2'b00 );


    // 読み込み可能フラグ
    wire    register_rflag;

    assign register_rflag = AR1 & ( read_addr[ 11:10 ] == 2'b00 );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // アクセラレータのモード
    // run ... アクセラレータ実行モード
    // com ... アクセラレータ準備モード　（ランダムなハイパーベクトルをitem_memoryに格納）

    // run ... 書き込みモードで2を代入
    // com ... 書き込みモードで１を代入
    reg                 com;
    reg                 run;

    //================================================================


    // UIO Register Write (書き込みモード)
    always @( posedge S_AXI_ACLK ) begin

        // 初期化
        if ( ~S_AXI_ARESETN ) begin

            { com, run } <= 2'b00;

        end

        // 書き込み
        else if ( register_wflag ) begin

            // 4の倍数に揃えるため、下位2bitは強制的に０
            case ( { write_addr[ 9:2 ], 2'b00 } )

                // アドレス０
                10'd00:
                    { com, run } <= write_data[ 1:0 ];

                // 上記アドレス以外は何もしない
                default:
                    ;

            endcase

        end

    end


    //================================================================


    // UIO Register Read (読み込みモード)
    always @( posedge S_AXI_ACLK ) begin

        // 読み込み
        if ( register_rflag ) begin

            // 4の倍数に揃えるため、下位2bitは強制的に０
            case ( { read_addr[ 9:2 ], 2'b00 } )

                // アドレス０
                10'h00:
                    S_AXI_RDATA[ 1:0 ] <= { com, run };

                // 上記アドレス以外は何もしない
                default:
                    S_AXI_RDATA <= 0;

            endcase

        end

    end


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
