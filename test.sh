#!/bin/bash

#./main input.txt output.txt
compareFiles(){
diff $1 $2

val=$?
if [ $val -eq 0 ]
then
echo "PASS"
elif [ $val -eq 1 ]
then
echo "*********"
echo "FAIL"
echo $3
echo "*********"
exit 1
else
echo "ERROR"
exit 1
fi
}

compareFiles $1 $2 $3
