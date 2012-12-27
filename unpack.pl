#!/usr/bin/perl

sub url_unpack($) {
  my $str = shift;
  $str =~ s/(.)/'%'.unpack('H2', $1)/eg;
  return $str;
}

while(<>){
	print url_unpack($_);
}
