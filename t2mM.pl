#!/usr/bin/perl
@str = ();
print "{\n";
while(<>){
	chomp;
	$_ =~ s/\[/\[DIM,/g;
	$_ =~ s/\(/\[/g;
	$_ =~ s/\)/\]/g;
	push(@str,$_);
}
$strout = join(",\n",@str);
print $strout;
print "\n}\n";
