#!/usr/bin/perl

while(<>){
	chomp;
	@arr = split(/\s/,$_);
	@brr = sort(@arr);
	@arr = &uniq(@brr);
	foreach (@arr) {
		print " $_";
	}
	#foreach(@brr){
	#	print " $_";
	#}
	print "\n";
}

sub uniq {
	my %seen;
	grep !$seen{$_}++, @_;
}
