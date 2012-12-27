#!/usr/bin/perl

while(<>){
	if($_ =~ /^\s*%/){
	}elsif($_ =~ /^\s*\\[a-zA-Z]*section/){
		print($_);
	}elsif($_ =~ /^\s*\\/){
	}elsif($_ =~ /^\s*&/){
	}else{
		print($_);
	}
}
