/*
 * Opis: FIO do wpychania kolanem. Nie należy wtedy używać cin/cout
 */

#ifdef WIN32
inline int getchar_unlocked() { return _getchar_nolock(); }
inline void putchar_unlocked(char c) { return _putchar_nolock(c); }
#endif

int fastin() {
	int n = 0, c = getchar_unlocked();
	while(c < '0' or '9' < c)
		c = getchar_unlocked();
	while('0' <= c and c <= '9') {
		n = 10 * n + (c - '0');
		c = getchar_unlocked();
	}
	return n;
}

int fastin_negative() {
	int n = 0, negative = false, c = getchar_unlocked();
	while(c != '-' and (c < '0' or '9' < c))
		c = getchar_unlocked();
	if(c == '-') {
		negative = true;
		c = getchar_unlocked();
	}
	while('0' <= c and c <= '9') {
		n = 10 * n + (c - '0');
		c = getchar_unlocked();
	}
	return negative ? -n : n;
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
