#!/usr/bin/perl

while(<>){
	if($_ =~ /^[^\s]+\s[^\s]+$/){
		print $_;
	}
}
