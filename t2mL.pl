#!/usr/bin/perl
@str = ();
while(<>){
	chomp;
	$_ =~ s/\[/\[DIM,/g;
	$_ =~ s/\(/\[/g;
	$_ =~ s/\)/\]/g;
	push(@str,$_);
}
$strout = join("\n",@str);
print $strout;
print "\n";
