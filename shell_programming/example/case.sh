#!/bin/bash


func_arg() {
	local n=$1
	if (( n == 0 )); then
		return 42
	fi
	echo $n
	((--n))
	func_arg $n
}

n=$(func_arg 10)
echo $?
echo $n # 10 9 8 7 6 5 4 3 2 1

while getopts :a:bc opt; do
	case $opt in
		a) echo "opt_a";;
		b) echo "opt_b $OPTARG";;
		c) echo "opt_c";;
		*) echo "error";;
	esac
done
