#!/usr/bin/perl

#static %c#
%c = ();
if($#ARGV == 1){
	if($ARGV[0] != '-f'){
	}else{
		$len_0 = length($ARGV[0]);
		$len_1 = length($ARGV[1]);
	}
}

&match_table($ARGV[0],$ARGV[1]);
&print_c;

sub match_table {
	local($a,$b);
	for($a=0;$a<$len_1;$a++){
		for($b=0;$b<$len_0;$b++){
			if(substr($_[1],$a,1) eq substr($_[0],$b,1)){
				$c{$a,$b} = 0;
			}else{
				$c{$a,$b} = 1;
			}
		}
	}
}

sub print_c {
	local($a,$b);
	for($a=0;$a<$len_1;$a++){
		for($b=0;$b<$len_0;$b++){
			print "$c{$a,$b}\t";
		}
		print "\n";
	}
}
