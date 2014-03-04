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
print "SparseArray[{";
for $mainKey ( keys %{$count} ){
	for $subKey ( keys %{$count->{$mainKey}} ){
		if($ol == 0){
			;
		}else{
			print ",\n";
		}
		print "{$mainKey,$subKey}"." -> "."$count->{$mainKey}->{$subKey}";
		$ol++;
	}
}
print "}\n";
$cl = $cl - 1;
print ",{$cl,$max_col}]\n";
