#!/bin/bash
# this is a tq meta command
# Needs: tq.o, c_tq.o

if [ $# -eq 0 ]; then
  echo "Usage:"
  echo "  tq target=<file>"
  echo "  tq -h"
  exit;
fi

if [ $1 = "-h" ]; then
  echo "==tq=="
  ./tq.o -h
  echo "==c_tq=="
  ./c_tq.o -h
  exit;
fi
