#!/usr/bin/perl

# vars
$help = 0;
$check = 0;
$status = 0;
$X = 1;
$ie = 0;

# subroutine
sub _help {
	print "USAGE:\n";
	printf " extract_terms.pl sf=<source file> qf=<query file> span=<before>,<after> [-X|+X]\n";
	printf "  <query file> : escaped term list.\n";
	printf "  <before>,<after> : print before <before> bytes, and after <after> bytes.\n";
	printf "  [-X|+X] : knock out XML-tags; -X:on, +X:off.\n";
}

sub _check {
	print "ARGS:\n";
	print " help:$help:\n";
	print " check:$check:\n";
	print " status:$status:\n";
	print " sf:$sf:\n";
	print " qf:$qf:\n";
	print " be:$be:\n";
	print " af:$af:\n";
	print " X:$X:\n";
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
	}elsif($l =~ /sf=(.*)/){
		$sf = $1;
	}elsif($l =~ /qf=(.*)/){
		$qf = $1;
	}elsif($l =~ /span=([^,]*),([^,]*)/){
		$be = $1;
		$af = $2;
	}elsif($l =~ /^-X$/){
		$X = 1;	#knock out XML-tags
	}elsif($l =~ /^\+X$/){
		$X = 0;	#print XML-tags
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

##store query (escaped)
open(IN,$qf);
while(<IN>){
	chomp;
	push(@qr,$_);
}
close(IN);

##store src
open(IN,$sf);
while(<IN>){
	push(@sr,$_);
}
close(IN);
$sr = join("",@sr);
$sr =~ s/\s/ /g;
if($X == 1){
	$sr =~ s/(<[^<>]*?>)/$count=0;$sb="";while($count < length($1)){$sb = $sb." "; $count++;};$sb/eg;
}

##mach / print @ each term
foreach(@qr){
	print "$_\n";
	@arr = ();
	while($sr =~ /(.{0,$be})($_)(.{0,$af})/g){
		push(@arr,$1.$2.$3);
		$p = pos($sr);
		pos($sr) = $p - length($3) + 1;
	}
	foreach(@arr){
		print "\t$_\n";
	}
}

