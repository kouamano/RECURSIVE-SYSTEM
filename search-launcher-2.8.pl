#!/usr/bin/perl
# ^^^^^^^^^^^^^
# change this line to set where you have perl installed 
#
#
# search-launcher-2.8 Submit sequences to search-launcher WWW-server.
#
# Copyright (C) 1995 Baylor College of Medicine
#
# All rights reserved.
#
# Contact sl-help@bcm.tmc.edu
#
#
# The following script is a batch interface to the WWW page
# http://searchlauncher.bcm.tmc.edu/
# It will submit sequence files for searching and save the output into files.
# If given just '-h' option for a Unix system, or if no files are dropped
# on it for a Mac, this script will printout a help message.
# Please look at this help message for further information.
#
# This script requires a functioning network connection to the internet.
# On a Unix system a perl interpreter is also required.  On a Mac a runtime
# version of this script or MacPerl is required.  The latest version of
# this program is available via ftp from searchlauncher.bcm.tmc.edu
# in the pub/software/search-launcher directory (URL
# ftp://searchlauncher.bcm.tmc.edu/pub/software/search-launcher).
#
# 2 Jul 2001 Mike McLeod (ver 2.8)
# minor changes so that the batch client will work with the new server.
# (port changes, name changes, etc.) no new features added.
#
# 11/17/99 Zhenwu Yang (ver 2.7)
# ******   Important !!!    ******
# Every time you update the search launcher batch client and CHANGE its VERSION number,
# You MUST change the server CONFiguration. The reason is that batch client is not
# a standard browser (guess??). The server must be configured to accept batch client's request.
# For instance: the version number is changed from 2.5 to 2.7
# Find file "httpd.conf"
# Add:  BrowserMatch "search-launcher/2\.7" force-response-1.0  in the BrowserMatch directive
# Then stop the server and restart it. It's ready to take requests from your new batch client.
#
# 10/27/99 Zhenwu Yang
# Our Batch Client users, especially the users under DOS complained about that
# the instruction for selecting the number or the name of the tool is printed out
# too fast and they can not go back to look at it.
# Therefore this program is modified for both Unix and DOS version to print the instruction 
# screen by screen.

# 11/17/95
# Added support for IRIX systems which are much like solaris as far as
# socket parameters are concerned.  Should really consider using the
# sys/socket.ph file if available (wrap in an eval).  Then adding a
# system specific entry would be optional because one could just run
# h2ph on sys/socket.h to get it to work.
#
# 9/25/95
# Added code to deal with any of the various line termination methods
# (CRLF, LF, or CR) on input and always output lines that end in "\n"
# (which on a Mac is a CR and on UN*X is LF).  Also added do_warn to
# warn if a read timed out, and split limit of 2 when splitting off
# query string (post input).  Forced 'Date:' match to be at beginning
# of line till end of line, as it should be; also started adding trailing
# newline to headers (removed by split(/\n\n/, ...).  Also modified
# proxy request slightly, now using 'http://host:port' instead of
# '/http://host:port' per httpd protocol specs.

# 9/22/95
# Added option to set debug value and to not fork.

# 9/14/95
# Modified for proxy support.  Additionally, the 'Date: ' match expression
# was changed from 'Date: (.+)\n' to just 'Date:\s*(.+)' since this was
# causing problems also.  Also made $host and $port local to open_socket
# since they are passed as parameters and were being ignored.
# For debugging or the following values together, else zero for no debugging.
#   1 => parameter summary, will quit after processing parameters.
#   2 => http requests and headers.
#   4 => search-list list data.
#   8 => search-list info data.
#  16 => select and read information in get subroutine.
$debug = 0;

$launcher_version = '2.8';	# If changed delete instances of '(beta)'.
$http_host = 'searchlauncher.bcm.tmc.edu';

$http_port = '80';
# starting with version 2.8 of the batch client 
# version of batch client will match search list version 
$http_list_path = '/cgi-bin/seq-search/search-list-2.8.pl';
$timeout = 7200; # Excessive timeout, but that should be okay.

# Set to a proxy host/port to use a proxy, otherwise leave null.  Should
# probably use environment variable on Unix.
$proxy_host = '';
$proxy_port = '';

