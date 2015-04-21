#!/usr/bin/perl

while(<>){
	if($_ =~ /\t/){
		$_ =~ s/^[^\t]*\t//;
		print $_;
	}
}
