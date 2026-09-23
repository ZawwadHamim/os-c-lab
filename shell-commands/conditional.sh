#!/bin/bash
echo "Enter the first number"
read n1
echo "Enter the second number"
read n2

if [ $n1 -gt $n2 ]; then
	echo "$n1 is greater than $n2"
elif [ $n1 -lt $n2 ]; then
	echo "$n1 is less than $n2"
else
	echo "$n1 and $n2 are equal"
fi
