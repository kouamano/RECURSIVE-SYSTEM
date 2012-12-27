#!/usr/bin/perl

print("`");
while(<>){
	$_ =~ s/\{/(/g;
	$_ =~ s/,/ /g;
	$_ =~ s/\}/)/g;
	print($_);
}
