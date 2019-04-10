#!/usr/bin/perl
while(<>){
	chomp;
	if($_ eq "{"){
		;
	}elsif($_ eq "}"){
		;
	}else{
		$_ =~ s/\[/\(/g;
		$_ =~ s/\]/\)/g;
		$_ =~ s/(\(DIM,)(.*?)(\))/\[$2\]/g;
		$_ =~ s/,$//;
		print "$_\n";
	}
}
