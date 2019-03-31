#!/bin/bash


while true;
do
	read -r -p 'Password: '

	if [[ -z "$REPLY" ]]; 
	then
		exit
	fi

	echo $REPLY 
	if [[ ! "$REPLY" =~ ^[a-zA-Z0-9\*]{1,10}$ ]]; 
	then
		echo "Wrong Password!!!"
	else
		echo "Good!!"
	fi
done
