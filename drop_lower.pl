#!/usr/bin/perl
while(<>){
	$_ =~ s/[a-z]+//g;
	print($_);
}
