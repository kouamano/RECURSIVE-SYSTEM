#!/usr/bin/perl
use List::Util qw(max);

%count = ();
$cl = 1;
$ct = 1;
@cc = ();
while(<>){
	chomp;
	@tmp_arr = split("\t",$_);
	$ct = 1;
	foreach(@tmp_arr){
		if($_ == 0){
			;
		}else{
			$count->{$cl}->{$ct} = $_;
		}
		$ct++;
	}
	$cc[$cl] = @tmp_arr;
	$cl++;
}
$max_col = max(@cc);
$ol = 0;
$cl = $cl - 1;
@out = ();
for $mainKey ( keys %{$count} ){
	for $subKey ( keys %{$count->{$mainKey}} ){
		#print "$mainKey\t$subKey\t$count->{$mainKey}->{$subKey}\n";
		push(@out,"$mainKey\t$subKey\t$count->{$mainKey}->{$subKey}\n");
		$ol++;
	}
}
print "$cl\t$max_col\t$ol\n";
print @out;
