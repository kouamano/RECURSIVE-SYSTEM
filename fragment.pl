#!/usr/bin/perl

if(($#ARGV != 2) && ($#ARGV != 3)){
	die "Usage fragment.pl gap segment shift [file]\n";
}

if($#ARGV == 2){
	$seg = $ARGV[0];
	$gap = $ARGV[1];
	$sht = $ARGV[2];
	while($line = <STDIN>){
		chomp($line);
		push(@a,$line);
	}
	$seq = join('',@a);
	print_fragment($seq);
}

if($#ARGV == 3){
	$seg = $ARGV[0];
        $gap = $ARGV[1];
        $sht = $ARGV[2];
	open(IN,$ARGV[3]);
	while($line = <IN>){
                chomp($line);
                push(@a,$line);
        }
	close(IN);
        $seq = join('',@a);
        print_fragment($seq);
}

sub print_fragment {
	$len = length($_[0]);
	print "$len\n";
	#print $_[0];
	for($j=0+$sht;$j<=$len-$seg;$j=$j+$gap){
		$tmp = substr($_[0],$j,$seg);
		print "$tmp\n";
	}
}
