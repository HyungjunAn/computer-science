#!/bin/bash

path="/sys/class/gpio/"

echo 16 > $path/export
#echo out > $path/gpio16/direction
while true
do
	#echo 1 > $path/gpio16/value
	sleep 1
	echo 0 > $path/gpio16/value
	sleep 1
done


