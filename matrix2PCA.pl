#!/usr/bin/perl
@mat = ();
@title = ();
while(<STDIN>){
	push(@mat,$_);
}
$dm = shift(@mat);
($col,$row) = split(' ',$dm);
$tmp = $ARGV[0];
$flag = $ARGV[1];
if($flag eq '-Ii'){
	for($i=0;$i<$col;$i++){
		$mat[$i] =~ s/([^\s]*)//;
		#$title[$i] = $1;
	}
	print("$col $row\n");
	system("echo \"@mat\" \| /home/pub/bin/PCA $row $col $tmp");
}elsif($flag eq '-II'){
	for($i=0;$i<$col;$i++){
		$mat[$i] =~ s/([^\s]*)//;
		$title[$i] = $1;
	}
	print("$col $row\n");
	#system("echo \"@mat\" \| /home/pub/bin/PCA $row $col $tmp");
	@out = `echo \"@mat\" \| /home/pub/bin/PCA $row $col $tmp`;
	for($i=0;$i<$row;$i++){
		print "$title[$i] ";
		print $out[$i];
	}
}
