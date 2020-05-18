// Name: Cameron Shatto
// EUID: chs0090

#!/bin/bash

clear

echo "Enter a string: "
read STRING
echo

for WORD in $STRING
do
	echo $WORD
done
echo

for FILE in *
do
	BYTES=`stat -c %s $FILE`
	KBYTES=`ls -sh $FILE`
	echo "$BYTES bytes $KBYTES"
done
echo
