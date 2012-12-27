#!/usr/bin/perl

while(<>){
	chomp($_);
	$_ =~ s/\s+/ /g;
	if($_ != ""){
		printf("$_\n");
	}
}
