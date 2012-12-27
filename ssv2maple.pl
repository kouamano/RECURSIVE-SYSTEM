#!/usr/bin/perl
print("\[\n");
while(<>){
	chomp;
	print "[";
	$_ =~ s/\s+$//;
	$_ =~ s/(^[^\s]*[a-zA-Z]+[^\s]*)\s/\"$1\",/;
	$_ =~ s/\s+/,/g;
	print $_;
	print "],\n";
}
print("];\n");
