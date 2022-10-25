/*
 * Opis: Trzeba wywołać pod koniec main'a.
 */

#ifdef LOCAL
system("grep VmPeak /proc/$PPID/status");
#endif

