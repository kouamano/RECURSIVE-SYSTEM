#!/bin/bash

file_head=$1
num_files=$2

echo "{"
	echo "{"
	#echo ${file_head}-1.dmat
	MST dmat=${file_head}-1.dmat
	echo "}"
for n in `seq 2 $num_files`;
	do #echo ${file_head}-${n}.dmat;
	echo ",{"
	MST dmat=${file_head}-${n}.dmat
	echo "}"
done
echo "}"
