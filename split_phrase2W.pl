#!/usr/bin/perl

while(<>){
	chomp;
	@word = split(/\s/,$_);
	if($word[0] == ""){
		shift(@word);
	}
	for($i=0; $i<@word-1; $i++){
		print "$word[$i] $word[$i]+1\n";
	}
}
