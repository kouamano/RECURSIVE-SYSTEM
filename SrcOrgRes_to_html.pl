#!/usr/bin/perl

print "<html>\n";
print "<head><title>$SRGV[0]</title></head>\n";
print "<body>\n";


while(<>){
	push(@arr,$_);
}
$al = join('',@arr);
@brr = split(/;;;\n/,$al);
$n = @brr;
#print "\n$n\n";
#print $brr[28];
#print "$al";
foreach(@brr){
	@ln = split(/;;\n/,$_);
	$src = $ln[0];
	@src = split(/\t/,$src);
	$src = pop(@src);
	$head = join('',@src);
	$orglist = $ln[1];
	$reslist = $ln[2];
	#Orglist
	chomp($orglist);
	@orglist = split(/\n/,$orglist);
	foreach(@orglist){
		$_ =~ s/\t.*$//;
		push(@srtorglist,$_)
	}
	@srtorglist = sort @srtorglist;
	@uniqsrtorglist = &uniq(@srtorglist);
	@escuniqsrtorglist = &escape(@uniqsrtorglist);
	#Reslist
	chomp($reslist);
	@reslist = split(/\n/,$reslist);
	foreach(@reslist){
		$_ =~ s/\t.*$//;
		push(@srtreslist,$_)
	}
	@srtreslist = sort @srtreslist;
	@uniqsrtreslist = &uniq(@srtreslist);
	@escuniqsrtreslist = &escape(@uniqsrtreslist);
	#ins font col
	foreach(@escuniqsrtorglist){
		$src =~ s/$_/<font color="red">$_<\/font>/g;
	}
	foreach(@escuniqsrtreslist){
		#$src =~ s/([ .,:;\-\^\(\[]$_[ .,:;\-\^\)\]])/<font color="blue">$1<\/font>/g;
		$src =~ s/([ \.,:;\/\?\-\^\(\[>])($_)([ \.,:;\/\?\-\^\)\]<])/$1<font color="blue">$2<\/font>$3/g;
		#$src =~ s/([^0-9a0zA-Z])($_)([0-9a-zA-Z])/$1<font color="blue">$2<\/font>$3/g;
	}
	print "<br> $head <br>";
	print $src;
	print "\n<;;/>\n";
	print $orglist;
	print "\n<;;/>\n";
	print $reslist;
	print "\n<;;;/>\n";
}

print "</body>\n";
print "</html>\n";

sub uniq {
	my %seen;
	grep !$seen{$_}++, @_;
}

sub escape {
        my @all = ();
        my @out = ();
        my @sp = ();
        my $out = "";
        foreach(@_){
                @out = ();
                @sp = split(//,$_);
                foreach(@sp){
                        if($_ eq '\\'){
                                push(@out,"\\\\");
                        }elsif($_ eq '*'){
                                push(@out,"\\\*");
                        }elsif($_ eq '+'){
                                push(@out,"\\\+");
                        }elsif($_ eq '.'){
                                push(@out,"\\\.");
                        }elsif($_ eq '?'){
                                push(@out,"\\\?");
                        }elsif($_ eq '{'){
                                push(@out,"\\\{");
                        }elsif($_ eq '}'){
                                push(@out,"\\\}");
                        }elsif($_ eq '('){
                                push(@out,"\\\(");
                        }elsif($_ eq ')'){
                                push(@out,"\\\)");
                        }elsif($_ eq '['){
                                push(@out,"\\\[");
                        }elsif($_ eq ']'){
                                push(@out,"\\\]");
                        }elsif($_ eq '^'){
                                push(@out,"\\\^");
                        }elsif($_ eq '$'){
                                push(@out,"\\\$");
                        }elsif($_ eq '|'){
                                push(@out,"\\\|");
                        }elsif($_ eq '/'){
                                push(@out,"\\\/");
                        }else{
                                push(@out,"$_");
                        }
                }
                $out = join("",@out);
                push(@all,$out);
        }
        return @all;
}
