#!/usr/bin/perl

while($line = <>){
 push(@tmp,$line);
 $a = join('',@tmp);
 @b = split(/>[^\n]*\n/,$a);
}
foreach $i (@b) {
 $i =~ s/\n//g;
 $i =~ s/\s//g;
 $i =~ s/[0-9]//g;
 push(@c,$i);
}
$len = @c;
for($i=1;$i<$len;$i++){
 print 'blastclient -k POST ';
 print 'http://www.ncbi.nlm.nih.gov/';
 print 'cgi-bin/BLAST/nph-blast_report?';
 print "@c[$i]";
 print "\n";
}

