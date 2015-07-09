#!/usr/bin/perl

while(<>){
	chomp;
	@tmp = split(' or ',$_);
	foreach(@tmp){
		print "$_\n";
	}
}
