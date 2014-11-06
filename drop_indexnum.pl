#!/usr/bin/perl

while(<>){
	$_ =~ s/\s+[0-9]+\s+//i;
	print $_;
}
