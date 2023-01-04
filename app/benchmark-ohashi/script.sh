#!/bin/bash

echo "評価スクリプト"

i=0
while [ $i -lt 10 ]; do
	if [ "$1" == "ohashi_perm" ] || [ "$1" == "ohashi_perm_bound" ]; then
		j=$((RANDOM % 512))
		k=$((RANDOM % 1024))
		echo $i:  ./$1 $j $k
		./$1 j k
	else
		j=$((RANDOM % 512))
		k=$((RANDOM % 512))
		echo $i:  ./$1 $j $k
		./$1 j k
	fi
    ((i++))
done