#!/usr/bin/perl

while(<>){
	$_ =~ s/\s/ /g;
	$_ =~ s/, /\t/g;
	$_ =~ s/; /\t/g;
	print $_;
}
