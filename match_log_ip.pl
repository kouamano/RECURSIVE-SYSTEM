#!/usr/bin/perl

$userFile = $ARGV[0];
$logFile = $ARGV[1];

open(IN,$userFile);
%ip = ();
@tmp = ();
while(<IN>){
	chomp;
	@tmp = split(/\t/,$_);
	#print ";;;$tmp[2];;;\n";
	if($tmp[2] ne ""){
		$ip{$tmp[2]} = "$tmp[0]\t$tmp[1]\t$tmp[2]";
	}
}
close(IN);

#print $ip{"144.213.167.32"};
#print "\n";
#print $ip{"144.213.73.31"};
#print "\n";

@tmp = ();
open(IN,$logFile);
while(<IN>){
	chomp;
	$_=~ s/ +/ /g;
	@tmp = split(/ /,$_);
	print "$_";
	print "\t<==\t";
	print "$ip{$tmp[2]}";
	print "\n";
}
close(IN);
