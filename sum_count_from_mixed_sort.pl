#!/usr/bin/perl

while(<>){
	chomp;
	$_ =~ s/\s/ /ig;
	$_ =~ s/^\s//;
	$_ =~ s/\s$//;
	push(@arr,$_);
}
($fn,$ft) = split(' ',$arr[0]);
$former = $arr[0];
$sum = $fn;
shift(@arr);
foreach (@arr){
	($fn,$ft) = split(' ',$former);
	($cn,$ct) = split(' ',$_);
	if($ft eq $ct){
		$sum = $sum + $cn;
	}else{
		print "$sum $ft\n";
		$sum = $cn;
	}
	$former = $_;
}
print "$sum $ct\n";
