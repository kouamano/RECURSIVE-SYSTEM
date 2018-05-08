#!/usr/bin/perl
## mkfastafromseq ##

if(($#ARGV == 2) || ($#ARGV == 3)){
 print "argument(s) : 1 or 2\n";
 exit;
}

if($ARGV[0] eq '-test'){
 $file = $ARGV[1];
 $case = 100;
}elsif($ARGV[0] eq '-html'){
 $file = $ARGV[1];
 $case = 4;
}elsif(($ARGV[0] eq '-sn') || ($ARGV[0] eq '-ns')){
 $file = $ARGV[1];
 $case = 3;
}elsif($ARGV[0] eq '-s'){
 $file = $ARGV[1];
 $case = 2;
}elsif($ARGV[0] eq '-n'){
 $file = $ARGV[1];
 $case = 1;
}else{
 $file = $ARGV[0];
 $case = 0;
} 

open(IN,$file) || die "$file : open failed\n";
while(<IN>){
 push(@data,$_);
}
close(IN);

## pick sequence ##
if($case == 4){

}else{
 $data_str = join('',@data);
 @data_new = split("\n\/\/",$data_str);
 pop(@data_new);
 foreach $a (@data_new) {
  @tmp = split("ORIGIN*[^\n]*\n",$a);
  push(@data_out,$tmp[-1]);
 }
}
## end pick sequence ##

## pre-operation ## 
if((case) == 0 || (case == 1)){
 foreach $a (@data_new) {
  if($a =~ /(VERSION*[^\n]*\n)/){
   push(@com1,$1);
  }
 }
 foreach $a (@com1) {
  @gar = split(' ',$a);
  $tmp = pop(@gar);
  $tmp =~ s/GI://;
  push(@com1_new,$tmp);
 }
 foreach $a (@data_new) {
  if($a =~ /(ACCESSION*[^\n]*\n)/){
   push(@com2,$1);
  }
 }
 foreach $a (@com2) {
  ($gar,$tmp) = split(' ',$a);
  push(@com2_new,$tmp);
 }
}
## end pre-operation ##

## output ##
if($case == 0){
 $num_e = @data_out;
 $n = 0;
 while($n < $num_e){
  print ">gi|";
  print "@com1_new[$n]";
  print '|';
  print "gb|";
  print "@com2_new[$n]\n";
  $a = @data_out[$n];
  $a =~ s/[0-9\s]*//g;
  print "$a\n\n";
  $n = $n+1;
 }
}elsif($case == 1){
 $num_e = @data_out;
 $n = 0;
 while($n < $num_e){
  print ">gi|";
  print "@com1_new[$n]";
  print '|';
  print "gb|";
  print "@com2_new[$n]";
  print "\n";
  $a = @data_out[$n];
  print "$a\n\n";
  $n = $n+1;
 }
}elsif($case == 2){
 $num = 0;
 foreach $a (@data_out) {
  print '>sequence_';
  print "$num\n";
  $num = $num+1;
  $a =~ s/[0-9\s]*//g;
  print "$a\n\n";
 }
}elsif($case == 3){
 $num = 0;
 foreach $a (@data_out) {
  print '>sequence_';
  print "$num\n";
  $num = $num+1;
  print "$a\n";
 }
}elsif($case == 100){
 print "test\n"
 # for test script(s) #
}
## end output ##
