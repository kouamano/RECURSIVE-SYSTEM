#!/usr/bin/perl

use List::Util qw(max);
use Parallel::ForkManager;

my $pm = Parallel::ForkManager->new(24);

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
	$pm->start and next;
	$str = $_;
	#print "SRC:$str:\n";
	foreach(@substr){
		#print "SUB:$_:\n";
		if($str =~ /$_/){
			#print "HIT:$str:\n";
			print "$str\n";
			last;
		}
	}
	$pm->finish;
}
$pm->wait_all_children;
