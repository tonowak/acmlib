/*
 * Opis: Struktura znajdująca najbliższy punkt dla danego zapytania, używając hashowania płaszczyzny
 * Czas: zapytanie O(\frac{nK}{2^L}) dodanie O(KL) pamięciowo O(nK)
 * Użycie: NearestPoints<L, K>, gdzie L to ilość prostych do hashowania i K to ilość hashowań
 * jeśli potrzebujemy usuwać, w PointHashing dajemy seta zamiast vectora
 * jeśli potrzebujemy id punktów, musimy je trzymać w structcie
 * jeśli pytamy o punkt który został dodany, zwróci sam siebie; można to łatwo zmienić dodając flagę czy już znalazło siebie
 */
#include "../point/main.cpp"
struct Line {
	P a, b;
	int bound = 100;
	Line() {
		a = P(rd(-bound, bound), rd(-bound, bound));
		Double theta = M_PIl * 2 * rd(0, 1e9) / 1e9;
		b = a + polar(1.0L, theta);
		debug(a, b);
	}
	bool side(P p) {
		return max(0, sign(cross(b - a, p - a)));
	}
};

template<size_t L>
struct PointHashing {
	vector<Line> lines;
	// jeśli potrzebujemy usuwać, dajemy seta
	// jeśli potrzebujemy id punktów, musimy zrobić strukta z id
	unordered_map<bitset<L>, vector<P>> buckets;
	PointHashing() : lines(L) {}
	bitset<L> get_hasz(P p) {
		bitset<L> hasz;
		REP(i, L) hasz[i] = lines[i].side(p);
		return hasz;
	}
	void add(P p) {
		buckets[get_hasz(p)].emplace_back(p);
	}
	// jesli pytamy o punkt który został dodany, zwróci sam siebie, można to łatwo zmienić dodając flagę czy już siebie znalazło
	pair<int, P> query(P p) {
		const auto &vec = buckets[get_hasz(p)];
		Double dst = -1; P curr;
		auto update = [&](P q) {
			Double _d = dist(p, q);
			if(dst == -1 || dst > _d) 
				dst = _d, curr = q;
		};
		for(const P &q : vec) update(q);
		return {dst, curr};
	}
};

template<size_t L, size_t K>
struct NearestPoints {
	vector<PointHashing<L>> ph;
	NearestPoints() : ph(K) {}
	void add(P p) {
		for(auto &h : ph)
			h.add(p);
	}
	P query(P p) {
		Double dst = -1; P curr;
		for(auto &h : ph) {
			Double _d; P q;
			tie(_d, q) = h.query(p);
			if(_d == -1) continue;
			if(dst == -1 || dst > _d)
				dst = _d, curr = q;	
		}
		assert(dst != -1);
		return curr;
	}
};
