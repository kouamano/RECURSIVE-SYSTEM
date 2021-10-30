#!/bin/bash
# This is a tq meta command
# Needs: tq.o, c_tq.o, exprt.pl
# How to install
# sudo cp tq.sh /usr/local/bin/tq
array=$@
exec=0

TQ=~/gitsrc/RECURSIVE-SYSTEM/tq.o		#必要に応じて書き換え
CQ=~/gitsrc/RECURSIVE-SYSTEM/c_tq.o		#必要に応じて書き換え
EXPRT=~/gitsrc/RECURSIVE-SYSTEM/exprt.pl	#必要に応じて書き換え

if [ $# -eq 0 ]; then
  echo "Usage:"
  echo "  tq --h"
  echo "  tq <args>"
  echo "  tq --<OP> <args>"
  echo "  <OP>: comma separated charactor"
  echo "  <OP>:C execute c_tq"
  echo "  <OP>:E execute <command> in {<command>}"
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

#if [ $1 = "--C" ]; then
if [[ $1 =~ --.* ]]; then
  if [ $# -eq 1 ]; then
    exit;
  fi

  op=$1
  op=${op:2}
  #echo op:$op:
  list=(${op//,/ })
  for e in ${list[@]}; do
    if [ $e = "C" ]; then
      TQ=$CQ
    fi
    if [ $e = "E" ]; then
      exec=1
    fi
  done

  array=${array#--* }
fi

if [ $exec = 1 ]; then
  $TQ $array | $EXPRT
else
  $TQ $array
fi
