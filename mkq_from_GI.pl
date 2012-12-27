#!/usr/bin/perl

$key = 'list_uids=';
while (<>) {
 if($_ =~ /($key[0-9]+)/){
  push(@tmp,$1)
 }
}
foreach $i (@tmp) {
 $i =~ /([0-9]+)/;
 push(@tmp2,$1);
}

@tmp3 = sort(@tmp2);
@tmp4 = uniq(@tmp3);
print_query(@tmp4);


## sub routines ##
sub print_query {
 foreach $i (@_) {
  $i =~ /([0-9]+)/;
  print 'blastclient ';
  print 'http://www.ncbi.nlm.nih.gov/entrez';
  print "\/query\.fcgi\?cmd=Retrieve\'&\'db=nucleotide\'&\'list_uids=";
  print "$1";
  print "\'&\'dopt=GenBank";
  print "\n";
 }
}

sub uniq {
 local(@out);
 local($el);
 local($i);
 $el = @_;
 push(@out,$_[0]);
 for($i=0; $i<$el-1; $i++){
  if($_[$i] ne $_[$i+1]){
   push(@out,$_[$i+1]);
  }
 }
 return(@out);
}

## end sub routines ##
