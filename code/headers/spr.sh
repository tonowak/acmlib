for ((i=0;;i++)); do
	./gen < g.in > t.in
	./main < t.in > m.out
	./brute < t.in > b.out
	printf "OK $i\r"
	diff -wq m.out b.out || break
done
