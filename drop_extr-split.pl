#!/usr/bin/perl

while(<>){
	$l = $_;
	$l =~ s/(<italic>[^<>]*)(<;\/>)([^<>]*<\/italic>)/$1$3/g;
	print $l;
}
