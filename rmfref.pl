#!/usr/bin/perl
while(<>){
	$_ =~ s/\(@\)//g;
	print $_;
}
