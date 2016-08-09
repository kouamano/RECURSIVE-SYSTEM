#!/usr/bin/perl

while(<>){
	chomp;
	push(@arr,$_);
}
($first_count,$first_term) = split(/\t/,$arr[0]);
$former = $first_term;
$sum = $first_count;
shift(@arr);
foreach (@arr){
	($current_count,$current_term) = split(/\t/,$_);
	if($former eq $current_term){
		$sum = $sum + $current_count;
	}else{
		print "$sum\t$former\n";
		$sum = $current_count;
	}
	$former = $current_term;
}
print "$sum\t$former\n";
