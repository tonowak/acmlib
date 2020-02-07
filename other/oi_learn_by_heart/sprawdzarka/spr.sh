#!/bin/bash

for ((i=0; 1; i++)); do
	./gen < t.conf > t.in
	./main < t.in > m.out
	./brute < t.in > b.out

	if diff -w m.out b.out > /dev/null; then
		echo "OK $i"
	else
		echo "WA"
		exit 0
	fi
done
