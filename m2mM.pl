#!/usr/bin/perl
@arr = ();
while(<>){
	chomp;
	push(@arr,$_);
}
$arr = join(",\n",@arr);
print "{\n";
print $arr;
print "\n}\n";
