#!/usr/bin/perl
while(<>){
	#$_ =~ s/I\(([^I(]*)\)/\1/g;
	$_ =~ s/^I\(([^(]*)\)/\1/g;
	#$_ =~ s/K\(([^K(]*)\([^K(]*\)\)/\1/g;
	$_ =~ s/^K\(([^(]*)\([^(]*\)\)/\1/g;
	#$_ =~ s/S\(([^S(]*)\(([^S(]*)\(([^S(]*)\)\)\)/\1\(\3\(\2\(\3\)\)\)/g;
	$_ =~ s/^S\(([^(]*)\(([^(]*)\(([^(]*)\)\)\)/\1\(\3\(\2\(\3\)\)\)/g;
	print $_;
}
