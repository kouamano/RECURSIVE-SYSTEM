#!/usr/bin/perl

# vars
$help = 0;
$check = 0;
$status = 0;
$sf = 0;
$qf = "";
$ie = 0;
$head = "[^A-Za-z]";
$tail = "[^A-Za-z]";

# subroutine
sub _help {
	print "USAGE:\n";
	printf " match_lines.pl -c -h -s sf=<source file> qf=<query file>\n"
}

sub _check {
	print "ARGS:\n";
	print " help:$help:\n";
	print " check:$check:\n";
	print " status:$status:\n";
	print " sf:$sf:\n";
	print " qf:$qf:\n";
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
	}elsif($l =~ /sf=(.*)/){
		$sf = $1;
	}elsif($l =~ /qf=(.*)/){
		$qf = $1;
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

## read query file
open(IN,$qf);
while(<IN>){
	chomp;
	push(@arr,$_);
}
close(IN);

## read source file
open(IN,$sf);
while(<IN>){
	chomp;
	$sl = $_;
	print $sl;
	print "\t<\t>\t";
	foreach(@arr){
		if($sl =~ /($head)($_)($tail)/i){
			print "\t$_";
		}
	}
	print "\n";
}
close(IN);
