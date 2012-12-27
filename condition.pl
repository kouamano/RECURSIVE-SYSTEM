#!/usr/bin/perl

$n_first_file = 2;
$n_last_file = $#ARGV;
$condition = $ARGV[0];
$command = $ARGV[1];
$w_sep = "\n";
for($i=$n_first_file;$i<=$n_last_file;$i++){
	push(@file_list,($ARGV[$i]));
}
#print("$#ARGV\n");
#print("$ARGV[$#ARGV]\n");
#print("$ARGV[0]");
#print("$ARGV[1]");
#print("$ARGV[2]");
if($#ARGV == 0){
	#print("$ARGV[0]\n");
	if($ARGV[0] eq '-h'){
		&print_usage();
		&print_help();
	}elsif($ARGV[0] eq '-test'){
	}
}elsif($#ARGV >= 2){
	if($condition =~ /^\-lt/){
		$v = substr($condition,3);
		@size = &get_f_size(@file_list);
		for($i=0;$i<@size;$i++){
			if($size[$i] < $v){
				push(@out_file_list,$file_list[$i]);
			}
		}
	}elsif($condition =~ /^\-le/){
		$v = substr($condition,3);
		@size = &get_f_size(@file_list);
		for($i=0;$i<@size;$i++){
			if($size[$i] <= $v){
				push(@out_file_list,$file_list[$i]);
			}
		}
	}elsif($condition =~ /^\-gt/){
		$v = substr($condition,3);
		@size = &get_f_size(@file_list);
		for($i=0;$i<@size;$i++){
			if($size[$i] > $v){
				push(@out_file_list,$file_list[$i]);
			}
		}
	}elsif($condition =~ /^\-ge/){
		$v = substr($condition,3);
		@size = &get_f_size(@file_list);
		for($i=0;$i<@size;$i++){
			if($size[$i] >= $v){
				push(@out_file_list,$file_list[$i]);
			}
		}
	}elsif($condition =~ /^\-eq/){
		$v = substr($condition,3);
		@size = &get_f_size(@file_list);
		for($i=0;$i<@size;$i++){
			if($size[$i] == $v){
				push(@out_file_list,$file_list[$i]);
			}
		}
	}elsif($condition =~ /^\-oid/){
		$v = substr($condition,4);
		@owner = &get_f_own(@file_list);
		for($i=0;$i<@owner;$i++){
			if($owner[$i] == $v){
				push(@out_file_list,$file_list[$i]);
			}
		}
	}
	if($command eq 'print'){
		&print_f_list(@out_file_list);
		$num_list = @out_file_list;
		#print($num_list);
		if($num_list > 0){
			print("\n");
		}
	}elsif($command eq 'remove'){
		&apply_command("rm",@out_file_list);
	}elsif($command eq 'concat'){
		&apply_command("cat",@out_file_list);
	}else{
		&print_usage();
	}
}else{
	&print_usage();
}

## (* subroutines ##
sub print_usage{
	print("USAGE : \n");
	print("\tcondition.pl \"condition\" \"command\" [\"file\"]...\n");
	print("\tcondition.pl -h\n");
}

sub print_help{
	print("\"condition\" available : \n");
	print("\t{-lt|-le|-gt|-ge|-eq}\"size\"\n");
	print("\"cammand\" available : \n");
	print("\tprint\n");
	print("\tremove\n");
	print("\tconcat\n");
}

sub print_f_list{
	$n = @_;
	print($_[0]);
	for($i=1;$i<$n;$i++){
		print($w_sep,$_[$i]);
	}
}

sub get_f_size{
	$n = @_;
	for($i=0;$i<$n;$i++){
		$size = -s $_[$i];
		push(@f_size,$size);
	}
	return(@f_size);
}

sub get_f_own{
	$n = @_;
	for($i=0;$i<$n;$i++){
		push(@f_own,(stat($_[$i]))[4]);
	}
	return(@f_own);
}

sub apply_command{
	$n = @_;
	$command = $_[0];
	for($i=1;$i<$n;$i++){
		system("$_[0] '$_[$i]'");
	}
}
## subroutines *) ##
