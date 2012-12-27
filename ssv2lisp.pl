#!/usr/bin/perl

while(<>){
	push(@a,$_);
}
print("(setq data \n");
print("\'(\n");
foreach $i(@a){
	chomp($i);
	#$i =~ s/[a-zA_Z]+/\"$&\"/g;
	$j = $i;
	$j = " ($j)\n";
	push(@b,$j);
}
print(@b);
print(" ) )\n");
