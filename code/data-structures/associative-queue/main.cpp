/*
 * Opis: Kolejka wspierająca dowolną operację łączną, O(1) zamortyzowany.
 *   Konstruktor przyjmuje dwuargumentową funkcję oraz jej element neutralny.
 *   Dla minów jest \texttt{AssocQueue<int> q([](int a, int b)\{ return min(a, b); \}, numeric\_limits<int>::max());}
 */
template<typename T>
struct AssocQueue {
	using fn = function<T(T, T)>;
	fn f;
	vector<pair<T, T>> s1, s2; // {x, f(pref)}
	AssocQueue(fn _f, T e = T()) : f(_f), s1({{e, e}}), s2({{e, e}}) {}
	void mv() {
		if (ssize(s2) == 1)
			while (ssize(s1) > 1) {
				s2.emplace_back(s1.back().first, f(s1.back().first, s2.back().second));
				s1.pop_back();
			}
	}
	void emplace(T x) {
		s1.emplace_back(x, f(s1.back().second, x));
	}
	void pop() {
		mv();
		s2.pop_back();
	}
	T calc() {
		return f(s2.back().second, s1.back().second);
	}
	T front() {
		mv();
		return s2.back().first;
	}
	int size() {
		return ssize(s1) + ssize(s2) - 2;
	}
	void clear() {
		s1.resize(1);
		s2.resize(1);
	}
};
