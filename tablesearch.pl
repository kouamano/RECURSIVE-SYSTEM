#!/usr/bin/perl

$IFS = ' ';		#default field separator of input file.
$OFS = ' ';		#default field separator of output file.
$CHECK = 0;		#0 : normal execution. or 1 : print argments & exit.
$SEARCH_TYPE = '-r';	#'-r' : regular exp. or '-c' : full coincidence.
$SEARCH_FIELD;
$SEARCH_TERM;
$INPUT_FILE = '/dev/stdin';
$OUTPUT_FILE = '/dev/stdout';
$INPUT_DATA_FORM = 'd';	#'t' : with title or 'd' : data only.
$idf = 0;
$OUTPUT_DATA_FORM = 'd';#'t' : with title, 'd' : data only or 'p' : position.
$odf = 0;
$OUTPUT_FIELDS = '-a';	#'-a' : all fileds or '-m' : only matched field.

## ---- argument analysis and search ---- ##
if($#ARGV == -1){
	print("type \"ssvsearch.pl -h\"\n");
	exit();
}elsif($ARGV[0] eq '-h'){
	&print_usage();
	exit();
}

&set_args(@ARGV);
if($CHECK == 1){
	&print_args();
	exit();
}else{
	## ---- search process ---- ##
	@fields = &split_multiple(',',$SEARCH_FIELD);
	$num_fields = @fields;
	@terms = &split_multiple(',',$SEARCH_TERM);
	$num_terms = @terms;
	@n_elm_array;
	$n_line;
	@IDF = &split_multiple(',',$INPUT_DATA_FORM);
	foreach $x (@IDF) {
		if($x eq 't'){
			$idf = $idf + 1;
		}
		if($x eq 'd'){
			$idf = $idf + 2;
		}
		if($x eq 'p'){
			$idf = $idf + 4;
		}
	}
	@ODF = &split_multiple(',',$OUTPUT_DATA_FORM);
	foreach $x (@ODF) {
		if($x eq 't'){
			$odf = $odf + 1;
		}
		if($x eq 'd'){
			$odf = $odf + 2
		}
		if($x eq 'p'){
			$odf = $odf + 4;
		}
	}
	#%data_array = &make_data_array_from_file($idf,$INPUT_FILE);
	%data_array = &make_data_array_from_file($INPUT_FILE);
	if(($SEARCH_TYPE eq '-c')&&($SEARCH_FIELD eq '')&&($OUTPUT_FIELDS eq '-m')){
		for($i=0+($idf&1);$i<$n_line;$i++){
			for($j=0;$j<$n_elm_array[$i];$j++){
				foreach $x (@terms){
					if($data_array{$i,$j} eq $x){
						if(($odf&4) == 4){
							print("[$i,$j] ");
						}
						if(($odf&2) == 2){
							print("$data_array{$i,$j}");
						}
						print("\n");
					}
				}
			}
		}
	}elsif(($SEARCH_TYPE eq '-c')&&($SEARCH_FIELD ne '')&&($OUTPUT_FIELDS eq '-m')){
		for($i=0+($idf&1);$i<$n_line;$i++){
			for($j=0;$j<$num_fields;$j++){
				foreach $x (@terms) {
					if($data_array{$i,$fields[$j]} eq $x){
						if(($odf&4) == 4){
							print("[$i,$fields[$j]] ");
						}
						if(($odf&2) == 2){
							print("$data_array{$i,$fields[$j]}");
						}
						print("\n");
					}
				}
			}
		}
	}elsif(($SEARCH_TYPE eq '-r')&&($SEARCH_FIELD eq '')&&($OUTPUT_FIELDS eq '-m')){
		for($i=0+($idf&1);$i<$n_line;$i++){
			for($j=0;$j<$n_elm_array[$i];$j++){
				foreach $x (@terms){
					if($data_array{$i,$j} =~ /$x/){
						if(($odf&4) == 4){
							print("[$i,$j] ");
						}
						if(($odf&2) == 2){
							print("$data_array{$i,$j}");
						}
						printf("\n");
					}
				}
			}
		}
	}elsif(($SEARCH_TYPE eq '-r')&&($SEARCH_FIELD ne '')&&($OUTPUT_FIELDS eq '-m')){
		for($i=0+($idf&1);$i<$n_line;$i++){
			for($j=0;$j<$num_fields;$j++){
				foreach $x (@terms) {
					if($data_array{$i,$fields[$j]} =~ /$x/){
						if(($odf&4) == 4){
							print("[$i,$fields[$j]] ");
						}
						if(($odf&2) == 2){
							print("$data_array{$i,$fields[$j]}");
						}
						print("\n");
					}
				}
			}
		}
	}elsif(($SEARCH_TYPE eq '-c')&&($SEARCH_FIELD eq '')&&($OUTPUT_FIELDS eq '-a')){
		for($i=0+($idf&1);$i<$n_line;$i++){
			for($j=0;$j<$n_elm_array[$i];$j++){
				foreach $x (@terms){
					if($data_array{$i,$j} eq $x){
						if(($odf&4) == 4){
							print("[$i] ");
						}
						print("$data_array{$i,0}");
						for($k=1;$k<$n_elm_array[$i];$k++){
							print("$OFS$data_array{$i,$k}");
						}
						print("\n");
					}
				}
			}
		}
	}elsif(($SEARCH_TYPE eq '-c')&&($SEARCH_FIELD ne '')&&($OUTPUT_FIELDS eq '-a')){
		for($i=0+($idf&1);$i<$n_line;$i++){
			for($j=0;$j<$num_fields;$j++){
				foreach $x (@terms) {
					if($data_array{$i,$fields[$j]} eq $x){
						if(($odf&4) == 4){
							print("[$i] ");
						}
						print("$data_array{$i,0}");
						for($k=1;$k<$n_elm_array[$i];$k++){
							print("$OFS$data_array{$i,$k}");
						}
						print("\n");
					}
				}
			}
		}
	}elsif(($SEARCH_TYPE eq '-r')&&($SEARCH_FIELD eq '')&&($OUTPUT_FIELDS eq '-a')){
		for($i=0+($idf&1);$i<$n_line;$i++){
			for($j=0;$j<$n_elm_array[$i];$j++){
				foreach $x (@terms){
					if($data_array{$i,$j} =~ /$x/){
						if(($odf&4) == 4){
							print("[$i] ");
						}
						print("$data_array{$i,0}");
						for($k=1;$k<$n_elm_array[$i];$k++){
							print("$OFS$data_array{$i,$k}");
						}
						print("\n");
					}
				}
			}
		}
	}elsif(($SEARCH_TYPE eq '-r')&&($SEARCH_FIELD ne '')&&($OUTPUT_FIELDS eq '-a')){
		for($i=0+($idf&1);$i<$n_line;$i++){
			for($j=0;$j<$num_fields;$j++){
				foreach $x (@terms) {
					if($data_array{$i,$fields[$j]} =~ /$x/){
						if(($odf&4) == 4){
							print("[$i] ");
						}
						print("$data_array{$i,0}");
						for($k=1;$k<$n_elm_array[$i];$k++){
							print("$OFS$data_array{$i,$k}");
						}
						print("\n");
					}
				}
			}
		}
	}
	## ----/search process ---- ##
}
## ----/argument analysis and search ---- ##

