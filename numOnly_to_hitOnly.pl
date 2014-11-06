#!/usr/bin/perl

while(<>){
	chomp;
	@arr = split("\t",$_);
	$first = shift(@arr);
	if($first == 0){
		print $first;
	}else{
		print "1";
	}
	foreach(@arr){
		if($_ == 0){
			print "\t$_";
		}else{
			print "\t"."1";
		}
	}
	print "\n";
}
