#!/usr/bin/perl

while(<>){
	$_ =~ s/^\s*//;
	$_ =~ s/\s/\t/;
	print $_;
}
