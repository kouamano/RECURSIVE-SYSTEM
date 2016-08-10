#!/usr/bin/perl

while(<>){
	$_ =~ s/ {2,}/\t/g;
	print $_;
}
