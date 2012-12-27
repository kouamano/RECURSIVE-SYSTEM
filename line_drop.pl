#!/usr/bin/perl

#print($#ARGV);
if($#ARGV == 0){
	$drops=$ARGV[0];
	#print("drops : $drops\n");
	while(<STDIN>){
		push(@a,$_);
	}
}elsif($#ARGV == 1){
	$drops=$ARGV[1];
	open(IN,$ARGV[0]);
	while(<IN>){
		push(@a,$_);
	}
}
$num_a = @a;
#print("num_a : $num_a\n");
if($drops >= 0){
	for($i=$drops;$i<$num_a;$i++){
		print($a[$i]);
	}
}elsif($drops < 0){
	for($i=0;$i<$num_a+$drops;$i++){
		print($a[$i]);
	}
}
