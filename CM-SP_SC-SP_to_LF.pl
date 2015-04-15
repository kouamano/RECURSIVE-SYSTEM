#!/usr/bin/perl

while(<>){
	$_ =~ s/, /\n/g;
	$_ =~ s/; /\n/g;
	print $_;
}
