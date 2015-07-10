#!/usr/bin/perl

while(<>){
	chomp;
	if($_ =~ /\([a-zA-Z]+[0-9]+\)/){
		$_ =~ s/\(([a-zA-Z]+[0-9]+)\)/\n$1\n/g;
		print "$_\n";
	}else{
		print "$_\n";
	}
}
