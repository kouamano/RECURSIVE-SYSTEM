#!/usr/bin/perl

use strict;
use warnings;

&main;

sub main() {
    my ($field_num, $filename) = chk_argument(@ARGV);
    open my $fd, '<', $filename;
    my @lines;
    while (my $line = <$fd>) {
        chomp $line;
        push @lines, $line;
    }
    close $fd;

    foreach my $line (sort {
        my $a_item = (split /\s+/, $a)[$field_num];
        my $b_item = (split /\s+/, $b)[$field_num];
        return hex($a_item) <=> hex($b_item);
    } @lines) {
        print "$line\n";
    }
}

sub chk_argument(@) {
    my @argvs = @_;
    my $field_num = 0;
    my $filename;
    while (defined(my $argv = shift @argvs)) {
        if ($argv =~ m{^-}) {
            if ($argv eq '-f') {
                $field_num = shift @argvs;
                $field_num--;
            }
        }
        else {
            $filename = $argv;
        }
    }
    return ($field_num, $filename);
}

