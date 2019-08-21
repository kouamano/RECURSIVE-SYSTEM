#!/usr//bin/perl

$str = $ARGV[0];
$fname = $ARGV[1];

open(IN,$fname);

while(<IN>){
	if($_ =~ /$str/){
		exit(0);
	}
}

close(IN);

print "$fname\n";
