#!/usr/bin/perl

sub url_encode($) {
  my $str = shift;
  $str =~ s/([^\w ])/'%'.unpack('H2', $1)/eg;
  $str =~ tr/ /+/;
  return $str;
}

while(<>){
	print url_encode($_);
}
