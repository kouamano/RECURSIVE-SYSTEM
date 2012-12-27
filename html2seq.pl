#!/usr/bin/perl
$in_html = 0;
$in_pre = 0;
$in_seq =0;
while(<>){
	if ($_ =~ /<html>/i) {
		$in_html++;
	}
	if ($_ =~ /<\/html>/i) {
		$in_html--;
	}
	if ($_ =~ s/<pre>//i) {
		$in_pre++;
	}
	if ($_ =~ /<\/pre>/i) {
		$in_pre--;
	}
	if ($_ =~ /LOCUS\s+/) {
		$in_seq++;
	}
	if ($_ =~ /^\/\/$/) {
		$in_seq--;
		print "//\n";
	}
	#print "$in_html:$in_pre:$in_seq";
	if(($in_seq > 0)&&($in_seq == $in_pre)&&($in_pre == $in_html)){
		print $_;
	}
}
