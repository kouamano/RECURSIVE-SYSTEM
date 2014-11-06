#!/usr/bin/perl

print "{\n";
$ln = 0;
while(<>){
	chomp;
	if($ln == 0){
		@tmp_arr = split("\t",$_);
		$num_tmp_arr = @tmp_arr;
		$cn = 0;
		print "{";
		foreach(@tmp_arr){
			$_ =~ s/"/\\"/g;
			if($cn == 0){
				print "\"$_\"";
			}else{
				print ",\"$_\"";
			}
			$cn++;
		}
		print "}";
	}else{
		@tmp_arr = split("\t",$_);
		$cn = 0;
		print ",\n{";
		foreach(@tmp_arr){
			if($cn == 0){
				$_ =~ s/"/\\"/g;
				print "\"$_\"";
			}else{
				print ",$_";
			}
			$cn++;
		}
		print "}";
	}
	$ln++;
}
print "}\n";
