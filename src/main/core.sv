`default_nettype none

module core
    #(
         parameter DIM = 1023
     )
     (
         input wire              clk,
         input wire              run,
         input wire              gen,
         input wire              update_item,
         input wire [15:0]       item_a,
         input wire [15:0]       item_memory_num,
         input wire [DIM:0]     rand_num,
         input wire              get_v,
         input wire [31:0]       get_d,
         input wire [19:0]       addr_j,
         input wire              exec,
         input wire              update,

         output logic [DIM:0]   core_result
     );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // BRAMになるはず
    (* ram_style = "block" *)
    reg [DIM:0]      item_memory [0:1023];


    reg [DIM:0]      hv;
    always_ff @(posedge clk) begin
                  if (gen & (item_a != item_memory_num) & update_item) begin
                      item_memory[item_a] <= rand_num;
                      hv <= 0;
                  end
                  else if (get_v) begin
                      hv <= item_memory[get_d];
                  end
              end;

    // integer i;
    // initial begin
    //     for (i=0; i < 100; i++) begin
    //         item_memory[i] = i;
    //     end
    // end


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 後々要改造（permutation == addr_j)
    reg [9:0]      permutation;

    always @(posedge clk) begin
        if (~run) begin
            permutation <= 10'h0;
        end
        else if (exec) begin
            if (permutation == addr_j) begin
                permutation <= 10'h0;
            end
            else begin
                permutation <= permutation + 1;
            end
        end
    end;



    reg [DIM:0]      enc;

    always_ff @(posedge clk) begin
                  if (~run) begin
                      enc <= 0;
                  end
                  else if (exec) begin
                      if (update) begin
                          enc <= hv;
                      end
                      else begin
                          // 次元数可変にするなら、これの左側（hv>>permutation)と右側に分けて、一番右の右側を一番左に持ってくる配線にしたら良いと
                          //   enc <= enc ^ (hv >> permutation | ( ( hv & ((1'b1 << permutation) - 1'b1) ) << (DIM+1 - permutation) ) );
                          if (permutation == 10'd1) begin
                              enc <= enc ^ ({hv[0], hv[DIM:1]});
                          end
                          else if (permutation == 10'd2) begin
                              enc <= enc ^ ({hv[1:0], hv[DIM:2]});
                          end
                          else if (permutation == 10'd3) begin
                              enc <= enc ^ ({hv[2:0], hv[DIM:3]});
                          end
                          else if (permutation == 10'd4) begin
                              enc <= enc ^ ({hv[3:0], hv[DIM:4]});
                          end
                          else if (permutation == 10'd5) begin
                              enc <= enc ^ ({hv[4:0], hv[DIM:5]});
                          end
                          else if (permutation == 10'd6) begin
                              enc <= enc ^ ({hv[5:0], hv[DIM:6]});
                          end
                          else if (permutation == 10'd7) begin
                              enc <= enc ^ ({hv[6:0], hv[DIM:7]});
                          end
                          else if (permutation == 10'd8) begin
                              enc <= enc ^ ({hv[7:0], hv[DIM:8]});
                          end
                          else if (permutation == 10'd9) begin
                              enc <= enc ^ ({hv[8:0], hv[DIM:9]});
                          end
                          else if (permutation == 10'd10) begin
                              enc <= enc ^ ({hv[9:0], hv[DIM:10]});
                          end
                          else if (permutation == 10'd11) begin
                              enc <= enc ^ ({hv[10:0], hv[DIM:11]});
                          end
                          else if (permutation == 10'd12) begin
                              enc <= enc ^ ({hv[11:0], hv[DIM:12]});
                          end
                          else if (permutation == 10'd13) begin
                              enc <= enc ^ ({hv[12:0], hv[DIM:13]});
                          end
                          else if (permutation == 10'd14) begin
                              enc <= enc ^ ({hv[13:0], hv[DIM:14]});
                          end
                          else if (permutation == 10'd15) begin
                              enc <= enc ^ ({hv[14:0], hv[DIM:15]});
                          end
                          else if (permutation == 10'd16) begin
                              enc <= enc ^ ({hv[15:0], hv[DIM:16]});
                          end
                          else if (permutation == 10'd17) begin
                              enc <= enc ^ ({hv[16:0], hv[DIM:17]});
                          end
                          else if (permutation == 10'd18) begin
                              enc <= enc ^ ({hv[17:0], hv[DIM:18]});
                          end
                          else if (permutation == 10'd19) begin
                              enc <= enc ^ ({hv[18:0], hv[DIM:19]});
                          end
                          else if (permutation == 10'd20) begin
                              enc <= enc ^ ({hv[19:0], hv[DIM:20]});
                          end
                          else if (permutation == 10'd21) begin
                              enc <= enc ^ ({hv[20:0], hv[DIM:21]});
                          end
                          else if (permutation == 10'd22) begin
                              enc <= enc ^ ({hv[21:0], hv[DIM:22]});
                          end
                          else if (permutation == 10'd23) begin
                              enc <= enc ^ ({hv[22:0], hv[DIM:23]});
                          end
                          else if (permutation == 10'd24) begin
                              enc <= enc ^ ({hv[23:0], hv[DIM:24]});
                          end
                          else if (permutation == 10'd25) begin
                              enc <= enc ^ ({hv[24:0], hv[DIM:25]});
                          end
                          else if (permutation == 10'd26) begin
                              enc <= enc ^ ({hv[25:0], hv[DIM:26]});
                          end
                          else if (permutation == 10'd27) begin
                              enc <= enc ^ ({hv[26:0], hv[DIM:27]});
                          end
                          else if (permutation == 10'd28) begin
                              enc <= enc ^ ({hv[27:0], hv[DIM:28]});
                          end
                          else if (permutation == 10'd29) begin
                              enc <= enc ^ ({hv[28:0], hv[DIM:29]});
                          end
                          else if (permutation == 10'd30) begin
                              enc <= enc ^ ({hv[29:0], hv[DIM:30]});
                          end
                          else if (permutation == 10'd31) begin
                              enc <= enc ^ ({hv[30:0], hv[DIM:31]});
                          end
                          else if (permutation == 10'd32) begin
                              enc <= enc ^ ({hv[31:0], hv[DIM:32]});
                          end
                          else if (permutation == 10'd33) begin
                              enc <= enc ^ ({hv[32:0], hv[DIM:33]});
                          end
                          else if (permutation == 10'd34) begin
                              enc <= enc ^ ({hv[33:0], hv[DIM:34]});
                          end
                          else if (permutation == 10'd35) begin
                              enc <= enc ^ ({hv[34:0], hv[DIM:35]});
                          end
                          else if (permutation == 10'd36) begin
                              enc <= enc ^ ({hv[35:0], hv[DIM:36]});
                          end
                          else if (permutation == 10'd37) begin
                              enc <= enc ^ ({hv[36:0], hv[DIM:37]});
                          end
                          else if (permutation == 10'd38) begin
                              enc <= enc ^ ({hv[37:0], hv[DIM:38]});
                          end
                          else if (permutation == 10'd39) begin
                              enc <= enc ^ ({hv[38:0], hv[DIM:39]});
                          end
                          else if (permutation == 10'd40) begin
                              enc <= enc ^ ({hv[39:0], hv[DIM:40]});
                          end
                          else if (permutation == 10'd41) begin
                              enc <= enc ^ ({hv[40:0], hv[DIM:41]});
                          end
                          else if (permutation == 10'd42) begin
                              enc <= enc ^ ({hv[41:0], hv[DIM:42]});
                          end
                          else if (permutation == 10'd43) begin
                              enc <= enc ^ ({hv[42:0], hv[DIM:43]});
                          end
                          else if (permutation == 10'd44) begin
                              enc <= enc ^ ({hv[43:0], hv[DIM:44]});
                          end
                          else if (permutation == 10'd45) begin
                              enc <= enc ^ ({hv[44:0], hv[DIM:45]});
                          end
                          else if (permutation == 10'd46) begin
                              enc <= enc ^ ({hv[45:0], hv[DIM:46]});
                          end
                          else if (permutation == 10'd47) begin
                              enc <= enc ^ ({hv[46:0], hv[DIM:47]});
                          end
                          else if (permutation == 10'd48) begin
                              enc <= enc ^ ({hv[47:0], hv[DIM:48]});
                          end
                          else if (permutation == 10'd49) begin
                              enc <= enc ^ ({hv[48:0], hv[DIM:49]});
                          end
                          else if (permutation == 10'd50) begin
                              enc <= enc ^ ({hv[49:0], hv[DIM:50]});
                          end
                          else if (permutation == 10'd51) begin
                              enc <= enc ^ ({hv[50:0], hv[DIM:51]});
                          end
                          else if (permutation == 10'd52) begin
                              enc <= enc ^ ({hv[51:0], hv[DIM:52]});
                          end
                          else if (permutation == 10'd53) begin
                              enc <= enc ^ ({hv[52:0], hv[DIM:53]});
                          end
                          else if (permutation == 10'd54) begin
                              enc <= enc ^ ({hv[53:0], hv[DIM:54]});
                          end
                          else if (permutation == 10'd55) begin
                              enc <= enc ^ ({hv[54:0], hv[DIM:55]});
                          end
                          else if (permutation == 10'd56) begin
                              enc <= enc ^ ({hv[55:0], hv[DIM:56]});
                          end
                          else if (permutation == 10'd57) begin
                              enc <= enc ^ ({hv[56:0], hv[DIM:57]});
                          end
                          else if (permutation == 10'd58) begin
                              enc <= enc ^ ({hv[57:0], hv[DIM:58]});
                          end
                          else if (permutation == 10'd59) begin
                              enc <= enc ^ ({hv[58:0], hv[DIM:59]});
                          end
                          else if (permutation == 10'd60) begin
                              enc <= enc ^ ({hv[59:0], hv[DIM:60]});
                          end
                          else if (permutation == 10'd61) begin
                              enc <= enc ^ ({hv[60:0], hv[DIM:61]});
                          end
                          else if (permutation == 10'd62) begin
                              enc <= enc ^ ({hv[61:0], hv[DIM:62]});
                          end
                          else if (permutation == 10'd63) begin
                              enc <= enc ^ ({hv[62:0], hv[DIM:63]});
                          end
                          else if (permutation == 10'd64) begin
                              enc <= enc ^ ({hv[63:0], hv[DIM:64]});
                          end
                          else if (permutation == 10'd65) begin
                              enc <= enc ^ ({hv[64:0], hv[DIM:65]});
                          end
                          else if (permutation == 10'd66) begin
                              enc <= enc ^ ({hv[65:0], hv[DIM:66]});
                          end
                          else if (permutation == 10'd67) begin
                              enc <= enc ^ ({hv[66:0], hv[DIM:67]});
                          end
                          else if (permutation == 10'd68) begin
                              enc <= enc ^ ({hv[67:0], hv[DIM:68]});
                          end
                          else if (permutation == 10'd69) begin
                              enc <= enc ^ ({hv[68:0], hv[DIM:69]});
                          end
                          else if (permutation == 10'd70) begin
                              enc <= enc ^ ({hv[69:0], hv[DIM:70]});
                          end
                          else if (permutation == 10'd71) begin
                              enc <= enc ^ ({hv[70:0], hv[DIM:71]});
                          end
                          else if (permutation == 10'd72) begin
                              enc <= enc ^ ({hv[71:0], hv[DIM:72]});
                          end
                          else if (permutation == 10'd73) begin
                              enc <= enc ^ ({hv[72:0], hv[DIM:73]});
                          end
                          else if (permutation == 10'd74) begin
                              enc <= enc ^ ({hv[73:0], hv[DIM:74]});
                          end
                          else if (permutation == 10'd75) begin
                              enc <= enc ^ ({hv[74:0], hv[DIM:75]});
                          end
                          else if (permutation == 10'd76) begin
                              enc <= enc ^ ({hv[75:0], hv[DIM:76]});
                          end
                          else if (permutation == 10'd77) begin
                              enc <= enc ^ ({hv[76:0], hv[DIM:77]});
                          end
                          else if (permutation == 10'd78) begin
                              enc <= enc ^ ({hv[77:0], hv[DIM:78]});
                          end
                          else if (permutation == 10'd79) begin
                              enc <= enc ^ ({hv[78:0], hv[DIM:79]});
                          end
                          else if (permutation == 10'd80) begin
                              enc <= enc ^ ({hv[79:0], hv[DIM:80]});
                          end
                          else if (permutation == 10'd81) begin
                              enc <= enc ^ ({hv[80:0], hv[DIM:81]});
                          end
                          else if (permutation == 10'd82) begin
                              enc <= enc ^ ({hv[81:0], hv[DIM:82]});
                          end
                          else if (permutation == 10'd83) begin
                              enc <= enc ^ ({hv[82:0], hv[DIM:83]});
                          end
                          else if (permutation == 10'd84) begin
                              enc <= enc ^ ({hv[83:0], hv[DIM:84]});
                          end
                          else if (permutation == 10'd85) begin
                              enc <= enc ^ ({hv[84:0], hv[DIM:85]});
                          end
                          else if (permutation == 10'd86) begin
                              enc <= enc ^ ({hv[85:0], hv[DIM:86]});
                          end
                          else if (permutation == 10'd87) begin
                              enc <= enc ^ ({hv[86:0], hv[DIM:87]});
                          end
                          else if (permutation == 10'd88) begin
                              enc <= enc ^ ({hv[87:0], hv[DIM:88]});
                          end
                          else if (permutation == 10'd89) begin
                              enc <= enc ^ ({hv[88:0], hv[DIM:89]});
                          end
                          else if (permutation == 10'd90) begin
                              enc <= enc ^ ({hv[89:0], hv[DIM:90]});
                          end
                          else if (permutation == 10'd91) begin
                              enc <= enc ^ ({hv[90:0], hv[DIM:91]});
                          end
                          else if (permutation == 10'd92) begin
                              enc <= enc ^ ({hv[91:0], hv[DIM:92]});
                          end
                          else if (permutation == 10'd93) begin
                              enc <= enc ^ ({hv[92:0], hv[DIM:93]});
                          end
                          else if (permutation == 10'd94) begin
                              enc <= enc ^ ({hv[93:0], hv[DIM:94]});
                          end
                          else if (permutation == 10'd95) begin
                              enc <= enc ^ ({hv[94:0], hv[DIM:95]});
                          end
                          else if (permutation == 10'd96) begin
                              enc <= enc ^ ({hv[95:0], hv[DIM:96]});
                          end
                          else if (permutation == 10'd97) begin
                              enc <= enc ^ ({hv[96:0], hv[DIM:97]});
                          end
                          else if (permutation == 10'd98) begin
                              enc <= enc ^ ({hv[97:0], hv[DIM:98]});
                          end
                          else if (permutation == 10'd99) begin
                              enc <= enc ^ ({hv[98:0], hv[DIM:99]});
                          end
                          else if (permutation == 10'd100) begin
                              enc <= enc ^ ({hv[99:0], hv[DIM:100]});
                          end
                          else if (permutation == 10'd101) begin
                              enc <= enc ^ ({hv[100:0], hv[DIM:101]});
                          end
                          else if (permutation == 10'd102) begin
                              enc <= enc ^ ({hv[101:0], hv[DIM:102]});
                          end
                          else if (permutation == 10'd103) begin
                              enc <= enc ^ ({hv[102:0], hv[DIM:103]});
                          end
                          else if (permutation == 10'd104) begin
                              enc <= enc ^ ({hv[103:0], hv[DIM:104]});
                          end
                          else if (permutation == 10'd105) begin
                              enc <= enc ^ ({hv[104:0], hv[DIM:105]});
                          end
                          else if (permutation == 10'd106) begin
                              enc <= enc ^ ({hv[105:0], hv[DIM:106]});
                          end
                          else if (permutation == 10'd107) begin
                              enc <= enc ^ ({hv[106:0], hv[DIM:107]});
                          end
                          else if (permutation == 10'd108) begin
                              enc <= enc ^ ({hv[107:0], hv[DIM:108]});
                          end
                          else if (permutation == 10'd109) begin
                              enc <= enc ^ ({hv[108:0], hv[DIM:109]});
                          end
                          else if (permutation == 10'd110) begin
                              enc <= enc ^ ({hv[109:0], hv[DIM:110]});
                          end
                          else if (permutation == 10'd111) begin
                              enc <= enc ^ ({hv[110:0], hv[DIM:111]});
                          end
                          else if (permutation == 10'd112) begin
                              enc <= enc ^ ({hv[111:0], hv[DIM:112]});
                          end
                          else if (permutation == 10'd113) begin
                              enc <= enc ^ ({hv[112:0], hv[DIM:113]});
                          end
                          else if (permutation == 10'd114) begin
                              enc <= enc ^ ({hv[113:0], hv[DIM:114]});
                          end
                          else if (permutation == 10'd115) begin
                              enc <= enc ^ ({hv[114:0], hv[DIM:115]});
                          end
                          else if (permutation == 10'd116) begin
                              enc <= enc ^ ({hv[115:0], hv[DIM:116]});
                          end
                          else if (permutation == 10'd117) begin
                              enc <= enc ^ ({hv[116:0], hv[DIM:117]});
                          end
                          else if (permutation == 10'd118) begin
                              enc <= enc ^ ({hv[117:0], hv[DIM:118]});
                          end
                          else if (permutation == 10'd119) begin
                              enc <= enc ^ ({hv[118:0], hv[DIM:119]});
                          end
                          else if (permutation == 10'd120) begin
                              enc <= enc ^ ({hv[119:0], hv[DIM:120]});
                          end
                          else if (permutation == 10'd121) begin
                              enc <= enc ^ ({hv[120:0], hv[DIM:121]});
                          end
                          else if (permutation == 10'd122) begin
                              enc <= enc ^ ({hv[121:0], hv[DIM:122]});
                          end
                          else if (permutation == 10'd123) begin
                              enc <= enc ^ ({hv[122:0], hv[DIM:123]});
                          end
                          else if (permutation == 10'd124) begin
                              enc <= enc ^ ({hv[123:0], hv[DIM:124]});
                          end
                          else if (permutation == 10'd125) begin
                              enc <= enc ^ ({hv[124:0], hv[DIM:125]});
                          end
                          else if (permutation == 10'd126) begin
                              enc <= enc ^ ({hv[125:0], hv[DIM:126]});
                          end
                          else if (permutation == 10'd127) begin
                              enc <= enc ^ ({hv[126:0], hv[DIM:127]});
                          end
                          else if (permutation == 10'd128) begin
                              enc <= enc ^ ({hv[127:0], hv[DIM:128]});
                          end
                          else if (permutation == 10'd129) begin
                              enc <= enc ^ ({hv[128:0], hv[DIM:129]});
                          end
                          else if (permutation == 10'd130) begin
                              enc <= enc ^ ({hv[129:0], hv[DIM:130]});
                          end
                          else if (permutation == 10'd131) begin
                              enc <= enc ^ ({hv[130:0], hv[DIM:131]});
                          end
                          else if (permutation == 10'd132) begin
                              enc <= enc ^ ({hv[131:0], hv[DIM:132]});
                          end
                          else if (permutation == 10'd133) begin
                              enc <= enc ^ ({hv[132:0], hv[DIM:133]});
                          end
                          else if (permutation == 10'd134) begin
                              enc <= enc ^ ({hv[133:0], hv[DIM:134]});
                          end
                          else if (permutation == 10'd135) begin
                              enc <= enc ^ ({hv[134:0], hv[DIM:135]});
                          end
                          else if (permutation == 10'd136) begin
                              enc <= enc ^ ({hv[135:0], hv[DIM:136]});
                          end
                          else if (permutation == 10'd137) begin
                              enc <= enc ^ ({hv[136:0], hv[DIM:137]});
                          end
                          else if (permutation == 10'd138) begin
                              enc <= enc ^ ({hv[137:0], hv[DIM:138]});
                          end
                          else if (permutation == 10'd139) begin
                              enc <= enc ^ ({hv[138:0], hv[DIM:139]});
                          end
                          else if (permutation == 10'd140) begin
                              enc <= enc ^ ({hv[139:0], hv[DIM:140]});
                          end
                          else if (permutation == 10'd141) begin
                              enc <= enc ^ ({hv[140:0], hv[DIM:141]});
                          end
                          else if (permutation == 10'd142) begin
                              enc <= enc ^ ({hv[141:0], hv[DIM:142]});
                          end
                          else if (permutation == 10'd143) begin
                              enc <= enc ^ ({hv[142:0], hv[DIM:143]});
                          end
                          else if (permutation == 10'd144) begin
                              enc <= enc ^ ({hv[143:0], hv[DIM:144]});
                          end
                          else if (permutation == 10'd145) begin
                              enc <= enc ^ ({hv[144:0], hv[DIM:145]});
                          end
                          else if (permutation == 10'd146) begin
                              enc <= enc ^ ({hv[145:0], hv[DIM:146]});
                          end
                          else if (permutation == 10'd147) begin
                              enc <= enc ^ ({hv[146:0], hv[DIM:147]});
                          end
                          else if (permutation == 10'd148) begin
                              enc <= enc ^ ({hv[147:0], hv[DIM:148]});
                          end
                          else if (permutation == 10'd149) begin
                              enc <= enc ^ ({hv[148:0], hv[DIM:149]});
                          end
                          else if (permutation == 10'd150) begin
                              enc <= enc ^ ({hv[149:0], hv[DIM:150]});
                          end
                          else if (permutation == 10'd151) begin
                              enc <= enc ^ ({hv[150:0], hv[DIM:151]});
                          end
                          else if (permutation == 10'd152) begin
                              enc <= enc ^ ({hv[151:0], hv[DIM:152]});
                          end
                          else if (permutation == 10'd153) begin
                              enc <= enc ^ ({hv[152:0], hv[DIM:153]});
                          end
                          else if (permutation == 10'd154) begin
                              enc <= enc ^ ({hv[153:0], hv[DIM:154]});
                          end
                          else if (permutation == 10'd155) begin
                              enc <= enc ^ ({hv[154:0], hv[DIM:155]});
                          end
                          else if (permutation == 10'd156) begin
                              enc <= enc ^ ({hv[155:0], hv[DIM:156]});
                          end
                          else if (permutation == 10'd157) begin
                              enc <= enc ^ ({hv[156:0], hv[DIM:157]});
                          end
                          else if (permutation == 10'd158) begin
                              enc <= enc ^ ({hv[157:0], hv[DIM:158]});
                          end
                          else if (permutation == 10'd159) begin
                              enc <= enc ^ ({hv[158:0], hv[DIM:159]});
                          end
                          else if (permutation == 10'd160) begin
                              enc <= enc ^ ({hv[159:0], hv[DIM:160]});
                          end
                          else if (permutation == 10'd161) begin
                              enc <= enc ^ ({hv[160:0], hv[DIM:161]});
                          end
                          else if (permutation == 10'd162) begin
                              enc <= enc ^ ({hv[161:0], hv[DIM:162]});
                          end
                          else if (permutation == 10'd163) begin
                              enc <= enc ^ ({hv[162:0], hv[DIM:163]});
                          end
                          else if (permutation == 10'd164) begin
                              enc <= enc ^ ({hv[163:0], hv[DIM:164]});
                          end
                          else if (permutation == 10'd165) begin
                              enc <= enc ^ ({hv[164:0], hv[DIM:165]});
                          end
                          else if (permutation == 10'd166) begin
                              enc <= enc ^ ({hv[165:0], hv[DIM:166]});
                          end
                          else if (permutation == 10'd167) begin
                              enc <= enc ^ ({hv[166:0], hv[DIM:167]});
                          end
                          else if (permutation == 10'd168) begin
                              enc <= enc ^ ({hv[167:0], hv[DIM:168]});
                          end
                          else if (permutation == 10'd169) begin
                              enc <= enc ^ ({hv[168:0], hv[DIM:169]});
                          end
                          else if (permutation == 10'd170) begin
                              enc <= enc ^ ({hv[169:0], hv[DIM:170]});
                          end
                          else if (permutation == 10'd171) begin
                              enc <= enc ^ ({hv[170:0], hv[DIM:171]});
                          end
                          else if (permutation == 10'd172) begin
                              enc <= enc ^ ({hv[171:0], hv[DIM:172]});
                          end
                          else if (permutation == 10'd173) begin
                              enc <= enc ^ ({hv[172:0], hv[DIM:173]});
                          end
                          else if (permutation == 10'd174) begin
                              enc <= enc ^ ({hv[173:0], hv[DIM:174]});
                          end
                          else if (permutation == 10'd175) begin
                              enc <= enc ^ ({hv[174:0], hv[DIM:175]});
                          end
                          else if (permutation == 10'd176) begin
                              enc <= enc ^ ({hv[175:0], hv[DIM:176]});
                          end
                          else if (permutation == 10'd177) begin
                              enc <= enc ^ ({hv[176:0], hv[DIM:177]});
                          end
                          else if (permutation == 10'd178) begin
                              enc <= enc ^ ({hv[177:0], hv[DIM:178]});
                          end
                          else if (permutation == 10'd179) begin
                              enc <= enc ^ ({hv[178:0], hv[DIM:179]});
                          end
                          else if (permutation == 10'd180) begin
                              enc <= enc ^ ({hv[179:0], hv[DIM:180]});
                          end
                          else if (permutation == 10'd181) begin
                              enc <= enc ^ ({hv[180:0], hv[DIM:181]});
                          end
                          else if (permutation == 10'd182) begin
                              enc <= enc ^ ({hv[181:0], hv[DIM:182]});
                          end
                          else if (permutation == 10'd183) begin
                              enc <= enc ^ ({hv[182:0], hv[DIM:183]});
                          end
                          else if (permutation == 10'd184) begin
                              enc <= enc ^ ({hv[183:0], hv[DIM:184]});
                          end
                          else if (permutation == 10'd185) begin
                              enc <= enc ^ ({hv[184:0], hv[DIM:185]});
                          end
                          else if (permutation == 10'd186) begin
                              enc <= enc ^ ({hv[185:0], hv[DIM:186]});
                          end
                          else if (permutation == 10'd187) begin
                              enc <= enc ^ ({hv[186:0], hv[DIM:187]});
                          end
                          else if (permutation == 10'd188) begin
                              enc <= enc ^ ({hv[187:0], hv[DIM:188]});
                          end
                          else if (permutation == 10'd189) begin
                              enc <= enc ^ ({hv[188:0], hv[DIM:189]});
                          end
                          else if (permutation == 10'd190) begin
                              enc <= enc ^ ({hv[189:0], hv[DIM:190]});
                          end
                          else if (permutation == 10'd191) begin
                              enc <= enc ^ ({hv[190:0], hv[DIM:191]});
                          end
                          else if (permutation == 10'd192) begin
                              enc <= enc ^ ({hv[191:0], hv[DIM:192]});
                          end
                          else if (permutation == 10'd193) begin
                              enc <= enc ^ ({hv[192:0], hv[DIM:193]});
                          end
                          else if (permutation == 10'd194) begin
                              enc <= enc ^ ({hv[193:0], hv[DIM:194]});
                          end
                          else if (permutation == 10'd195) begin
                              enc <= enc ^ ({hv[194:0], hv[DIM:195]});
                          end
                          else if (permutation == 10'd196) begin
                              enc <= enc ^ ({hv[195:0], hv[DIM:196]});
                          end
                          else if (permutation == 10'd197) begin
                              enc <= enc ^ ({hv[196:0], hv[DIM:197]});
                          end
                          else if (permutation == 10'd198) begin
                              enc <= enc ^ ({hv[197:0], hv[DIM:198]});
                          end
                          else if (permutation == 10'd199) begin
                              enc <= enc ^ ({hv[198:0], hv[DIM:199]});
                          end
                          else if (permutation == 10'd200) begin
                              enc <= enc ^ ({hv[199:0], hv[DIM:200]});
                          end
                          else if (permutation == 10'd201) begin
                              enc <= enc ^ ({hv[200:0], hv[DIM:201]});
                          end
                          else if (permutation == 10'd202) begin
                              enc <= enc ^ ({hv[201:0], hv[DIM:202]});
                          end
                          else if (permutation == 10'd203) begin
                              enc <= enc ^ ({hv[202:0], hv[DIM:203]});
                          end
                          else if (permutation == 10'd204) begin
                              enc <= enc ^ ({hv[203:0], hv[DIM:204]});
                          end
                          else if (permutation == 10'd205) begin
                              enc <= enc ^ ({hv[204:0], hv[DIM:205]});
                          end
                          else if (permutation == 10'd206) begin
                              enc <= enc ^ ({hv[205:0], hv[DIM:206]});
                          end
                          else if (permutation == 10'd207) begin
                              enc <= enc ^ ({hv[206:0], hv[DIM:207]});
                          end
                          else if (permutation == 10'd208) begin
                              enc <= enc ^ ({hv[207:0], hv[DIM:208]});
                          end
                          else if (permutation == 10'd209) begin
                              enc <= enc ^ ({hv[208:0], hv[DIM:209]});
                          end
                          else if (permutation == 10'd210) begin
                              enc <= enc ^ ({hv[209:0], hv[DIM:210]});
                          end
                          else if (permutation == 10'd211) begin
                              enc <= enc ^ ({hv[210:0], hv[DIM:211]});
                          end
                          else if (permutation == 10'd212) begin
                              enc <= enc ^ ({hv[211:0], hv[DIM:212]});
                          end
                          else if (permutation == 10'd213) begin
                              enc <= enc ^ ({hv[212:0], hv[DIM:213]});
                          end
                          else if (permutation == 10'd214) begin
                              enc <= enc ^ ({hv[213:0], hv[DIM:214]});
                          end
                          else if (permutation == 10'd215) begin
                              enc <= enc ^ ({hv[214:0], hv[DIM:215]});
                          end
                          else if (permutation == 10'd216) begin
                              enc <= enc ^ ({hv[215:0], hv[DIM:216]});
                          end
                          else if (permutation == 10'd217) begin
                              enc <= enc ^ ({hv[216:0], hv[DIM:217]});
                          end
                          else if (permutation == 10'd218) begin
                              enc <= enc ^ ({hv[217:0], hv[DIM:218]});
                          end
                          else if (permutation == 10'd219) begin
                              enc <= enc ^ ({hv[218:0], hv[DIM:219]});
                          end
                          else if (permutation == 10'd220) begin
                              enc <= enc ^ ({hv[219:0], hv[DIM:220]});
                          end
                          else if (permutation == 10'd221) begin
                              enc <= enc ^ ({hv[220:0], hv[DIM:221]});
                          end
                          else if (permutation == 10'd222) begin
                              enc <= enc ^ ({hv[221:0], hv[DIM:222]});
                          end
                          else if (permutation == 10'd223) begin
                              enc <= enc ^ ({hv[222:0], hv[DIM:223]});
                          end
                          else if (permutation == 10'd224) begin
                              enc <= enc ^ ({hv[223:0], hv[DIM:224]});
                          end
                          else if (permutation == 10'd225) begin
                              enc <= enc ^ ({hv[224:0], hv[DIM:225]});
                          end
                          else if (permutation == 10'd226) begin
                              enc <= enc ^ ({hv[225:0], hv[DIM:226]});
                          end
                          else if (permutation == 10'd227) begin
                              enc <= enc ^ ({hv[226:0], hv[DIM:227]});
                          end
                          else if (permutation == 10'd228) begin
                              enc <= enc ^ ({hv[227:0], hv[DIM:228]});
                          end
                          else if (permutation == 10'd229) begin
                              enc <= enc ^ ({hv[228:0], hv[DIM:229]});
                          end
                          else if (permutation == 10'd230) begin
                              enc <= enc ^ ({hv[229:0], hv[DIM:230]});
                          end
                          else if (permutation == 10'd231) begin
                              enc <= enc ^ ({hv[230:0], hv[DIM:231]});
                          end
                          else if (permutation == 10'd232) begin
                              enc <= enc ^ ({hv[231:0], hv[DIM:232]});
                          end
                          else if (permutation == 10'd233) begin
                              enc <= enc ^ ({hv[232:0], hv[DIM:233]});
                          end
                          else if (permutation == 10'd234) begin
                              enc <= enc ^ ({hv[233:0], hv[DIM:234]});
                          end
                          else if (permutation == 10'd235) begin
                              enc <= enc ^ ({hv[234:0], hv[DIM:235]});
                          end
                          else if (permutation == 10'd236) begin
                              enc <= enc ^ ({hv[235:0], hv[DIM:236]});
                          end
                          else if (permutation == 10'd237) begin
                              enc <= enc ^ ({hv[236:0], hv[DIM:237]});
                          end
                          else if (permutation == 10'd238) begin
                              enc <= enc ^ ({hv[237:0], hv[DIM:238]});
                          end
                          else if (permutation == 10'd239) begin
                              enc <= enc ^ ({hv[238:0], hv[DIM:239]});
                          end
                          else if (permutation == 10'd240) begin
                              enc <= enc ^ ({hv[239:0], hv[DIM:240]});
                          end
                          else if (permutation == 10'd241) begin
                              enc <= enc ^ ({hv[240:0], hv[DIM:241]});
                          end
                          else if (permutation == 10'd242) begin
                              enc <= enc ^ ({hv[241:0], hv[DIM:242]});
                          end
                          else if (permutation == 10'd243) begin
                              enc <= enc ^ ({hv[242:0], hv[DIM:243]});
                          end
                          else if (permutation == 10'd244) begin
                              enc <= enc ^ ({hv[243:0], hv[DIM:244]});
                          end
                          else if (permutation == 10'd245) begin
                              enc <= enc ^ ({hv[244:0], hv[DIM:245]});
                          end
                          else if (permutation == 10'd246) begin
                              enc <= enc ^ ({hv[245:0], hv[DIM:246]});
                          end
                          else if (permutation == 10'd247) begin
                              enc <= enc ^ ({hv[246:0], hv[DIM:247]});
                          end
                          else if (permutation == 10'd248) begin
                              enc <= enc ^ ({hv[247:0], hv[DIM:248]});
                          end
                          else if (permutation == 10'd249) begin
                              enc <= enc ^ ({hv[248:0], hv[DIM:249]});
                          end
                          else if (permutation == 10'd250) begin
                              enc <= enc ^ ({hv[249:0], hv[DIM:250]});
                          end
                          else if (permutation == 10'd251) begin
                              enc <= enc ^ ({hv[250:0], hv[DIM:251]});
                          end
                          else if (permutation == 10'd252) begin
                              enc <= enc ^ ({hv[251:0], hv[DIM:252]});
                          end
                          else if (permutation == 10'd253) begin
                              enc <= enc ^ ({hv[252:0], hv[DIM:253]});
                          end
                          else if (permutation == 10'd254) begin
                              enc <= enc ^ ({hv[253:0], hv[DIM:254]});
                          end
                          else if (permutation == 10'd255) begin
                              enc <= enc ^ ({hv[254:0], hv[DIM:255]});
                          end
                          else if (permutation == 10'd256) begin
                              enc <= enc ^ ({hv[255:0], hv[DIM:256]});
                          end
                          else if (permutation == 10'd257) begin
                              enc <= enc ^ ({hv[256:0], hv[DIM:257]});
                          end
                          else if (permutation == 10'd258) begin
                              enc <= enc ^ ({hv[257:0], hv[DIM:258]});
                          end
                          else if (permutation == 10'd259) begin
                              enc <= enc ^ ({hv[258:0], hv[DIM:259]});
                          end
                          else if (permutation == 10'd260) begin
                              enc <= enc ^ ({hv[259:0], hv[DIM:260]});
                          end
                          else if (permutation == 10'd261) begin
                              enc <= enc ^ ({hv[260:0], hv[DIM:261]});
                          end
                          else if (permutation == 10'd262) begin
                              enc <= enc ^ ({hv[261:0], hv[DIM:262]});
                          end
                          else if (permutation == 10'd263) begin
                              enc <= enc ^ ({hv[262:0], hv[DIM:263]});
                          end
                          else if (permutation == 10'd264) begin
                              enc <= enc ^ ({hv[263:0], hv[DIM:264]});
                          end
                          else if (permutation == 10'd265) begin
                              enc <= enc ^ ({hv[264:0], hv[DIM:265]});
                          end
                          else if (permutation == 10'd266) begin
                              enc <= enc ^ ({hv[265:0], hv[DIM:266]});
                          end
                          else if (permutation == 10'd267) begin
                              enc <= enc ^ ({hv[266:0], hv[DIM:267]});
                          end
                          else if (permutation == 10'd268) begin
                              enc <= enc ^ ({hv[267:0], hv[DIM:268]});
                          end
                          else if (permutation == 10'd269) begin
                              enc <= enc ^ ({hv[268:0], hv[DIM:269]});
                          end
                          else if (permutation == 10'd270) begin
                              enc <= enc ^ ({hv[269:0], hv[DIM:270]});
                          end
                          else if (permutation == 10'd271) begin
                              enc <= enc ^ ({hv[270:0], hv[DIM:271]});
                          end
                          else if (permutation == 10'd272) begin
                              enc <= enc ^ ({hv[271:0], hv[DIM:272]});
                          end
                          else if (permutation == 10'd273) begin
                              enc <= enc ^ ({hv[272:0], hv[DIM:273]});
                          end
                          else if (permutation == 10'd274) begin
                              enc <= enc ^ ({hv[273:0], hv[DIM:274]});
                          end
                          else if (permutation == 10'd275) begin
                              enc <= enc ^ ({hv[274:0], hv[DIM:275]});
                          end
                          else if (permutation == 10'd276) begin
                              enc <= enc ^ ({hv[275:0], hv[DIM:276]});
                          end
                          else if (permutation == 10'd277) begin
                              enc <= enc ^ ({hv[276:0], hv[DIM:277]});
                          end
                          else if (permutation == 10'd278) begin
                              enc <= enc ^ ({hv[277:0], hv[DIM:278]});
                          end
                          else if (permutation == 10'd279) begin
                              enc <= enc ^ ({hv[278:0], hv[DIM:279]});
                          end
                          else if (permutation == 10'd280) begin
                              enc <= enc ^ ({hv[279:0], hv[DIM:280]});
                          end
                          else if (permutation == 10'd281) begin
                              enc <= enc ^ ({hv[280:0], hv[DIM:281]});
                          end
                          else if (permutation == 10'd282) begin
                              enc <= enc ^ ({hv[281:0], hv[DIM:282]});
                          end
                          else if (permutation == 10'd283) begin
                              enc <= enc ^ ({hv[282:0], hv[DIM:283]});
                          end
                          else if (permutation == 10'd284) begin
                              enc <= enc ^ ({hv[283:0], hv[DIM:284]});
                          end
                          else if (permutation == 10'd285) begin
                              enc <= enc ^ ({hv[284:0], hv[DIM:285]});
                          end
                          else if (permutation == 10'd286) begin
                              enc <= enc ^ ({hv[285:0], hv[DIM:286]});
                          end
                          else if (permutation == 10'd287) begin
                              enc <= enc ^ ({hv[286:0], hv[DIM:287]});
                          end
                          else if (permutation == 10'd288) begin
                              enc <= enc ^ ({hv[287:0], hv[DIM:288]});
                          end
                          else if (permutation == 10'd289) begin
                              enc <= enc ^ ({hv[288:0], hv[DIM:289]});
                          end
                          else if (permutation == 10'd290) begin
                              enc <= enc ^ ({hv[289:0], hv[DIM:290]});
                          end
                          else if (permutation == 10'd291) begin
                              enc <= enc ^ ({hv[290:0], hv[DIM:291]});
                          end
                          else if (permutation == 10'd292) begin
                              enc <= enc ^ ({hv[291:0], hv[DIM:292]});
                          end
                          else if (permutation == 10'd293) begin
                              enc <= enc ^ ({hv[292:0], hv[DIM:293]});
                          end
                          else if (permutation == 10'd294) begin
                              enc <= enc ^ ({hv[293:0], hv[DIM:294]});
                          end
                          else if (permutation == 10'd295) begin
                              enc <= enc ^ ({hv[294:0], hv[DIM:295]});
                          end
                          else if (permutation == 10'd296) begin
                              enc <= enc ^ ({hv[295:0], hv[DIM:296]});
                          end
                          else if (permutation == 10'd297) begin
                              enc <= enc ^ ({hv[296:0], hv[DIM:297]});
                          end
                          else if (permutation == 10'd298) begin
                              enc <= enc ^ ({hv[297:0], hv[DIM:298]});
                          end
                          else if (permutation == 10'd299) begin
                              enc <= enc ^ ({hv[298:0], hv[DIM:299]});
                          end
                          else if (permutation == 10'd300) begin
                              enc <= enc ^ ({hv[299:0], hv[DIM:300]});
                          end
                          else if (permutation == 10'd301) begin
                              enc <= enc ^ ({hv[300:0], hv[DIM:301]});
                          end
                          else if (permutation == 10'd302) begin
                              enc <= enc ^ ({hv[301:0], hv[DIM:302]});
                          end
                          else if (permutation == 10'd303) begin
                              enc <= enc ^ ({hv[302:0], hv[DIM:303]});
                          end
                          else if (permutation == 10'd304) begin
                              enc <= enc ^ ({hv[303:0], hv[DIM:304]});
                          end
                          else if (permutation == 10'd305) begin
                              enc <= enc ^ ({hv[304:0], hv[DIM:305]});
                          end
                          else if (permutation == 10'd306) begin
                              enc <= enc ^ ({hv[305:0], hv[DIM:306]});
                          end
                          else if (permutation == 10'd307) begin
                              enc <= enc ^ ({hv[306:0], hv[DIM:307]});
                          end
                          else if (permutation == 10'd308) begin
                              enc <= enc ^ ({hv[307:0], hv[DIM:308]});
                          end
                          else if (permutation == 10'd309) begin
                              enc <= enc ^ ({hv[308:0], hv[DIM:309]});
                          end
                          else if (permutation == 10'd310) begin
                              enc <= enc ^ ({hv[309:0], hv[DIM:310]});
                          end
                          else if (permutation == 10'd311) begin
                              enc <= enc ^ ({hv[310:0], hv[DIM:311]});
                          end
                          else if (permutation == 10'd312) begin
                              enc <= enc ^ ({hv[311:0], hv[DIM:312]});
                          end
                          else if (permutation == 10'd313) begin
                              enc <= enc ^ ({hv[312:0], hv[DIM:313]});
                          end
                          else if (permutation == 10'd314) begin
                              enc <= enc ^ ({hv[313:0], hv[DIM:314]});
                          end
                          else if (permutation == 10'd315) begin
                              enc <= enc ^ ({hv[314:0], hv[DIM:315]});
                          end
                          else if (permutation == 10'd316) begin
                              enc <= enc ^ ({hv[315:0], hv[DIM:316]});
                          end
                          else if (permutation == 10'd317) begin
                              enc <= enc ^ ({hv[316:0], hv[DIM:317]});
                          end
                          else if (permutation == 10'd318) begin
                              enc <= enc ^ ({hv[317:0], hv[DIM:318]});
                          end
                          else if (permutation == 10'd319) begin
                              enc <= enc ^ ({hv[318:0], hv[DIM:319]});
                          end
                          else if (permutation == 10'd320) begin
                              enc <= enc ^ ({hv[319:0], hv[DIM:320]});
                          end
                          else if (permutation == 10'd321) begin
                              enc <= enc ^ ({hv[320:0], hv[DIM:321]});
                          end
                          else if (permutation == 10'd322) begin
                              enc <= enc ^ ({hv[321:0], hv[DIM:322]});
                          end
                          else if (permutation == 10'd323) begin
                              enc <= enc ^ ({hv[322:0], hv[DIM:323]});
                          end
                          else if (permutation == 10'd324) begin
                              enc <= enc ^ ({hv[323:0], hv[DIM:324]});
                          end
                          else if (permutation == 10'd325) begin
                              enc <= enc ^ ({hv[324:0], hv[DIM:325]});
                          end
                          else if (permutation == 10'd326) begin
                              enc <= enc ^ ({hv[325:0], hv[DIM:326]});
                          end
                          else if (permutation == 10'd327) begin
                              enc <= enc ^ ({hv[326:0], hv[DIM:327]});
                          end
                          else if (permutation == 10'd328) begin
                              enc <= enc ^ ({hv[327:0], hv[DIM:328]});
                          end
                          else if (permutation == 10'd329) begin
                              enc <= enc ^ ({hv[328:0], hv[DIM:329]});
                          end
                          else if (permutation == 10'd330) begin
                              enc <= enc ^ ({hv[329:0], hv[DIM:330]});
                          end
                          else if (permutation == 10'd331) begin
                              enc <= enc ^ ({hv[330:0], hv[DIM:331]});
                          end
                          else if (permutation == 10'd332) begin
                              enc <= enc ^ ({hv[331:0], hv[DIM:332]});
                          end
                          else if (permutation == 10'd333) begin
                              enc <= enc ^ ({hv[332:0], hv[DIM:333]});
                          end
                          else if (permutation == 10'd334) begin
                              enc <= enc ^ ({hv[333:0], hv[DIM:334]});
                          end
                          else if (permutation == 10'd335) begin
                              enc <= enc ^ ({hv[334:0], hv[DIM:335]});
                          end
                          else if (permutation == 10'd336) begin
                              enc <= enc ^ ({hv[335:0], hv[DIM:336]});
                          end
                          else if (permutation == 10'd337) begin
                              enc <= enc ^ ({hv[336:0], hv[DIM:337]});
                          end
                          else if (permutation == 10'd338) begin
                              enc <= enc ^ ({hv[337:0], hv[DIM:338]});
                          end
                          else if (permutation == 10'd339) begin
                              enc <= enc ^ ({hv[338:0], hv[DIM:339]});
                          end
                          else if (permutation == 10'd340) begin
                              enc <= enc ^ ({hv[339:0], hv[DIM:340]});
                          end
                          else if (permutation == 10'd341) begin
                              enc <= enc ^ ({hv[340:0], hv[DIM:341]});
                          end
                          else if (permutation == 10'd342) begin
                              enc <= enc ^ ({hv[341:0], hv[DIM:342]});
                          end
                          else if (permutation == 10'd343) begin
                              enc <= enc ^ ({hv[342:0], hv[DIM:343]});
                          end
                          else if (permutation == 10'd344) begin
                              enc <= enc ^ ({hv[343:0], hv[DIM:344]});
                          end
                          else if (permutation == 10'd345) begin
                              enc <= enc ^ ({hv[344:0], hv[DIM:345]});
                          end
                          else if (permutation == 10'd346) begin
                              enc <= enc ^ ({hv[345:0], hv[DIM:346]});
                          end
                          else if (permutation == 10'd347) begin
                              enc <= enc ^ ({hv[346:0], hv[DIM:347]});
                          end
                          else if (permutation == 10'd348) begin
                              enc <= enc ^ ({hv[347:0], hv[DIM:348]});
                          end
                          else if (permutation == 10'd349) begin
                              enc <= enc ^ ({hv[348:0], hv[DIM:349]});
                          end
                          else if (permutation == 10'd350) begin
                              enc <= enc ^ ({hv[349:0], hv[DIM:350]});
                          end
                          else if (permutation == 10'd351) begin
                              enc <= enc ^ ({hv[350:0], hv[DIM:351]});
                          end
                          else if (permutation == 10'd352) begin
                              enc <= enc ^ ({hv[351:0], hv[DIM:352]});
                          end
                          else if (permutation == 10'd353) begin
                              enc <= enc ^ ({hv[352:0], hv[DIM:353]});
                          end
                          else if (permutation == 10'd354) begin
                              enc <= enc ^ ({hv[353:0], hv[DIM:354]});
                          end
                          else if (permutation == 10'd355) begin
                              enc <= enc ^ ({hv[354:0], hv[DIM:355]});
                          end
                          else if (permutation == 10'd356) begin
                              enc <= enc ^ ({hv[355:0], hv[DIM:356]});
                          end
                          else if (permutation == 10'd357) begin
                              enc <= enc ^ ({hv[356:0], hv[DIM:357]});
                          end
                          else if (permutation == 10'd358) begin
                              enc <= enc ^ ({hv[357:0], hv[DIM:358]});
                          end
                          else if (permutation == 10'd359) begin
                              enc <= enc ^ ({hv[358:0], hv[DIM:359]});
                          end
                          else if (permutation == 10'd360) begin
                              enc <= enc ^ ({hv[359:0], hv[DIM:360]});
                          end
                          else if (permutation == 10'd361) begin
                              enc <= enc ^ ({hv[360:0], hv[DIM:361]});
                          end
                          else if (permutation == 10'd362) begin
                              enc <= enc ^ ({hv[361:0], hv[DIM:362]});
                          end
                          else if (permutation == 10'd363) begin
                              enc <= enc ^ ({hv[362:0], hv[DIM:363]});
                          end
                          else if (permutation == 10'd364) begin
                              enc <= enc ^ ({hv[363:0], hv[DIM:364]});
                          end
                          else if (permutation == 10'd365) begin
                              enc <= enc ^ ({hv[364:0], hv[DIM:365]});
                          end
                          else if (permutation == 10'd366) begin
                              enc <= enc ^ ({hv[365:0], hv[DIM:366]});
                          end
                          else if (permutation == 10'd367) begin
                              enc <= enc ^ ({hv[366:0], hv[DIM:367]});
                          end
                          else if (permutation == 10'd368) begin
                              enc <= enc ^ ({hv[367:0], hv[DIM:368]});
                          end
                          else if (permutation == 10'd369) begin
                              enc <= enc ^ ({hv[368:0], hv[DIM:369]});
                          end
                          else if (permutation == 10'd370) begin
                              enc <= enc ^ ({hv[369:0], hv[DIM:370]});
                          end
                          else if (permutation == 10'd371) begin
                              enc <= enc ^ ({hv[370:0], hv[DIM:371]});
                          end
                          else if (permutation == 10'd372) begin
                              enc <= enc ^ ({hv[371:0], hv[DIM:372]});
                          end
                          else if (permutation == 10'd373) begin
                              enc <= enc ^ ({hv[372:0], hv[DIM:373]});
                          end
                          else if (permutation == 10'd374) begin
                              enc <= enc ^ ({hv[373:0], hv[DIM:374]});
                          end
                          else if (permutation == 10'd375) begin
                              enc <= enc ^ ({hv[374:0], hv[DIM:375]});
                          end
                          else if (permutation == 10'd376) begin
                              enc <= enc ^ ({hv[375:0], hv[DIM:376]});
                          end
                          else if (permutation == 10'd377) begin
                              enc <= enc ^ ({hv[376:0], hv[DIM:377]});
                          end
                          else if (permutation == 10'd378) begin
                              enc <= enc ^ ({hv[377:0], hv[DIM:378]});
                          end
                          else if (permutation == 10'd379) begin
                              enc <= enc ^ ({hv[378:0], hv[DIM:379]});
                          end
                          else if (permutation == 10'd380) begin
                              enc <= enc ^ ({hv[379:0], hv[DIM:380]});
                          end
                          else if (permutation == 10'd381) begin
                              enc <= enc ^ ({hv[380:0], hv[DIM:381]});
                          end
                          else if (permutation == 10'd382) begin
                              enc <= enc ^ ({hv[381:0], hv[DIM:382]});
                          end
                          else if (permutation == 10'd383) begin
                              enc <= enc ^ ({hv[382:0], hv[DIM:383]});
                          end
                          else if (permutation == 10'd384) begin
                              enc <= enc ^ ({hv[383:0], hv[DIM:384]});
                          end
                          else if (permutation == 10'd385) begin
                              enc <= enc ^ ({hv[384:0], hv[DIM:385]});
                          end
                          else if (permutation == 10'd386) begin
                              enc <= enc ^ ({hv[385:0], hv[DIM:386]});
                          end
                          else if (permutation == 10'd387) begin
                              enc <= enc ^ ({hv[386:0], hv[DIM:387]});
                          end
                          else if (permutation == 10'd388) begin
                              enc <= enc ^ ({hv[387:0], hv[DIM:388]});
                          end
                          else if (permutation == 10'd389) begin
                              enc <= enc ^ ({hv[388:0], hv[DIM:389]});
                          end
                          else if (permutation == 10'd390) begin
                              enc <= enc ^ ({hv[389:0], hv[DIM:390]});
                          end
                          else if (permutation == 10'd391) begin
                              enc <= enc ^ ({hv[390:0], hv[DIM:391]});
                          end
                          else if (permutation == 10'd392) begin
                              enc <= enc ^ ({hv[391:0], hv[DIM:392]});
                          end
                          else if (permutation == 10'd393) begin
                              enc <= enc ^ ({hv[392:0], hv[DIM:393]});
                          end
                          else if (permutation == 10'd394) begin
                              enc <= enc ^ ({hv[393:0], hv[DIM:394]});
                          end
                          else if (permutation == 10'd395) begin
                              enc <= enc ^ ({hv[394:0], hv[DIM:395]});
                          end
                          else if (permutation == 10'd396) begin
                              enc <= enc ^ ({hv[395:0], hv[DIM:396]});
                          end
                          else if (permutation == 10'd397) begin
                              enc <= enc ^ ({hv[396:0], hv[DIM:397]});
                          end
                          else if (permutation == 10'd398) begin
                              enc <= enc ^ ({hv[397:0], hv[DIM:398]});
                          end
                          else if (permutation == 10'd399) begin
                              enc <= enc ^ ({hv[398:0], hv[DIM:399]});
                          end
                          else if (permutation == 10'd400) begin
                              enc <= enc ^ ({hv[399:0], hv[DIM:400]});
                          end
                          else if (permutation == 10'd401) begin
                              enc <= enc ^ ({hv[400:0], hv[DIM:401]});
                          end
                          else if (permutation == 10'd402) begin
                              enc <= enc ^ ({hv[401:0], hv[DIM:402]});
                          end
                          else if (permutation == 10'd403) begin
                              enc <= enc ^ ({hv[402:0], hv[DIM:403]});
                          end
                          else if (permutation == 10'd404) begin
                              enc <= enc ^ ({hv[403:0], hv[DIM:404]});
                          end
                          else if (permutation == 10'd405) begin
                              enc <= enc ^ ({hv[404:0], hv[DIM:405]});
                          end
                          else if (permutation == 10'd406) begin
                              enc <= enc ^ ({hv[405:0], hv[DIM:406]});
                          end
                          else if (permutation == 10'd407) begin
                              enc <= enc ^ ({hv[406:0], hv[DIM:407]});
                          end
                          else if (permutation == 10'd408) begin
                              enc <= enc ^ ({hv[407:0], hv[DIM:408]});
                          end
                          else if (permutation == 10'd409) begin
                              enc <= enc ^ ({hv[408:0], hv[DIM:409]});
                          end
                          else if (permutation == 10'd410) begin
                              enc <= enc ^ ({hv[409:0], hv[DIM:410]});
                          end
                          else if (permutation == 10'd411) begin
                              enc <= enc ^ ({hv[410:0], hv[DIM:411]});
                          end
                          else if (permutation == 10'd412) begin
                              enc <= enc ^ ({hv[411:0], hv[DIM:412]});
                          end
                          else if (permutation == 10'd413) begin
                              enc <= enc ^ ({hv[412:0], hv[DIM:413]});
                          end
                          else if (permutation == 10'd414) begin
                              enc <= enc ^ ({hv[413:0], hv[DIM:414]});
                          end
                          else if (permutation == 10'd415) begin
                              enc <= enc ^ ({hv[414:0], hv[DIM:415]});
                          end
                          else if (permutation == 10'd416) begin
                              enc <= enc ^ ({hv[415:0], hv[DIM:416]});
                          end
                          else if (permutation == 10'd417) begin
                              enc <= enc ^ ({hv[416:0], hv[DIM:417]});
                          end
                          else if (permutation == 10'd418) begin
                              enc <= enc ^ ({hv[417:0], hv[DIM:418]});
                          end
                          else if (permutation == 10'd419) begin
                              enc <= enc ^ ({hv[418:0], hv[DIM:419]});
                          end
                          else if (permutation == 10'd420) begin
                              enc <= enc ^ ({hv[419:0], hv[DIM:420]});
                          end
                          else if (permutation == 10'd421) begin
                              enc <= enc ^ ({hv[420:0], hv[DIM:421]});
                          end
                          else if (permutation == 10'd422) begin
                              enc <= enc ^ ({hv[421:0], hv[DIM:422]});
                          end
                          else if (permutation == 10'd423) begin
                              enc <= enc ^ ({hv[422:0], hv[DIM:423]});
                          end
                          else if (permutation == 10'd424) begin
                              enc <= enc ^ ({hv[423:0], hv[DIM:424]});
                          end
                          else if (permutation == 10'd425) begin
                              enc <= enc ^ ({hv[424:0], hv[DIM:425]});
                          end
                          else if (permutation == 10'd426) begin
                              enc <= enc ^ ({hv[425:0], hv[DIM:426]});
                          end
                          else if (permutation == 10'd427) begin
                              enc <= enc ^ ({hv[426:0], hv[DIM:427]});
                          end
                          else if (permutation == 10'd428) begin
                              enc <= enc ^ ({hv[427:0], hv[DIM:428]});
                          end
                          else if (permutation == 10'd429) begin
                              enc <= enc ^ ({hv[428:0], hv[DIM:429]});
                          end
                          else if (permutation == 10'd430) begin
                              enc <= enc ^ ({hv[429:0], hv[DIM:430]});
                          end
                          else if (permutation == 10'd431) begin
                              enc <= enc ^ ({hv[430:0], hv[DIM:431]});
                          end
                          else if (permutation == 10'd432) begin
                              enc <= enc ^ ({hv[431:0], hv[DIM:432]});
                          end
                          else if (permutation == 10'd433) begin
                              enc <= enc ^ ({hv[432:0], hv[DIM:433]});
                          end
                          else if (permutation == 10'd434) begin
                              enc <= enc ^ ({hv[433:0], hv[DIM:434]});
                          end
                          else if (permutation == 10'd435) begin
                              enc <= enc ^ ({hv[434:0], hv[DIM:435]});
                          end
                          else if (permutation == 10'd436) begin
                              enc <= enc ^ ({hv[435:0], hv[DIM:436]});
                          end
                          else if (permutation == 10'd437) begin
                              enc <= enc ^ ({hv[436:0], hv[DIM:437]});
                          end
                          else if (permutation == 10'd438) begin
                              enc <= enc ^ ({hv[437:0], hv[DIM:438]});
                          end
                          else if (permutation == 10'd439) begin
                              enc <= enc ^ ({hv[438:0], hv[DIM:439]});
                          end
                          else if (permutation == 10'd440) begin
                              enc <= enc ^ ({hv[439:0], hv[DIM:440]});
                          end
                          else if (permutation == 10'd441) begin
                              enc <= enc ^ ({hv[440:0], hv[DIM:441]});
                          end
                          else if (permutation == 10'd442) begin
                              enc <= enc ^ ({hv[441:0], hv[DIM:442]});
                          end
                          else if (permutation == 10'd443) begin
                              enc <= enc ^ ({hv[442:0], hv[DIM:443]});
                          end
                          else if (permutation == 10'd444) begin
                              enc <= enc ^ ({hv[443:0], hv[DIM:444]});
                          end
                          else if (permutation == 10'd445) begin
                              enc <= enc ^ ({hv[444:0], hv[DIM:445]});
                          end
                          else if (permutation == 10'd446) begin
                              enc <= enc ^ ({hv[445:0], hv[DIM:446]});
                          end
                          else if (permutation == 10'd447) begin
                              enc <= enc ^ ({hv[446:0], hv[DIM:447]});
                          end
                          else if (permutation == 10'd448) begin
                              enc <= enc ^ ({hv[447:0], hv[DIM:448]});
                          end
                          else if (permutation == 10'd449) begin
                              enc <= enc ^ ({hv[448:0], hv[DIM:449]});
                          end
                          else if (permutation == 10'd450) begin
                              enc <= enc ^ ({hv[449:0], hv[DIM:450]});
                          end
                          else if (permutation == 10'd451) begin
                              enc <= enc ^ ({hv[450:0], hv[DIM:451]});
                          end
                          else if (permutation == 10'd452) begin
                              enc <= enc ^ ({hv[451:0], hv[DIM:452]});
                          end
                          else if (permutation == 10'd453) begin
                              enc <= enc ^ ({hv[452:0], hv[DIM:453]});
                          end
                          else if (permutation == 10'd454) begin
                              enc <= enc ^ ({hv[453:0], hv[DIM:454]});
                          end
                          else if (permutation == 10'd455) begin
                              enc <= enc ^ ({hv[454:0], hv[DIM:455]});
                          end
                          else if (permutation == 10'd456) begin
                              enc <= enc ^ ({hv[455:0], hv[DIM:456]});
                          end
                          else if (permutation == 10'd457) begin
                              enc <= enc ^ ({hv[456:0], hv[DIM:457]});
                          end
                          else if (permutation == 10'd458) begin
                              enc <= enc ^ ({hv[457:0], hv[DIM:458]});
                          end
                          else if (permutation == 10'd459) begin
                              enc <= enc ^ ({hv[458:0], hv[DIM:459]});
                          end
                          else if (permutation == 10'd460) begin
                              enc <= enc ^ ({hv[459:0], hv[DIM:460]});
                          end
                          else if (permutation == 10'd461) begin
                              enc <= enc ^ ({hv[460:0], hv[DIM:461]});
                          end
                          else if (permutation == 10'd462) begin
                              enc <= enc ^ ({hv[461:0], hv[DIM:462]});
                          end
                          else if (permutation == 10'd463) begin
                              enc <= enc ^ ({hv[462:0], hv[DIM:463]});
                          end
                          else if (permutation == 10'd464) begin
                              enc <= enc ^ ({hv[463:0], hv[DIM:464]});
                          end
                          else if (permutation == 10'd465) begin
                              enc <= enc ^ ({hv[464:0], hv[DIM:465]});
                          end
                          else if (permutation == 10'd466) begin
                              enc <= enc ^ ({hv[465:0], hv[DIM:466]});
                          end
                          else if (permutation == 10'd467) begin
                              enc <= enc ^ ({hv[466:0], hv[DIM:467]});
                          end
                          else if (permutation == 10'd468) begin
                              enc <= enc ^ ({hv[467:0], hv[DIM:468]});
                          end
                          else if (permutation == 10'd469) begin
                              enc <= enc ^ ({hv[468:0], hv[DIM:469]});
                          end
                          else if (permutation == 10'd470) begin
                              enc <= enc ^ ({hv[469:0], hv[DIM:470]});
                          end
                          else if (permutation == 10'd471) begin
                              enc <= enc ^ ({hv[470:0], hv[DIM:471]});
                          end
                          else if (permutation == 10'd472) begin
                              enc <= enc ^ ({hv[471:0], hv[DIM:472]});
                          end
                          else if (permutation == 10'd473) begin
                              enc <= enc ^ ({hv[472:0], hv[DIM:473]});
                          end
                          else if (permutation == 10'd474) begin
                              enc <= enc ^ ({hv[473:0], hv[DIM:474]});
                          end
                          else if (permutation == 10'd475) begin
                              enc <= enc ^ ({hv[474:0], hv[DIM:475]});
                          end
                          else if (permutation == 10'd476) begin
                              enc <= enc ^ ({hv[475:0], hv[DIM:476]});
                          end
                          else if (permutation == 10'd477) begin
                              enc <= enc ^ ({hv[476:0], hv[DIM:477]});
                          end
                          else if (permutation == 10'd478) begin
                              enc <= enc ^ ({hv[477:0], hv[DIM:478]});
                          end
                          else if (permutation == 10'd479) begin
                              enc <= enc ^ ({hv[478:0], hv[DIM:479]});
                          end
                          else if (permutation == 10'd480) begin
                              enc <= enc ^ ({hv[479:0], hv[DIM:480]});
                          end
                          else if (permutation == 10'd481) begin
                              enc <= enc ^ ({hv[480:0], hv[DIM:481]});
                          end
                          else if (permutation == 10'd482) begin
                              enc <= enc ^ ({hv[481:0], hv[DIM:482]});
                          end
                          else if (permutation == 10'd483) begin
                              enc <= enc ^ ({hv[482:0], hv[DIM:483]});
                          end
                          else if (permutation == 10'd484) begin
                              enc <= enc ^ ({hv[483:0], hv[DIM:484]});
                          end
                          else if (permutation == 10'd485) begin
                              enc <= enc ^ ({hv[484:0], hv[DIM:485]});
                          end
                          else if (permutation == 10'd486) begin
                              enc <= enc ^ ({hv[485:0], hv[DIM:486]});
                          end
                          else if (permutation == 10'd487) begin
                              enc <= enc ^ ({hv[486:0], hv[DIM:487]});
                          end
                          else if (permutation == 10'd488) begin
                              enc <= enc ^ ({hv[487:0], hv[DIM:488]});
                          end
                          else if (permutation == 10'd489) begin
                              enc <= enc ^ ({hv[488:0], hv[DIM:489]});
                          end
                          else if (permutation == 10'd490) begin
                              enc <= enc ^ ({hv[489:0], hv[DIM:490]});
                          end
                          else if (permutation == 10'd491) begin
                              enc <= enc ^ ({hv[490:0], hv[DIM:491]});
                          end
                          else if (permutation == 10'd492) begin
                              enc <= enc ^ ({hv[491:0], hv[DIM:492]});
                          end
                          else if (permutation == 10'd493) begin
                              enc <= enc ^ ({hv[492:0], hv[DIM:493]});
                          end
                          else if (permutation == 10'd494) begin
                              enc <= enc ^ ({hv[493:0], hv[DIM:494]});
                          end
                          else if (permutation == 10'd495) begin
                              enc <= enc ^ ({hv[494:0], hv[DIM:495]});
                          end
                          else if (permutation == 10'd496) begin
                              enc <= enc ^ ({hv[495:0], hv[DIM:496]});
                          end
                          else if (permutation == 10'd497) begin
                              enc <= enc ^ ({hv[496:0], hv[DIM:497]});
                          end
                          else if (permutation == 10'd498) begin
                              enc <= enc ^ ({hv[497:0], hv[DIM:498]});
                          end
                          else if (permutation == 10'd499) begin
                              enc <= enc ^ ({hv[498:0], hv[DIM:499]});
                          end
                          else if (permutation == 10'd500) begin
                              enc <= enc ^ ({hv[499:0], hv[DIM:500]});
                          end
                          else if (permutation == 10'd501) begin
                              enc <= enc ^ ({hv[500:0], hv[DIM:501]});
                          end
                          else if (permutation == 10'd502) begin
                              enc <= enc ^ ({hv[501:0], hv[DIM:502]});
                          end
                          else if (permutation == 10'd503) begin
                              enc <= enc ^ ({hv[502:0], hv[DIM:503]});
                          end
                          else if (permutation == 10'd504) begin
                              enc <= enc ^ ({hv[503:0], hv[DIM:504]});
                          end
                          else if (permutation == 10'd505) begin
                              enc <= enc ^ ({hv[504:0], hv[DIM:505]});
                          end
                          else if (permutation == 10'd506) begin
                              enc <= enc ^ ({hv[505:0], hv[DIM:506]});
                          end
                          else if (permutation == 10'd507) begin
                              enc <= enc ^ ({hv[506:0], hv[DIM:507]});
                          end
                          else if (permutation == 10'd508) begin
                              enc <= enc ^ ({hv[507:0], hv[DIM:508]});
                          end
                          else if (permutation == 10'd509) begin
                              enc <= enc ^ ({hv[508:0], hv[DIM:509]});
                          end
                          else if (permutation == 10'd510) begin
                              enc <= enc ^ ({hv[509:0], hv[DIM:510]});
                          end
                          else if (permutation == 10'd511) begin
                              enc <= enc ^ ({hv[510:0], hv[DIM:511]});
                          end
                          else if (permutation == 10'd512) begin
                              enc <= enc ^ ({hv[511:0], hv[DIM:512]});
                          end
                          else if (permutation == 10'd513) begin
                              enc <= enc ^ ({hv[512:0], hv[DIM:513]});
                          end
                          else if (permutation == 10'd514) begin
                              enc <= enc ^ ({hv[513:0], hv[DIM:514]});
                          end
                          else if (permutation == 10'd515) begin
                              enc <= enc ^ ({hv[514:0], hv[DIM:515]});
                          end
                          else if (permutation == 10'd516) begin
                              enc <= enc ^ ({hv[515:0], hv[DIM:516]});
                          end
                          else if (permutation == 10'd517) begin
                              enc <= enc ^ ({hv[516:0], hv[DIM:517]});
                          end
                          else if (permutation == 10'd518) begin
                              enc <= enc ^ ({hv[517:0], hv[DIM:518]});
                          end
                          else if (permutation == 10'd519) begin
                              enc <= enc ^ ({hv[518:0], hv[DIM:519]});
                          end
                          else if (permutation == 10'd520) begin
                              enc <= enc ^ ({hv[519:0], hv[DIM:520]});
                          end
                          else if (permutation == 10'd521) begin
                              enc <= enc ^ ({hv[520:0], hv[DIM:521]});
                          end
                          else if (permutation == 10'd522) begin
                              enc <= enc ^ ({hv[521:0], hv[DIM:522]});
                          end
                          else if (permutation == 10'd523) begin
                              enc <= enc ^ ({hv[522:0], hv[DIM:523]});
                          end
                          else if (permutation == 10'd524) begin
                              enc <= enc ^ ({hv[523:0], hv[DIM:524]});
                          end
                          else if (permutation == 10'd525) begin
                              enc <= enc ^ ({hv[524:0], hv[DIM:525]});
                          end
                          else if (permutation == 10'd526) begin
                              enc <= enc ^ ({hv[525:0], hv[DIM:526]});
                          end
                          else if (permutation == 10'd527) begin
                              enc <= enc ^ ({hv[526:0], hv[DIM:527]});
                          end
                          else if (permutation == 10'd528) begin
                              enc <= enc ^ ({hv[527:0], hv[DIM:528]});
                          end
                          else if (permutation == 10'd529) begin
                              enc <= enc ^ ({hv[528:0], hv[DIM:529]});
                          end
                          else if (permutation == 10'd530) begin
                              enc <= enc ^ ({hv[529:0], hv[DIM:530]});
                          end
                          else if (permutation == 10'd531) begin
                              enc <= enc ^ ({hv[530:0], hv[DIM:531]});
                          end
                          else if (permutation == 10'd532) begin
                              enc <= enc ^ ({hv[531:0], hv[DIM:532]});
                          end
                          else if (permutation == 10'd533) begin
                              enc <= enc ^ ({hv[532:0], hv[DIM:533]});
                          end
                          else if (permutation == 10'd534) begin
                              enc <= enc ^ ({hv[533:0], hv[DIM:534]});
                          end
                          else if (permutation == 10'd535) begin
                              enc <= enc ^ ({hv[534:0], hv[DIM:535]});
                          end
                          else if (permutation == 10'd536) begin
                              enc <= enc ^ ({hv[535:0], hv[DIM:536]});
                          end
                          else if (permutation == 10'd537) begin
                              enc <= enc ^ ({hv[536:0], hv[DIM:537]});
                          end
                          else if (permutation == 10'd538) begin
                              enc <= enc ^ ({hv[537:0], hv[DIM:538]});
                          end
                          else if (permutation == 10'd539) begin
                              enc <= enc ^ ({hv[538:0], hv[DIM:539]});
                          end
                          else if (permutation == 10'd540) begin
                              enc <= enc ^ ({hv[539:0], hv[DIM:540]});
                          end
                          else if (permutation == 10'd541) begin
                              enc <= enc ^ ({hv[540:0], hv[DIM:541]});
                          end
                          else if (permutation == 10'd542) begin
                              enc <= enc ^ ({hv[541:0], hv[DIM:542]});
                          end
                          else if (permutation == 10'd543) begin
                              enc <= enc ^ ({hv[542:0], hv[DIM:543]});
                          end
                          else if (permutation == 10'd544) begin
                              enc <= enc ^ ({hv[543:0], hv[DIM:544]});
                          end
                          else if (permutation == 10'd545) begin
                              enc <= enc ^ ({hv[544:0], hv[DIM:545]});
                          end
                          else if (permutation == 10'd546) begin
                              enc <= enc ^ ({hv[545:0], hv[DIM:546]});
                          end
                          else if (permutation == 10'd547) begin
                              enc <= enc ^ ({hv[546:0], hv[DIM:547]});
                          end
                          else if (permutation == 10'd548) begin
                              enc <= enc ^ ({hv[547:0], hv[DIM:548]});
                          end
                          else if (permutation == 10'd549) begin
                              enc <= enc ^ ({hv[548:0], hv[DIM:549]});
                          end
                          else if (permutation == 10'd550) begin
                              enc <= enc ^ ({hv[549:0], hv[DIM:550]});
                          end
                          else if (permutation == 10'd551) begin
                              enc <= enc ^ ({hv[550:0], hv[DIM:551]});
                          end
                          else if (permutation == 10'd552) begin
                              enc <= enc ^ ({hv[551:0], hv[DIM:552]});
                          end
                          else if (permutation == 10'd553) begin
                              enc <= enc ^ ({hv[552:0], hv[DIM:553]});
                          end
                          else if (permutation == 10'd554) begin
                              enc <= enc ^ ({hv[553:0], hv[DIM:554]});
                          end
                          else if (permutation == 10'd555) begin
                              enc <= enc ^ ({hv[554:0], hv[DIM:555]});
                          end
                          else if (permutation == 10'd556) begin
                              enc <= enc ^ ({hv[555:0], hv[DIM:556]});
                          end
                          else if (permutation == 10'd557) begin
                              enc <= enc ^ ({hv[556:0], hv[DIM:557]});
                          end
                          else if (permutation == 10'd558) begin
                              enc <= enc ^ ({hv[557:0], hv[DIM:558]});
                          end
                          else if (permutation == 10'd559) begin
                              enc <= enc ^ ({hv[558:0], hv[DIM:559]});
                          end
                          else if (permutation == 10'd560) begin
                              enc <= enc ^ ({hv[559:0], hv[DIM:560]});
                          end
                          else if (permutation == 10'd561) begin
                              enc <= enc ^ ({hv[560:0], hv[DIM:561]});
                          end
                          else if (permutation == 10'd562) begin
                              enc <= enc ^ ({hv[561:0], hv[DIM:562]});
                          end
                          else if (permutation == 10'd563) begin
                              enc <= enc ^ ({hv[562:0], hv[DIM:563]});
                          end
                          else if (permutation == 10'd564) begin
                              enc <= enc ^ ({hv[563:0], hv[DIM:564]});
                          end
                          else if (permutation == 10'd565) begin
                              enc <= enc ^ ({hv[564:0], hv[DIM:565]});
                          end
                          else if (permutation == 10'd566) begin
                              enc <= enc ^ ({hv[565:0], hv[DIM:566]});
                          end
                          else if (permutation == 10'd567) begin
                              enc <= enc ^ ({hv[566:0], hv[DIM:567]});
                          end
                          else if (permutation == 10'd568) begin
                              enc <= enc ^ ({hv[567:0], hv[DIM:568]});
                          end
                          else if (permutation == 10'd569) begin
                              enc <= enc ^ ({hv[568:0], hv[DIM:569]});
                          end
                          else if (permutation == 10'd570) begin
                              enc <= enc ^ ({hv[569:0], hv[DIM:570]});
                          end
                          else if (permutation == 10'd571) begin
                              enc <= enc ^ ({hv[570:0], hv[DIM:571]});
                          end
                          else if (permutation == 10'd572) begin
                              enc <= enc ^ ({hv[571:0], hv[DIM:572]});
                          end
                          else if (permutation == 10'd573) begin
                              enc <= enc ^ ({hv[572:0], hv[DIM:573]});
                          end
                          else if (permutation == 10'd574) begin
                              enc <= enc ^ ({hv[573:0], hv[DIM:574]});
                          end
                          else if (permutation == 10'd575) begin
                              enc <= enc ^ ({hv[574:0], hv[DIM:575]});
                          end
                          else if (permutation == 10'd576) begin
                              enc <= enc ^ ({hv[575:0], hv[DIM:576]});
                          end
                          else if (permutation == 10'd577) begin
                              enc <= enc ^ ({hv[576:0], hv[DIM:577]});
                          end
                          else if (permutation == 10'd578) begin
                              enc <= enc ^ ({hv[577:0], hv[DIM:578]});
                          end
                          else if (permutation == 10'd579) begin
                              enc <= enc ^ ({hv[578:0], hv[DIM:579]});
                          end
                          else if (permutation == 10'd580) begin
                              enc <= enc ^ ({hv[579:0], hv[DIM:580]});
                          end
                          else if (permutation == 10'd581) begin
                              enc <= enc ^ ({hv[580:0], hv[DIM:581]});
                          end
                          else if (permutation == 10'd582) begin
                              enc <= enc ^ ({hv[581:0], hv[DIM:582]});
                          end
                          else if (permutation == 10'd583) begin
                              enc <= enc ^ ({hv[582:0], hv[DIM:583]});
                          end
                          else if (permutation == 10'd584) begin
                              enc <= enc ^ ({hv[583:0], hv[DIM:584]});
                          end
                          else if (permutation == 10'd585) begin
                              enc <= enc ^ ({hv[584:0], hv[DIM:585]});
                          end
                          else if (permutation == 10'd586) begin
                              enc <= enc ^ ({hv[585:0], hv[DIM:586]});
                          end
                          else if (permutation == 10'd587) begin
                              enc <= enc ^ ({hv[586:0], hv[DIM:587]});
                          end
                          else if (permutation == 10'd588) begin
                              enc <= enc ^ ({hv[587:0], hv[DIM:588]});
                          end
                          else if (permutation == 10'd589) begin
                              enc <= enc ^ ({hv[588:0], hv[DIM:589]});
                          end
                          else if (permutation == 10'd590) begin
                              enc <= enc ^ ({hv[589:0], hv[DIM:590]});
                          end
                          else if (permutation == 10'd591) begin
                              enc <= enc ^ ({hv[590:0], hv[DIM:591]});
                          end
                          else if (permutation == 10'd592) begin
                              enc <= enc ^ ({hv[591:0], hv[DIM:592]});
                          end
                          else if (permutation == 10'd593) begin
                              enc <= enc ^ ({hv[592:0], hv[DIM:593]});
                          end
                          else if (permutation == 10'd594) begin
                              enc <= enc ^ ({hv[593:0], hv[DIM:594]});
                          end
                          else if (permutation == 10'd595) begin
                              enc <= enc ^ ({hv[594:0], hv[DIM:595]});
                          end
                          else if (permutation == 10'd596) begin
                              enc <= enc ^ ({hv[595:0], hv[DIM:596]});
                          end
                          else if (permutation == 10'd597) begin
                              enc <= enc ^ ({hv[596:0], hv[DIM:597]});
                          end
                          else if (permutation == 10'd598) begin
                              enc <= enc ^ ({hv[597:0], hv[DIM:598]});
                          end
                          else if (permutation == 10'd599) begin
                              enc <= enc ^ ({hv[598:0], hv[DIM:599]});
                          end
                          else if (permutation == 10'd600) begin
                              enc <= enc ^ ({hv[599:0], hv[DIM:600]});
                          end
                          else if (permutation == 10'd601) begin
                              enc <= enc ^ ({hv[600:0], hv[DIM:601]});
                          end
                          else if (permutation == 10'd602) begin
                              enc <= enc ^ ({hv[601:0], hv[DIM:602]});
                          end
                          else if (permutation == 10'd603) begin
                              enc <= enc ^ ({hv[602:0], hv[DIM:603]});
                          end
                          else if (permutation == 10'd604) begin
                              enc <= enc ^ ({hv[603:0], hv[DIM:604]});
                          end
                          else if (permutation == 10'd605) begin
                              enc <= enc ^ ({hv[604:0], hv[DIM:605]});
                          end
                          else if (permutation == 10'd606) begin
                              enc <= enc ^ ({hv[605:0], hv[DIM:606]});
                          end
                          else if (permutation == 10'd607) begin
                              enc <= enc ^ ({hv[606:0], hv[DIM:607]});
                          end
                          else if (permutation == 10'd608) begin
                              enc <= enc ^ ({hv[607:0], hv[DIM:608]});
                          end
                          else if (permutation == 10'd609) begin
                              enc <= enc ^ ({hv[608:0], hv[DIM:609]});
                          end
                          else if (permutation == 10'd610) begin
                              enc <= enc ^ ({hv[609:0], hv[DIM:610]});
                          end
                          else if (permutation == 10'd611) begin
                              enc <= enc ^ ({hv[610:0], hv[DIM:611]});
                          end
                          else if (permutation == 10'd612) begin
                              enc <= enc ^ ({hv[611:0], hv[DIM:612]});
                          end
                          else if (permutation == 10'd613) begin
                              enc <= enc ^ ({hv[612:0], hv[DIM:613]});
                          end
                          else if (permutation == 10'd614) begin
                              enc <= enc ^ ({hv[613:0], hv[DIM:614]});
                          end
                          else if (permutation == 10'd615) begin
                              enc <= enc ^ ({hv[614:0], hv[DIM:615]});
                          end
                          else if (permutation == 10'd616) begin
                              enc <= enc ^ ({hv[615:0], hv[DIM:616]});
                          end
                          else if (permutation == 10'd617) begin
                              enc <= enc ^ ({hv[616:0], hv[DIM:617]});
                          end
                          else if (permutation == 10'd618) begin
                              enc <= enc ^ ({hv[617:0], hv[DIM:618]});
                          end
                          else if (permutation == 10'd619) begin
                              enc <= enc ^ ({hv[618:0], hv[DIM:619]});
                          end
                          else if (permutation == 10'd620) begin
                              enc <= enc ^ ({hv[619:0], hv[DIM:620]});
                          end
                          else if (permutation == 10'd621) begin
                              enc <= enc ^ ({hv[620:0], hv[DIM:621]});
                          end
                          else if (permutation == 10'd622) begin
                              enc <= enc ^ ({hv[621:0], hv[DIM:622]});
                          end
                          else if (permutation == 10'd623) begin
                              enc <= enc ^ ({hv[622:0], hv[DIM:623]});
                          end
                          else if (permutation == 10'd624) begin
                              enc <= enc ^ ({hv[623:0], hv[DIM:624]});
                          end
                          else if (permutation == 10'd625) begin
                              enc <= enc ^ ({hv[624:0], hv[DIM:625]});
                          end
                          else if (permutation == 10'd626) begin
                              enc <= enc ^ ({hv[625:0], hv[DIM:626]});
                          end
                          else if (permutation == 10'd627) begin
                              enc <= enc ^ ({hv[626:0], hv[DIM:627]});
                          end
                          else if (permutation == 10'd628) begin
                              enc <= enc ^ ({hv[627:0], hv[DIM:628]});
                          end
                          else if (permutation == 10'd629) begin
                              enc <= enc ^ ({hv[628:0], hv[DIM:629]});
                          end
                          else if (permutation == 10'd630) begin
                              enc <= enc ^ ({hv[629:0], hv[DIM:630]});
                          end
                          else if (permutation == 10'd631) begin
                              enc <= enc ^ ({hv[630:0], hv[DIM:631]});
                          end
                          else if (permutation == 10'd632) begin
                              enc <= enc ^ ({hv[631:0], hv[DIM:632]});
                          end
                          else if (permutation == 10'd633) begin
                              enc <= enc ^ ({hv[632:0], hv[DIM:633]});
                          end
                          else if (permutation == 10'd634) begin
                              enc <= enc ^ ({hv[633:0], hv[DIM:634]});
                          end
                          else if (permutation == 10'd635) begin
                              enc <= enc ^ ({hv[634:0], hv[DIM:635]});
                          end
                          else if (permutation == 10'd636) begin
                              enc <= enc ^ ({hv[635:0], hv[DIM:636]});
                          end
                          else if (permutation == 10'd637) begin
                              enc <= enc ^ ({hv[636:0], hv[DIM:637]});
                          end
                          else if (permutation == 10'd638) begin
                              enc <= enc ^ ({hv[637:0], hv[DIM:638]});
                          end
                          else if (permutation == 10'd639) begin
                              enc <= enc ^ ({hv[638:0], hv[DIM:639]});
                          end
                          else if (permutation == 10'd640) begin
                              enc <= enc ^ ({hv[639:0], hv[DIM:640]});
                          end
                          else if (permutation == 10'd641) begin
                              enc <= enc ^ ({hv[640:0], hv[DIM:641]});
                          end
                          else if (permutation == 10'd642) begin
                              enc <= enc ^ ({hv[641:0], hv[DIM:642]});
                          end
                          else if (permutation == 10'd643) begin
                              enc <= enc ^ ({hv[642:0], hv[DIM:643]});
                          end
                          else if (permutation == 10'd644) begin
                              enc <= enc ^ ({hv[643:0], hv[DIM:644]});
                          end
                          else if (permutation == 10'd645) begin
                              enc <= enc ^ ({hv[644:0], hv[DIM:645]});
                          end
                          else if (permutation == 10'd646) begin
                              enc <= enc ^ ({hv[645:0], hv[DIM:646]});
                          end
                          else if (permutation == 10'd647) begin
                              enc <= enc ^ ({hv[646:0], hv[DIM:647]});
                          end
                          else if (permutation == 10'd648) begin
                              enc <= enc ^ ({hv[647:0], hv[DIM:648]});
                          end
                          else if (permutation == 10'd649) begin
                              enc <= enc ^ ({hv[648:0], hv[DIM:649]});
                          end
                          else if (permutation == 10'd650) begin
                              enc <= enc ^ ({hv[649:0], hv[DIM:650]});
                          end
                          else if (permutation == 10'd651) begin
                              enc <= enc ^ ({hv[650:0], hv[DIM:651]});
                          end
                          else if (permutation == 10'd652) begin
                              enc <= enc ^ ({hv[651:0], hv[DIM:652]});
                          end
                          else if (permutation == 10'd653) begin
                              enc <= enc ^ ({hv[652:0], hv[DIM:653]});
                          end
                          else if (permutation == 10'd654) begin
                              enc <= enc ^ ({hv[653:0], hv[DIM:654]});
                          end
                          else if (permutation == 10'd655) begin
                              enc <= enc ^ ({hv[654:0], hv[DIM:655]});
                          end
                          else if (permutation == 10'd656) begin
                              enc <= enc ^ ({hv[655:0], hv[DIM:656]});
                          end
                          else if (permutation == 10'd657) begin
                              enc <= enc ^ ({hv[656:0], hv[DIM:657]});
                          end
                          else if (permutation == 10'd658) begin
                              enc <= enc ^ ({hv[657:0], hv[DIM:658]});
                          end
                          else if (permutation == 10'd659) begin
                              enc <= enc ^ ({hv[658:0], hv[DIM:659]});
                          end
                          else if (permutation == 10'd660) begin
                              enc <= enc ^ ({hv[659:0], hv[DIM:660]});
                          end
                          else if (permutation == 10'd661) begin
                              enc <= enc ^ ({hv[660:0], hv[DIM:661]});
                          end
                          else if (permutation == 10'd662) begin
                              enc <= enc ^ ({hv[661:0], hv[DIM:662]});
                          end
                          else if (permutation == 10'd663) begin
                              enc <= enc ^ ({hv[662:0], hv[DIM:663]});
                          end
                          else if (permutation == 10'd664) begin
                              enc <= enc ^ ({hv[663:0], hv[DIM:664]});
                          end
                          else if (permutation == 10'd665) begin
                              enc <= enc ^ ({hv[664:0], hv[DIM:665]});
                          end
                          else if (permutation == 10'd666) begin
                              enc <= enc ^ ({hv[665:0], hv[DIM:666]});
                          end
                          else if (permutation == 10'd667) begin
                              enc <= enc ^ ({hv[666:0], hv[DIM:667]});
                          end
                          else if (permutation == 10'd668) begin
                              enc <= enc ^ ({hv[667:0], hv[DIM:668]});
                          end
                          else if (permutation == 10'd669) begin
                              enc <= enc ^ ({hv[668:0], hv[DIM:669]});
                          end
                          else if (permutation == 10'd670) begin
                              enc <= enc ^ ({hv[669:0], hv[DIM:670]});
                          end
                          else if (permutation == 10'd671) begin
                              enc <= enc ^ ({hv[670:0], hv[DIM:671]});
                          end
                          else if (permutation == 10'd672) begin
                              enc <= enc ^ ({hv[671:0], hv[DIM:672]});
                          end
                          else if (permutation == 10'd673) begin
                              enc <= enc ^ ({hv[672:0], hv[DIM:673]});
                          end
                          else if (permutation == 10'd674) begin
                              enc <= enc ^ ({hv[673:0], hv[DIM:674]});
                          end
                          else if (permutation == 10'd675) begin
                              enc <= enc ^ ({hv[674:0], hv[DIM:675]});
                          end
                          else if (permutation == 10'd676) begin
                              enc <= enc ^ ({hv[675:0], hv[DIM:676]});
                          end
                          else if (permutation == 10'd677) begin
                              enc <= enc ^ ({hv[676:0], hv[DIM:677]});
                          end
                          else if (permutation == 10'd678) begin
                              enc <= enc ^ ({hv[677:0], hv[DIM:678]});
                          end
                          else if (permutation == 10'd679) begin
                              enc <= enc ^ ({hv[678:0], hv[DIM:679]});
                          end
                          else if (permutation == 10'd680) begin
                              enc <= enc ^ ({hv[679:0], hv[DIM:680]});
                          end
                          else if (permutation == 10'd681) begin
                              enc <= enc ^ ({hv[680:0], hv[DIM:681]});
                          end
                          else if (permutation == 10'd682) begin
                              enc <= enc ^ ({hv[681:0], hv[DIM:682]});
                          end
                          else if (permutation == 10'd683) begin
                              enc <= enc ^ ({hv[682:0], hv[DIM:683]});
                          end
                          else if (permutation == 10'd684) begin
                              enc <= enc ^ ({hv[683:0], hv[DIM:684]});
                          end
                          else if (permutation == 10'd685) begin
                              enc <= enc ^ ({hv[684:0], hv[DIM:685]});
                          end
                          else if (permutation == 10'd686) begin
                              enc <= enc ^ ({hv[685:0], hv[DIM:686]});
                          end
                          else if (permutation == 10'd687) begin
                              enc <= enc ^ ({hv[686:0], hv[DIM:687]});
                          end
                          else if (permutation == 10'd688) begin
                              enc <= enc ^ ({hv[687:0], hv[DIM:688]});
                          end
                          else if (permutation == 10'd689) begin
                              enc <= enc ^ ({hv[688:0], hv[DIM:689]});
                          end
                          else if (permutation == 10'd690) begin
                              enc <= enc ^ ({hv[689:0], hv[DIM:690]});
                          end
                          else if (permutation == 10'd691) begin
                              enc <= enc ^ ({hv[690:0], hv[DIM:691]});
                          end
                          else if (permutation == 10'd692) begin
                              enc <= enc ^ ({hv[691:0], hv[DIM:692]});
                          end
                          else if (permutation == 10'd693) begin
                              enc <= enc ^ ({hv[692:0], hv[DIM:693]});
                          end
                          else if (permutation == 10'd694) begin
                              enc <= enc ^ ({hv[693:0], hv[DIM:694]});
                          end
                          else if (permutation == 10'd695) begin
                              enc <= enc ^ ({hv[694:0], hv[DIM:695]});
                          end
                          else if (permutation == 10'd696) begin
                              enc <= enc ^ ({hv[695:0], hv[DIM:696]});
                          end
                          else if (permutation == 10'd697) begin
                              enc <= enc ^ ({hv[696:0], hv[DIM:697]});
                          end
                          else if (permutation == 10'd698) begin
                              enc <= enc ^ ({hv[697:0], hv[DIM:698]});
                          end
                          else if (permutation == 10'd699) begin
                              enc <= enc ^ ({hv[698:0], hv[DIM:699]});
                          end
                          else if (permutation == 10'd700) begin
                              enc <= enc ^ ({hv[699:0], hv[DIM:700]});
                          end
                          else if (permutation == 10'd701) begin
                              enc <= enc ^ ({hv[700:0], hv[DIM:701]});
                          end
                          else if (permutation == 10'd702) begin
                              enc <= enc ^ ({hv[701:0], hv[DIM:702]});
                          end
                          else if (permutation == 10'd703) begin
                              enc <= enc ^ ({hv[702:0], hv[DIM:703]});
                          end
                          else if (permutation == 10'd704) begin
                              enc <= enc ^ ({hv[703:0], hv[DIM:704]});
                          end
                          else if (permutation == 10'd705) begin
                              enc <= enc ^ ({hv[704:0], hv[DIM:705]});
                          end
                          else if (permutation == 10'd706) begin
                              enc <= enc ^ ({hv[705:0], hv[DIM:706]});
                          end
                          else if (permutation == 10'd707) begin
                              enc <= enc ^ ({hv[706:0], hv[DIM:707]});
                          end
                          else if (permutation == 10'd708) begin
                              enc <= enc ^ ({hv[707:0], hv[DIM:708]});
                          end
                          else if (permutation == 10'd709) begin
                              enc <= enc ^ ({hv[708:0], hv[DIM:709]});
                          end
                          else if (permutation == 10'd710) begin
                              enc <= enc ^ ({hv[709:0], hv[DIM:710]});
                          end
                          else if (permutation == 10'd711) begin
                              enc <= enc ^ ({hv[710:0], hv[DIM:711]});
                          end
                          else if (permutation == 10'd712) begin
                              enc <= enc ^ ({hv[711:0], hv[DIM:712]});
                          end
                          else if (permutation == 10'd713) begin
                              enc <= enc ^ ({hv[712:0], hv[DIM:713]});
                          end
                          else if (permutation == 10'd714) begin
                              enc <= enc ^ ({hv[713:0], hv[DIM:714]});
                          end
                          else if (permutation == 10'd715) begin
                              enc <= enc ^ ({hv[714:0], hv[DIM:715]});
                          end
                          else if (permutation == 10'd716) begin
                              enc <= enc ^ ({hv[715:0], hv[DIM:716]});
                          end
                          else if (permutation == 10'd717) begin
                              enc <= enc ^ ({hv[716:0], hv[DIM:717]});
                          end
                          else if (permutation == 10'd718) begin
                              enc <= enc ^ ({hv[717:0], hv[DIM:718]});
                          end
                          else if (permutation == 10'd719) begin
                              enc <= enc ^ ({hv[718:0], hv[DIM:719]});
                          end
                          else if (permutation == 10'd720) begin
                              enc <= enc ^ ({hv[719:0], hv[DIM:720]});
                          end
                          else if (permutation == 10'd721) begin
                              enc <= enc ^ ({hv[720:0], hv[DIM:721]});
                          end
                          else if (permutation == 10'd722) begin
                              enc <= enc ^ ({hv[721:0], hv[DIM:722]});
                          end
                          else if (permutation == 10'd723) begin
                              enc <= enc ^ ({hv[722:0], hv[DIM:723]});
                          end
                          else if (permutation == 10'd724) begin
                              enc <= enc ^ ({hv[723:0], hv[DIM:724]});
                          end
                          else if (permutation == 10'd725) begin
                              enc <= enc ^ ({hv[724:0], hv[DIM:725]});
                          end
                          else if (permutation == 10'd726) begin
                              enc <= enc ^ ({hv[725:0], hv[DIM:726]});
                          end
                          else if (permutation == 10'd727) begin
                              enc <= enc ^ ({hv[726:0], hv[DIM:727]});
                          end
                          else if (permutation == 10'd728) begin
                              enc <= enc ^ ({hv[727:0], hv[DIM:728]});
                          end
                          else if (permutation == 10'd729) begin
                              enc <= enc ^ ({hv[728:0], hv[DIM:729]});
                          end
                          else if (permutation == 10'd730) begin
                              enc <= enc ^ ({hv[729:0], hv[DIM:730]});
                          end
                          else if (permutation == 10'd731) begin
                              enc <= enc ^ ({hv[730:0], hv[DIM:731]});
                          end
                          else if (permutation == 10'd732) begin
                              enc <= enc ^ ({hv[731:0], hv[DIM:732]});
                          end
                          else if (permutation == 10'd733) begin
                              enc <= enc ^ ({hv[732:0], hv[DIM:733]});
                          end
                          else if (permutation == 10'd734) begin
                              enc <= enc ^ ({hv[733:0], hv[DIM:734]});
                          end
                          else if (permutation == 10'd735) begin
                              enc <= enc ^ ({hv[734:0], hv[DIM:735]});
                          end
                          else if (permutation == 10'd736) begin
                              enc <= enc ^ ({hv[735:0], hv[DIM:736]});
                          end
                          else if (permutation == 10'd737) begin
                              enc <= enc ^ ({hv[736:0], hv[DIM:737]});
                          end
                          else if (permutation == 10'd738) begin
                              enc <= enc ^ ({hv[737:0], hv[DIM:738]});
                          end
                          else if (permutation == 10'd739) begin
                              enc <= enc ^ ({hv[738:0], hv[DIM:739]});
                          end
                          else if (permutation == 10'd740) begin
                              enc <= enc ^ ({hv[739:0], hv[DIM:740]});
                          end
                          else if (permutation == 10'd741) begin
                              enc <= enc ^ ({hv[740:0], hv[DIM:741]});
                          end
                          else if (permutation == 10'd742) begin
                              enc <= enc ^ ({hv[741:0], hv[DIM:742]});
                          end
                          else if (permutation == 10'd743) begin
                              enc <= enc ^ ({hv[742:0], hv[DIM:743]});
                          end
                          else if (permutation == 10'd744) begin
                              enc <= enc ^ ({hv[743:0], hv[DIM:744]});
                          end
                          else if (permutation == 10'd745) begin
                              enc <= enc ^ ({hv[744:0], hv[DIM:745]});
                          end
                          else if (permutation == 10'd746) begin
                              enc <= enc ^ ({hv[745:0], hv[DIM:746]});
                          end
                          else if (permutation == 10'd747) begin
                              enc <= enc ^ ({hv[746:0], hv[DIM:747]});
                          end
                          else if (permutation == 10'd748) begin
                              enc <= enc ^ ({hv[747:0], hv[DIM:748]});
                          end
                          else if (permutation == 10'd749) begin
                              enc <= enc ^ ({hv[748:0], hv[DIM:749]});
                          end
                          else if (permutation == 10'd750) begin
                              enc <= enc ^ ({hv[749:0], hv[DIM:750]});
                          end
                          else if (permutation == 10'd751) begin
                              enc <= enc ^ ({hv[750:0], hv[DIM:751]});
                          end
                          else if (permutation == 10'd752) begin
                              enc <= enc ^ ({hv[751:0], hv[DIM:752]});
                          end
                          else if (permutation == 10'd753) begin
                              enc <= enc ^ ({hv[752:0], hv[DIM:753]});
                          end
                          else if (permutation == 10'd754) begin
                              enc <= enc ^ ({hv[753:0], hv[DIM:754]});
                          end
                          else if (permutation == 10'd755) begin
                              enc <= enc ^ ({hv[754:0], hv[DIM:755]});
                          end
                          else if (permutation == 10'd756) begin
                              enc <= enc ^ ({hv[755:0], hv[DIM:756]});
                          end
                          else if (permutation == 10'd757) begin
                              enc <= enc ^ ({hv[756:0], hv[DIM:757]});
                          end
                          else if (permutation == 10'd758) begin
                              enc <= enc ^ ({hv[757:0], hv[DIM:758]});
                          end
                          else if (permutation == 10'd759) begin
                              enc <= enc ^ ({hv[758:0], hv[DIM:759]});
                          end
                          else if (permutation == 10'd760) begin
                              enc <= enc ^ ({hv[759:0], hv[DIM:760]});
                          end
                          else if (permutation == 10'd761) begin
                              enc <= enc ^ ({hv[760:0], hv[DIM:761]});
                          end
                          else if (permutation == 10'd762) begin
                              enc <= enc ^ ({hv[761:0], hv[DIM:762]});
                          end
                          else if (permutation == 10'd763) begin
                              enc <= enc ^ ({hv[762:0], hv[DIM:763]});
                          end
                          else if (permutation == 10'd764) begin
                              enc <= enc ^ ({hv[763:0], hv[DIM:764]});
                          end
                          else if (permutation == 10'd765) begin
                              enc <= enc ^ ({hv[764:0], hv[DIM:765]});
                          end
                          else if (permutation == 10'd766) begin
                              enc <= enc ^ ({hv[765:0], hv[DIM:766]});
                          end
                          else if (permutation == 10'd767) begin
                              enc <= enc ^ ({hv[766:0], hv[DIM:767]});
                          end
                          else if (permutation == 10'd768) begin
                              enc <= enc ^ ({hv[767:0], hv[DIM:768]});
                          end
                          else if (permutation == 10'd769) begin
                              enc <= enc ^ ({hv[768:0], hv[DIM:769]});
                          end
                          else if (permutation == 10'd770) begin
                              enc <= enc ^ ({hv[769:0], hv[DIM:770]});
                          end
                          else if (permutation == 10'd771) begin
                              enc <= enc ^ ({hv[770:0], hv[DIM:771]});
                          end
                          else if (permutation == 10'd772) begin
                              enc <= enc ^ ({hv[771:0], hv[DIM:772]});
                          end
                          else if (permutation == 10'd773) begin
                              enc <= enc ^ ({hv[772:0], hv[DIM:773]});
                          end
                          else if (permutation == 10'd774) begin
                              enc <= enc ^ ({hv[773:0], hv[DIM:774]});
                          end
                          else if (permutation == 10'd775) begin
                              enc <= enc ^ ({hv[774:0], hv[DIM:775]});
                          end
                          else if (permutation == 10'd776) begin
                              enc <= enc ^ ({hv[775:0], hv[DIM:776]});
                          end
                          else if (permutation == 10'd777) begin
                              enc <= enc ^ ({hv[776:0], hv[DIM:777]});
                          end
                          else if (permutation == 10'd778) begin
                              enc <= enc ^ ({hv[777:0], hv[DIM:778]});
                          end
                          else if (permutation == 10'd779) begin
                              enc <= enc ^ ({hv[778:0], hv[DIM:779]});
                          end
                          else if (permutation == 10'd780) begin
                              enc <= enc ^ ({hv[779:0], hv[DIM:780]});
                          end
                          else if (permutation == 10'd781) begin
                              enc <= enc ^ ({hv[780:0], hv[DIM:781]});
                          end
                          else if (permutation == 10'd782) begin
                              enc <= enc ^ ({hv[781:0], hv[DIM:782]});
                          end
                          else if (permutation == 10'd783) begin
                              enc <= enc ^ ({hv[782:0], hv[DIM:783]});
                          end
                          else if (permutation == 10'd784) begin
                              enc <= enc ^ ({hv[783:0], hv[DIM:784]});
                          end
                          else if (permutation == 10'd785) begin
                              enc <= enc ^ ({hv[784:0], hv[DIM:785]});
                          end
                          else if (permutation == 10'd786) begin
                              enc <= enc ^ ({hv[785:0], hv[DIM:786]});
                          end
                          else if (permutation == 10'd787) begin
                              enc <= enc ^ ({hv[786:0], hv[DIM:787]});
                          end
                          else if (permutation == 10'd788) begin
                              enc <= enc ^ ({hv[787:0], hv[DIM:788]});
                          end
                          else if (permutation == 10'd789) begin
                              enc <= enc ^ ({hv[788:0], hv[DIM:789]});
                          end
                          else if (permutation == 10'd790) begin
                              enc <= enc ^ ({hv[789:0], hv[DIM:790]});
                          end
                          else if (permutation == 10'd791) begin
                              enc <= enc ^ ({hv[790:0], hv[DIM:791]});
                          end
                          else if (permutation == 10'd792) begin
                              enc <= enc ^ ({hv[791:0], hv[DIM:792]});
                          end
                          else if (permutation == 10'd793) begin
                              enc <= enc ^ ({hv[792:0], hv[DIM:793]});
                          end
                          else if (permutation == 10'd794) begin
                              enc <= enc ^ ({hv[793:0], hv[DIM:794]});
                          end
                          else if (permutation == 10'd795) begin
                              enc <= enc ^ ({hv[794:0], hv[DIM:795]});
                          end
                          else if (permutation == 10'd796) begin
                              enc <= enc ^ ({hv[795:0], hv[DIM:796]});
                          end
                          else if (permutation == 10'd797) begin
                              enc <= enc ^ ({hv[796:0], hv[DIM:797]});
                          end
                          else if (permutation == 10'd798) begin
                              enc <= enc ^ ({hv[797:0], hv[DIM:798]});
                          end
                          else if (permutation == 10'd799) begin
                              enc <= enc ^ ({hv[798:0], hv[DIM:799]});
                          end
                          else if (permutation == 10'd800) begin
                              enc <= enc ^ ({hv[799:0], hv[DIM:800]});
                          end
                          else if (permutation == 10'd801) begin
                              enc <= enc ^ ({hv[800:0], hv[DIM:801]});
                          end
                          else if (permutation == 10'd802) begin
                              enc <= enc ^ ({hv[801:0], hv[DIM:802]});
                          end
                          else if (permutation == 10'd803) begin
                              enc <= enc ^ ({hv[802:0], hv[DIM:803]});
                          end
                          else if (permutation == 10'd804) begin
                              enc <= enc ^ ({hv[803:0], hv[DIM:804]});
                          end
                          else if (permutation == 10'd805) begin
                              enc <= enc ^ ({hv[804:0], hv[DIM:805]});
                          end
                          else if (permutation == 10'd806) begin
                              enc <= enc ^ ({hv[805:0], hv[DIM:806]});
                          end
                          else if (permutation == 10'd807) begin
                              enc <= enc ^ ({hv[806:0], hv[DIM:807]});
                          end
                          else if (permutation == 10'd808) begin
                              enc <= enc ^ ({hv[807:0], hv[DIM:808]});
                          end
                          else if (permutation == 10'd809) begin
                              enc <= enc ^ ({hv[808:0], hv[DIM:809]});
                          end
                          else if (permutation == 10'd810) begin
                              enc <= enc ^ ({hv[809:0], hv[DIM:810]});
                          end
                          else if (permutation == 10'd811) begin
                              enc <= enc ^ ({hv[810:0], hv[DIM:811]});
                          end
                          else if (permutation == 10'd812) begin
                              enc <= enc ^ ({hv[811:0], hv[DIM:812]});
                          end
                          else if (permutation == 10'd813) begin
                              enc <= enc ^ ({hv[812:0], hv[DIM:813]});
                          end
                          else if (permutation == 10'd814) begin
                              enc <= enc ^ ({hv[813:0], hv[DIM:814]});
                          end
                          else if (permutation == 10'd815) begin
                              enc <= enc ^ ({hv[814:0], hv[DIM:815]});
                          end
                          else if (permutation == 10'd816) begin
                              enc <= enc ^ ({hv[815:0], hv[DIM:816]});
                          end
                          else if (permutation == 10'd817) begin
                              enc <= enc ^ ({hv[816:0], hv[DIM:817]});
                          end
                          else if (permutation == 10'd818) begin
                              enc <= enc ^ ({hv[817:0], hv[DIM:818]});
                          end
                          else if (permutation == 10'd819) begin
                              enc <= enc ^ ({hv[818:0], hv[DIM:819]});
                          end
                          else if (permutation == 10'd820) begin
                              enc <= enc ^ ({hv[819:0], hv[DIM:820]});
                          end
                          else if (permutation == 10'd821) begin
                              enc <= enc ^ ({hv[820:0], hv[DIM:821]});
                          end
                          else if (permutation == 10'd822) begin
                              enc <= enc ^ ({hv[821:0], hv[DIM:822]});
                          end
                          else if (permutation == 10'd823) begin
                              enc <= enc ^ ({hv[822:0], hv[DIM:823]});
                          end
                          else if (permutation == 10'd824) begin
                              enc <= enc ^ ({hv[823:0], hv[DIM:824]});
                          end
                          else if (permutation == 10'd825) begin
                              enc <= enc ^ ({hv[824:0], hv[DIM:825]});
                          end
                          else if (permutation == 10'd826) begin
                              enc <= enc ^ ({hv[825:0], hv[DIM:826]});
                          end
                          else if (permutation == 10'd827) begin
                              enc <= enc ^ ({hv[826:0], hv[DIM:827]});
                          end
                          else if (permutation == 10'd828) begin
                              enc <= enc ^ ({hv[827:0], hv[DIM:828]});
                          end
                          else if (permutation == 10'd829) begin
                              enc <= enc ^ ({hv[828:0], hv[DIM:829]});
                          end
                          else if (permutation == 10'd830) begin
                              enc <= enc ^ ({hv[829:0], hv[DIM:830]});
                          end
                          else if (permutation == 10'd831) begin
                              enc <= enc ^ ({hv[830:0], hv[DIM:831]});
                          end
                          else if (permutation == 10'd832) begin
                              enc <= enc ^ ({hv[831:0], hv[DIM:832]});
                          end
                          else if (permutation == 10'd833) begin
                              enc <= enc ^ ({hv[832:0], hv[DIM:833]});
                          end
                          else if (permutation == 10'd834) begin
                              enc <= enc ^ ({hv[833:0], hv[DIM:834]});
                          end
                          else if (permutation == 10'd835) begin
                              enc <= enc ^ ({hv[834:0], hv[DIM:835]});
                          end
                          else if (permutation == 10'd836) begin
                              enc <= enc ^ ({hv[835:0], hv[DIM:836]});
                          end
                          else if (permutation == 10'd837) begin
                              enc <= enc ^ ({hv[836:0], hv[DIM:837]});
                          end
                          else if (permutation == 10'd838) begin
                              enc <= enc ^ ({hv[837:0], hv[DIM:838]});
                          end
                          else if (permutation == 10'd839) begin
                              enc <= enc ^ ({hv[838:0], hv[DIM:839]});
                          end
                          else if (permutation == 10'd840) begin
                              enc <= enc ^ ({hv[839:0], hv[DIM:840]});
                          end
                          else if (permutation == 10'd841) begin
                              enc <= enc ^ ({hv[840:0], hv[DIM:841]});
                          end
                          else if (permutation == 10'd842) begin
                              enc <= enc ^ ({hv[841:0], hv[DIM:842]});
                          end
                          else if (permutation == 10'd843) begin
                              enc <= enc ^ ({hv[842:0], hv[DIM:843]});
                          end
                          else if (permutation == 10'd844) begin
                              enc <= enc ^ ({hv[843:0], hv[DIM:844]});
                          end
                          else if (permutation == 10'd845) begin
                              enc <= enc ^ ({hv[844:0], hv[DIM:845]});
                          end
                          else if (permutation == 10'd846) begin
                              enc <= enc ^ ({hv[845:0], hv[DIM:846]});
                          end
                          else if (permutation == 10'd847) begin
                              enc <= enc ^ ({hv[846:0], hv[DIM:847]});
                          end
                          else if (permutation == 10'd848) begin
                              enc <= enc ^ ({hv[847:0], hv[DIM:848]});
                          end
                          else if (permutation == 10'd849) begin
                              enc <= enc ^ ({hv[848:0], hv[DIM:849]});
                          end
                          else if (permutation == 10'd850) begin
                              enc <= enc ^ ({hv[849:0], hv[DIM:850]});
                          end
                          else if (permutation == 10'd851) begin
                              enc <= enc ^ ({hv[850:0], hv[DIM:851]});
                          end
                          else if (permutation == 10'd852) begin
                              enc <= enc ^ ({hv[851:0], hv[DIM:852]});
                          end
                          else if (permutation == 10'd853) begin
                              enc <= enc ^ ({hv[852:0], hv[DIM:853]});
                          end
                          else if (permutation == 10'd854) begin
                              enc <= enc ^ ({hv[853:0], hv[DIM:854]});
                          end
                          else if (permutation == 10'd855) begin
                              enc <= enc ^ ({hv[854:0], hv[DIM:855]});
                          end
                          else if (permutation == 10'd856) begin
                              enc <= enc ^ ({hv[855:0], hv[DIM:856]});
                          end
                          else if (permutation == 10'd857) begin
                              enc <= enc ^ ({hv[856:0], hv[DIM:857]});
                          end
                          else if (permutation == 10'd858) begin
                              enc <= enc ^ ({hv[857:0], hv[DIM:858]});
                          end
                          else if (permutation == 10'd859) begin
                              enc <= enc ^ ({hv[858:0], hv[DIM:859]});
                          end
                          else if (permutation == 10'd860) begin
                              enc <= enc ^ ({hv[859:0], hv[DIM:860]});
                          end
                          else if (permutation == 10'd861) begin
                              enc <= enc ^ ({hv[860:0], hv[DIM:861]});
                          end
                          else if (permutation == 10'd862) begin
                              enc <= enc ^ ({hv[861:0], hv[DIM:862]});
                          end
                          else if (permutation == 10'd863) begin
                              enc <= enc ^ ({hv[862:0], hv[DIM:863]});
                          end
                          else if (permutation == 10'd864) begin
                              enc <= enc ^ ({hv[863:0], hv[DIM:864]});
                          end
                          else if (permutation == 10'd865) begin
                              enc <= enc ^ ({hv[864:0], hv[DIM:865]});
                          end
                          else if (permutation == 10'd866) begin
                              enc <= enc ^ ({hv[865:0], hv[DIM:866]});
                          end
                          else if (permutation == 10'd867) begin
                              enc <= enc ^ ({hv[866:0], hv[DIM:867]});
                          end
                          else if (permutation == 10'd868) begin
                              enc <= enc ^ ({hv[867:0], hv[DIM:868]});
                          end
                          else if (permutation == 10'd869) begin
                              enc <= enc ^ ({hv[868:0], hv[DIM:869]});
                          end
                          else if (permutation == 10'd870) begin
                              enc <= enc ^ ({hv[869:0], hv[DIM:870]});
                          end
                          else if (permutation == 10'd871) begin
                              enc <= enc ^ ({hv[870:0], hv[DIM:871]});
                          end
                          else if (permutation == 10'd872) begin
                              enc <= enc ^ ({hv[871:0], hv[DIM:872]});
                          end
                          else if (permutation == 10'd873) begin
                              enc <= enc ^ ({hv[872:0], hv[DIM:873]});
                          end
                          else if (permutation == 10'd874) begin
                              enc <= enc ^ ({hv[873:0], hv[DIM:874]});
                          end
                          else if (permutation == 10'd875) begin
                              enc <= enc ^ ({hv[874:0], hv[DIM:875]});
                          end
                          else if (permutation == 10'd876) begin
                              enc <= enc ^ ({hv[875:0], hv[DIM:876]});
                          end
                          else if (permutation == 10'd877) begin
                              enc <= enc ^ ({hv[876:0], hv[DIM:877]});
                          end
                          else if (permutation == 10'd878) begin
                              enc <= enc ^ ({hv[877:0], hv[DIM:878]});
                          end
                          else if (permutation == 10'd879) begin
                              enc <= enc ^ ({hv[878:0], hv[DIM:879]});
                          end
                          else if (permutation == 10'd880) begin
                              enc <= enc ^ ({hv[879:0], hv[DIM:880]});
                          end
                          else if (permutation == 10'd881) begin
                              enc <= enc ^ ({hv[880:0], hv[DIM:881]});
                          end
                          else if (permutation == 10'd882) begin
                              enc <= enc ^ ({hv[881:0], hv[DIM:882]});
                          end
                          else if (permutation == 10'd883) begin
                              enc <= enc ^ ({hv[882:0], hv[DIM:883]});
                          end
                          else if (permutation == 10'd884) begin
                              enc <= enc ^ ({hv[883:0], hv[DIM:884]});
                          end
                          else if (permutation == 10'd885) begin
                              enc <= enc ^ ({hv[884:0], hv[DIM:885]});
                          end
                          else if (permutation == 10'd886) begin
                              enc <= enc ^ ({hv[885:0], hv[DIM:886]});
                          end
                          else if (permutation == 10'd887) begin
                              enc <= enc ^ ({hv[886:0], hv[DIM:887]});
                          end
                          else if (permutation == 10'd888) begin
                              enc <= enc ^ ({hv[887:0], hv[DIM:888]});
                          end
                          else if (permutation == 10'd889) begin
                              enc <= enc ^ ({hv[888:0], hv[DIM:889]});
                          end
                          else if (permutation == 10'd890) begin
                              enc <= enc ^ ({hv[889:0], hv[DIM:890]});
                          end
                          else if (permutation == 10'd891) begin
                              enc <= enc ^ ({hv[890:0], hv[DIM:891]});
                          end
                          else if (permutation == 10'd892) begin
                              enc <= enc ^ ({hv[891:0], hv[DIM:892]});
                          end
                          else if (permutation == 10'd893) begin
                              enc <= enc ^ ({hv[892:0], hv[DIM:893]});
                          end
                          else if (permutation == 10'd894) begin
                              enc <= enc ^ ({hv[893:0], hv[DIM:894]});
                          end
                          else if (permutation == 10'd895) begin
                              enc <= enc ^ ({hv[894:0], hv[DIM:895]});
                          end
                          else if (permutation == 10'd896) begin
                              enc <= enc ^ ({hv[895:0], hv[DIM:896]});
                          end
                          else if (permutation == 10'd897) begin
                              enc <= enc ^ ({hv[896:0], hv[DIM:897]});
                          end
                          else if (permutation == 10'd898) begin
                              enc <= enc ^ ({hv[897:0], hv[DIM:898]});
                          end
                          else if (permutation == 10'd899) begin
                              enc <= enc ^ ({hv[898:0], hv[DIM:899]});
                          end
                          else if (permutation == 10'd900) begin
                              enc <= enc ^ ({hv[899:0], hv[DIM:900]});
                          end
                          else if (permutation == 10'd901) begin
                              enc <= enc ^ ({hv[900:0], hv[DIM:901]});
                          end
                          else if (permutation == 10'd902) begin
                              enc <= enc ^ ({hv[901:0], hv[DIM:902]});
                          end
                          else if (permutation == 10'd903) begin
                              enc <= enc ^ ({hv[902:0], hv[DIM:903]});
                          end
                          else if (permutation == 10'd904) begin
                              enc <= enc ^ ({hv[903:0], hv[DIM:904]});
                          end
                          else if (permutation == 10'd905) begin
                              enc <= enc ^ ({hv[904:0], hv[DIM:905]});
                          end
                          else if (permutation == 10'd906) begin
                              enc <= enc ^ ({hv[905:0], hv[DIM:906]});
                          end
                          else if (permutation == 10'd907) begin
                              enc <= enc ^ ({hv[906:0], hv[DIM:907]});
                          end
                          else if (permutation == 10'd908) begin
                              enc <= enc ^ ({hv[907:0], hv[DIM:908]});
                          end
                          else if (permutation == 10'd909) begin
                              enc <= enc ^ ({hv[908:0], hv[DIM:909]});
                          end
                          else if (permutation == 10'd910) begin
                              enc <= enc ^ ({hv[909:0], hv[DIM:910]});
                          end
                          else if (permutation == 10'd911) begin
                              enc <= enc ^ ({hv[910:0], hv[DIM:911]});
                          end
                          else if (permutation == 10'd912) begin
                              enc <= enc ^ ({hv[911:0], hv[DIM:912]});
                          end
                          else if (permutation == 10'd913) begin
                              enc <= enc ^ ({hv[912:0], hv[DIM:913]});
                          end
                          else if (permutation == 10'd914) begin
                              enc <= enc ^ ({hv[913:0], hv[DIM:914]});
                          end
                          else if (permutation == 10'd915) begin
                              enc <= enc ^ ({hv[914:0], hv[DIM:915]});
                          end
                          else if (permutation == 10'd916) begin
                              enc <= enc ^ ({hv[915:0], hv[DIM:916]});
                          end
                          else if (permutation == 10'd917) begin
                              enc <= enc ^ ({hv[916:0], hv[DIM:917]});
                          end
                          else if (permutation == 10'd918) begin
                              enc <= enc ^ ({hv[917:0], hv[DIM:918]});
                          end
                          else if (permutation == 10'd919) begin
                              enc <= enc ^ ({hv[918:0], hv[DIM:919]});
                          end
                          else if (permutation == 10'd920) begin
                              enc <= enc ^ ({hv[919:0], hv[DIM:920]});
                          end
                          else if (permutation == 10'd921) begin
                              enc <= enc ^ ({hv[920:0], hv[DIM:921]});
                          end
                          else if (permutation == 10'd922) begin
                              enc <= enc ^ ({hv[921:0], hv[DIM:922]});
                          end
                          else if (permutation == 10'd923) begin
                              enc <= enc ^ ({hv[922:0], hv[DIM:923]});
                          end
                          else if (permutation == 10'd924) begin
                              enc <= enc ^ ({hv[923:0], hv[DIM:924]});
                          end
                          else if (permutation == 10'd925) begin
                              enc <= enc ^ ({hv[924:0], hv[DIM:925]});
                          end
                          else if (permutation == 10'd926) begin
                              enc <= enc ^ ({hv[925:0], hv[DIM:926]});
                          end
                          else if (permutation == 10'd927) begin
                              enc <= enc ^ ({hv[926:0], hv[DIM:927]});
                          end
                          else if (permutation == 10'd928) begin
                              enc <= enc ^ ({hv[927:0], hv[DIM:928]});
                          end
                          else if (permutation == 10'd929) begin
                              enc <= enc ^ ({hv[928:0], hv[DIM:929]});
                          end
                          else if (permutation == 10'd930) begin
                              enc <= enc ^ ({hv[929:0], hv[DIM:930]});
                          end
                          else if (permutation == 10'd931) begin
                              enc <= enc ^ ({hv[930:0], hv[DIM:931]});
                          end
                          else if (permutation == 10'd932) begin
                              enc <= enc ^ ({hv[931:0], hv[DIM:932]});
                          end
                          else if (permutation == 10'd933) begin
                              enc <= enc ^ ({hv[932:0], hv[DIM:933]});
                          end
                          else if (permutation == 10'd934) begin
                              enc <= enc ^ ({hv[933:0], hv[DIM:934]});
                          end
                          else if (permutation == 10'd935) begin
                              enc <= enc ^ ({hv[934:0], hv[DIM:935]});
                          end
                          else if (permutation == 10'd936) begin
                              enc <= enc ^ ({hv[935:0], hv[DIM:936]});
                          end
                          else if (permutation == 10'd937) begin
                              enc <= enc ^ ({hv[936:0], hv[DIM:937]});
                          end
                          else if (permutation == 10'd938) begin
                              enc <= enc ^ ({hv[937:0], hv[DIM:938]});
                          end
                          else if (permutation == 10'd939) begin
                              enc <= enc ^ ({hv[938:0], hv[DIM:939]});
                          end
                          else if (permutation == 10'd940) begin
                              enc <= enc ^ ({hv[939:0], hv[DIM:940]});
                          end
                          else if (permutation == 10'd941) begin
                              enc <= enc ^ ({hv[940:0], hv[DIM:941]});
                          end
                          else if (permutation == 10'd942) begin
                              enc <= enc ^ ({hv[941:0], hv[DIM:942]});
                          end
                          else if (permutation == 10'd943) begin
                              enc <= enc ^ ({hv[942:0], hv[DIM:943]});
                          end
                          else if (permutation == 10'd944) begin
                              enc <= enc ^ ({hv[943:0], hv[DIM:944]});
                          end
                          else if (permutation == 10'd945) begin
                              enc <= enc ^ ({hv[944:0], hv[DIM:945]});
                          end
                          else if (permutation == 10'd946) begin
                              enc <= enc ^ ({hv[945:0], hv[DIM:946]});
                          end
                          else if (permutation == 10'd947) begin
                              enc <= enc ^ ({hv[946:0], hv[DIM:947]});
                          end
                          else if (permutation == 10'd948) begin
                              enc <= enc ^ ({hv[947:0], hv[DIM:948]});
                          end
                          else if (permutation == 10'd949) begin
                              enc <= enc ^ ({hv[948:0], hv[DIM:949]});
                          end
                          else if (permutation == 10'd950) begin
                              enc <= enc ^ ({hv[949:0], hv[DIM:950]});
                          end
                          else if (permutation == 10'd951) begin
                              enc <= enc ^ ({hv[950:0], hv[DIM:951]});
                          end
                          else if (permutation == 10'd952) begin
                              enc <= enc ^ ({hv[951:0], hv[DIM:952]});
                          end
                          else if (permutation == 10'd953) begin
                              enc <= enc ^ ({hv[952:0], hv[DIM:953]});
                          end
                          else if (permutation == 10'd954) begin
                              enc <= enc ^ ({hv[953:0], hv[DIM:954]});
                          end
                          else if (permutation == 10'd955) begin
                              enc <= enc ^ ({hv[954:0], hv[DIM:955]});
                          end
                          else if (permutation == 10'd956) begin
                              enc <= enc ^ ({hv[955:0], hv[DIM:956]});
                          end
                          else if (permutation == 10'd957) begin
                              enc <= enc ^ ({hv[956:0], hv[DIM:957]});
                          end
                          else if (permutation == 10'd958) begin
                              enc <= enc ^ ({hv[957:0], hv[DIM:958]});
                          end
                          else if (permutation == 10'd959) begin
                              enc <= enc ^ ({hv[958:0], hv[DIM:959]});
                          end
                          else if (permutation == 10'd960) begin
                              enc <= enc ^ ({hv[959:0], hv[DIM:960]});
                          end
                          else if (permutation == 10'd961) begin
                              enc <= enc ^ ({hv[960:0], hv[DIM:961]});
                          end
                          else if (permutation == 10'd962) begin
                              enc <= enc ^ ({hv[961:0], hv[DIM:962]});
                          end
                          else if (permutation == 10'd963) begin
                              enc <= enc ^ ({hv[962:0], hv[DIM:963]});
                          end
                          else if (permutation == 10'd964) begin
                              enc <= enc ^ ({hv[963:0], hv[DIM:964]});
                          end
                          else if (permutation == 10'd965) begin
                              enc <= enc ^ ({hv[964:0], hv[DIM:965]});
                          end
                          else if (permutation == 10'd966) begin
                              enc <= enc ^ ({hv[965:0], hv[DIM:966]});
                          end
                          else if (permutation == 10'd967) begin
                              enc <= enc ^ ({hv[966:0], hv[DIM:967]});
                          end
                          else if (permutation == 10'd968) begin
                              enc <= enc ^ ({hv[967:0], hv[DIM:968]});
                          end
                          else if (permutation == 10'd969) begin
                              enc <= enc ^ ({hv[968:0], hv[DIM:969]});
                          end
                          else if (permutation == 10'd970) begin
                              enc <= enc ^ ({hv[969:0], hv[DIM:970]});
                          end
                          else if (permutation == 10'd971) begin
                              enc <= enc ^ ({hv[970:0], hv[DIM:971]});
                          end
                          else if (permutation == 10'd972) begin
                              enc <= enc ^ ({hv[971:0], hv[DIM:972]});
                          end
                          else if (permutation == 10'd973) begin
                              enc <= enc ^ ({hv[972:0], hv[DIM:973]});
                          end
                          else if (permutation == 10'd974) begin
                              enc <= enc ^ ({hv[973:0], hv[DIM:974]});
                          end
                          else if (permutation == 10'd975) begin
                              enc <= enc ^ ({hv[974:0], hv[DIM:975]});
                          end
                          else if (permutation == 10'd976) begin
                              enc <= enc ^ ({hv[975:0], hv[DIM:976]});
                          end
                          else if (permutation == 10'd977) begin
                              enc <= enc ^ ({hv[976:0], hv[DIM:977]});
                          end
                          else if (permutation == 10'd978) begin
                              enc <= enc ^ ({hv[977:0], hv[DIM:978]});
                          end
                          else if (permutation == 10'd979) begin
                              enc <= enc ^ ({hv[978:0], hv[DIM:979]});
                          end
                          else if (permutation == 10'd980) begin
                              enc <= enc ^ ({hv[979:0], hv[DIM:980]});
                          end
                          else if (permutation == 10'd981) begin
                              enc <= enc ^ ({hv[980:0], hv[DIM:981]});
                          end
                          else if (permutation == 10'd982) begin
                              enc <= enc ^ ({hv[981:0], hv[DIM:982]});
                          end
                          else if (permutation == 10'd983) begin
                              enc <= enc ^ ({hv[982:0], hv[DIM:983]});
                          end
                          else if (permutation == 10'd984) begin
                              enc <= enc ^ ({hv[983:0], hv[DIM:984]});
                          end
                          else if (permutation == 10'd985) begin
                              enc <= enc ^ ({hv[984:0], hv[DIM:985]});
                          end
                          else if (permutation == 10'd986) begin
                              enc <= enc ^ ({hv[985:0], hv[DIM:986]});
                          end
                          else if (permutation == 10'd987) begin
                              enc <= enc ^ ({hv[986:0], hv[DIM:987]});
                          end
                          else if (permutation == 10'd988) begin
                              enc <= enc ^ ({hv[987:0], hv[DIM:988]});
                          end
                          else if (permutation == 10'd989) begin
                              enc <= enc ^ ({hv[988:0], hv[DIM:989]});
                          end
                          else if (permutation == 10'd990) begin
                              enc <= enc ^ ({hv[989:0], hv[DIM:990]});
                          end
                          else if (permutation == 10'd991) begin
                              enc <= enc ^ ({hv[990:0], hv[DIM:991]});
                          end
                          else if (permutation == 10'd992) begin
                              enc <= enc ^ ({hv[991:0], hv[DIM:992]});
                          end
                          else if (permutation == 10'd993) begin
                              enc <= enc ^ ({hv[992:0], hv[DIM:993]});
                          end
                          else if (permutation == 10'd994) begin
                              enc <= enc ^ ({hv[993:0], hv[DIM:994]});
                          end
                          else if (permutation == 10'd995) begin
                              enc <= enc ^ ({hv[994:0], hv[DIM:995]});
                          end
                          else if (permutation == 10'd996) begin
                              enc <= enc ^ ({hv[995:0], hv[DIM:996]});
                          end
                          else if (permutation == 10'd997) begin
                              enc <= enc ^ ({hv[996:0], hv[DIM:997]});
                          end
                          else if (permutation == 10'd998) begin
                              enc <= enc ^ ({hv[997:0], hv[DIM:998]});
                          end
                          else if (permutation == 10'd999) begin
                              enc <= enc ^ ({hv[998:0], hv[DIM:999]});
                          end
                          else if (permutation == 10'd1000) begin
                              enc <= enc ^ ({hv[999:0], hv[DIM:1000]});
                          end
                          else if (permutation == 10'd1001) begin
                              enc <= enc ^ ({hv[1000:0], hv[DIM:1001]});
                          end
                          else if (permutation == 10'd1002) begin
                              enc <= enc ^ ({hv[1001:0], hv[DIM:1002]});
                          end
                          else if (permutation == 10'd1003) begin
                              enc <= enc ^ ({hv[1002:0], hv[DIM:1003]});
                          end
                          else if (permutation == 10'd1004) begin
                              enc <= enc ^ ({hv[1003:0], hv[DIM:1004]});
                          end
                          else if (permutation == 10'd1005) begin
                              enc <= enc ^ ({hv[1004:0], hv[DIM:1005]});
                          end
                          else if (permutation == 10'd1006) begin
                              enc <= enc ^ ({hv[1005:0], hv[DIM:1006]});
                          end
                          else if (permutation == 10'd1007) begin
                              enc <= enc ^ ({hv[1006:0], hv[DIM:1007]});
                          end
                          else if (permutation == 10'd1008) begin
                              enc <= enc ^ ({hv[1007:0], hv[DIM:1008]});
                          end
                          else if (permutation == 10'd1009) begin
                              enc <= enc ^ ({hv[1008:0], hv[DIM:1009]});
                          end
                          else if (permutation == 10'd1010) begin
                              enc <= enc ^ ({hv[1009:0], hv[DIM:1010]});
                          end
                          else if (permutation == 10'd1011) begin
                              enc <= enc ^ ({hv[1010:0], hv[DIM:1011]});
                          end
                          else if (permutation == 10'd1012) begin
                              enc <= enc ^ ({hv[1011:0], hv[DIM:1012]});
                          end
                          else if (permutation == 10'd1013) begin
                              enc <= enc ^ ({hv[1012:0], hv[DIM:1013]});
                          end
                          else if (permutation == 10'd1014) begin
                              enc <= enc ^ ({hv[1013:0], hv[DIM:1014]});
                          end
                          else if (permutation == 10'd1015) begin
                              enc <= enc ^ ({hv[1014:0], hv[DIM:1015]});
                          end
                          else if (permutation == 10'd1016) begin
                              enc <= enc ^ ({hv[1015:0], hv[DIM:1016]});
                          end
                          else if (permutation == 10'd1017) begin
                              enc <= enc ^ ({hv[1016:0], hv[DIM:1017]});
                          end
                          else if (permutation == 10'd1018) begin
                              enc <= enc ^ ({hv[1017:0], hv[DIM:1018]});
                          end
                          else if (permutation == 10'd1019) begin
                              enc <= enc ^ ({hv[1018:0], hv[DIM:1019]});
                          end
                          else if (permutation == 10'd1020) begin
                              enc <= enc ^ ({hv[1019:0], hv[DIM:1020]});
                          end
                          else if (permutation == 10'd1021) begin
                              enc <= enc ^ ({hv[1020:0], hv[DIM:1021]});
                          end
                          else if (permutation == 10'd1022) begin
                              enc <= enc ^ ({hv[1021:0], hv[DIM:1022]});
                          end
                          else if (permutation == 10'd1023) begin
                              enc <= enc ^ ({hv[1022:0], hv[1023]});
                          end

                      end
                  end
              end;


    //================================================================


    always_comb begin
                    core_result = 0;

                    if (update) begin
                        core_result = enc;
                    end
                end;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

endmodule

`default_nettype wire
