#!/usr/bin/perl

while($line = <>){
 chomp($line);
 @a = split(' ',$line);
 foreach $i (@a) {
  print 'blastclient http://www.ncbi.nlm.nih.gov/entrez/query.fcgi?cmd=Retrieve';
  print "\'&\'";
  print 'db=nucleotide';
  print "\'&\'";
  print 'list_uids=';
  print "$i";
  print "\'&\'";
  print 'dopt=GenBank';
  print "\n";
 }
}
