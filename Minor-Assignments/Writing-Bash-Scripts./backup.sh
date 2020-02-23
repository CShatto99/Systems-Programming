#!/bin/bash

clear

# command-line -arguments
DIR_NAME="$1"
DAYS=$2

# variables to construct the tgz file
SRC_DIR=`find / -type d -name "$DIR_NAME" 2>/dev/null`
DEST_DIR="/home/$USER/backups/"
FILE_NAME=src_$(date +%F).tgz

# check for optional parameter (default 5 days)
if [ -z "$DAYS" ]; then
	DAYS=5
else
	DAYS=$2
fi

# delete files that are older than N days
for FILE in *
do
	OLD_FILE=`find . -type f -mtime +$DAYS -name $FILE`
	if [ ! -z $OLD_FILE ]; then
		find . -type f -samefile $FILE -delete
	fi
done

# create the backup directory
mkdir $DEST_DIR

# create the tgz backup of the directory with the remaining files
tar --create -gzip --file=$DEST_DIR$FILE_NAME $SRC_DIR
