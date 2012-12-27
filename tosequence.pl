#!/usr/bin/perl

##initialize##
$fa = 0;	#fasta
$al = 0;	#alphabetical
$ex = 0;	#extent
$si = 0;	#STDIN
$he = 0;	#help

##get options##
foreach $option (@ARGV) {
	if($option eq '-f'){
		$fa = 1;
		print STDERR "fasta format::\n";
	}elsif($option eq '-a'){
		$al = 1;
		print STDERR "alphabet mode::\n";
	}elsif($option eq '-e'){
		$ex = 1;
		print STDERR "extent mode::\n";
	}elsif($option eq '-s'){
		$si = 1;
		print STDERR "stdin mode::\n";
	}elsif($option eq '-h'){
		$he = 1;
	}else{
		push(@files,$option);
	}
}

##main process##
if($he == 1){
	&help();
	exit;
}

if($si == 1){	#from STDIN
	while(<STDIN>){
		if($_ =~ /^>/){
			if(($al == 0) && ($ex == 0)){
				$seq =~ s/[^AGCTagct]//g;
			}
			if(length($seq) != 0){
				print "$seq\n";
			}
			$seq = '';
			print $_;
		}else{
			$seq = $seq.$_;
		}
	}
	if(($al == 0) && ($ex == 0)){
	$seq =~ s/[^AGCTagct]//g;
	if(length($seq) != 0){
		print "$seq\n";
	}
}else{		#from file(s)
}

exit;

##subroutines##
sub help {
	my($SPACEV,$SPACEX);
	$SPACEV = "     ";
	$SPACEX = "          ";
	print "USAGE:\n";
	print " tosequence.pl [-f] [-a] [-e] [-s] [-h] [<files>]\n";
	print "OPTIONS:\n";
	print " -f $SPACEX output is set FASTA format.\n";
	print " -a $SPACEX output allows alphabetical letters.\n";
	print " -e $SPACEX output allows extra expression of nucleotide such as N or W.\n";
	print " -s $SPACEX input file is set STDIN.\n";
	print " -h $SPACEX print help.\n";
	print " <files> $SPACEV input file(s).\n";
}

##END##
