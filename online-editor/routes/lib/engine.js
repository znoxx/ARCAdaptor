var sprintf = require("sprintf-js").sprintf

//globals:

var ORDER = ["X2N3",
"X2N6",
"X2N7",
"X2N8",
"X1N2",
"X1N1",
"X1N3",
"X1N4",
"X1N5",
"X1N6",
"X1N7",
"X1N8",
"shift",
"X3N1",
"X2N2",
"X2N5",
"X2N4",
"X2N1",

"X2S3",
"X2S6",
"X2S7",
"X2S8",
"X1S2",
"X1S1",
"X1S3",
"X1S4",
"X1S5",
"X1S6",
"X1S7",
"X1S8",
"shift",
"X3S1",
"X2S2",
"X2S5",
"X2S4",
"X2S1"];

var codes = {};
//lowercased!!!
codes['key_a']=4;
codes['key_b']=5;
codes['key_c']=6;
codes['key_d']=7;
codes['key_e']=8;
codes['key_f']=9;
codes['key_g']=10;
codes['key_h']=11;
codes['key_i']=12;
codes['key_j']=13;
codes['key_k']=14;
codes['key_l']=15;
codes['key_m']=16;
codes['key_n']=17;
codes['key_o']=18;
codes['key_p']=19;
codes['key_q']=20;
codes['key_r']=21;
codes['key_s']=22;
codes['key_t']=23;
codes['key_u']=24;
codes['key_v']=25;
codes['key_w']=26;
codes['key_x']=27;
codes['key_y']=28;
codes['key_z']=29;
codes['key_1']=30;
codes['key_2']=31;
codes['key_3']=32;
codes['key_4']=33;
codes['key_5']=34;
codes['key_6']=35;
codes['key_7']=36;
codes['key_8']=37;
codes['key_9']=38;
codes['key_0']=39;
codes['key_enter']=40;
codes['key_esc']=41;
codes['key_backspace']=42;
codes['key_tab']=43;
codes['key_space']=44;
codes['key_minus']=45;
codes['key_equal']=46;
codes['key_leftbr']=47;
codes['key_rightbr']=48;
codes['key_backslash']=49;
codes['key_hash']=50;
codes['key_semicolon']=51;
codes['key_quotation']=52;
codes['key_tilde']=53;
codes['key_comma']=54;
codes['key_dot']=55;
codes['key_slash']=56;
codes['key_capslock']=57;
codes['key_f1']=58;
codes['key_f2']=59;
codes['key_f3']=60;
codes['key_f4']=61;
codes['key_f5']=62;
codes['key_f6']=63;
codes['key_f7']=64;
codes['key_f8']=65;
codes['key_f9']=66;
codes['key_f10']=67;
codes['key_f11']=68;
codes['key_f12']=69;
codes['key_prtscr']=70;
codes['key_scrlck']=71;
codes['key_pause']=72;
codes['key_ins']=73;
codes['key_home']=74;
codes['key_pageup']=75;
codes['key_del']=76;
codes['key_end']=77;
codes['key_pagedown']=78;
codes['key_rightarrow']=79;
codes['key_leftarrow']=80;
codes['key_downarrow']=81;
codes['key_uparrow']=82;
codes['key_numlock']=83;
codes['key_kp_slash']=84;
codes['key_kp_ast']=85;
codes['key_kp_minus']=86;
codes['key_kp_plus']=87;
codes['key_kp_enter']=88;
codes['key_kp_1']=89;
codes['key_kp_2']=90;
codes['key_kp_3']=91;
codes['key_kp_4']=92;
codes['key_kp_5']=93;
codes['key_kp_6']=94;
codes['key_kp_7']=95;
codes['key_kp_8']=96;
codes['key_kp_9']=97;
codes['key_kp_0']=98;
codes['key_kp_comma']=99;
codes['key_euro']=100;
codes['key_application']=101;
codes['km_alt_f4']=112;
codes['km_shift_f7']=113;
codes['ac_volumeup']=144;
codes['ac_volumedown']=145;
codes['ac_mute']=146;
codes['j1_left']=160;
codes['j1_right']=161;
codes['j1_up']=162;
codes['j1_down']=163;
codes['j1_button1']=164;
codes['j1_button2']=165;
codes['j1_button3']=166;
codes['j1_button4']=167;
codes['j1_button5']=168;
codes['j1_button6']=169;
codes['j1_button7']=170;
codes['j1_button8']=171;
codes['j2_left']=172;
codes['j2_right']=173;
codes['j2_up']=174;
codes['j2_down']=175;
codes['j2_button1']=176;
codes['j2_button2']=177;
codes['j2_button3']=178;
codes['j2_button4']=179;
codes['j2_button5']=180;
codes['j2_button6']=181;
codes['j2_button7']=182;
codes['j2_button8']=183;

//special value to set zeroes
codes['shift']=0;
codes['reserved']=0;

function calcChecksum( pre_checksum )
{
  // calculating checksum
  var checksum_s = sprintf("%02X", pre_checksum);
  var checksum =  0x100 - parseInt(checksum_s.substr(-2),16);
  return checksum;
}

this.generateHex = function(request_body)
{
   //initialising hash
  var pins={};
   
  for (count = 1; count < 9; count++) 
  {
    pins[`X1N${count}`.toLowerCase()] = request_body[`X1N${count}`].toLowerCase(); 
    pins[`X1S${count}`.toLowerCase()]= request_body[`X1S${count}`].toLowerCase();
    pins[`X2N${count}`.toLowerCase()]= request_body[`X2N${count}`].toLowerCase(); 
    pins[`X2S${count}`.toLowerCase()]= request_body[`X2S${count}`].toLowerCase(); 
  }

  pins[`X3N1`.toLowerCase()] = request_body[`X3N1`].toLowerCase(); 
  pins[`X3S1`.toLowerCase()] = request_body[`X3S1`].toLowerCase();
  
  //creating array for encoding
  var out_array=[];

  for (index=0;index<ORDER.length;index++)
  {
	order = ORDER[index].toLowerCase();
	var val = pins[order];
	var code = 0;
	
	if (val in codes)
	{
	  code = codes[val];
	}
    out_array.push(code);
  }

  var output_data="";

  //should create output here.
  //some calculations:
  // first - getting length

  var total_size = out_array.length;

  // second - modulus by 16

  var remains = total_size % 16; //ya, magic numbah!

  // third - full cycles;
  var full_cycles = (total_size-remains)/16;

  var currentaddress = 0;

  for (var cycle = 0; cycle < full_cycles; cycle++) 
  {
     var string =  sprintf("%02X%04X00",16,currentaddress);
     var checksum=16+currentaddress;
     for (var i=0; i<16; i++)
     {
       string = string+sprintf("%02X",out_array[currentaddress]);
       checksum=checksum + out_array[currentaddress];
       currentaddress=currentaddress+1; 
     }
    output_data = output_data+":"+string+sprintf("%02X",calcChecksum(checksum))+"\r\n";   
  }

  var string=sprintf("%02X%04X00",remains,currentaddress);
  var checksum = remains+currentaddress;
  {
    while(currentaddress <total_size)
    {
      string = string+sprintf("%02X",out_array[currentaddress]);
      checksum=checksum + out_array[currentaddress];
      currentaddress=currentaddress+1;
    }
      
      output_data = output_data+":"+string+sprintf("%2X",calcChecksum(checksum))+"\r\n";
  }

  output_data = output_data+":00000001FF\r\n";
  
  return output_data;
     
}