#!/usr/bin/perl
while(<>){
	$_ =~ s/[\$\#][0123456789\$\#@]*[0-9]+//g;
	print $_;
}
