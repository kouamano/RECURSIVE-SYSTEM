#!/usr/bin/perl

while(<>){
	chomp;
	if($_ =~ /\(RDB[0-9]+\)/){
		#print "$_\n";
		$_ =~ s/\((RDB[0-9]+)\)/\n$1\n/g;
		#$_ =~ s/ \(/\n/g;
		#$_ =~ s/\) /\n/g;
		print "$_\n";
	}else{
		print "$_\n";
	}
}