%html_entity_to_char = ('lt', '<', 'gt', '>', 'amp', '&', 'quot', '"',
			'nbsp', ' ');

&init_system;

# Used for web server and log file.
$search_agent = "$launcher_name/$launcher_version"; 

$seq_type = '';
$search = '';
$email = '';
$fork = 1;
$db_type = '';
$search_num = '';
$file_type = '';

if ($system eq 'mac') {
    open(STDIN, "+>Dev:Console:$launcher_name") || &do_die("open console, $!");
    select((select(STDIN), $| = 1)[0]);
    open(STDOUT, "+>&STDIN") || &do_die("dup STDIN to STDOUT, $!");
    select((select(STDOUT), $| = 1)[0]);
    if (@ARGV == 0) {
	&print_help;
    }
} else {
    while ((@ARGV > 0) && ($ARGV[0] =~ /^-./)) {
	if ($ARGV[0] eq '-h') {
	    &print_help;
	} elsif ($ARGV[0] eq '-d') {
	    shift;
	    $debug = shift;
	} elsif ($ARGV[0] eq '-e') {
	    shift;
	    $email = shift;
	} elsif ($ARGV[0] eq '-f') {
	    shift;
	    $fork = 0;
	} elsif ($ARGV[0] eq '-s') {
	    shift;
	    $search = shift;
	} elsif ($ARGV[0] eq '-t') {
	    shift;
	    $_ = shift;
	    if (! defined($_)) {
		&do_die("$launcher_name: Missing -t option parameter.\n");
	    } elsif (substr('protein', 0, length($_)) eq $_) {
		$seq_type = 'protein';
	    } elsif (substr('dna', 0, length($_)) eq $_) {
		$seq_type = 'dna';
	    } elsif (substr('output', 0, length($_)) eq $_) {
		$seq_type = 'output';
            } elsif (substr('seq', 0, length($_)) eq $_) {
		$seq_type = 'seq';
	    } else {
		&do_die("$launcher_name: Bad -t option parameter '$_'.\n");
	    }
        } elsif ($ARGV[0] eq '-r') {
	    shift;
            $file_type = shift;
        } elsif ($ARGV[0] eq '-v') {
#	    print("$launcher_name version $launcher_version (beta).\n");
	    print("$launcher_name version $launcher_version.\n");
	    &do_exit(0);
	} else {
	    die "$launcher_name: Unknown option $ARGV[0], use -h for help\n";
	}
    }
}

#
# Prompt for type of sequences.  Could automatically do this, but since there
# might be a time delay to convert and the user often knows this, it was
# done this way as a compromise between easy of use and efficiency.  Checking
# a large number of files could really take a long time.
#
# This catches a bad option value also, although maybe not intentionally.

while ($seq_type ne 'protein' && $seq_type ne 'dna' && $seq_type ne 'output' && $seq_type ne 'seq') {
    print("Enter type of sequence ([protein seq(s)]/dna seq(s)/output file(s)/seq ID file(s)): ");
    $_ = <STDIN>; &do_exit(0) unless $_; chop;
    # Allow any case and abbreviations.
    $_ = "\L$_";
    if (substr('protein', 0, length($_)) eq $_) {
	$seq_type = 'protein';
    } elsif (substr('dna', 0, length($_)) eq $_) {
	$seq_type = 'dna';
    } elsif (substr('output', 0, length($_)) eq $_){
        $seq_type = 'output';
    } elsif (substr('seq', 0, length($_)) eq $_){
       $seq_type = 'seq';
    } elsif (substr('quit', 0, length($_)) eq $_) {
	&do_exit(0);
    } else {
	print("Unknown sequence type of '$_'\n");
    }
}

