#!/usr/bin/perl

print "<html>\n";
print "<head><title>$SRGV[0]</title></head>\n";
print "<body>\n";


while(<>){
	push(@arr,$_);
}
$al = join('',@arr);
@brr = split(/;;;\n/,$al);
$n = @brr;
#print "\n$n\n";
#print $brr[28];
#print "$al";
foreach(@brr){
	@ln = split(/;;\n/,$_);
	$src = $ln[0];
	$orglist = $ln[1];
	$reslist = $ln[2];
	#Orglist
	chomp($orglist);
	@orglist = split(/\n/,$orglist);
	foreach(@orglist){
		$_ =~ s/\t.*$//;
		push(@srtorglist,$_)
	}
	@srtorglist = sort @srtorglist;
	@uniqsrtorglist = &uniq(@srtorglist);
	#Reslist
	chomp($reslist);
	@reslist = split(/\n/,$reslist);
	foreach(@reslist){
		$_ =~ s/\t.*$//;
		push(@srtreslist,$_)
	}
	@srtreslist = sort @srtreslist;
	@uniqsrtreslist = &uniq(@srtreslist);
	#ins font col
	foreach(@uniqsrtorglist){
		$src =~ s/$_/<font color="red">$_<\/font>/g;
	}
	foreach(@uniqsrtreslist){
		$src =~ s/([ .,:;\-\^\(\[]$_[ .,:;\-\^\)\]])/<font color="blue">$1<\/font>/g;
	}
	print $src;
	print "\n<;;/>\n";
	print $orglist;
	print "\n<;;/>\n";
	print $reslist;
	print "\n<;;;/>\n";
}

print "</body>\n";
print "</html>\n";

sub uniq {
	my %seen;
	grep !$seen{$_}++, @_;
}

