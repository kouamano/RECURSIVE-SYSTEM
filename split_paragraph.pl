#!/usr/bin/perl

while(<>){
	$_=~s/<\/p><p>/<\/p><;\/><p>/g;
	print $_;
}
