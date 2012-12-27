#!/usr/bin/perl

while(<>){
	if($_ =~ /^%.+/){
		;
	}elsif($_ =~ s/.*\\uline{//){
		$_ =~ s/\}.*$//;
		push(@a,$_);
	}elsif($_ =~ /\s*\\item\[.+\]/){
		$_ =~ s/\s*\\item/\t/g;
		push(@a,$_);
	}elsif($_ =~ s/\s*\\item/\t¡¦/g){
		push(@a,$_);
	}elsif($_ =~ s/\\font.*\{.*\}.*selectfont//g){
		push(@a,$_);
	}elsif($_ =~ s/^\\[^\{]+//){
		;
	}else{
		push(@a,$_);
	}
}

foreach $l (@a) {
	$l =~ s/\\vspace\{[^\}]*\}//g;
	$l =~ s/\\normalfont\{\}//g;
}

print(@a);
