struct Int {
	int var;
	Int(int x) {
		var = x;
	}
};

Int operator+(Int a, Int b) {
	return Int(a.var + b.var);
}

int main() {
	Int x(4), y(5);
	Int suma = x + y;
	cout << suma.var << endl;
}

/////

+
-
*
/
<
>
+=
-=
*=
/=
<<
>>
<<=
>>=
==
!=
<=
>=
++
--
%
&
^
!
|
~
&=
^=
|=
&&
||
%=
[]
()
oraz domyślne:
=
new
delete
->
konstruktory
destruktory

/////

struct Struktura {
	int a, b;
	int& operator[](int index) {
		if(index == 0)
			return a;
		else
			return b;
	}
};

/////

bool operator<(Int &a, Int &b) {
	return a.var < b.var;
}

int main() {
	vector<Int> vec(n);
	sort(vec.begin(), vec.end());
}

/////

struct Node {
	int mn = int(1e9), lazy = 0, size = 1;
};
Node operator+(Node &a, Node &b) {
	Node n;
	n.mn = min(a.mn, b.mn);
	n.size = a.size + b.size;
	return n;
}

struct Tree {
	int size;
	vector<Node> t;

	Tree(int n) {
		size = 1;
		while(size < n)
			size *= 2;
		t.resize(size * 2);
	}

	void add() { /* ... */ }
	int get() { /* ... */ }

	// t[v] = t[v * 2] + t[v * 2 + 1]
}

