#!/usr/bin/perl

use utf8;

while(<>){
	$_ =~ s/(.)/sprintf '&#x%x;', ord($1)/eg;
	print $_;
}
