#!/usr/bin/perl
@mat = ();
@item = ();
while(<STDIN>){
	push(@mat,$_);
}
$dm = shift(@mat);
($col,$row) = split(' ',$dm);
@opt = @ARGV;
if(($ARGV[0] eq '-h')||($ARGV[0] eq '-help')){
	print "This is a wrapper of binary tf_idf.\n";
	print "First argument (\$ARGV[0]) must be sequence \"-II\" or \"-Ii\".\n";
	print "Other following options are transfered to tf_idf.\n";
	print "Try to type \"tf_idf -h\".\n";
}
if($ARGV[0] eq '-II'){
	$flag = $ARGV[0];
	for($i=0;$i<$col;$i++){
		$mat[$i] =~ s/([^\s]*\s)//;
		$item[$i] = $1;
	}
	shift(@opt);
	$opt = join(' ',@opt);
	@out = `echo \"@mat\" \| /home/pub/bin/tf_idf dm=$col,$row -v0 $opt`;
	for($i=0;$i<$col;$i++){
		print $item[$i];
		print $out[$i];
	}
}elsif($ARGV[0] eq '-Ii'){
	$flag = $ARGV[0];
	for($i=0;$i<$col;$i++){
		$mat[$i] =~ s/([^\s]*\s)//;
		#$item[$i] = $1;
	}
	shift(@opt);
	$opt = join(' ',@opt);
	system("echo \"@mat\" \| /home/pub/bin/tf_idf dm=$col,$row -v0 $opt");
}
#system("echo \"@mat\" \| /home/pub/bin/tf_idf dm=$col,$row -v0 $opt");
