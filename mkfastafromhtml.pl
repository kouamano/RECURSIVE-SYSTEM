#!/usr/bin/perl
# mkfastafromhtml.pl #
@version = ();
while(<>){
	push(@data,$_);
}
$data_str = join('',@data);
@data = split('LOCUS',$data_str);
shift(@data);
$elm = @data;
for($i=0;$i<$elm;$i++){
	if($data[$i] =~ /VERSION.*\n/){
		print "PK";
		print $1;
		$version[$i] = $1;
	}
}
print $version[0];
print $elm;
