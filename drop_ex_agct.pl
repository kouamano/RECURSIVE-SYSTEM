#!/usr/bin/perl

while(<>){
	if($_ =~ /[BDEFH-SU-Z]+/){
		#print($_);
	}elsif($_ =~ /[bdefh-su-z]+/){
		#print($_);
	}else{
		print($_);
	}
}
