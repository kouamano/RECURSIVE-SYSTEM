#!/usr/bin/perl
## extract_fasta_from_html ##

while(<STDIN>){
	push(@data,$_);
}
$data_str = join('',@data);
@data_new = split(/<\/html>/i,$data_str);
pop(@data_new);
$num_of_ele = @data_new;
#&plane_extract($data_new[0]);
#&plane_extract($data_new[1]);
#&gbfasta_extract($data_new[0]);
for($i=0;$i<$num_of_ele;$i++){
	if($data_new[$i] =~ /Entry/){
		&plane_extract($data_new[$i]);
	}else{
		&gbfasta_extract($data_new[$i]);
	}
}

# sub routines #
sub plane_extract {
	$a = $_[0];
	$a =~ s/\n//g;
	$a =~ s/\s//g;
	$gi = $a;
	$acc = $a;
	$seq = $a;
	$gi =~ /(\[gi:[^\]]+\])/;
	$gi = $1;
	$gi =~ s/^\[gi://;
	$gi =~ s/\]$//;
	print(">gi|$gi");
	$acc =~ /(Acc:[A-Z0-9]+)/;
	$acc = $1;
	$acc =~ s/^Acc://;
	$acc =~ s/[a-zA-Z]+$//;
	print("|gb|$acc");
	$seq =~ /(SEQUENCE.*)/;
	$seq = $1;
	$seq =~ s/^SEQUENCE<\/[bB]>//;
	$seq =~ s/Entry.*$//;
	print("\n$seq\n");
}

sub gbfasta_extract {
	$a = $_[0];
	$a =~ s/\n//g;
	#$a =~ s/\s//g;
	$gi = $a;
	$acc = $a;
	$seq = $a;
	$gi =~ /([Gg][Ii]:[A-Z]*[0-9]+)/;
	$gi = $1;
	$gi =~ s/\s//g;
	$gi =~ s/gi://i;
	print(">gi|$gi");
	$acc =~ /(ACCESSION\s+[A-Z]*[0-9]+)/;
	$acc = $1;
	$acc =~ s/\s//g;
	$acc =~ s/ACCESSION//;
	print("|gb|$acc");
	$seq =~ /(ORIGIN[^\/]*\/\/)/;
	$seq = $1;
	$seq =~ s/^ORIGIN//;
	$seq =~ s/\/\/$//;
	$seq =~ s/[0-9]//g;
	$seq =~ s/\s//g;
	print("\n$seq\n");
}
