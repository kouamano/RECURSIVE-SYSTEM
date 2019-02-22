#!/bin/env perl
$file = $ARGV[0];
$head = "";
%rls = ();
@script = ();
@vals = ();
while(<>){
	chomp;
	if($_ =~ /^\$RE\$/){
		$head = $_;
	}elsif($_ =~ /^\$E\$/){
		$head = $_;
	}elsif($_ =~ /^\$CM\$/){
		($meta,$app) = split(/\(/,$_);
		$app =~ s/\)$//;
		$metacomm{$meta} = $app;
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
if( "$metacomm{'$CM$Application'}" eq '$X$Mathematica' ){
	$fedfile = $file.".dry.fed";
	$comfile = $file.".dry.fed.com";
	open(DATA,">",$comfile);
	print DATA "cat ".$fedfile." | "."math";
	close(DATA);
	# create metacomannd
	print '$M$./tq.o($-FW,$-Cr)';
	print "\n";
	print '$X$Get($`~/gitsrc/MATH_SCRIPT/SCRIPTS/DataFederation.m)';
	print "\n";
}elsif( "$rls{'$CM$Application'}" eq '$X$Python' && "$rls{'$X$DDF'}" eq '$X$PackedData'){
	$fedfile = $file.".dry.fed";
	$comfile = $file.".dry.fed.com";
	$target = $rls{'$X$Target'};
	$target =~ s/^\$`//;
	open(DATA,">",$comfile);
	print DATA "python"." convert_jpeg_to_json.py"," $target";
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
