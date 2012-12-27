#!/usr/bin/perl

while(<>){
	push(@arr,$_);
}
$str = join('',@arr);
$str =~ s/\n+/\n/g;
print $str;
