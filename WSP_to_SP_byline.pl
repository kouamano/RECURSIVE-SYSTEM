#!/usr/bin/perl
while(<>){
	$_ =~ s/\s/ /ig;
	print "$_\n";
}
