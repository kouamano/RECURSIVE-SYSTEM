#!/usr/bin/perl

sub _padding{
	@sarr = split(/:/,$_[0]);
	@oarr = ();
	foreach(@sarr){
		if(length($_) > 1){
			$n = $_;
		}else{
			$n = "0"."$_";
		}
		push(@oarr,$n);
	}
	return join(":",@oarr);
}

while(<>){
	chomp;
	if($_ =~ / ([0-9a-fA-F]+:){5}[0-9a-fA-F]+$/){
		@line = split(/ /,$_);
		$target = pop(@line);
		$str = join(" ",@line);
#		@target = split(/:/,$target);
#		@out = ();
#		foreach(@target){
#			if(length($_) > 1){
#				$n = $_;
#			}else{
#				$n = "0"."$_";
#			}
#			push(@out,$n);
#		}
#		$out = join(":",@out);
		$pout = &_padding($target);
		$pout =~ tr/A-Z/a-z/;
		print "$str $pout\n";
	}else{
		print "$_\n";
	}
}
