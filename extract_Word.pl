#!/usr/bin/perl

# vars
$help = 0;
$check = 0;
$status = 0;
$delimfile = "";
$srcfile = "";
$ie = 0;

# subroutine
sub _help {
	print "USAGE:\n";
	printf " extract_Word.pl [-h] [-c] [-s] df=<delimfile> sf=<srcfile> \n"
}

sub _check {
	print "ARGS:\n";
	print " help:$help:\n";
	print " check:$check:\n";
	print " status:$status:\n";
	print " delimfile:$delimfile:\n";
	print " srcfile:$srcfile:\n";
}

sub _status {
	print "STATUS:\n";
	printf " Complete.\n"
}

# argment analysis
foreach $l (@ARGV) {
	if($l eq "-h"){
		$help = 1;
	}elsif($l eq "-c"){
		$check = 1;
	}elsif($l eq "-s"){
		$status = 1;
	}elsif($l =~ /df=(.*)/){
		$delimfile = $1;
	}elsif($l =~ /sf=(.*)/){
		$srcfile = $1;
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

## read delimfile
@arr = ();
open(IN,$delimfile);
while(<IN>){
	chomp;
	#print $_;
	push(@arr,$_);
}
close(IN);
$dcs = join('',@arr);
#print ";;;$dcs;;;\n";

## read source file
open(IN,$srcfile);
while(<IN>){
	chomp;
	@word = split(/$dcs/,$_);
	for($i=0;$i<@word;$i++){
		print "$word[$i]\n";
	}
}
close(IN);
