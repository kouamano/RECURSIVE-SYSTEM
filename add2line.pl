#!/user/bin/perl
$add = $ARGV[0];
$l = 0;
while(<STDIN>){
	$l = $add + $_;
	print $l;
}
