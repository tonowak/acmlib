// Rozszerzony Algorytm Euklidesa
// Status : Przetestowany
// a*x + b*y = gcd(a, b)

LL extended_gcd(LL a, LL b, LL &x, LL &y)
{
	if(a == 0)
	{
		x = 0, y = 1;
		return b;
	}
	
	LL _x, _y;
	LL gcd = extended_gcd(b % a, a, _x, _y);
	x = _y - (b / a) * _x;
	y = _x;

	return gcd;
}
