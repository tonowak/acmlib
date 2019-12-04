/*
 * Opis: szybsza mapa
 * Czas: O(1)
 * Użycie:
 * np hash_map<int, int>
 * trzeba przed includem dać undef _GLIBCXX_DEBUG
 */

#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
	const uint64_t C = LL(2e18 * M_PI) + 69;
	const int RANDOM = rng();
	size_t operator()(uint64_t x) const {
		return __builtin_bswap64((x^RANDOM) * C);
	}
};
template<class L, class R> 
using hash_map = gp_hash_table<L, R, chash>;
