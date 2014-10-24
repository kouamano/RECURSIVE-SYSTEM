#!/usr/bin/perl
while(<>){
	$_ =~ s/&#x([0-9a-fA-F]*)\;/pack("H*",$1)/eg;
	print $_;
}
exit;
