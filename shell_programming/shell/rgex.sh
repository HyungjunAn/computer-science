#!/bin/bash

#read -r $(find . -type f | tr '\n' '\n')
#str=$(find . -type f)

#printf "%s\n" $str

for file in $(find . -type f); do 
	if [[ $file =~ $1 ]]
	then
		echo ""
		#echo $file 
	fi
done


#arr="+"
#arr="+-/*abc cdd"
unset arr
MUL=*
#arr=($MUL)
arr="+ - / \*"
echo $MUL
for op in $arr; do
	echo $op
	echo $((4 $op 3)) 
done

#op=+
#echo $((4 $op 3)) 
