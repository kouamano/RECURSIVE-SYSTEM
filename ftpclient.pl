#!/usr/bin/perl

use POSIX;
use Socket;
use Getopt::Std;

my ($host, $port, $addr, $proto, $ent);

$port = 21;

