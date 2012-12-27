#!/usr/bin/perl

$sep=$ARGV[0];
shift(@ARGV);

foreach $file (@ARGV) {
	open(IN,$file);
	while(<IN>){
		chomp;
		($head,@tail) = split($sep,$_);
		foreach $tail (@tail){
			print "$tail$sep";
		}
		print "$head\n";
	}
	close(IN)
}
