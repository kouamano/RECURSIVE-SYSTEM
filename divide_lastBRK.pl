#!/usr/bin/perl

$hit = 0;
while(<>){
	chomp;
	$id = "";
	s/^\s+//;
	s/\s+$//;
	s/\s+/ /g;
	$hit = ($_ =~ s/(\([^()]+\)).{0,1}$//);
	#print "$hit\n";
	print "$_\t";
	if($hit == 1){
		print "$1\n";
	}else{
		print "\n";
	}
}
