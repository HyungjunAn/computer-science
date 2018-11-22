#!/bin/bash

ORI_EXT=$1
NEW_EXT=$2

ls *.$ORI_EXT > /tmp/my.tmp

while read -r; do
	OLD_FILE=$REPLY
	NEW_FILE="$(basename $REPLY .$ORI_EXT).$NEW_EXT"
	mv $OLD_FILE $NEW_FILE
done < /tmp/my.tmp

rm /tmp/my.tmp





