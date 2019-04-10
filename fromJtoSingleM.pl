#!/usr/bin/perl

while(<>){
	push(@arr,$_);
}
$str = join('',@arr);
$str =~ s/\n//g;
print "{\n";
print "$str\n";
print "}\n";
