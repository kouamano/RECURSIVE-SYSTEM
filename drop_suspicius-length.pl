#!/usr/bin/perl

while(<>){
	chomp;
	if(length($_) < 80 && length($_) > 1){
		print "$_\n";
	}
}
