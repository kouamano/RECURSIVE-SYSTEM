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

#if [ $1 = "--C" ]; then
if [[ $1 =~ --.* ]]; then
  if [ $# -eq 1 ]; then
    exit;
  fi

  op=$1
  op=${op:2}
  #echo op:$op:
  list=(${op//,/ })
  #echo ${list[@]}
  for e in ${list[@]}; do
    #echo $e
    if [ $e = "C" ]; then
      TQ=$CQ
    fi
    if [ $e = "E" ]; then
      echo hit:E
    fi
  done

  array=${array#--* }
  echo arr:$array:
fi

$TQ $array
