#!/bin/bash
password="abc"
echo "Enter password"
read pass
while [ $pass != $password ]
do
echo "Wrong password, try again: "
read pass
done
echo "right Password"
