#!/usr/bin/perl
## mkq_ACC ##

if($#ARGV <= -1){
 print "ファイル名を指定してください\n";
 exit;
}
#open(IN,$ARGV[0]) || die "ファイルの読み込みに失敗しました\n";
while ($line = <>) {
 print 'blastclient ';
 print 'http://www.ncbi.nlm.nih.gov/';
 print 'entrez/query.fcgi?db=nucleotide\'&\'cmd=search\'&\'term=';
 print $line;
}
close(IN);
