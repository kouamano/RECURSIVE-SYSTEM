#!/usr/bin/perl

# vars
$help = 0;
$check = 0;
$status = 0;
$patt = "";
$if = "";
$ie = 0;

# subroutine
sub _help {
	print "USAGE:\n";
	printf " count_patt.pl patt=<pattern> if=<input file> [-h] [-c] [-s] \n"
}

sub _check {
	print "ARGS:\n";
	print " help:$help:\n";
	print " check:$check:\n";
	print " status:$status:\n";
	print " patt:$patt:\n";
	print " if:$if:\n";
}

sub _status {
	print "STATUS:\n";
	printf " Available.\n"
}

# argment analysis
foreach $l (@ARGV) {
	if($l eq "-h"){
		$help = 1;
	}elsif($l eq "-c"){
		$check = 1;
	}elsif($l eq "-s"){
		$status = 1;
	}elsif($l =~ /patt=(.*)/){
		$patt = $1;
	}elsif($l =~ /if=(.*)/){
		$if = $1;
	}else{
		print "unknown:$l:\n";
	}
}

# main
if($help == 1){
	&_help;
	$ie = 1;
}
if($check == 1){
	&_check;
	$ie = 1;
}
if($status == 1){
	&_status;
	$ie = 1;
}
if($ie == 1){
	exit(0);
}

## function
my $count;
open(IN,$if);
while(<IN>){
	#push(@arr,$_);
	$count++ while($_ =~ m/$patt/g);
}
close(IN);
#$str = join("",@arr);
#$count++ while($str =~ m/$patt/g);
print "$count\t$patt\n";

