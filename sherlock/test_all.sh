#!/bin/bash
#by John and Nas

[ "$#" -eq 1 ] || { echo "Usage: test_all.sh ./commandtoexecute" >&2; exit 1; }

COMMAND=$1
x=0
correct=0
timeout=0
wrong=0
while [ $x -le 19 ]
do
	var=$( ./test.sh $COMMAND $x )
	if echo "$var" | grep -q "WRONG"; then
	  wrong=$(( $wrong + 1 ))
	elif
	  echo "$var" | grep -q "TIMEOUT"; then
	  timeout=$(( $timeout + 1 ))
	else
	  correct=$(( $correct + 1 ))
	fi
	echo "$x."
	echo "$var"
	echo
	x=$(( $x + 1 ))
done

echo
echo "  Risposte corrette: $correct su 20"
echo "  Timeout: $timeout su 20"
echo
