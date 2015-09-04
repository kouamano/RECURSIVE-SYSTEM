#!/usr/bin/perl

#use Parallel::ForkManager;


# vars
$help = 0;
$check = 0;
$status = 0;
$X = 1;
$ie = 0;
$be = 0;
$af = 0;
#$P = 1;

# subroutine
sub _help {
	print "USAGE:\n";
	print " 対象ファイルを1ラインとしてマッチ処理を行なう。\n";
	printf " extract_term_span_byline.pl sf=<source file> qf=<query file> span=<before>,<after> [-X|+X] \n";
	printf "  <query file> : escaped term list.\n";
	printf "  <before>,<after> : print before <before> terms, and after <after> terms.\n";
	printf "  [-X|+X] : knock out XML-tags; -X:on, +X:off.\n";
	#printf "  <par> threads for parallel.\n";
}

sub _check {
	print "ARGS:\n";
	print " help:$help:\n";
	print " check:$check:\n";
	print " status:$status:\n";
	print " sf:$sf:\n";
	print " qf:$qf:\n";
	print " be:$be:\n";
	print " af:$af:\n";
	print " X:$X:\n";
	print " P:$P:\n";
}

sub _status {
	print "STATUS:\n";
	printf " OK.\n"
}

# argment analysis
foreach $l (@ARGV) {
	if($l eq "-h"){
		$help = 1;
	}elsif($l eq "-c"){
		$check = 1;
	}elsif($l eq "-s"){
		$status = 1;
	}elsif($l =~ /sf=(.*)/){
		$sf = $1;
	}elsif($l =~ /qf=(.*)/){
		$qf = $1;
	}elsif($l =~ /span=([^,]*),([^,]*)/){
		$be = $1;
		$af = $2;
	}elsif($l =~ /P=(.*)/){
		$P = $1;
	}elsif($l =~ /col=(.*)/){
		$col = $1;
	}elsif($l =~ /^-XX$/){
		$X = 2;	#complete knock out XML-tags
	}elsif($l =~ /^-X$/){
		$X = 1;	#knock out XML-tags
	}elsif($l =~ /^\+X$/){
		$X = 0;	#print XML-tags
	}else{
		print "unknown:$l:\n";
	}
}

# main
if($help == 1){
	&_help;
	$ie = 1;
}
if($check == 1){
	&_check;
	$ie = 1;
}
if($status == 1){
	&_status;
	$ie = 1;
}
if($ie == 1){
	exit(0);
}

##store query (escaped)
open(IN,$qf);
while(<IN>){
	chomp;
	push(@qr,$_);
}
close(IN);


##store source
open(IN,$sf);
while(<IN>){
	push(@sr,$_);
}
close(IN);

##create term array (@tr)
$sr = join('',@sr);
$sr =~ s/\s+/ /g;
@tr = split(/ /,$sr);

##match
#my $pm = Parallel::ForkManager->new($P);
foreach(@qr){
	#$pm->start and next;
	$qterm = $_;
	#print "$qterm\n";
	#$lcount = 0;
	#foreach(@sr){
		#$sline = $_;
		#print "\t$sline\n";
		#if($X == 1){
		#	$sline =~ s/<[^<>]*?>/ /g;
		#	$sline =~ s/^\s+//;
		#	$sline =~ s/\s+$//;
		#	$sline =~ s/\s+/ /;
		#}
		#@tr = split(/\s/,$sline);
		$posterm = 0;
		foreach(@tr){
			if($_ =~ /$qterm/){
				print "$qterm"."\t[$posterm]\t";
				#print ":be:"."$be".":";
				for($i=0;$i<$be;$i++){
					#print "[$posterm-$be+$i]";
					$targetpos = $posterm-$be+$i;
					#print "::"."$targetpos"."::";
					if($targetpos >= 0){ print "$tr[$posterm-$be+$i] "; }
				}
				#print "[["."$posterm"." : "."$_"."]]";
				print "<|>"."$tr[$posterm]"."</|>";
				#print " :af:"."$af".":";
				for($i=0;$i<$af;$i++){
					#print "[$posterm+$i+1]";
					$targetpos = $posterm+$i+1;
					if($targetpos >= 0){ print " $tr[$posterm+$i+1]"; }
				}
				print "\n";
			}
			$posterm++;
		}
		#print "\n";
		#$lcount++;
	#}
	#$pm->finish;
}
#$pm->wait_all_children;

