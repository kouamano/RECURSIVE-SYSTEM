#!/usr/bin/perl

while(<>){
	push(@a,$_);
}
@a = sort(@a);
chomp(@a);
$na = @a;
@f = ();
$count = 1;
for($i=0;$i<$na;$i++){
	if($a[$i] eq $a[$i+1]){
		$count++;
	}else{
		print($a[$i]);
		print(" $count\n");
		$count = 1;	
	}
}