if (! $search) {
    print("Contacting server, please wait ...\n");
    $search_list = &get($http_host, $http_port,
			"$http_list_path?list+$seq_type");
    print(STDERR "search_list: $search_list") if $debug & 4;
    if ($search_list =~ /^ERROR/) {
	$search_list =~ s/^ERROR/$launcher_name/;
	&do_die($search_list);
    } elsif (! $get_success) {
	&do_die("$launcher_name: HTTP error to http://$http_host:$http_port$http_list_path?list+$seq_type\n");
    }
} else {
    # Need to make sure $search isn't 'list' or 'help', since this will
    # return successful but not be what we want.
    if ($search eq 'list' || $search eq 'help') {
	&do_die("$launcher_name: Search option can not be 'list' or 'help'.");
    }
    $search_info = &get($http_host, $http_port,
			"$http_list_path?$search+$seq_type");
    print(STDERR "search_info: (from command line) $search_info")
	if $debug & 8;
    if ($search_info =~ /^ERROR/) {
	$search_info =~ s/^ERROR/$launcher_name/;
	&do_die($search_info);
    } elsif (! $get_success) {
	&do_die("$launcher_name: HTTP error to http://$http_host:$http_port/$http_list_path?$search+$seq_type\n");
    } else {
	chop($search_info);
	($program, $path, %flags) = split(' ', $search_info);
    }
}

while (! $search) {

#    print($search_list, "Enter number or name of search (? for help): ");

##  Modified by Zhenwu, Oct 27, 99
##  Purpose: Showing instruction screen by screen for DOS user

    @search_array = split(/\n/, $search_list);
    $i =1;
    my($j)=1;
    my($selected_search) = '';

    LABEL1 : foreach $key (@search_array)
    {
       print $key, "\n";
        
       $i++;
       $j++;

       # It will print 22 lines each time, 
       # To change the number of lines, change the value of j.
	if($j == 22)
	{
	    print "Hit enter to see next screen ... \n";
	    print ("or  Enter number or name of search (? for help): ");

	    $j = 1;
	    $_ = <STDIN>;
	    system("clear");  #for unix
	    &do_exit(0) unless $_; chop($_);
	    
	    # If user selects a search number, then jump out of
	    # this loop, LABEL1.
	    if($_)
	    {
		$selected_search = $_;
		last LABEL1;
	    }
	}
    }

    $_ = $selected_search;
######    End Zhenwu Oct 27, 99

    if ($_ eq '') {
	print("Please enter a search or 'quit'\n");
	$_ = <STDIN>;
    } elsif (substr('quit', 0, length($_)) eq $_) {
	&do_exit(0);
    } elsif ($_ eq '?') {
	if (! $search_help) {
	    print("Contacting server, please wait ...\n");
	    $search_help = &get_help;
	}
	print($search_help);
	print("Return to continue: ");
	$_ = <STDIN>; &do_exit(0) unless $_; chop;
	if ($_ && substr('quit', 0, length($_)) eq $_) {
	    &do_exit(0);
	}
    } else {
        $search_num = $_;
	$search_info = &get($http_host, $http_port,
			"$http_list_path?$_+$seq_type");
	print(STDERR "search_info: $search_info") if $debug & 8;
	if ($search_info =~ /^ERROR/) {
	    $search_info =~ s/^ERROR: //;
	    print($search_info);
	} elsif (! $get_success) {
	    &do_die("$launcher_name: HTTP error to http://$http_host:$http_port/$http_list_path?$_+$seq_type\n");
	} else {
	    chop($search_info);
	    ($program, $path, %flags) = split(' ', $search_info);
	    $search = $_;
	}
    }

}

while (@ARGV == 0) {
    while (1) {
	print("Enter file name (wildcard okay, return when done): ");
	$_ = <STDIN>; &do_exit(0) unless $_; chop;
	if ($_ eq '') {
	    last;
	} elsif (/[\*\?\[\]{}~]/) {
	    @_ = &glob_files($_);
	    if (@_ == 0) {
		print("No file names matched '$_'\n");
	    } else {
		print("Matched: @_\n");
                push(@ARGV, @_);
            }
 	} elsif (-f $_) { 
 	       push(@ARGV, $_);
 	} elsif (substr('quit', 0, length($_)) eq $_) {
	    &do_exit(0);
	} else {
	    print("No such file name '$_'\n");
	}
        print("Files selected: @ARGV\n");
    }
}

@db_type = '';
undef(@_);

