#!/bin/bash

for (( i = 0; i < 5; ++i )); do
	echo $i
done


read year month
if  [[ ( $year =~ ^[1-9][0-9]{0,3}$ ) && ( $month =~ ^1[0-2]$|^[1-9]$ ) ]]; then
	echo good
else
	echo !!!!!!!!!!!!!!!!!!!!!!!!!!
fi



