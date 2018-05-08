#!/usr/bin/perl

$/ = '>';
while(<>){
	$_ =~ /(\[[^\[]+\])/;
	$tmp = $1;
	$tmp =~ s/\[//g;
	$tmp =~ s/\]//g;
	$tmp =~ s/ //g;
	$tmp =~ s/-/ /g;
	print "$tmp\n";
}
