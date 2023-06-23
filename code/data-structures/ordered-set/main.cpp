/*
 * Opis:
 *   \texttt{insert(x)} dodaje element $x$ (nie ma emplace),
 *   \texttt{find\_by\_order(i)} zwraca iterator do $i$-tego elementu,
 *   \texttt{order\_of\_key(x)} zwraca ile jest mniejszych elementów
 *   ($x$ nie musi być w secie).
 *   Jeśli chcemy multiseta, to używamy par $(val, id)$.
 *   Przed includem trzeba dać \texttt{undef \_GLIBCXX\_DEBUG}.
 */

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<
	T,
	null_type,
	less<T>,
	rb_tree_tag,
	tree_order_statistics_node_update
>;

