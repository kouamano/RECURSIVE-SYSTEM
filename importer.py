#!/usr/bin/env python
import sys
import json

print(sys.argv[1])
IN = open(sys.argv[1],'r')
json.load(IN)
