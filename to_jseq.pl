#!/usr/bin/perl
@arr = ();
while(<>){
	chomp;
	push(@arr,$_);
}
$arr = join(",\n",@arr);
$out = "[".$arr."]\n";
print $out;
