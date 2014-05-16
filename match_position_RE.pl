#!/usr/bin/perl

# vars
$help = 0;
$check = 0;
$stat = 0;
$qf = "";
$sf = "";

# subroutines
## help
sub _help {
	print "USAGE:\n";
	print " match_position_RE.pl [-h] [-c] [-s] qf=<query file> sf=<source file>\n";
	print "SEARCH RULE:\n";
	print " match_position_RE.pl searchs query(RE) as line by line of <query file>.\n";
	print " It uses valiable for query as like $str =~ /($query)/ \n";
}

## print argv
sub _check {
	print "ARGS:\n";
	print " help:$help:\n";
	print " check:$check:\n";
	print " stat:$stat:\n";
	print " qf:$qf:\n";
	print " sf:$sf:\n";
}

## print status
sub _status {
	print "STATUS:\n";
	printf " Under construction.\n"
}

## argument analysis
foreach $l (@ARGV) {
	if($l eq "-h"){
		$help = 1;
	}elsif($l eq "-c"){
		$check = 1;
	}elsif($l eq "-s"){
		$stat = 1;
	}elsif($l =~ /qf=(.*)/){
		$qf = $1;
	}elsif($l =~ /sf=(.*)/){
		$sf = $1;
	}else{
		print "unknown:$l:\n";
	}
}

# main
## argument check
if($help == 1){
	&_help;
	$ie = 1;
}
if($check == 1){
	&_check;
	$ie = 1;
}
if($stat == 1){
	&_status;
	$ie = 1;
}
if($ie == 1){
	exit(0);
}

## read source
open(IN,$sf);
while (<IN>) {
	push(@arr,$_);
}
close(IN);
$sstr = join('',@arr);

## read query
@arr = {};
open(IN,$qf);
while (<IN>) {
	chomp;
	push(@arr,$_)
}
close(IN);

## matching
foreach(@arr){
	while($sstr =~ /($_)/gim){
		$e = pos($sstr) - 1;
		$p = $e - length($1) + 1;
		print "$1	$p	$e\n";
	}
}

