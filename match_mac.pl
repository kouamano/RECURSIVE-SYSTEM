#!/usr/bin/perl

$fip = $ARGV[0];
$fuser = $ARGV[1];

%machash = ();
open(IN,$fuser);
while(<IN>){
	chomp;
	$_ =~ s/^\s+//;
	$_ =~ s/\s+$//;
	$_ =~ s/\s+/\t/g;
	@arr = split(/\t/,$_);
	$machash{$arr[0]} = $arr[1];
}
close(IN);
#print %machash;

open(IN,$fip);
while(<IN>){
	chomp;
	$_ =~ s/^\s+//g;
	$_ =~ s/\s+$//g;
	$_ =~ s/\s+/\t/g;
	@line = split(/\t/,$_);
	print "$line[0]\t$line[2]\t";
	print $machash{$line[2]};
	print "\n";
}
close(IN);

