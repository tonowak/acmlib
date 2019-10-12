#!/bin/bash
for ((i=0; i<1000000; i++)); do
	./gen < conf.txt > gen.txt
	./main < gen.txt > main.txt
	./brute < gen.txt > brute.txt

	if diff -w main.txt brute.txt > /dev/null; then
		echo "OK $i"
	else
		echo "WA"
		exit 0
	fi
done
