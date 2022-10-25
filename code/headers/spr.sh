for ((i=0;;i++)); do
	./gen < g.in > t.in
	./main < t.in > m.out
	./brute < t.in > b.out
	if diff -w m.out b.out > /dev/null; then
		printf "OK $i\r"
	else
		echo WA
		return 0
	fi
done
