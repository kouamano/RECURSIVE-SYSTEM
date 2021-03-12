#!/bin/bash
# this is a tq meta command
# Needs: tq.o, c_tq.o
array=$@

TQ=~/gitsrc/RECURSIVE-SYSTEM/tq.o	#必要に応じて書き換え
CQ=~/gitsrc/RECURSIVE-SYSTEM/c_tq.o	#必要に応じて書き換え

if [ $# -eq 0 ]; then
  echo "Usage:"
  echo "  tq --h"
  echo "  tq --C <args>"
  echo "  tq <args>"
  exit;
fi

if [ $1 = "--h" ]; then
  echo "==tq=="
  ./tq.o -h
  echo
  echo "==c_tq=="
  ./c_tq.o -h
  exit;
fi

if [ $1 = "--C" ]; then
  if [ $# -eq 1 ]; then
    exit;
  fi
  TQ=$CQ
  array=${array#--C}
fi

$TQ $array
