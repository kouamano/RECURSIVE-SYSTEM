#!/usr/bin/perl

while(<>){
	push(@arr,$_);
}
$l = join('',@arr);
$l =~ s/\s/ /g;
print "$l\n";
