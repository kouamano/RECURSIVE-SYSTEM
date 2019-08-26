#!/usr/bin/env python

import sys
import fileinput
import nltk
from nltk import tokenize

nltk.download('punkt')

for line in fileinput.input():
  print(' <;/>'.
    join(
      #sent_detector.tokenize(line.strip()) ) )
      tokenize.sent_tokenize(line.strip()) ) )
