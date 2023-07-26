c() {
	g++ -std=c++20 -Wall -Wextra -Wshadow \
		-Wconversion -Wno-sign-conversion -Wfloat-equal \
		-D_GLIBCXX_DEBUG -fsanitize=address,undefined -ggdb3 \
		-DDEBUG -DLOCAL $1.cpp -o $1
}
nc() {
	g++ -DLOCAL -O3 -std=c++20 -static $1.cpp -o $1 # -m32
}
alias cp='cp -i'
alias mv='mv -i'
