#!/usr/bin/perl
while(<>){
	$_ =~ s/[a-zA-Z]*@//g;
	print $_;
}
