#!/usr/bin/perl
$i = 0;
while(<>){
	if($_ =~ /^>/){
		if($i == 0){
			chomp $_;
			print "$_\n";
		}else{
			chomp $_;
			print "\n$_\n";
		}
		$i++;
	}else{
		chomp $_;
		print $_;
	}
}
