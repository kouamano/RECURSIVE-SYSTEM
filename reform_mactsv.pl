#!/usr/bin/perl

while(<>){
	chomp;
	@arr = split(/\t/,$_);
	$mac = shift(@arr);
	$mac =~ s/\"//g;
	$mac =~ s/-/:/g;
	$mac =~ tr/A-Z/a-z/;
	$str = join("	",@arr);
	print "$mac\t$str\n";
}
