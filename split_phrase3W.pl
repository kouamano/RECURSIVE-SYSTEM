#!/usr/bin/perl

while(<>){
	chomp;
	@word = split(/\s/,$_);
	if($word[0] == ""){
		shift(@word);
	}
	for($i=0; $i<$#word; $i++){
		print "$word[$i] $word[$i+1] $word[$i+2]\n";
	}
}
