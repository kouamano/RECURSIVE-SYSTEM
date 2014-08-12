#!/usr/bin/perl

while(<>){
	chomp;
	$_ =~ s/\s/ /ig;
	$_ =~ s/^\s//;
	$_ =~ s/\s$//;
	push(@arr,$_);
}

$fn=0;
$ft="";
$former = "0 	";
$sum = 1;
foreach (@arr){
	($fn,$ft) = split(' ',$former);
	#print "fn:$fn\n";
	($cn,$ct) = split(' ',$_);
	#print "cn:$cn\n";
	if($ft eq $ct){
		$sum = $sum + $cn;
		#print "BINGO\n";
		#print "cn:$cn\n";
	}else{
		print "$sum $ft\n";
		$sum = $cn;
	}
	$former = $_;
}
print "$sum $ct\n";
