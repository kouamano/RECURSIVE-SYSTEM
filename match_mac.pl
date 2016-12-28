#!/usr/bin/perl

$fip = $ARGV[0];
$fuser = $ARGV[1];

open(IN,$fip);
%ip = ();
while(<IN>){
	chomp;
	@arr = split(/\s/,$_);
	$first = shift(@arr);
	$last = pop(@arr);
	#print "$first\n";
	#print "$last\n";
	$ip{$last} = $first;
}
close(IN);

#print %ip;

open(IN,$fuser);
while(<IN>){
	chomp;
	@arr = split(/\s/,$_);
	$mac = shift(@arr);
	$usr = pop(@arr);
	print "$mac\t$usr\t$ip{$mac}\n";
}
close(IN);
