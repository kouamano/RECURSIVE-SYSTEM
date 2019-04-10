#!/usr/bin/perl
@arr = ();
while(<>){
	chomp;
	push(@arr,$_);
}
$arr = join("",@arr);
@arr = split("==========",$arr);
foreach (@arr) {
	$_ =~ s/^.*?#T //;
	$_ =~ s/=*$//;
	$_ =~ s/^\s+//;
	$_ =~ s/\s+$//;
	#print "$_\n";
	@pair = split("#S ",$_);
	$cnt = @pair;
	#print $cnt
	if($cnt == 2){
		print "echo \'$pair[0]\' | /home/kamano/gitsrc/DimensionDefinitionLanguage/t\n";
		print "echo \'$pair[1]\' | /home/kamano/gitsrc/DimensionDefinitionLanguage/s\n";
		print "echo \'$pair[1]\'\n";
		print "echo \'$pair[0]\'\n";
		print "echo \'$pair[1]\' | /home/kamano/gitsrc/DimensionDefinitionLanguage/cst in=/dev/stdin\n";
		print "diff \<(echo \'$pair[0]\') \<(echo \'$pair[1]\' | /home/kamano/gitsrc/DimensionDefinitionLanguage/cst in=/dev/stdin)\n";
		print "echo \n";
	}
}
