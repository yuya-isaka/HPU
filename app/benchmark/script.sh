#!/bin/bash

echo "評価スクリプト"

i=0
while [ $i -lt 100 ]; do
	# echo $i:  ./$1
	./$1
    ((i++))
done