#!/usr/bin/perl

while(<>){
	$_ =~ s/[\.\,\";:<>\(\)\{\}\[\]]//ig;
	print $_;
}
