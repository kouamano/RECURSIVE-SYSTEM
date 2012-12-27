#!/usr/bin/perl

$prog = '/home/pub/bin/extract_region_ORGANISM_from_Gbk';
@files = @ARGV;

foreach $file (@files) {
	$tmp = `$prog $file`;
	$tmp =~ s/^M +([^;]+);/$1::/;
	$tmp =~ s/ ([a-zA-Z]+)::/:: $1;/;
	$tmp =~ s/\s+/ /g;
	$tmp =~s/ +REFERENC//;
	print "$tmp\n";
}
