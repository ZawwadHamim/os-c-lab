#!/bin/bash
echo "Is it morning? Answer yes or no: "
read timeofday
case "$timeofday" in
	yes|y|YES|Yes) echo "Good morning";;
	no|n|NO|No) echo "good afternoon";;
	*) echo "Sorry, answer not recognized";;
esac
