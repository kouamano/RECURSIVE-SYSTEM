#!/usr/bin/perl
## mkq_ACC ##

if($#ARGV <= -1){
 print "�ե�����̾����ꤷ�Ƥ�������\n";
 exit;
}
#open(IN,$ARGV[0]) || die "�ե�������ɤ߹��ߤ˼��Ԥ��ޤ���\n";
while ($line = <>) {
 print 'blastclient ';
 print 'http://www.ncbi.nlm.nih.gov/';
 print 'entrez/query.fcgi?db=nucleotide\'&\'cmd=search\'&\'term=';
 print $line;
}
close(IN);
