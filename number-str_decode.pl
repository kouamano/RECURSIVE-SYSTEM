#!/usr/bin/perl

use utf8;
use Encode 'decode';

while(<>){
	$_ =~ s/&#x([0-7][0-9a-fA-F]);/decode('UTF-8', pack('H*', $1))/eg;
	$_ =~ s/&#x([0-9a-fA-F]);/decode('ASCII', pack('h*', $1))/eg;
	print $_;
}
