#!/usr/bin/perl
#!"Z:\xampp\perl\bin\perl.exe"
####switch your perl above

use CGI qw/:standard/;


my $q = CGI->new();


@ORDER = ("X2N3",
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
"X2S1",
);

#extracting parameters and setting them to hash 
my %codes = ();

 
while (my $line = <main::DATA>) {
  chomp $line;
 my @fields = split "," , lc($line);
$codes{$fields[0]} = $fields[1]; 
}

$codes{"shift"} = 0; #special value to set zeroes
$codes{"reserved"} = 0;


#initializing hash

my %pins = ();

for (my $count = 1; $count < 9; $count++) 
{
  $pins{(lc "X1N$count")} = lc ($q->param("X1N$count")); 
  $pins{(lc "X1S$count")} = lc ($q->param("X1S$count"));
  $pins{(lc "X2N$count")} = lc ($q->param("X2N$count")); 
  $pins{(lc "X2S$count")} = lc ($q->param("X2S$count")); 
}

  $pins{(lc "X3N1")} = lc ($q->param("X3N1")); 
  $pins{(lc "X3S1")} = lc ($q->param("X3S1"));
 


#creating array for encoding
my @out_array;
for my $order (@ORDER) {

  my $val = $pins{lc($order)}; #getting pin value by order
  my $code = 0;
  if (exists $codes{$val})
  {
    $code = $codes{$val};     
  } 
  push @out_array, $code
}

my $output_data;

#should create output here.
#some calculations:
# first - getting length

my $total_size = @out_array;

# second - modulus by 16

my $remains = $total_size % 16; #ya, magic numbah!


# third - full cycles;
my $full_cycles = ($total_size-$remains)/16;


my $currentaddress = 0;

for (my $cycle = 0; $cycle < $full_cycles; $cycle++) 
{
  
   my $string =  sprintf("%02X%04X00",16,$currentaddress);
   
   my $checksum=16+$currentaddress;
   for (my $i=0; $i<16; $i++)
   {
     $string = $string.sprintf("%02X",$out_array[$currentaddress]);
     $checksum=$checksum + $out_array[$currentaddress];
     $currentaddress=$currentaddress+1; 
   }
   
   #calculating checksum
   my $checksum_s = sprintf("%02X", $checksum);
   $checksum =  0x100 - (hex(substr($checksum_s,-2)));

   $output_data = $output_data.":".$string.sprintf("%02X",$checksum)."\r\n";
   
}

  my $string=sprintf("%02X%04X00",$remains,$currentaddress);
  my $checksum = $remains+$currentaddress;
  {
    while($currentaddress <$total_size)
    {
      $string = $string.sprintf("%02X",$out_array[$currentaddress]);
      $checksum=$checksum + $out_array[$currentaddress];
      $currentaddress=$currentaddress+1;
    }
      #calculating checksum
      my $checksum_s = sprintf("%02X", $checksum);
      $checksum =  0x100 - (hex(substr($checksum_s,-2)));
      $output_data = $output_data.":".$string.sprintf("%2X",$checksum)."\r\n";
      
  }

$output_data = $output_data.":00000001FF\r\n";
#eof here

print "Content-type: application/octet-stream\n";
print "Content-Disposition: attachment; filename=arcadaptor8.eep\n";
print "Content-Description: File to download\n\n";

print $output_data;


end_html; 

__END__
KEY_A,4
KEY_B,5
KEY_C,6
KEY_D,7
KEY_E,8
KEY_F,9
KEY_G,10
KEY_H,11
KEY_I,12
KEY_J,13
KEY_K,14
KEY_L,15
KEY_M,16
KEY_N,17
KEY_O,18
KEY_P,19
KEY_Q,20
KEY_R,21
KEY_S,22
KEY_T,23
KEY_U,24
KEY_V,25
KEY_W,26
KEY_X,27
KEY_Y,28
KEY_Z,29
KEY_1,30
KEY_2,31
KEY_3,32
KEY_4,33
KEY_5,34
KEY_6,35
KEY_7,36
KEY_8,37
KEY_9,38
KEY_0,39
KEY_Enter,40
KEY_Esc,41
KEY_BackSpace,42
KEY_Tab,43
KEY_Space,44
KEY_Minus,45
KEY_Equal,46
KEY_LeftBr,47
KEY_RightBr,48
KEY_BackSlash,49
KEY_Hash,50
KEY_Semicolon,51
KEY_Quotation,52
KEY_Tilde,53
KEY_Comma,54
KEY_Dot,55
KEY_Slash,56
KEY_CapsLock,57
KEY_F1,58
KEY_F2,59
KEY_F3,60
KEY_F4,61
KEY_F5,62
KEY_F6,63
KEY_F7,64
KEY_F8,65
KEY_F9,66
KEY_F10,67
KEY_F11,68
KEY_F12,69
KEY_PrtScr,70
KEY_ScrLck,71
KEY_Pause,72
KEY_Ins,73
KEY_Home,74
KEY_PageUp,75
KEY_Del,76
KEY_End,77
KEY_PageDown,78
KEY_RightArrow,79
KEY_LeftArrow,80
KEY_DownArrow,81
KEY_UpArrow,82
KEY_NumLock,83
KEY_KP_Slash,84
KEY_KP_Ast,85
KEY_KP_Minus,86
KEY_KP_Plus,87
KEY_KP_Enter,88
KEY_KP_1,89
KEY_KP_2,90
KEY_KP_3,91
KEY_KP_4,92
KEY_KP_5,93
KEY_KP_6,94
KEY_KP_7,95
KEY_KP_8,96
KEY_KP_9,97
KEY_KP_0,98
KEY_KP_Comma,99
KEY_Euro,100
KEY_Application,101
KM_ALT_F4,112
KM_SHIFT_F7,113
AC_VolumeUp,144
AC_VolumeDown,145
AC_Mute,146
J1_Left,160
J1_Right,161
J1_Up,162
J1_Down,163
J1_Button1,164
J1_Button2,165
J1_Button3,166
J1_Button4,167
J1_Button5,168
J1_Button6,169
J1_Button7,170
J1_Button8,171
J2_Left,172
J2_Right,173
J2_Up,174
J2_Down,175
J2_Button1,176
J2_Button2,177
J2_Button3,178
J2_Button4,179
J2_Button5,180
J2_Button6,181
J2_Button7,182
J2_Button8,183