if ($flags{'email'}) {
    while (! $email) {
	if ($system eq 'mac') {
	    print("Enter email address: ");
	} else {
	    local(@a, $user);

	    # Get the user name.
	    $user = ($ENV{'USER'} || $ENV{'LOGNAME'} || (getpwuid($<))[0]);

	    # Get fully qualified host name.
	    @a = gethostbyname($this_host);
	    # Do an extra lookup by addr since some systems seem to not give
	    # a fully qualified name with gethostbyname but do for
	    # gethostbyaddr.  Not to bad since the extra lookup is not too
	    # expensive, but the hard-coded value of 2 is none ideal.
	    @a = gethostbyaddr($a[4], 2);
	    $email = "\L$user\@$a[0]";
	    print("Enter email address [$email]: ");
	}
	$_ = <STDIN>; &do_exit(0) unless $_; chop;
	if ($_ eq '') {
	    # Do nothing, will keep prompting on a Mac.
	} elsif (substr('quit', 0, length($_)) eq $_) {
	    &do_exit(0);
	} else {
	    $email = $_;
	}
    }
}

if ($seq_type eq 'seq'){
    @find_files = @ARGV;
    $counter = 0;
    foreach $file (@find_files) {
         if (!$file_type) {
          print("Enter type of sequence ([protein seq(s)]/dna seq(s) for $file: ");
          $_ = <STDIN>; &do_exit(0) unless $_; chop;
          # Allow any case and abbreviations.
          $_ = "\L$_";
          if (substr('protein', 0, length($_)) eq $_) {
	         $db_type[$counter] = 'p';
                 $counter++;
          } elsif (substr('dna', 0, length($_)) eq $_) {
	         $db_type[$counter] = 'n';
                 $counter++;
          } else {
	  print("Unknown sequence type of '$_'\n");
          }
      } else {
                if ($file_type eq 'p' || $file_type eq 'protein') {
	          $db_type[$counter] ='p';
                  $counter++;
                } elsif ($file_type eq 'd' || $file_type eq 'dna') {
	          $db_type[$counter] = 'n';
                  $counter++;	
                } else {
		  print("Unknown sequence type of '$file_type'\n");
	      }
	    }
     }
}


if ($debug & 1) {
    print(STDERR "seq_type is $seq_type\nARGV is @ARGV\n",
	  "search is $search\nprogram is $program\nemail is $email\n");
    if ($system eq 'mac') {
	print("\nReturn to quit: ");
	$_ = <STDIN>;
    }
    &do_exit(0);
}

undef($search_list);
undef($search_info);
undef($search_help);
undef($url);
undef($_);

if ($system eq 'mac') {
    print("Submitting searches, check the file $launcher_name.log when done ...\n");
} elsif ($fork) {
    print("Submitting searches as background task, check the file $launcher_name.log\nfor status.\n");
    if ($pid = fork) {
	exit(0);
    } elsif (defined($pid)) {
	close(STDIN);
	close(STDOUT) unless $debug;
	$SIG{'HUP'} = 'IGNORE';
    } else {
	&do_die("can't fork: $!");
    }
}

#
# Open log file for appending and print initial log entry of what was requested
# and the date as returned from the server.
#
open(LOG, ">>$launcher_name.log") || &do_die("open $launcher_name.log, $!");
select((select(LOG), $| = 1)[0]);
print(LOG "$search_agent: $program on @ARGV\n was started at $date\n")
    || &do_die("print to log, $!");

$seq_data = '';
$multi_seq = '';
$n_search = 0;
$n_search_success = 0;

if ($seq_type eq 'output') {  
                                           # Currently, the only output files processes are for blast.
    $filename = $url = $out = $sfile = '';
    $file = '';
    $sfile = ''; 
    $seqbuf = '';
    $filebuf = '';
CHECK:
       foreach $filename (@ARGV) {
	if ($filename =~ m@\.fa$@ || $filename =~ m@\.seq$@) {
            next CHECK;
        }
       $file = $filename;
       $tstfile = $file;
       $tstfile =~ s@\.\w*@\.fa@;
       $sfile = $tstfile;
       if(!open(LTV, "$sfile")) {
           $tstfile =~ s@\.fa@\.seq@;
	   $sfile = $tstfile;
 	   if (!open(MDC, "$sfile")) {
               print(LOG "No sequence file found.\n");
               &do_die("No sequence file found.\n");
           }
       }
       close(LTV);
       close(MDC);
       open(TST, "$file") || &do_die("open $file, $!");
       while(<TST>) {
           $filebuf .= $_;
       }
       close(TST);
       
       open(TXT, "$sfile") || &do_die("open $sfile, $!");
       while(<TXT>) {
           $seqbuf .= $_;
       }
       close(TXT); 
       $url = "/cgi-bin/${path}blastout=$filebuf&seqfile=$seqbuf";
       $out = "$filename.beauty_pp.html";
       open(OUT, ">$out") || &do_die("open $out, $!");
       &get($http_host, $http_port, $url, OUT, 1);
       close(OUT);
       $filebuf = '';
	$seqbuf = '';
       $n_search++;
       if ($get_success) {
             $n_search_success++;
             print(LOG 'finished ');
       } else {
             print(LOG 'failed ');
	 }
           print(LOG "$out at $date\n") || &do_die("print to log, $!");
   }
     print (LOG "$search_agent: $n_search_success of $n_search searches completed. \n") || &do_die("print to log, $!");
     close(LOG);
     &do_exit(0);
}
@seqs ='';
$in_file = '';

