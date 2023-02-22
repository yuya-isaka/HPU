
`default_nettype none


module permute
    #(

         // ハイパーベクトルの次元数
         parameter DIM = 1023

     )
     (

         // in
         input wire                     clk,
         input wire                     exec,
         input wire [ DIM:0 ]           data,
         input wire [ 9:0 ]             permute_num,


         // out
         output reg [ DIM:0 ]          result

     );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // スレッド数可変

    // STAGE0 ---------------------------------------
    logic [ DIM:0 ]       stage0;
    // ----------------------------------------------

    // STAGE1 ---------------------------------------
    logic [ DIM:0 ]       stage1;
    // ----------------------------------------------

    // STAGE2 ---------------------------------------
    logic [ DIM:0 ]       stage2;
    // ----------------------------------------------

    // STAGE3 ---------------------------------------
    logic [ DIM:0 ]       stage3;
    // ----------------------------------------------

    // STAGE4 ---------------------------------------
    logic [ DIM:0 ]       stage4;
    // ----------------------------------------------


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // スレッド数可変
    // 時分割実行
    always_comb begin

                    stage0 = 0;
                    stage1 = 0;
                    stage2 = 0;
                    stage3 = 0;
                    stage3 = 0;
                    stage4 = 0;

                    if ( exec ) begin

                        //stage 0, shift 0 or 1 or 512 or 513bit -----------------------------
                        if( permute_num[ 0 ] & permute_num[ 9 ] ) begin

                            stage0 = { data[ 512:0 ], data[ DIM:513 ] };

                        end

                        else if ( permute_num[ 0 ] ) begin

                            stage0 = { data[ 0 ], data[ DIM:1 ] };

                        end

                        else if ( permute_num[ 9 ] ) begin

                            stage0 = { data[ 511:0 ], data[ DIM:512 ] };

                        end

                        else begin

                            stage0 = data;

                        end
                        //-------------------------------------------------------


                        //stage 1, shift 0 or 2 or 256 or 258bits ----------------------------
                        if( permute_num[ 1 ] & permute_num[ 8 ] ) begin

                            stage1 = { stage0[ 257:0 ], stage0[ DIM:258 ] };

                        end

                        else if ( permute_num[ 1 ] ) begin

                            stage1 = { stage0[ 1:0 ], stage0[ DIM:2 ] };

                        end

                        else if ( permute_num[ 8 ] ) begin

                            stage1 = { stage0[ 255:0 ], stage0[ DIM:256 ] };

                        end

                        else begin

                            stage1 = stage0;

                        end
                        //------------------------------------------------------


                        //stage 2, shift 0 or 4 or 128 or 132bits ----------------------------

                        if( permute_num[ 2 ] & permute_num[ 7 ] ) begin

                            stage2 = { stage1[ 131:0 ], stage1[ DIM:130 ] };

                        end

                        else if ( permute_num[ 2 ] ) begin

                            stage2 = { stage1[ 3:0 ], stage1[ DIM:4 ] };

                        end

                        else if ( permute_num[ 7 ] ) begin

                            stage2 = { stage1[ 127:0 ], stage1[ DIM:128 ] };

                        end

                        else begin

                            stage2 = stage1;

                        end
                        //------------------------------------------------------


                        //stage 3, shift 0 or 8 or 64 or 72bits ----------------------------
                        if( permute_num[ 3 ] & permute_num[ 6 ] ) begin

                            stage3 = { stage2[ 71:0 ], stage2[ DIM:72 ] };

                        end

                        else if ( permute_num[ 3 ] ) begin

                            stage3 = { stage2[ 7:0 ], stage2[ DIM:8 ] };

                        end

                        else if ( permute_num[ 6 ] ) begin

                            stage3 = { stage2[ 63:0 ], stage2[ DIM:64 ] };

                        end

                        else begin

                            stage3 = stage2;

                        end
                        //------------------------------------------------------


                        //stage 4, shift 0 or 16 or 32 or 48bits ----------------------------
                        if( permute_num[ 4 ] & permute_num[ 5 ] ) begin

                            stage4 = { stage3[ 47:0 ], stage3[ DIM:48 ] };

                        end

                        else if ( permute_num[ 4 ] ) begin

                            stage4 = { stage3[ 15:0 ], stage3[ DIM:16 ] };

                        end

                        else if ( permute_num[ 5 ] ) begin

                            stage4 = { stage3[ 31:0 ], stage3[ DIM:32 ] };

                        end

                        else begin

                            stage4 = stage3;

                        end
                        //------------------------------------------------------

                    end

                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // スレッド数可変
    // assign result = stage4;

    always_ff @( posedge clk) begin


                  if ( exec) begin
                      result <= stage4;
                  end

              end;


endmodule


`default_nettype wire
