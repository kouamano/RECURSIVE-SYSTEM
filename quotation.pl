#!/usr/bin/perl

print("\"");
while(<>){
	$_ =~ s/"/\\"/g;
	print($_);
}
print("\"");
