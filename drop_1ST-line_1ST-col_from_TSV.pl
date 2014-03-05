#!/usr/bin/perl

$l_count = 0;
while(<>){
	if($l_count == 0){
		;
	}else{
		$_ =~ s/[^\t]*\t//;
		print $_;
	}
	$l_count++;
}
