
`default_nettype none


module permute
    #(

         // ハイパーベクトルの次元数
         parameter DIM = 1023
     )
     (

         // in
         input wire clk,
         input wire [ DIM:0 ] data,
         input wire [ 9:0 ] permute_num,

         // out
         output wire [ DIM:0 ] result

     );


    // スレッド数可変
    reg [ DIM:0 ] stage0;
    wire [ 9:0 ] stage0_permute_num;
    assign stage0_permute_num = permute_num;

    reg [ DIM:0 ] stage1;
    reg [ 9:0 ] stage1_permute_num;

    reg [ DIM:0 ] stage2;
    reg [ 9:0 ] stage2_permute_num;

    reg [ DIM:0 ] stage3;
    reg [ 9:0 ] stage3_permute_num;

    reg [ DIM:0 ] stage4;
    reg [ 9:0 ] stage4_permute_num;

    // スレッド数可変
    always_ff @( posedge clk ) begin
                  stage1_permute_num[ 9:0 ] <= stage0_permute_num[ 9:0 ];
                  stage2_permute_num[ 9:0 ] <= stage1_permute_num[ 9:0 ];
                  stage3_permute_num[ 9:0 ] <= stage2_permute_num[ 9:0 ];
                  stage4_permute_num[ 9:0 ] <= stage3_permute_num[ 9:0 ];
              end;

    // スレッド数可変
    always_ff @( posedge clk ) begin
                  //stage 0, shift 0 or 1 bit
                  if( stage0_permute_num[ 0 ] ) begin
                      stage0 <= { data[ 0 ], data[ DIM:1 ] };
                  end
                  else begin
                      stage0 <= data;
                  end

                  //stage 1, shift 0 or 2 bits
                  if( stage1_permute_num[ 1 ] ) begin
                      stage1 <= { stage0[ 1:0 ], stage0[ DIM:2 ] };
                  end
                  else begin
                      stage1 <= stage0;
                  end

                  //stage 2, shift 0 or 4 bits
                  if( stage2_permute_num[ 2 ] ) begin
                      stage2 <= { stage1[ 3:0 ], stage1[ DIM:4 ] };
                  end
                  else begin
                      stage2 <= stage1;
                  end

                  //stage 3, shift 0 or 8 bits
                  if( stage3_permute_num[ 3 ] ) begin
                      stage3 <= { stage2[ 7:0 ], stage2[ DIM:8 ] };
                  end
                  else begin
                      stage3 <= stage2;
                  end

                  //stage 4, shift 0 or 16 bits
                  if( stage4_permute_num[ 4 ] ) begin
                      stage4 <= { stage3[ 15:0 ], stage3[ DIM:16 ] };
                  end
                  else begin
                      stage4 <= stage3;
                  end
              end;

    assign result = stage4;

endmodule


`default_nettype wire
