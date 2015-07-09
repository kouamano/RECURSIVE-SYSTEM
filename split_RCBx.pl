#!/usr/bin/perl

while(<>){
	chomp;
	if($_ =~ /\(RCB[0-9]+\)/){
		#print "$_\n";
		@tmp = split(/[\(\)]/,$_);
		foreach(@tmp){
			print "$_\n";
		}
	}else{
		print "$_";
	}
}
