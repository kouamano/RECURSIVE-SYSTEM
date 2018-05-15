#!/usr/bin/perl

print "{";
@arr = ();
while(<>){
	chomp;
	$_ =~ s/\s+/\",\"/g;
	$_ =~ s/ $//;
	$_ =~ s/^ //;
	push(@arr,"{\"$_\"}");
}
$out = join(",\n",@arr);
print $out;
print "}\n";
