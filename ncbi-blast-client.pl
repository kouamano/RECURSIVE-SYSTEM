#!/usr/bin/perl

use POSIX;
use Socket;
use Getopt::Std;

my ($host, $port, $addr, $proto, $ent);

## set variables ##
$port = 80;
$var = 'HTTP/1.0';
$argc = $#ARGV;
$socket = 'SOCKE';
$in = $socket;
$out = $socket;
$n = 0;			## argument index
$e = 0;			## argument index
$f = 0;			## argument index
$case = 0;		## for "no-test" mode
$prog = 'blastn';
$data_lib = 'nr';
$expect = '0.001';
$agent = "\nUser-Agent: http/blast-client";
$type = "\nContent-type: application/x-www-form-urlencoded";
$blast_meth = "PROGRAM $prog\nDATALIB $data_lib\nEXPECTATION $expect\n\nBEGIN\n";
$data = '';
## end set variables ##

## test arguments for input file ##
if($ARGV[0] eq '-i'){
 $file = $ARGV[1];
 $n = $n+2;
 $e = $e+2;
 open(IN,$file);
 while(<IN>){
  push(@tmp_data,$_);
 }
 close(IN);
 $data = join('',@tmp_data);
 chomp($data);
}
## end test arguments for input file ##

## test argument for data_lib ##
if($ARGV[-2] eq '-db'){
 $data_lib = $ARGV[-1];
 $f = $f+2;
 $blast_meth = "PROGRAM $prog\nDATALIB $data_lib\n\nBEGIN\n";
}
## end test argument for data_lib ##

## test arguments for output&connection ##
if($ARGV[$e] eq '-t'){
 $out = 'STDOUT';
 $in = '/dev/null';
 $n = $n+1;
 $case = 1;
}elsif($ARGV[$e] eq '-k'){
 $connection = "\nConnection: Keep-Alive";
 $n = $n+1;
}elsif(($ARGV[$e] eq '-tk') || ($ARGV[$e] eq '-kt')){
 $connection = "\nConnection: Keep-Alive";
 $out = 'STDOUT';
 $in = '/dev/null';
 $n = $n+1;
 $case = 1;
}elsif($ARGV[$e] =~ /^-.+/){
 print "options : -k -t\n";
 exit;
}
## end test arguments for output&connection ##

## test arguments for URL ##
if($argc == 0+$n+$f){
 $meth = "GET";
 $argument = "$ARGV[0+$n]";
}elsif($argc == 1+$n+$f){
 $meth = "$ARGV[0+$n]";
 $argument = "$ARGV[1+$n]";
}else{
 print "argument(s) : 1 or more\n";
 exit;
}
## end test arguments for URL ##

## process hostname ##
@url = split('/',$argument);
if($url[0] !~ /http:/i){
 print "URL : start at http:\n";
 exit;
}
$url_tmp = $url[2];
if($url_tmp =~ /:/){
 @host_tmp = split(':',$url_tmp);
 $host = $host_tmp[0];
 $port = $host_tmp[1];
}else{
 $host = $url_tmp;
}
## end process hostname ##

## process query ##
if($meth =~ /post/i){
 $end = $url[-1];
 ($argument,$tail) = split('\?',$argument);
 @host_query_end = split('\?',$end);
 $end_end = $host_query_end[1];
 $end_end =~ tr/\\n/\n/;
 $data = join('',$data,$end_end);
 $data = join('',$blast_meth,$data,"\n");
 $data_length = length($data);
 $switch_data = "\nContent-Length: $data_length\n\n$data";
}elsif($meth =~ /get/i){
 $switch_data = "\n\n";
}
## end process query ##

## process socket ##
if($case == 0){
 @n = gethostbyname($host);
 $addr = $n[4];
 $proto = getprotobyname('tcp');
 socket($socket, PF_INET, SOCK_STREAM, $proto);
 $ent = pack('S n a4 x8', AF_INET, $port, $addr);
}
## end process socket ##

## put query ##
if($case == 0){
 connect($socket, $ent);
}
select($out);
print "$meth";
print " ";
print "$argument";
print " ";
print "$var";
print "$agent";
print "$connection";
print "$type";
print "$switch_data";
$| = 1;
## end put query ##

## output ##
select(STDOUT);
while($line = <$in>){
 print "$line";
 if($line =~ /<\/html>/i){
  last;
 }
}
## end output ##

## process socket(close) ##
close($socket);
## end process socket(close) ##

exit;
