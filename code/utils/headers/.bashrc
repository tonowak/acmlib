c() {
	clang++ -std=c++11 -Wall -Wextra -Wshadow \
		-Wconversion -Wno-sign-conversion -Wfloat-equal \
		-D_GLIBCXX_DEBUB -fsanitize=address,undefined -ggdb3 \
		-DDEBUG $1.cpp -o $1
}

nc() {
	clang++ -O3 -std=c++11 -static $1.cpp -o $1 # -m32
}
