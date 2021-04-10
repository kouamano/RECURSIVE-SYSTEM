#!/usr/bin/perl

@arr = ();
while(<>){
	push(@arr,$_);
}
$arr =  join('',@arr);
@brr = split(/\}/,$arr);

foreach(@brr){
	($head,$body) = split(/\{/,$_);
	print $head;
	$ret = `$body`;
	print $ret;
}
