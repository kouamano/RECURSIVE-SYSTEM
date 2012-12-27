#!/usr/bin/perl

sub drop_head {
	local(@a,$num_a,$i,@ret);
	@a = @_;
	$num_a = @a;
	for($i=0;$i<=$num_a;$i++){
		if($a[$i] =~ s/^\s+[0-9]+\s//){
			push(@ret,$a[$i]);
		}
	}
	return(@ret);
}

sub drop_tail {
	local(@a,$num_a,$i,@ret);
	@a = @_;
	$num_a = @a;
	for($i=0;$i<=$num_a;$i++){
		if($a[$i] =~ s/\s+<[aA]//){
			push(@ret,$a[$i]);
		}
	}
	return(@ret);
}

sub print_plus {
	local(@a,$num_a,$i,@ret);
	@a = @_;
	$num_a = @a;
	for($i=0;$i<=$num_a;$i++){
		if($a[$i] =~ s/\(\+\)\s//){
			print("$a[$i]\n");
			push(@ret,$a[$i]);
		}
	}
}

sub print_minus {
	local(@a,$num_a,$i,@ret);
	@a = @_;
	$num_a = @a;
	for($i=0;$i<=$num_a;$i++){
		if($a[$i] =~ s/\(\-\)\s//){
			print("$a[$i]\n");
			push(@ret,$a[$i]);
		}
	}
}

sub print_all {
	local(@a,$num_a,$i,@ret);
	@a = @_;
	$num_a = @a;
	for($i=0;$i<=$num_a;$i++){
		if($a[$i] =~ s/\([\+|\-]\)\s//){
			print("$a[$i]\n");
			push(@ret,$a[$i]);
		}
	}
}

## start main routine ##
while(<>){
	push(@a,$_);
	$input = join('',@a);
}

@b = split('site',$input);
$num_b = @b;
for($i=1;$i<$num_b-1;$i++){
	if($b[$i] =~ /(.+\<[aA])/){
		push(@c,$1)
	}
}

@d = &drop_head(@c);
@e = &drop_tail(@d);
#&print_plus(@e);
#&plint_minus(@e);
if($0 =~ /extract_motif_from_PLACE_all.pl/){
	&print_all(@e);
}elsif($0 =~ /extract_motif_from_PLACE_plus.pl/){
	&print_plus(@e);
}elsif($0 =~ /extract_motif_from_PLACE_minus.pl/){
	&print_minus(@e);
}
## end main routine ##
