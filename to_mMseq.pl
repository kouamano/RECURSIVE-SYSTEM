#!/usr/bin/perl
@arr = ();
while(<>){
	chomp;
	push(@arr,$_);
}
$arr = join(",\n",@arr);
$out = "{\n".$arr."\n}\n";
print $out;
