#!/usr/bin/perl

while(<>){
	chomp;
	$_ =~ s/\s/\t/ig;
	$_ =~ s/^\s//;
	$_ =~ s/\s$//;
	$_ =~ s/\t/ /;
	push(@arr,$_);
}
#print "=====\n";
($fn,$ft) = split(/ /,$arr[0]);
#print ";;;$fn;;;";
#print ";;;$ft;;;";
#print "=====\n";
$former = $arr[0];
$sum = $fn;
shift(@arr);
foreach (@arr){
	($fn,$ft,$fk) = split(/ /,$former);
	#print ";;; $ft ;;; $fk ;;;\n";
	($cn,$ct) = split(/ /,$_);
	if($ft eq $ct){
		$sum = $sum + $cn;
	}else{
		print "$sum $ft\n";
		$sum = $cn;
	}
	$former = $_;
}
print "$sum $ct\n";
