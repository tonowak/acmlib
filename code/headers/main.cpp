/*
 * Opis: Główny nagłówek
 */
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r) for(int i=(l);i<=(r);++i)
#define REP(i,n) FOR(i,0,(n)-1)
#ifdef DEBUG
auto&operator<<(auto&o,pair<auto,auto>p){return o<<'('<<p.first<<", "<<p.second<<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';REP(i,ssize(x))o<<","[!i]<<x[i];return o<<'}';}
#define debug(X...) cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...);}(X),cerr<<'\n'
#else
#define debug(...) {}
#endif

int main() {
	cin.tie(0)->sync_with_stdio(0);

}
