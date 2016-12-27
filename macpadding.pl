#!/usr/bin/perl

while(<>){
	chomp;
	if($_ =~ / ([0-9a-fA-F]+:)+[0-9a-fA-F]+$/){
		@line = split(/ /,$_);
		$target = pop(@line);
		$str = join(" ",@line);
		@target = split(/:/,$target);
		@out = ();
		foreach(@target){
			$n = sprintf("%02d",$_);
			push(@out,$n);
		}
		$out = join(":",@out);
		print "$str $out\n";
	}else{
		print "$_\n";
	}
}
