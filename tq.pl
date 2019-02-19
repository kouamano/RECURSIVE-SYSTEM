#!/bin/env perl
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
$conv = $head;
$conv =~ s/\(.*$//;
$conv =~ s/DRY/FED/;
print "$conv";

# for target application
if( "$rls{'$X$Application'}" eq '$X$Mathematica' ){
	print '($`-FW,$`-Cr)';
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
