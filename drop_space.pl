#!/usr/bin/perl
while(<>){
	chomp($_);
	$_ =~ s/\s//g;
	print $_;
}
print "\n";
