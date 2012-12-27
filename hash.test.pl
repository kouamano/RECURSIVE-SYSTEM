#!/usr/bin/perl

$t{'A'}{'B'}=7;
$t{'A'}{'C'}=8;
$t{'D'}{'G'}=10;
$t{'D'}{'Y'}=9;

foreach $item(keys %t){
	print $item;
		foreach $itemitem(keys %{$t{$item}}){
			print " $itemitem";
		}
	print "\n";
}

