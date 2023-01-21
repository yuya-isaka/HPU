`default_nettype none


module xorshift
    (

        // in
        input wire                          clk,
        input wire                          gen,
        input wire                          reset_item,


        // out
        output logic [ 31:0 ]               rand_num

    );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // レジスタ４つ
    reg [ 31:0 ]      x;
    reg [ 31:0 ]      y;
    reg [ 31:0 ]      z;
    reg [ 31:0 ]      w;


    // RNG回路
    always_ff @( posedge clk ) begin

                  // ランダム生成のフラグが立ったら、再び初期値を設定
                  if ( ~reset_item ) begin

                      x <= 123456789;
                      y <= 362436069;
                      z <= 521288629;
                      w <= 88675123;

                  end

                  else if ( gen ) begin

                      x <= y;
                      y <= z;
                      z <= w;
                      w <= ( w ^ ( w >> 19 ) ) ^ ( ( x ^ ( x << 11 ) ) ^ ( ( x ^ ( x << 11 ) ) >> 8 ) );

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 結果出力
    assign rand_num = w;


endmodule


`default_nettype wire
