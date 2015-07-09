#!/usr/bin/perl

while(<>){
	chomp;
	@tmp = split(/ [oO][rR] /,$_);
	foreach(@tmp){
		print "$_\n";
	}
}
