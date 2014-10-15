#!/bin/bash

file_head=$1
num_files=$2

for n in `seq 1 $num_files`;
	do echo ${file_head}-${n}.dmat;
	MST dmat=${file_head}-${n}.dmat > ${file_head}-${n}.MST
done
