#!/usr/bin/perl

sub pattern_recv_match {
	if($_ =~ s/(file=[^,]+,)//){
		$str = $1;
		$str =~ s/^file=//;
		$str =~ s/,$//;
		print "$str\n";
		&pattern_recv_match($_);
	}elsif($_ =~ s/(\\includegraphics[^{]*{[^}]+})//){
		$str = $1;
		$str =~ s/^\\includegraphics.*{//;
		$str =~ s/}$//;
		print "$str\n";
		&pattern_recv_match($_);
	}elsif($_ =~ s/(\\input{[^}]*})//){
		$str = $1;
		$str =~ s/^\\input{//;
		$str =~ s/}$//;
		print "$str\n";
		open(IN,$str) || print("no file: $str\n");
			while(<IN>){
				&pattern_recv_match($_);
			}
		close(IN);
		&pattern_recv_match($_);
	}
}

while(<>){
	&pattern_recv_match($_);
}
