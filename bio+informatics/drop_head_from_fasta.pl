#!/usr/bin/perl
#drop_head_from_fasta#

while(<>){
	if($_ !~ /^>/){
		print $_;
	}
}
