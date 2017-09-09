#!/usr/bin/perl

while(<>){
	$_=~s/<p>/<;\/><p>/g;
	$_=~s/<sec>/<;\/><sec>/g;
	$_=~s/<sec /<;\/><sec /g;
	#$_=~s/<\/sec><sec([^>]*?)>/<\/sec><;\/><sec${1}>/g;
	print $_;
}
