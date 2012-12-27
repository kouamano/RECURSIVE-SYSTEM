#!/usr/bin/perl

while(<>){
	push(@a,$_);
}
$num_a = @a;
print("[");
chomp($a[0]);
$a[$0] =~ s/[a-zA_Z]+/\"$&\"/g;
$a[$i] =~ s/\s+/,/g;
$j = $a[$0];
$j = "[$j]";
push(@b,$j);
for($i=1;$i<$num_a;$i++){
	chomp($a[$i]);
	$a[$i] =~ s/([a-zA-Z]*[0-9]*[a-zA_Z]+|[a-zA-Z]+[0-9]*[a-zA_Z]*)/\"$&\"/g;
	$a[$i] =~ s/\s+/,/g;
	$j = $a[$i];
	$j = ",[$j]";
	push(@b,$j);
}
print(@b);
print("];\n");