## ---- subroutines ---- ##
sub print_usage{
	print("ssvsearch usage :: \n");
	print("ssvsearch.pl -h\n\tprint this message.\n");
	print("ssvsearch.pl [--check] [-c|-r] [ifs=\"separator\"] [k=\"field No.\"] t=\"search term\" [if=\"input file\"] [idf=\"input data form\"] [of=\"output file\"] [odf=\"output data form\"] [-a|-m]\n\tsearch the term(s) from the file.\n");
	print("options \n");
	print("\t--check : print argments.\n");
	print("\t-c|-r : full coincidence (-c) or regular expression (-r).\n");
	print("\tifs=\"input field separator\" : separator used in inputfile.\n");
	print("\tk=\"field1,field2,...\" : search field.\n");
	print("\tt=\"term1,term2,...\" : search term.\n");
	print("\tif=\"input file name\" : input file, /dev/stdin as default.\n");
	print("\tof=\"output file name\" : output file, /dev/stdout as default.\n");
	print("\todf=\"output data form\" : data table (d),  position (p).\n");
	print("\t-a|-m : printout whole line (-a) or matched field only (-m).\n");
}

sub split_multiple{
	$n = @_;
	$sep = $_[0];
	@out = split($sep,$_[1]);
	return(@out);
}

sub make_data_array_from_file{
	%a = NULL;
	$n = @_;
	$i = 0;
	if($n != 1){
		print("internal data fromat error at 'make_data_array_from_file\(\)' -- exit.\n");
		exit();
	}
	open(IN,$_[0]);
	$i = 0;
	while(<IN>){
		#$_ =~ s/$IFS+/$IFS/g;
		#$_ =~ s/\s+/ /g;
		chomp($_);
		@tmp = &split_multiple($IFS,$_);
		$j = 0;
		foreach $x (@tmp) {
			$a{$i,$j} = $x;
			$j++;
		}
		push(@n_elm_array,$j);
		$i++;
	}
	$n_line = $i;
	close(IN);
	return(%a);
}

