#!/usr/bin/perl
$in_origin = 0;
while(<>){
	if ($_ =~ /^LOCUS\s+/) {
		@locus = split('\s+',$_);
		$locus = join('_',@locus);
	}
	if ($_ =~ /^ACCESSION\s+/) {
		@accesion = split('\s+',$_);
	}
	if ($_ =~ /^VERSION\s+/) {
		@version = split('\s+',$_);
		$version[2] =~ s/^GI://;
	}
	if ($_ =~ s/^ORIGIN\s+//) {
		$in_origin++;
		print ">gi|".$version[2];
		print "|gb|".$version[1];
		print "|".$locus."\n";
	}
	if ($_ =~ /^\/\/$/) {
		$in_origin--;
		print "\n";
	}
	if ($in_origin > 0) {
		$_ =~ s/[0-9]//g;
		$_ =~ s/\s+//g;
		print $_;
	}
}
