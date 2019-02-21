#!/bin/env perl
$file = $ARGV[0];
$head = "";
%rls = ();
@script = ();
@vals = ();
while(<>){
	chomp;
	if($_ =~ /\$RE\$/){
		$head = $_;
	}elsif($_ =~ /\$E\$/){
		$head = $_;
	}elsif($_ =~ /\t->\t/){
		($k,$v) = split(/\t->\t/,$_);
		$rls{$k} = $v;
	}else{
		push(@script,$_);
	}
}
# header
$stage = $head;
$stage =~ s/\(.*$//;
if($stage =~ /DRY/){
	$next = $stage;
	$next =~ s/DRY/FED/;
}
print "$next\n";

# for target application
if( "$rls{'$X$Application'}" eq '$X$Mathematica' ){
	$tfile = $file.".dry.fed";
	$ofile = $file.".dry.fed.com";
	open(DATA,">",$ofile);
	print DATA "cat ".$tfile." | "."math";
	close(DATA);
	# create metacomannd
	print '$M$./tq.o($-FW,$-Cr)';
	print "\n";
	print '$X$Get($`~/gitsrc/MATH_SCRIPT/SCRIPTS/DataFederation.m)';
	print "\n";
}

# application scripts
$head =~ s/[^(]+//;
$head =~ s/^\(//;
$head =~ s/\)$//;
@vals = split(/,/,$head);
foreach(@script){
	$line = $_;
	foreach(@vals){
		$pt = $_;
		$pt =~ s/\$/\\\$/g;
		$tgt = $rls{$_};
		$line =~ s/$pt/$tgt/g;
	}
	print "$line\n";
}
