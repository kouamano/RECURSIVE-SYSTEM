#!/bin/env perl
$file = $ARGV[0];
$head = "";
%rls = ();
@script = ();
@vals = ();
$copt = "";
while(<>){
	chomp;
	if($_ =~ /^\$ER\$/){
		$head = $_;
		$copt = '$-Cr';
	}elsif($_ =~ /^\$E\$/){
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
	$fedfile = $file.".dry.fed";
	$comfile = $file.".dry.fed.com";
	open(DATA,">",$comfile);
	print DATA "cat ".$fedfile." | "."math";
	close(DATA);
	# create metacomannd
	$meta = '$M$./tq.o ($-FW,'.$copt.')';
	print $meta;
	print "\n";
	print '$X$Get($`~/gitsrc/MATH_SCRIPT/SCRIPTS/DataFederation.m)';
	print "\n";
}elsif( "$rls{'$X$Application'}" eq '$X$Python' && "$rls{'$X$DDF'}" eq '$X$PackedData'){
	$fedfile = $file.".dry.fed";
	$comfile = $file.".dry.fed.com";
	$target = $rls{'$X$Target'};
	if(length($rls{'$X$FederationFile'}) > 0){
		$fedfile = $rls{'$X$FederationFile'};
	}
	$target =~ s/^\$`//;
	open(DATA,">",$comfile);
	print DATA "python"." $fedfile"," $target";
	close(DATA);
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
