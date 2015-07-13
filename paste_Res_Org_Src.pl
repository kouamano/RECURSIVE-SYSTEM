#!/usr/bin/perl
##ソースに対してResとOrgのposiotion情報を付加

$ResFile = $ARGV[0];
$OrgFile = $ARGV[1];
$SrcFile = $ARGV[2];

open(IN,$ResFile);
while(<IN>){
	chomp;
	push(@resarr,$_);
}
close(IN);

open(IN,$OrgFile);
while(<IN>){
	chomp;
	push(@orgarr,$_);
}
close(IN);

open(IN,$SrcFile);
$lcount=0;
while(<IN>){
	print $_;
	print ";;\n";
	#Org position
	foreach(@orgarr){
		if($_ =~ /L:$lcount$/){
			print "$_\n";
		}
	}
	print ";;\n";
	#Res
	foreach(@resarr){
		if($_ =~ /L:$lcount$/){
			print "$_\n";
		}
	}
	$lcount++;
	print ";;;\n";
}
close(IN);


