#!/usr/bin/perl

while(<>){
	$_ =~ s/\s+/ /;
	$_ =~ s/([a-z0-9]{4}\.) /$1\n/g;
	$_ =~ s/([A-Z0-9]{4}\.) /$1\n/g;
	print $_;
}
