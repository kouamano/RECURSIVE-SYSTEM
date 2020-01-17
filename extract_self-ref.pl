#!/usr/bin/perl

while(<>){
	"" =~ /()/;
	chomp;
	$_ =~ /(\[.*\])/;
	$self = $1;
	print $self;
	$self =~ /([0-9]*)\]/;
	$selfnum = $1;
	$line = $_;
	$line =~ s/\[.*\]//;
	@line = split(/,/,$line);
	foreach(@line){
		$_ =~ s/^[^0-9]*//;
		if($selfnum eq $_){
			print ",:>$_<";
		}
	}
	print "\n";
}
