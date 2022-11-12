
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

        // AXI Stream Master Interface -------------------
        input wire                      M_AXIS_TREADY,
        output wire [ 1023:0 ]          M_AXIS_TDATA,
        output wire                     M_AXIS_TVALID,
        output wire [ 7:0 ]             M_AXIS_TSTRB,
        output wire                     M_AXIS_TLAST,
        // -----------------------------------------------

        // AXI Stream Slave Interface --------------------
        input wire [ 1023:0 ]           S_AXIS_TDATA,
        input wire [ 7:0 ]              S_AXIS_TSTRB,
        input wire                      S_AXIS_TLAST,
        input wire                      S_AXIS_TVALID,
        output wire                     S_AXIS_TREADY
        // -----------------------------------------------

    );


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
    parameter WI = 31;
    // -----------------------


    // コア数可変
    // 2コア -------------------
    parameter CORENUM = 12;
    // ------------------------


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    wire        get_v;
    wire        exec;

    get_enable get_enable
               (

                   // in
                   .clk( AXIS_ACLK ),
                   .gen( gen ),
                   .run( run ),
                   .get_valid( S_AXIS_TVALID ),


                   // out
                   .get_ready( S_AXIS_TREADY ),
                   .get_v( get_v ),
                   .exec( exec )

               );


    // 現時点のcounterの値
    wire [ DIM:0 ]      sign_bit;

    // コア数可変
    // 次元数可変
    // buffer_ctrl #( .DIM( 31 ), .CORENUM( 16 ) ) buffer_ctrl
    buffer_ctrl #( .DIM( 1023 ), .CORENUM( 12 ) ) buffer_ctrl
                (

                    // in
                    .clk( AXIS_ACLK ),
                    .rst( ~run ),
                    // 1コア
                    // .core_result_1( core_result ),
                    // コア数可変
                    .core_result_1( core_result[ 0 ] ),
                    .core_result_2( core_result[ 1 ] ),
                    .core_result_3( core_result[ 2 ] ),
                    .core_result_4( core_result[ 3 ] ),
                    .core_result_5( core_result[ 4 ] ),
                    .core_result_6( core_result[ 5 ] ),
                    .core_result_7( core_result[ 6 ] ),
                    .core_result_8( core_result[ 7 ] ),
                    .core_result_9( core_result[ 8 ] ),
                    .core_result_10( core_result[ 9 ] ),
                    .core_result_11( core_result[ 10 ] ),
                    .core_result_12( core_result[ 11 ] ),
                    // .core_result_13( core_result[ 12 ] ),
                    // .core_result_14( core_result[ 13 ] ),
                    // .core_result_15( core_result[ 14 ] ),
                    // .core_result_16( core_result[ 15 ] ),
                    // 1コア
                    .store( store[ CORENUM-1:0 ] ),
                    // .store( store ),
                    .stream_v( stream_v ),


                    // out
                    // バス幅可変
                    .stream_d( M_AXIS_TDATA[ 1023:0 ] ),
                    .sign_bit( sign_bit[ DIM:0 ] )

                );



    // 計算結果を送るタイミングの１クロック前に立つ
    // counterの値(sign_bit)をM_AXIS_TDATAに格納するタイミングを知らせる役割
    wire              stream_v;

    // コア数可変
    stream_ctrl #( .CORENUM( 12 ) ) stream_ctrl
                (

                    // in
                    .clk( AXIS_ACLK ),
                    .rst( ~run ),
                    // 1コア
                    .last( last[ CORENUM-1:0 ] ),
                    // .last( last ),
                    .get_v( get_v ),
                    .dst_ready( M_AXIS_TREADY ),


                    // out
                    .dst_valid( M_AXIS_TVALID ),
                    .dst_last( M_AXIS_TLAST ),
                    .stream_v( stream_v)

                );


    // ================================================== ランダム関連 ==============================================================
    // ランダム関連はgen信号によって駆動
    // ============================================================================================================================


    // 32bitのランダム値の生成数
    // (1024bitのハイパーベクトルが生成される場合、32個生成）
    // (現状最大で32個なので、5bit幅)
    reg [ 4:0 ]       item_a_tmp;

    always @( posedge AXIS_ACLK ) begin

        if ( ~gen ) begin
            item_a_tmp <= 0;
        end

        else begin

            if ( item_a_tmp == WI ) begin
                item_a_tmp <= 5'd0;
            end

            else begin
                item_a_tmp <= item_a_tmp + 5'd1;
            end
        end
    end


    // 各コアのitem_memoryにランダム値を格納するタイミング
    // item_a_tmpの値から、更新タイミングを決定
    reg             update_item;

    always @( posedge AXIS_ACLK ) begin

        if ( ~gen ) begin
            update_item <= 0;
        end

        else if ( item_a_tmp == WI ) begin
            update_item <= 1'd1;
        end

        else begin
            update_item <= 0;
        end
    end


    // 各コアのitem_memoryのアドレス
    // (現状最大で1024個なので、10bit指定)
    reg [ 9:0 ]      item_a;

    always @( posedge AXIS_ACLK ) begin

        if ( ~gen ) begin
            item_a <= 0;
        end

        else if ( update_item ) begin
            item_a <= item_a + 10'd1;
        end
    end


    // xorshiftモジュールから生成される32bitのランダム値
    wire [ 31:0 ]         rand_num_tmp;

    xorshift prng
             (

                 // in
                 .clk( AXIS_ACLK ),
                 .gen( gen ),


                 // out
                 .rand_num( rand_num_tmp[ 31:0 ] )

             );


    // xorshiftから生成されたランダム値(rand_num_tmp)の格納先
    // (ハイパーベクトル次元数が1024なら、31回別々に格納する)
    reg [ DIM:0 ]       rand_num;

    always @( posedge AXIS_ACLK ) begin

        if ( ~gen ) begin
            rand_num <= 0;
        end

        // 次元数可変
        else if ( item_a_tmp == 0 ) begin
            rand_num[ 31:0 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 1 ) begin
            rand_num[ 63:32 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 2 ) begin
            rand_num[ 95:64 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 3 ) begin
            rand_num[ 127:96 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 4 ) begin
            rand_num[ 159:128 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 5 ) begin
            rand_num[ 191:160 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 6 ) begin
            rand_num[ 223:192 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 7 ) begin
            rand_num[ 255:224 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 8 ) begin
            rand_num[ 287:256 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 9 ) begin
            rand_num[ 319:288 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 10 ) begin
            rand_num[ 351:320 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 11 ) begin
            rand_num[ 383:352 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 12 ) begin
            rand_num[ 415:384 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 13 ) begin
            rand_num[ 447:416 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 14 ) begin
            rand_num[ 479:448 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 15 ) begin
            rand_num[ 511:480 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 16 ) begin
            rand_num[ 543:512 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 17 ) begin
            rand_num[ 575:544 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 18 ) begin
            rand_num[ 607:576 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 19 ) begin
            rand_num[ 639:608 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 20 ) begin
            rand_num[ 671:640 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 21 ) begin
            rand_num[ 703:672 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 22 ) begin
            rand_num[ 735:704 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 23 ) begin
            rand_num[ 767:736 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 24 ) begin
            rand_num[ 799:768 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 25 ) begin
            rand_num[ 831:800 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 26 ) begin
            rand_num[ 863:832 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 27 ) begin
            rand_num[ 895:864 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 28 ) begin
            rand_num[ 927:896 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 29 ) begin
            rand_num[ 959:928 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 30 ) begin
            rand_num[ 991:960 ] <= rand_num_tmp;
        end

        else if ( item_a_tmp == 31 ) begin
            rand_num[ 1023:992 ] <= rand_num_tmp;
        end
    end


    // ============================================================================================================================
    // ============================================================================================================================


    // 各コアのストア信号
    // 1コア
    wire [ CORENUM-1:0 ]              store;
    // wire                            store;

    // 各コアの演算結果
    // 1コア
    wire [ DIM:0 ]                    core_result [ 0:CORENUM-1 ];
    // wire [DIM:0]                    core_result;

    // 各コアのラスト信号
    // 1コア
    wire [ CORENUM-1:0 ]              last;
    // wire                            last;

    // 各コアでエンコーディング
    generate

        genvar      i;

        for ( i = 0; i < CORENUM; i = i + 1 ) begin

            // 次元数可変
            // core #( .DIM( 31 ) ) core
            core #( .DIM( 1023 ) ) core
                 (

                     // in
                     .clk( AXIS_ACLK ),
                     .run( run ),
                     .gen( gen ),
                     .update_item( update_item ),
                     .item_a( item_a[ 9:0 ] ),
                     .rand_num( rand_num[ DIM:0 ] ),
                     .get_v( get_v ),
                     // 16bit命令
                     .get_d( S_AXIS_TDATA[ 15+16*i:16*i ] ),
                     .exec( exec ),
                     .sign_bit( sign_bit[ DIM:0] ),


                     // out
                     // 1コア
                     .store( store[ i ] ),
                     //  .store( store ),
                     // 1コア
                     .core_result( core_result[ i ] ),
                     //  .core_result( core_result ),
                     // 1コア
                     .last( last[ i ] )
                     //  .last( last)

                 );
        end
    endgenerate


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
                write_data <= S_AXI_WDATA;
            end

            else if ( S_AXI_AWVALID ) begin
                // go AW
                state <= 4'b0001;
                write_addr[ 11:2 ] <= S_AXI_AWADDR[ 11:2 ];
            end

            else if ( S_AXI_WVALID ) begin
                // go W
                state <= 4'b0010;
                write_data <= S_AXI_WDATA;
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
                write_data <= S_AXI_WDATA;
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
    wire            register_wflag;

    assign register_wflag = AWW & ( write_addr[ 11:10 ] == 2'b00 );


    // 読み込み可能フラグ
    wire            register_rflag;

    assign register_rflag = AR1 & ( read_addr[ 11:10 ] == 2'b00 );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // アクセラレータのモード
    // gen ... アクセラレータ準備モード　（ランダムなハイパーベクトルをitem_memoryに格納）
    // run ... アクセラレータ実行モード

    // gen ... 書き込みモードで１を代入
    // run ... 書き込みモードで2を代入
    reg             gen, run;

    // item_memoryに格納するハイパーベクトルの数
    // (現状の最大値は1023)
    reg [ 9:0 ]       item_memory_num;


    //================================================================


    // UIO Register Write (書き込みモード)
    always @( posedge S_AXI_ACLK ) begin

        // 初期化
        if ( ~S_AXI_ARESETN ) begin
            { run, gen } <= 2'b00;
            item_memory_num <= 10'd0;
        end

        // 書き込み
        else if ( register_wflag ) begin

            // 4の倍数に揃えるため、下位2bitは強制的に０
            case ( { write_addr[ 9:2 ], 2'b00 } )

                // アドレス０
                10'd00:
                    { run, gen } <= write_data[ 1:0 ];

                // アドレス４
                10'd04:
                    // 最大1023
                    item_memory_num[ 9:0 ] <= write_data[ 9:0 ];

                // 上記アドレス以外は何もしない
                default:
                    ;
            endcase

        end

        // アクセラレータ準備モード終了
        // (item_memory_num数のハイパーベクトルを生成して終了)
        // (現状S_AXI_ACLK, S_AXIS_ACLKが同じ周波数を用いているため問題ない)
        else if ( gen & item_a == item_memory_num & update_item ) begin
            gen <= 1'b0;
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
                    S_AXI_RDATA[ 1:0 ] <= { run, gen };

                // アドレス４
                10'd04:
                    S_AXI_RDATA[ 9:0 ] <= item_memory_num[ 9:0 ];

                // 上記アドレス以外は何もしない
                default:
                    S_AXI_RDATA <= 0;
            endcase

        end
    end


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule


`default_nettype wire
