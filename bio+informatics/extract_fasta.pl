#!/usr/bin/perl

while($line = <>){
 push(@tmp_data,$line);
}

$data = join('',@tmp_data);
@new_data = split(">",$data);
$len = @new_data;

foreach $i (@new_data) {
 $i =~ s/^/\>/;
 push(@out_data,$i);
}

foreach $i (@out_data) {
 $i =~ /(\|[A-Z0-9]+\n)/;
 $b = $1;
 $b =~ /([A-Z0-9]+)/;
 push(@name,$1);
}

for($i=0;$i<$len;$i++){
 open(OUT,"> $name[$i].nt");
 print(OUT "$out_data[$i]");
 close(OUT);
}

#print @out_data;
#print @name;
