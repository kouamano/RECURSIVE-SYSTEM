#!/usr/bin/perl

while(<>){
	chomp;
	$_ =~ s/^\s+//;
	$_ =~ s/\s+$//;
	$_ =~ s/ +/ /;
	#print $_;
	@arr = split(' ',$_);
	foreach(@arr){
		print "$.\t$_\n";
	}
}
