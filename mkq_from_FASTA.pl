#!/usr/bin/perl

while($line = <>){
 if($line =~ /^(a|g|c|t|n|A|G|C|T|N)+$/){
  print 'blastclient -k POST ';
  print 'http://www.ncbi.nlm.nih.gov/';
  print 'cgi-bin/BLAST/nph-blast_report?';
  print "$line";
  print "\n";
 }
}
