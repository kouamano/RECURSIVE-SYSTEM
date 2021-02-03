#!/usr/bin/perl

print "(\n";
while(<>){
	chomp;
	print "(";
	print $_;
	print ")";
}
print ")\n";
