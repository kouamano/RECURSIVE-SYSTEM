#!/usr/bin/perl

while(<>){
	push(@a,$_);
}
$num_a = @a;
for($i=0;$i<$num_a;$i++){
	chomp($a[$i]);
	$a[$i] =~ s/,/\s/g;
	$a[$i] = "[$a[$i]]";
	push(@b,$a[$i]);
}
$c = join('',@b);
$c =~ s/^\[//;
$c =~ s/\]$//;
$c =~ s/\]\[/\n/g;
print($c);
print("\n");