if ($seq_type eq 'seq') {
    $filename = $url = $out = $file = $buf = '';
    foreach $filename (@ARGV) { 
     foreach $type (@db_type) {
        $db = $type;  
        open(TMP, "$filename") || &do_die("open $filename, $!");
        $i = 0;
        while(<TMP>) {
	    $buf .= $_;
            chop;
            $seqs[$i] = $_;
            $seqs[$i] =~ s/\s*//g;
            $i++;
        }
        close(TMP);
        $url = "/cgi-bin/${path}input=$buf&db_type=$db&prg=$search_num";
        $out = "$filename.txt";
        open(OUT, ">$out") || &do_die("open $out, $!");
        &get($http_host, $http_port, $url, OUT, 1);
        close(OUT);
        open(IN, "$out") || &do_die("open $out, $!");
        $buf = '';
        $i = 0;
        $program =~ s/\s*//g;
	while(<IN>) {
            if(m@Content-type: text/html@)  {
                $in_file = $seqs[$i++] . '.' . $program;
                open(SEQ, ">$in_file") || &do_die("open $in_file, $!");
                print(SEQ $buf);
	        close(SEQ);
 	        $_ = <IN>;
                $_ = <IN>;
                $in_file = '';
                $buf = '';
 	   }
	    $buf .= $_;
	}
        if (!$buf =~ m@^\s*$@ ) {
           $in_file .= $seqs[$i++] . '.' . $program;
           open(SEQ, ">$in_file") || &do_die("open $in_file, $!");
           print(SEQ $buf);
	   close(SEQ);
       }
        close(IN);
        $n_search++;
        if ($get_success) {
              $n_search_success++;
              print(LOG 'finished ');
        } else {
              print(LOG 'failed ');
	  }
         print(LOG "$out at $date\n") || &do_die("print to log, $!");
    }
  }
     print (LOG "$search_agent: $n_search_success of $n_search searches completed. \n") || &do_die("print to log, $!");
     close(LOG);
     system("rm -f $out");
     &do_exit(0);
}
     
