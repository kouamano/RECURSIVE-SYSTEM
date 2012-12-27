#!/usr/bin/perl

while(<>){
	if($_ =~ /^;;;/){
	}elsif($_ =~ /\(DSKSETQ/){
	}elsif($_ =~ /\(ADD/){
	}elsif($_ =~ /\(in-package/){
	}else{
		push(@a,$_);
	}
}
$lines = @a;
for($i=0;$i<$lines;$i++){
	$a[$i] =~ s/\(MLIST\sSIMP\)//g;
	#print($a[$i]);
}
$b = join('',@a);
$b =~ s/\n*//g;
$b =~ s/\)[\s|\t]*\(/\n/g;
$b =~ s/\'//g;
@c = split('\n',$b);
$elm_c = @c;
for($i=0;$i<$elm_c;$i++){
	$c[$i] =~ s/[\(|\)]*//g;
	$c[$i] =~ s/^[\s|\t]*//;
	print("$c[$i]\n");
}
