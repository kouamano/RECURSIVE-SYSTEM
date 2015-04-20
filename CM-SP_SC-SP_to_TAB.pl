#!/usr/bin/perl

while(<>){
	chomp;
	$_ =~ s/\s/ /g;
	$_ =~ s/, /\t/g;
	$_ =~ s/; /\t/g;
	print "$_\n";
}
