#!/bin/env perl
$file = $ARGV[0];
#print $file;
$head = "";
%rls = ();
@script = ();
@vals = ();
while(<>){
        chomp;
        if($_ =~ /\$RE\$/){
                $head = $_;
        }elsif($_ =~ /\$E\$/){
                $head = $_;
        }elsif($_ =~ /\t->\t/){
                ($k,$v) = split(/\t->\t/,$_);
                $rls{$k} = $v;
        }else{
                push(@script,$_);
        }
}
$l = "";
while($l !~ /^\$M\$/){
	$l = shift(@script);
}
$comm = "echo '".$l."'"." | ./tq.o -C -FC in=/dev/stdin";
#print $comm;
$exe = `$comm`;
$exe =~ s/\s*$//;
#print $exe;

$script = join("\n",@script);
#$comm = "echo '".$script."'"." | ./tq.o in=/dev/stdin -Cr -FW";
#$comm = "echo '".$script."'"." | "."./tq.o -Cr -FW"." in=/dev/stdin";
$comm = "echo '".$script."'"." | ".$exe." in=/dev/stdin";
#print $comm;
$str = `$comm`;
#print $str;
$ofile = $file.".fed";
#print $ofile;

open(DATA,">",$ofile,O_EXECL);
print DATA $str;
close(DATA);