#
# Process each sequence from all the files.
#
LOOP:
foreach $filename (@ARGV) {
    #
    # Convert file to fasta format using readseq on the server.
    #
    if (!open(FILE, $filename)) {
          next LOOP;
    } else {
        while (<FILE>) {
	   chop;
	   $seq_data .= $_ . "\12";
         }
    }
    close(FILE);

    #
    # Consider writing the sequence data to a file if memory is a problem.
    #
    $url = '/cgi-bin/seq-util/readseq.pl?seq_data=' . &escape($seq_data)
	. '&format=Pearson%2FFasta';
    $seq_data = &get($http_host, $http_port, $url, undef, 1);
    $seq_data =~ s/&(\w+);/$html_entity_to_char{$1}/g;
    @seq_lines = split(/\n/, $seq_data);
    $seq_data = '';

    $data_okay = 0;
    $line = shift(@seq_lines);
    while ($line && $line ne '<pre><hr>') {
	if ($line =~ /<base href.+readseq.pl/) {
	    $data_okay = 1;
	}
	if ($line =~ /<h1>ERROR reading/) {
	    $data_okay = 0;
	}
	$line = shift(@seq_lines);
    }
    if ($data_okay == 0) {
	print(LOG "$launcher_name: Error converting sequence using web readseq\n");
        next LOOP;
    }

    #
    # Scan the sequence lines in this file.
    #
    if ($flags{'multi'}) {
	if (! $multi_name) {
	    $multi_name = $filename;
	}
	while ($line = shift(@seq_lines)) {
	    last if $line eq '<hr></pre>';
	    $multi_seq .= $line . "\12";
	}
    } else {
	$have_seq = 0;
	while ($line = shift(@seq_lines)) {
	    last if $line eq '<hr></pre>';
	    if ($line =~ /^>/) {
		&process_seq;
		# Get rid of extra information added by readseq.
		$line =~ s/, \d+ bases, [\dA-F]+ checksum\.$//;
		($name) = split(' ', $line, 2);
		$name =~ s/^>//;
		$seq = '';
		$have_seq++;
	    } else {
		$seq .= $line . "\12";
	    }
	}
	&process_seq($filename);
    }

    if ($flags{'multi'}) {
         &process_multi_seq;
         print(LOG "$search_agent: multiple sequence search ");
         if ($get_success) {
	      print(LOG "completed.\n") || next LOOP;
         } else {
	      print(LOG "failed.\n") || next LOOP;
	 }
    } else {
         print(LOG "$search_agent: $n_search_success of $n_search searches completed.\n")
	         || next LOOP;
     }
}

close(LOG);
&do_exit(0);


#
# Submit each sequence to WWW server.
#
sub process_seq
{
    local($last_filename) = @_;
    local($filename, $doc, $url, $out);

    if (! $have_seq) {
	return;
    } elsif ($last_filename && $have_seq == 1) {
	$filename = $last_filename;
	$filename =~ s/.*$dir_sep(.)/$1/;
	$filename =~ s/$dir_sep$//;
    } else {
	$filename = $name;
	$filename =~ s/$dir_sep/_/g;
    }
    
    $name = &escape($name);
    $seq = &escape($seq);
    $url = "/cgi-bin/${path}seq_data=$seq&program_name=$program&seq_name=$name";
    if ($flags{'email'}) {
	$url .= "&email=$email";
    }
    if ($system eq 'mac') {
	print("Running $program on $filename ...\n");
    }
    $out = "$filename.$program.html";
    open(OUT, ">$out")
	|| &do_die("open $out, $!");
    &get($http_host, $http_port, $url, OUT, $flags{'post'});
    close(OUT);
    $n_search++;
    if ($get_success) {
	$n_search_success++;
	print(LOG 'finished');
    } else {
	print(LOG 'failed');
    }
    print(LOG " $out at $date\n") || &do_die("print to log, $!");
}

#
# Submit multiple sequence data to WWW server.
#
sub process_multi_seq
{
    local($doc, $url, $out);

    $url = "/cgi-bin/${path}seq_data=" . &escape($multi_seq). "&program_name=$program";
    if ($flags{'email'}) {
	$url .= "&email=$email";
    }
    if ($system eq 'mac') {
	print("Running $program on all files ...\n");
    }
    $multi_name =~ s/.*$dir_sep(.)/$1/;
    $out = "$multi_name.$program.html";
    open(OUT, ">$out")
	|| &do_die("open $out, $!");
    &get($http_host, $http_port, $url, OUT, $flags{'post'});
    close(OUT);
    if ($get_success) {
	print(LOG 'finished');
    } else {
	print(LOG 'failed');
    }
    print(LOG " $out at $date\n") || &do_die("print to log, $!");
}


