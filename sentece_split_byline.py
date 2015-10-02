#!/usr/bin/python

import sys
import fileinput
import nltk
from nltk import tokenize

for line in fileinput.input():
  print('\n<;/>\n'.
    join(
      #sent_detector.tokenize(line.strip()) ) )
      tokenize.sent_tokenize(line.strip()) ) )
