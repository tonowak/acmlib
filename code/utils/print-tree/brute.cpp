#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r) for(int i=(l);i<=(r);++i)
#define REP(i,n) FOR(i,0,(n)-1)
#define ssize(x) int(x.size())
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<'('<<p.first<<", "<<p.second<<')';}
template<class T>auto operator<<(ostream&o,T x)->decltype(x.end(),o){o<<'{';int i=0;for(auto e:x)o<<(", ")+2*!i++<<e;return o<<'}';}
#ifdef DEBUG
#define debug(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...);}(x),cerr<<'\n'
#else
#define debug(...) {}
#endif

#include "main.cpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);


	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	REP(i,n-1) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}
	print_tree(adj);
}
