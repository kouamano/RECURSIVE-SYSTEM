#!/bin/env perl
$file = $ARGV[0];
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

# meta command operation
$l = "";
$ct = 0;
$ctmax = @script;
while($l !~ /^\$M\$/ && $ct <= $ctmax){
	$l = shift(@script);
	$ct++;
}
if(length($l) > 0){
	$comm = "echo '".$l."'"." | ./tconv -C -FC in=/dev/stdin";
	$exe = `$comm`;
	$exe =~ s/\s*$//;
	$script = join("\n",@script);
	$comm = "echo '".$script."'"." | ".$exe." in=/dev/stdin";
	$str = `$comm`;
	$ofile = $file.".fed";
}else{	# no metacomannd
	$str = join("\n",@script);
	$ofile = $file.".fed";
}

# output
open(DATA,">",$ofile);
print DATA $str;
close(DATA);

