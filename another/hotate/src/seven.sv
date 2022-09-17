`default_nettype none

module seven (
	clk,
	rst,
	data_seg,
	anode,
	seg
);

	// ポート
	input wire clk, rst;
	input wire [31:0] data_seg;
	output logic [3:0] anode; 	// wire
	output logic [6:0] seg; 	// wire

	// デコード関数（4bitのバイナリ → 7bitのコード（どこを光らせるか）
	// 0のところが光る
   	function [6:0] decode (input [31:0] binary);
   	   begin
   	      case (binary[3:0])
   	         4'h0: decode = 7'b1000000; // 0
   	         4'h1: decode = 7'b1111001; // 1
   	         4'h2: decode = 7'b0100100;
   	         4'h3: decode = 7'b0110000;
   	         4'h4: decode = 7'b0011001;
   	         4'h5: decode = 7'b0010010;
   	         4'h6: decode = 7'b0000010;
   	         4'h7: decode = 7'b1011000;
   	         4'h8: decode = 7'b0000000;
   	         4'h9: decode = 7'b0010000;
   	         4'ha: decode = 7'b0001000;
   	         4'hb: decode = 7'b0000011;
   	         4'hc: decode = 7'b1000110;
   	         4'hd: decode = 7'b0100001;
   	         4'he: decode = 7'b0000110; // E
   	         4'hf: decode = 7'b0001110; // F
   	      endcase
   	   end
   	endfunction

	// regだからalways_ffで更新する
   	reg [31:0] seg_counter;
	initial begin
		seg_counter = 32'd0;
	end

	// カウンターを高速に4回切り替えるための動作
   	always_ff @(posedge clk) begin
   		if (rst) begin
			seg_counter <= 32'd0;
		end
   	   	else if (seg_counter == 32'd400000) begin
			seg_counter <= 32'd0;
		end
   	   	else begin
			seg_counter <= seg_counter + 32'd1;
		end
   	end

	// カウンターの値に従い、4回に分けて、各７segの値を更新
   	always_comb begin
   	   if (seg_counter < 32'd100000) begin
   	      anode = 4'b1110;
   	      seg = decode(data_seg%10);
   	   end
   	   else if (seg_counter < 32'd200000) begin
   	      anode = 4'b1101;
   	      seg = decode(data_seg/10%10);
   	   end
   	   else if (seg_counter < 32'd300000) begin
   	      anode = 4'b1011;
   	      seg = decode(data_seg/100%10);
   	   end
   	   else begin
   	      anode = 4'b0111;
   	      seg = decode(data_seg/1000%10);
   	   end
   	end
endmodule

`default_nettype wire
