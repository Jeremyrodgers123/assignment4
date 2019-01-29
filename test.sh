#!/bin/bash

echo run test

./main input.txt output.txt

diff expectedOutput.txt output.txt

if [ "$?" -eq 0 ]
then
    echo PASS
else 
    echo FAIL
fi
