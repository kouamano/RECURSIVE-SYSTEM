#!/usr/bin/perl
$ch = $ARGV[0];
while(<STDIN>){
	$count = $_;
	$count = $count =~ s/$ch//g;
	print "$count\n";
}
