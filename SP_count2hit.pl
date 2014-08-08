#!/usr/bin/perl

while(<>){
	chomp;
	($ax1,$ax2,$v) = split("\t",$_);
	if($v == 0){
		print "$ax1\t$ax2\t$v\n";
	}elsif($v > 0){
		print "$ax1\t$ax2\t1\n";

	}elsif($v < 0){
		print "$ax1\t$ax2\t-1\n";
	}
}
