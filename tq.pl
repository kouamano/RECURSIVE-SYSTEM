#!/bin/env perl
$head = "";
$rls = ();
$script = ();
while(<>){
	if($_ =~ /\$RE$/){
		print $_;
	}elsif($_ =~ /\$E$/){
		;
	}
}
