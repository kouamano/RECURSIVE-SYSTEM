#!/usr/bin/perl
while(<>){
	$_ =~ s/\${0,1}\#{1,2}[0-9]+//g;
	print $_;
}
