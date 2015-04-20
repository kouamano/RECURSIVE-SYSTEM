#!/usr/bin/perl

$hit = 0;
while(<>){
	chomp;
	$id = "";
	s/^\s+//;
	s/\s+$//;
	s/\s+/ /g;
	$hit = ($_ =~ s/(\([^()]+\)).{0,1}$//);
	$id = $1;
	$id =~ s/^(//;
	$id =~ s/)$//;
	#print "$hit\n";
	print "$_\t";
	if($hit == 1){
		print "$id\n";
	}else{
		print "\n";
	}
}
