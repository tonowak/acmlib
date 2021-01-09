#!/bin/bash
for ((i=0; i<1000000; i++)); do
	./gen < g.in > t.in
	./main < t.in > m.out
	./brute < t.in > b.out

	if diff -w m.out b.out > /dev/null; then
		printf "OK $i\r"
	else
		echo "WA"
		exit 0
	fi
done
