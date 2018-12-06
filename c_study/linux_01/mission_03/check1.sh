#!/bin/bash

read -p "enter input: "

if [[ $REPLY =~ ^[a-zA-Z0-9]+$ ]]
then
	echo "Input is Valid"
else
	echo "Please enter only letters and numbers"
fi
	


