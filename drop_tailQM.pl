#!/usr/bin/perl

while(<>){
	chomp;
	$_ =~ s/\?+$//;
	print "$_\n";
}
