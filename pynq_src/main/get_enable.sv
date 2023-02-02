
`default_nettype none


module get_enable
    (

        // in
        input wire                  clk,
        input wire                  run,
        input wire                  com,
        input wire                  get_valid,


        // out
        output wire                 get_ready,
        output logic                get_v,
        output logic                exec,
        output logic                get_c

    );


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // データ受信の次から演算を開始
    always_ff @( posedge clk ) begin

                  if ( ~run ) begin

                      exec <= 1'b0;

                  end

                  else begin

                      exec <= get_v;

                  end

              end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 現状、アクセラレータ側で受信を拒否することはない
    assign get_ready = 1'b1;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 受信設定 run
    always_comb begin

                    get_v = 1'b0;

                    if ( get_valid & get_ready & run & ~com ) begin

                        get_v = 1'b1;

                    end

                end;


    // 受信設定 com
    always_comb begin

                    get_c = 1'b0;

                    if ( get_valid & get_ready & com ) begin

                        get_c = 1'b1;

                    end

                end;


endmodule


`default_nettype wire
