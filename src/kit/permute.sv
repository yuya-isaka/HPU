
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
         output wire [ DIM:0 ]          result

     );


    // スレッド数可変

    // STAGE0 ---------------------------------------
    reg [ DIM:0 ]       stage0;
    wire [ 9:0 ]        stage0_permute_num;
    assign stage0_permute_num[ 9:0 ] = permute_num[ 9:0 ];
    // ----------------------------------------------

    // STAGE1 ---------------------------------------
    reg [ DIM:0 ]       stage1;
    reg [ 8:0 ]         stage1_permute_num;
    // ----------------------------------------------

    // STAGE2 ---------------------------------------
    reg [ DIM:0 ]       stage2;
    reg [ 7:0 ]         stage2_permute_num;
    // ----------------------------------------------

    // STAGE3 ---------------------------------------
    reg [ DIM:0 ]       stage3;
    reg [ 6:0 ]         stage3_permute_num;
    // ----------------------------------------------

    // STAGE4 ---------------------------------------
    reg [ DIM:0 ]       stage4;
    reg [ 5:0 ]         stage4_permute_num;
    // ----------------------------------------------

    // STAGE5 ---------------------------------------
    reg [ DIM:0 ]       stage5;
    reg [ 4:0 ]         stage5_permute_num;
    // ----------------------------------------------

    // STAGE6 ---------------------------------------
    reg [ DIM:0 ]       stage6;
    reg [ 3:0 ]         stage6_permute_num;
    // ----------------------------------------------

    // STAGE7 ---------------------------------------
    reg [ DIM:0 ]       stage7;
    reg [ 2:0 ]         stage7_permute_num;
    // ----------------------------------------------

    // STAGE8 ---------------------------------------
    reg [ DIM:0 ]       stage8;
    reg [ 1:0 ]         stage8_permute_num;
    // ----------------------------------------------

    // STAGE9 ---------------------------------------
    reg [ DIM:0 ]       stage9;
    reg                 stage9_permute_num;
    // ----------------------------------------------

    // スレッド数可変
    always_ff @( posedge clk ) begin

                  if ( exec) begin

                      stage1_permute_num[ 8:0 ] <= stage0_permute_num[ 9:1 ];

                      stage2_permute_num[ 7:0 ] <= stage1_permute_num[ 8:1 ];

                      stage3_permute_num[ 6:0 ] <= stage2_permute_num[ 7:1 ];

                      stage4_permute_num[ 5:0 ] <= stage3_permute_num[ 6:1 ];

                      stage5_permute_num[ 4:0 ] <= stage4_permute_num[ 5:1 ];

                      stage6_permute_num[ 3:0 ] <= stage5_permute_num[ 4:1 ];

                      stage7_permute_num[ 2:0 ] <= stage6_permute_num[ 3:1 ];

                      stage8_permute_num[ 1:0 ] <= stage7_permute_num[ 2:1 ];

                      stage9_permute_num <= stage8_permute_num[ 1 ];

                  end

              end;


    // スレッド数可変
    always_ff @( posedge clk ) begin

                  if ( exec ) begin

                      //stage 0, shift 0 or 1 bit -----------------------------
                      if( stage0_permute_num[ 0 ] ) begin
                          stage0 <= { data[ 0 ], data[ DIM:1 ] };
                      end
                      else begin
                          stage0 <= data;
                      end
                      //-------------------------------------------------------


                      //stage 1, shift 0 or 2 bits ----------------------------
                      if( stage1_permute_num[ 0 ] ) begin
                          stage1 <= { stage0[ 1:0 ], stage0[ DIM:2 ] };
                      end
                      else begin
                          stage1 <= stage0;
                      end
                      //------------------------------------------------------


                      //stage 2, shift 0 or 4 bits ----------------------------
                      if( stage2_permute_num[ 0 ] ) begin
                          stage2 <= { stage1[ 3:0 ], stage1[ DIM:4 ] };
                      end
                      else begin
                          stage2 <= stage1;
                      end
                      //------------------------------------------------------


                      //stage 3, shift 0 or 8 bits ----------------------------
                      if( stage3_permute_num[ 0 ] ) begin
                          stage3 <= { stage2[ 7:0 ], stage2[ DIM:8 ] };
                      end
                      else begin
                          stage3 <= stage2;
                      end
                      //------------------------------------------------------


                      //stage 4, shift 0 or 16 bits ----------------------------
                      if( stage4_permute_num[ 0 ] ) begin
                          stage4 <= { stage3[ 15:0 ], stage3[ DIM:16 ] };
                      end
                      else begin
                          stage4 <= stage3;
                      end
                      //------------------------------------------------------


                      //stage 5, shift 0 or 32 bits ----------------------------
                      if( stage5_permute_num[ 0 ] ) begin
                          stage5 <= { stage4[ 31:0 ], stage4[ DIM:32 ] };
                      end
                      else begin
                          stage5 <= stage4;
                      end
                      //------------------------------------------------------


                      //stage 6, shift 0 or 64 bits ----------------------------
                      if( stage6_permute_num[ 0 ] ) begin
                          stage6 <= { stage5[ 63:0 ], stage5[ DIM:64 ] };
                      end
                      else begin
                          stage6 <= stage5;
                      end
                      //------------------------------------------------------


                      //stage 7, shift 0 or 128 bits ----------------------------
                      if( stage7_permute_num[ 0 ] ) begin
                          stage7 <= { stage6[ 127:0 ], stage6[ DIM:128 ] };
                      end
                      else begin
                          stage7 <= stage6;
                      end
                      //------------------------------------------------------


                      //stage 8, shift 0 or 256 bits ----------------------------
                      if( stage8_permute_num[ 0 ] ) begin
                          stage8 <= { stage7[ 255:0 ], stage7[ DIM:256 ] };
                      end
                      else begin
                          stage8 <= stage7;
                      end
                      //------------------------------------------------------


                      //stage 9, shift 0 or 512 bits ----------------------------
                      if( stage9_permute_num ) begin
                          stage9 <= { stage8[ 511:0 ], stage8[ DIM:512 ] };
                      end
                      else begin
                          stage9 <= stage8;
                      end
                      //------------------------------------------------------


                  end

              end;


    // スレッド数可変
    assign result = stage9;


endmodule


`default_nettype wire
