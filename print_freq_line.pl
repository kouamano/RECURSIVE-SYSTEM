#!/usr/bin/perl

$l = 11;
if($#ARGV == -1){
	while(<>){
		push(@a,$_)
	}
}elsif($#ARGV == 0){
	$l = $ARGV[0];
	while(<STDIN>){
		push(@a,$_);
	}
}elsif($#ARGV >= 1){
	$l = $ARGV[0];
	for($i=1;$i<=$#ARGV;$i++){
		open(IN,$ARGV[$i]);
		while(<IN>){
			push(@a,$_);
		}
		close(IN);
	}
}
@a = sort(@a);
chomp(@a);
$na = @a;
@b = ();
@f = ();
$count = 1;
for($i=0;$i<$na;$i++){
	if($a[$i] eq $a[$i+1]){
		$count++;
	}else{
		if($count >= $l){
			print($a[$i]);
			print(" $count\n");
		}
		$count = 1;	
	}
}
