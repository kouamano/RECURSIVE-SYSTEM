#!/usr/bin/perl
while(<>){
	$_ =~ s/\s+/ /g;
	$_ =~ s/^\s//;
	$_ =~ s/\s$//;
	print "$_\n";
}
exit;
