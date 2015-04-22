#!/usr/bin/perl

use List::Util qw(max);

$sourcefile = $ARGV[0];
$substrfile = $ARGV[1];

open(IN,$sourcefile);
while(<IN>){
	chomp;
	push(@source,$_);
}
close(IN);

open(IN,$substrfile);
while(<IN>){
	chomp;
	push(@substr,$_);
}
close(IN);

foreach(@source){
	$str = $_;
	foreach(@substr){
		if($src =~ /$_/){
			print "$src\n";
			break;
		}
	}
}
