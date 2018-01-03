#!/usr/bin/perl

while(<>){
	$l = $_;
	$l =~ s/(<italic>[^<>]*)(<;\/>)([^<>]*<\/italic>)/${1}${2}/g;
	print $1;
}
