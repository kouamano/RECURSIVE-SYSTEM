#!/usr/bin/python

import sys
import fileinput
import re

for line in fileinput.input():
  if re.match("^CONTENTS",line):
    sys.stdout.write(line)
    sb = re.findall(r'<xref .*?>.*?</xref>',line)
    #sys.stdout.write(sb.group())
    #print sb
    for rf in sb:
      print "REF	" + rf
  else:
    sys.stdout.write(line)
