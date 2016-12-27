#!/usr/bin/perl

while(<>){
	chomp;
	@arr = split(/\t/,$_);
	$mac = shift(@arr);
	$mac =~ s/\"//g;
	$mac =~ s/-/:/g;
	$str = join("	",@arr);
	print "$mac\t$str\n";
}
