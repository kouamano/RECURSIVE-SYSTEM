#!/usr/bin/perl

while(<>){
	chomp;
	$_ =~ s/{//g;
	$_ =~ s/},*/\n/g;
	$_ =~ s/,/ /g;
	print $_;
}
