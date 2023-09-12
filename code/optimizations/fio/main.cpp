/*
 * Opis: FIO do wpychania kolanem. Nie należy wtedy używać cin/cout
 */
#ifdef ONLINE_JUDGE
// write this when judge is on Windows
inline int getchar_unlocked() { return _getchar_nolock(); }
inline void putchar_unlocked(char c) { _putchar_nolock(c); }
#endif
int fastin() {
	int n = 0, c = getchar_unlocked();
	while(isspace(c))
		c = getchar_unlocked();
	while(isdigit(c)) {
		n = 10 * n + (c - '0');
		c = getchar_unlocked();
	}
	return n;
}
int fastin_negative() {
	int n = 0, negative = false, c = getchar_unlocked();
	while(isspace(c))
		c = getchar_unlocked();
	if(c == '-') {
		negative = true;
		c = getchar_unlocked();
	}
	while(isdigit(c)) {
		n = 10 * n + (c - '0');
		c = getchar_unlocked();
	}
	return negative ? -n : n;
}
double fastin_double() {
	double x = 0, t = 1;
	int negative = false, c = getchar_unlocked();
	while(isspace(c))
		c = getchar_unlocked();
	if (c == '-') {
		negative = true;
		c = getchar_unlocked();
	}
	while (isdigit(c)) {
		x = x * 10 + (c - '0');
		c = getchar_unlocked();
	}
	if (c == '.') {
		c = getchar_unlocked();
		while (isdigit(c)) {
			t /= 10;
			x = x + t * (c - '0');
			c = getchar_unlocked();
		}
	}
	return negative ? -x : x;
}
void fastout(int x) {
	if(x == 0) {
		putchar_unlocked('0');
		putchar_unlocked(' ');
		return;
	}
	if(x < 0) {
		putchar_unlocked('-');
		x *= -1;
	}
	static char t[10];
	int i = 0;
	while(x) {
		t[i++] = char('0' + (x % 10));
		x /= 10;
	}
	while(--i >= 0)
		putchar_unlocked(t[i]);
	putchar_unlocked(' ');
}
void nl() { putchar_unlocked('\n'); }
