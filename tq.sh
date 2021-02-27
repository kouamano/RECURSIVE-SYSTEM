#!/bin/bash
# this is a tq meta command
# Needs: tq.o, c_tq.o
if [ $1 = "-h" ]; then
  echo ==tq==
  ./tq.o -h
  echo ==c_tq==
  ./c_tq.o -h
  exit;
else
  ;
fi
