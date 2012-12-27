#!/usr/bin/perl
## gbsearch ##

$TAG = 'SOURCE';
$KEY = 'Oryza sativa.';

if($#ARGV != 4){
 print "arguments : 5\n";
 exit;
}elsif(($ARGV[0] ne '-t') || ($ARGV[2] ne '-k')){
 print "usege : gbsearch -t \"tag\" -k \"keyword\" \"file\"\n";
 exit;
}

$TAG = $ARGV[1];
$KEY = $ARGV[3];
$file = $ARGV[4];

open(IN,$file) || die "$file : open failed\n";
while(<IN>){
 push(@data,$_);
}
close(IN);

$data_str = join('',@data);
@data_new = split("\n\/\/",$data_str);
pop(@data_new);

foreach $a (@data_new) {
 if($a =~ /\n$TAG[^\n]*$KEY[^\n]*\n/){
  print $a;
  print "\n\/\/"
 }
}

print "\n";
