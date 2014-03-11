#!/usr/bin/perl

while(<>){
	$_ =~ s/^[^\t]*\t//;
	print $_;
}