#
# Subroutine to escape all the characters of a string suitable to pass
# as a query_string.
#
sub escape # ($string_to_escape)
{
    local($str) = @_;

    $str =~ s/([\0-\37!-\)+,\/:-\?\[-^\`\{-\177])/sprintf('%%%02X', unpack('c', $1))/ge;
    $str =~ s/ /+/g;
    $str;
}


#
# Get information from the http server using either GET or POST requests.
#
sub get
{
    local($host, $port, $request, $file, $use_post) = @_;
    local($S, $path, $post, $http_request);
    local($rin, $rout, $buf, $output, $n_found, $n_read, $headers);
    local($skip_headers, $common_headers);
    local($eof, $buf_cut);

    if ($proxy_host) {
	# Shouldn't need escaping ...
	$request = "http://$host:$port" . $request;
	$S = &open_socket($proxy_host, $proxy_port);
    } else {
	$S = &open_socket($host, $port);
    }

    $common_headers = "Accept: text/html\15\12" . "Accept: text/plain\15\12" .
	"Accept: */*\15\12" . "User-Agent: $search_agent\15\12" .
	    "Referer: file:/$launcher_name-$launcher_version\15\12";

    if ($use_post) {
	($path, $post) = split(/\?/, $request, 2);
	$http_request = "POST $path HTTP/1.0";
	print($S "$http_request\15\12");
	print(STDERR "$http_request\n") if $debug & 2;
	print($S $common_headers);
	print($S "Content-type: application/x-www-form-urlencoded\15\12");
	print($S "Content-length: ", length($post), "\15\12\15\12");
	print($S $post) || &do_die("print to server, $!");
    } else {
	$http_request = "GET $request HTTP/1.0";
	print($S "$http_request\15\12");
	print(STDERR "$http_request\n") if $debug & 2;
	print($S "$common_headers\15\12") || &do_die("print to server, $!");
    }

    $rin = '';
    vec($rin, fileno($S), 1) = 1;
    $output = $buf = $buf_cut = '';
    $get_success = 0;
    $skip_headers = 1;
    $eof = 0;
    do {
	if (! $eof) {
	    ($n_found) = select($rout = $rin, undef, undef, $timeout);
	    print(STDERR "n_found of $n_found, rin of ", unpack('b*', $rin),
		  ", rout of ", unpack('b*', $rout), "\n") if $debug & 16;
	    if ($n_found) {
		$n_read = sysread($S, $buf, 4096);
		defined($n_read) || &do_die("read from server, $!");
		print(STDERR "n_read of $n_read\n") if $debug & 16;
	    } else {
		&do_warn("read timed out.\n");
		$buf = '';
	    }
	    if (! ($n_found && $n_read)) {
		print(STDERR "eof\n") if $debug & 16;
		$eof = 1;
	    }
	}
	if ($buf_cut) {
	    print(STDERR "paste from buf_cut\n") if $debug & 16;
	    substr($buf, $[, 0) = $buf_cut;
	    $buf_cut = '';
	}
	if ($buf) {
	    # Only consider cutting CR from end of buf if not EOF.
	    if (! $eof && substr($buf, -1, 1) eq "\15") {
		print(STDERR "cut to buf_cut\n") if $debug & 16;
		$buf_cut = chop($buf);
	    }
	    $buf =~ s/\15\12/\12/g;
	    if ($system eq 'mac') {
		$buf =~ s/\12/\n/g;
	    } else {
		$buf =~ s/\15/\n/g;
	    }
	    if ($skip_headers) {
		print(STDERR "checking for headers\n") if $debug & 16;
		$output .= $buf;
		if ($output =~ /\n\n/) {
		    $skip_headers = 0;
		    if ($output =~ m@^HTTP/1.0 200@) {
			$get_success = 1;
		    }
		    ($headers, $output) = split(/\n\n/, $output, 2);
		    print(STDERR "header: ",
			  join("\nheader: ", split("\n", $headers)), "\n")
			if $debug & 2;
		    $headers .= "\n";
		    if ($headers !~ m@\nDate:\s*(.+)\n@) {
			&do_die('document not dated');
		    }
		    $date = $1;
		    if ($file) {
			print($file $output) || &do_die("print to $out, $!");
			$output = '';
		    }
		}
	    } elsif ($file) {
		print($file $buf) || &do_die("print to $out, $!");
	    } else {
		$output .= $buf;
	    }
	}
    } while ($buf_cut || ! $eof);

    close($S);
    $output;
}


#
# Setup networking parameters by system type.
#
sub init_system
{
    local($uname);

    # Assume we aren't on a unix machine if '.' isn't the last place to look
    # for libraries; which for now means we are on a Mac.
    if ($MacPerl'Version) { #'
	$system = 'mac';
	$launcher_name = 'SearchLauncher'; # Change search-list-*.pl also.
	$uname = $MacPerl'Version; #' Avoids possible typo.
	$dir_sep = ':';
    } else {
	$uname = `(uname -r -s) 2>/dev/null`;
	if ($uname =~ /^SunOS 5/ || $uname =~ /^IRIX.* [56]/) {
	    $system = 'sysvr4';
	} else {
	    $system = 'does not matter';
	}
	$launcher_name = 'search-launcher'; # Change search-list-*.pl also.
	$dir_sep = '/';
    }

    if ($system eq 'mac') {
	($domain, $socket_type, $protocol) = (2, 1, 0);
	$addr_pack_template = 's S a4 x8';
    } elsif ($system eq 'sysvr4') {
	($domain, $socket_type, $protocol) = (2, 2, 6);
    } else {
	($domain, $socket_type, $protocol) = (2, 1, 6);
    }

    if ($system ne 'mac') {
	$addr_pack_template = 'S n a4 x8';
	chop($this_host = `(uname -n || hostname) 2>/dev/null`);
	$this_ip = (gethostbyname($this_host))[4];
	$this_addr = pack($addr_pack_template, $domain, 0, $this_ip);
    }
}


#
# Open a socket to a remote host at the given port.
#
sub open_socket # ($host, $port)
{
    local($host, $port) = @_;

    if ($host =~ /^(\d+)+\.(\d+)\.(\d+)\.(\d+)/) {
	$ip = pack('C4', $1, $2, $3, $4);
    } else {
	local(@x) = gethostbyname($host);
	&do_die("Unknown hostname $host") unless @x;
	$ip = $x[4];
    }

    $addr = pack($addr_pack_template, $domain, $port, $ip);

    socket(S, $domain, $socket_type, $protocol)	|| &do_die("socket error: $!");
    if ($system ne 'mac') {
	bind(S, $this_addr) || &do_die("bind error: $!");
    }
    connect(S, $addr) || &do_die("connect error: $!");
    select((select(S), $| = 1)[0]);
    return(S);
}


sub get_help
{
    local($url, $help);

    $url = "$http_list_path?help+";
    # Just use dna for mac, and protein for unix (closes alphabetically).
    if ($system eq 'mac') {
	$url .= 'dna';
    } else {
	$url .= 'protein';
    }
    $help = &get($http_host, $http_port, $url);
    if ($help =~ /^ERROR/) {
	$help =~ s/^ERROR: //;
    } elsif (! $get_success) {
	&do_die("$launcher_name: HTTP error to http://$http_host:$http_port/$url");
    }
#    "$launcher_name version $launcher_version (beta) help.\n" . $help;
    "$launcher_name version $launcher_version help.\n" . $help;
}

sub print_help
{
    local($help);

    $help = &get_help;
    chop($help);
    print($help);
    if ($system eq 'mac') {
	print("\nReturn to quit: ");
	$_ = <STDIN>;
    }
    &do_exit(0);
}


sub do_die
{
    local($mesg) = @_;
    local($log_mesg, $last_char, $fileno);
    
    if (defined($fileno = fileno(LOG))) {
	$log_mesg = $mesg;
	$last_char = chop($log_mesg);
	if ($last_char ne "\n") {
	    $log_mesg .= $last_char;
	}
	print(LOG "$log_mesg\n");
	close(LOG);
    }

    if ($system eq 'mac') {
	if (! $mesg) {
	    $mesg = "Unknown error has occured in $launcher_name.";
	}
	&MacPerl'Answer($mesg, "OK"); #'
	&MacPerl'Quit(2); #'
	exit(1);
    } else {
	die $mesg;
    }
}

sub do_warn
{
    local($mesg) = @_;
    local($log_mesg, $last_char, $fileno);
    
    if (defined($fileno = fileno(LOG))) {
	$log_mesg = $mesg;
	$last_char = chop($log_mesg);
	if ($last_char ne "\n") {
	    $log_mesg .= $last_char;
	}
	print(LOG "$log_mesg\n");
    }

    warn($mesg);
}


sub do_exit
{
    local($status) = @_;

    if ($system eq 'mac') {
	&MacPerl'Quit(2); #'
	exit($status);
    } else {
	exit($status);
    }
}

# Keep this at the end of the file, the globbing part throws off perl-mode
# in emacs.
sub glob_files
{
    local($_) = @_;
    local(@a);

    @a = <${_}>;
    grep(-f, @a);
}











