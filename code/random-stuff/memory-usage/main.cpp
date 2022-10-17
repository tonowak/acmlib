/*
 * Opis: Wypisuje zużycie pamięci programu (trzeba wywołać to pod koniec maina)
 */

#ifdef LOCAL
system("grep VmPeak /proc/$PPID/status");
#endif
