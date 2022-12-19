
`default_nettype none


module pop_count
    #(

         // ハイパーベクトルの次元数
         parameter DIM = 1023

     )
     (

         // in
         input wire                     clk,
         input wire                     exec,
         input wire [ DIM:0 ]           data,


         // out
         output wire [ 9:0 ]          result

     );






endmodule


`default_nettype wire
