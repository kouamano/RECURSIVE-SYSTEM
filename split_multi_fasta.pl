#!/usr/bin/perl

while(<>){
	push(@tmp_data,$_);
}

$data = join('',@tmp_data);
@new_data = split(">",$data);
$len = @new_data;

foreach $i (@new_data) {
	$i =~ s/^/\>/;
	push(@out_data,$i);
}

foreach $i (@out_data) {
	($h,$t) = split("\n",$i);
	$h =~ s/^>*//;
	$h =~ s/\|/-/g;
	$h =~ s/,/./g;
	$h =~ s/\s/_/g;
	push(@name,$h);
}

for($i=1;$i<$len;$i++){
	open(OUT,"> $name[$i].nt");
	print(OUT "$out_data[$i]");
	close(OUT);
}
