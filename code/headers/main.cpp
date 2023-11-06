/*
 * Opis: Główny nagłówek
 */
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r)for(int i=(l);i<=(r);++i)
#define REP(i,n)FOR(i,0,(n)-1)
#define ssize(x)int(x.size())
#ifdef DEBUG
auto&operator<<(auto&o,pair<auto,auto>p){return o<<"("<<p.first<<", "<<p.second<<")";}
auto&operator<<(auto&o,auto x){o<<"{";int i=0;for(auto e:x)o<<","+!i++<<e;return o<<"}";}
#define debug(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X)
#else
#define debug(...){}
#endif
int main() {
	cin.tie(0)->sync_with_stdio(0);
	REP(i, 5)
		debug(i);
}
