#!/usr/bin/perl

while(<>){
	chomp;
	($f,$ref) = split(";",$_);
	@arr=split(",",$ref);
	%brr = {};
	@hit = $_ =~ /\$[0-9]+/g;		# initialize
	foreach $j (@hit) {
		$brr{$j} = $j;
	}
	foreach $l (@arr) {			# replace rule
		($head,$body,$tail) = split(":",$l);
		$tail =~ s/\]$//;
		$body =~ s/^\[//;
		$brr{$head} = '$'.$body.'$'.$tail;
		#print ":${f}:";
		#print ":${head}:";
		#print ":$brr{$head}:";
		#print "::${f}::";
		#print "::${f}::";
	}
		$f =~ s/(\$[0-9]+)/$brr{$1}/eg;
		print "$f\n";
}
