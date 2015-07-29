#!/usr/bin/perl

# vars
$help = 0;
$check = 0;
$status = 0;
$col = -1;
$ie = 0;

# subroutine
sub _help {
	print "USAGE:\n";
	printf " hit_least.pl src=<source file> qury=<query file> col=<target columns all n-th after>.\n";
	print "STATEMENTS:\n";
}

sub _check {
	print "ARGS:\n";
	print " help:$help:\n";
	print " check:$check:\n";
	print " status:$status:\n";
	print " src:$src:\n";
	print " qury:$qury:\n";
	print " col:$col:\n";
}

sub _status {
	print "STATUS:\n";
	printf " Under construction.\n"
}

# argment analysis
foreach $l (@ARGV) {
	if($l eq "-h"){
		$help = 1;
	}elsif($l eq "-c"){
		$check = 1;
	}elsif($l eq "-s"){
		$status = 1;
	}elsif($l =~ /src=(.*)/){
		$src = $1;
	}elsif($l =~ /qury=(.*)/){
		$qury = $1;
	}elsif($l =~ /col=(.*)/){
		$col = $1;
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

open(IN,$qury);
while(<IN>){
	chomp;
	push(@qarr,$_);
}
close(IN);

open(IN,$src);
while(<IN>){
	$out = $_;
	$target = $_;
	@target = split(/\t/,$target);
	for($i=0;$i<$col;$i++){
		shift(@target);
	}
	$target = join("\t",@target);
	foreach(@qarr){
		if($target =~ /$_/){
			print "$out";
			last;
		}
	}
}
close(IN);





