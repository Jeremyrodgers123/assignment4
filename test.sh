#!/bin/bash

./main input.txt output.txt

diff expectedOutput.txt output.txt

val=$?
if [ $val -eq 0 ]
then
echo "PASS"
elif [ $val -eq 1 ]
then
echo "FAIL"
exit 1 
else
echo "ERROR"
exit 1
fi
