vim .bashrc
c() {
	g++ -std=c++17 -Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Wfloat-equal -D_GLIBCXX_DEBUG -fsanitize=address,undefined -ggdb3 -DDEBUG -DLOCAL $1.cpp -o $1
}
nc() {
	g++ -DLOCAL -O3 -std=c++17 -static $1.cpp -o $1
}
alias cp='cp -i'
alias mv='mv -i':wq
source .bashrc
mkdir template
cd template
vim main.cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r) for(int i=(l);i<=(r);++i)
#define REP(i,n) FOR(i,0,(n)-1)
#define ssize(x) int(x.size())
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<'('<<p.first<<", "<<p.second<<')';}
template<class T>auto operator<<(ostream&o,T x)->decltype(x.end(),o){o<<'{';int i=0;for(auto e:x)o<<(", ")+2*!i++<<e;return o<<'}';}
#ifdef DEBUG
#define debug(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<'\n';}(x)
#else
#define debug(...) {}
#endif

int main() {
	cin.tie(0)->sync_with_stdio(0);

}:wq
cp main.cpp brute.cpp
cp main.cpp gen.cpp
vim gen.cpp
G5komt19937 rng(chrono::system_clock::now().time_since_epoch().count());
int rd(int l, int r) {
	return rng()%(r-l+1)+l;
}:wq
cd ..
vim .bashrc
Gospr() {
	for ((i=0;;i++));do
		./gen<g.in>t.in
		./main<t.in>m.out
		./brute<t.in>b.out
		if diff -w m.out b.out>/dev/null;then
			printf "OK $i\r"
		else
			echo WA
			return 0
		fi
	done
}:wq
vim .vimrc
set nu rnu hls is nosol ts=4 sw=4 ch=2 sc
filetype indent plugin on
syntax on:wq

