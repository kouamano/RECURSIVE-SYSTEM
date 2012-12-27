#!/usr/bin/perl

$sep=$ARGV[0];
shift(@ARGV);

foreach $file (@ARGV) {
        open(IN,$file);
        while(<IN>){
                chomp;
                @arr = split($sep,$_);
		$len = @arr;
		for($i=$len;$i>=0;$i--){
			print $arr[$i];
			print $sep;
		}
		print "\n";
        }
        close(IN)
}
