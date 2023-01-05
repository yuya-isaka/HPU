#!/bin/bash

echo "評価スクリプト"

i=0
if [ "$1" == "ohashi_perm" ] || [ "$1" == "ohashi_perm_bound" ]; then
	j=1024
else
	j=512
fi

while [ $i -lt 100 ]; do
	k=$((RANDOM % 512))
	l=$((RANDOM % $j))
	echo $i:  ./$1 $k $l
	./$1 $k $l
    ((i++))
done