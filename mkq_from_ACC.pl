#!/usr/bin/perl
## mkq_ACC ##

$e = 0;
$case = 0;

if($#ARGV == -1){
 $case = 10;
}

if($ARGV[-2] eq '-f'){
 $e = -2;
 $case = 2;
 $out = $ARGV[-1];
}elsif($ARGV[-1] eq '-f'){
 $e = -1;
 $case = 1;
}

#print "e:$e\n";
#print "case:$case\n";

print "#!/bin/sh\n";
if($case != 10){
 $i = 0;
 while($i <= $#ARGV+$e){
  $file = $ARGV[$i];
  open(IN,$file) || die "$file : ファイルの読み込みに失敗しました\n";
  while ($line = <IN>) {
   chomp($line);
   print 'blastclient ';
   print 'http://www.ncbi.nlm.nih.gov/';
   print 'entrez/query.fcgi?db=nucleotide\'&\'cmd=search\'&\'term=';
   if($case == 0){
    print "$line\n";
   }elsif($case == 1){
    print "$line > $line\n";
   }elsif($case == 2){
    print "$line >> $out\n";
   }
  }
  close(IN);
  $i = $i+1;
 }
}elsif($case == 10){
 while ($line = <STDIN>) {
  chomp($line);
  print 'blastclient ';
  print 'http://www.ncbi.nlm.nih.gov/';
  print 'entrez/query.fcgi?db=nucleotide\'&\'cmd=search\'&\'term=';
  print "$line\n";
 }
}
