#!/usr/bin/perl

while(<>){
	"" =~ /()/;
	$_ =~ /\],:>([0-9]+)</;
	if(length($1) > 0){
		print "$1\n";
	}
}
