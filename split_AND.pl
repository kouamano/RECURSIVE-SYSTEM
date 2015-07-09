#!/usr/bin/perl

while(<>){
	chomp;
	@tmp = split(/ [aA][nN][dD] /,$_);
	foreach(@tmp){
		print "$_\n";
	}
}
