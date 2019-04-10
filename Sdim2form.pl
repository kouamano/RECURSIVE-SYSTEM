#!/usr/bin/perl

while(<>){
	$_ =~ s/(\$[0-9a-zA-Z\$\#]*)\[(.*?)\]/[\1,\$\$dim,\2]/g;
	print $_;
}
