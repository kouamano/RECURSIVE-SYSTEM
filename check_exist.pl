#!/usr//bin/perl

$str = $ARGV[0];
$fname = $ARGV[1];

open(IN,$fname);

while(<IN>){
	if($_ =~ /$str/){
		print "$fname\n";
		exit(0);
	}
}

close(IN);
