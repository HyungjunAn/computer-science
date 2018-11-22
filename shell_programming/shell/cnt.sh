#!/bin/bash

file_cnt=0
dir_cnt=0
for file in $(ls);
do 
	if [ -d $file ] 
	then
		((dir_cnt++))
	else
		((file_cnt++))
	fi
done
echo "file: $file_cnt"
echo "dir:  $dir_cnt"
