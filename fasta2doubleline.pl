#!/usr/bin/perl

$count = 0;
while(<>){
	chomp;
	$_ =~ s/\t+/ /g;
	if($_ =~ /^>/){	
		if($count == 0){
			print "$_\n";
		}else{
			print "\n$_\n";
		}
	}else{
		$_ =~ s/\s//g;
		print $_;
	}
	$count++;
}
print "\n";