sub set_args{
	$n_args = @_;
	$r = $n_args;
	while($r > 0){
		for($i=0;$i<$n_args;$i++){
			if($_[$i] eq '--check'){
				$CHECK = 1;
			}elsif(($_[$i] eq '-c')||($_[$i] eq '-r')){
				$SEARCH_TYPE = $_[$i];
				$r--;
			}elsif($_[$i] =~ /^ifs=/){
				if(length($_[$i]) < 5){
					printf("please set ifs (input field separator).\n");
					exit();
				}
				$IFS = substr($_[$i],4);
				$r--;
			}elsif($_[$i] =~ /^ofs=/){
				if(length($_[$i]) < 5){
					printf("please set ifs (input field separator).\n");
					exit();
				}
				$OFS = substr($_[$i],4);
				$r--;
			}elsif($_[$i] =~ /^k=/){
				if(length($_[$i]) < 3){
					printf("please set k (search field).\n");
					exit();
				}
				$SEARCH_FIELD = substr($_[$i],2);
				$r--;
			}elsif($_[$i] =~ /^t=/){
				if(length($_[$i]) < 3){
					printf("please set t (search term).\n");
					exit();
				}
				$SEARCH_TERM = substr($_[$i],2);
				$r--;
			}elsif($_[$i] =~ /^if=/){
				if(length($_[$i]) < 4){
					printf("please set if (input file).\n");
					exit();
				}
				$INPUT_FILE = substr($_[$i],3);
				$r--;
			}elsif($_[$i] =~ /^of=/){
				if(length($_[$i]) < 4){
					printf("please set of (output file).\n");
					exit();
				}
				$OUTPUT_FILE = substr($_[$i],3);
				$r--;
			}elsif($_[$i] =~ /^idf=/){
				if(length($_[$i]) < 5){
					printf("please set idf (input data form).\n");
					exit();
				}
				$INPUT_DATA_FORM = substr($_[$i],4);
				$r--;
			}elsif($_[$i] =~ /^odf=/){
				if(length($_[$i]) < 5){
					printf("please set odf (output data form).\n");
					exit();
				}
				$OUTPUT_DATA_FORM = substr($_[$i],4);
				$r--;
			}elsif(($_[$i] eq '-a')||($_[$i] eq '-m')){
				$OUTPUT_FIELDS = $_[$i];
				$r--;
			}else{
				print("unknown argment : $_[$i]  -- exit.\n");
				exit();
			}
		}
	}
}

sub print_args{
	print("CHECK = $CHECK\n");
	print("IFS = '$IFS'\n");
	print("SEARCH_TYPE = $SEARCH_TYPE\n");
	print("SEARCH_FIELD = $SEARCH_FIELD\n");
	print("SEARCH_TERM = $SEARCH_TERM\n");
	print("INPUT_FILE = $INPUT_FILE\n");
	print("OUTPUT_FILE = $OUTPUT_FILE\n");
	print("INPUT_DATA_FORM = $INPUT_DATA_FORM\n");
	print("OUTPUT_DATA_FORM = $OUTPUT_DATA_FORM\n");
	print("OUTPUT_FIELDS = $OUTPUT_FIELDS\n");
}
## ----/subroutines ---- ##
