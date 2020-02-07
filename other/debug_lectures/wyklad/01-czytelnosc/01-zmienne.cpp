struct NajdluzszyCiag
{
	int dlugosc_najdluzszego_ciagu, dlugosc_od_lewej, dlugosc_od_prawej, calkowita_dlugosc_ciagu;
	char poczatek, koniec;

	NajdluzszyCiag(char poczatek = '-', char koniec = '-', int calkowita_dlugosc_ciagu = 0)
	{
		this->poczatek = poczatek;
		this->koniec = koniec;
		this->calkowita_dlugosc_ciagu = calkowita_dlugosc_ciagu;
		this->dlugosc_od_lewej = calkowita_dlugosc_ciagu;
		this->dlugosc_od_prawej = calkowita_dlugosc_ciagu;
		this->dlugosc_najdluzszego_ciagu = calkowita_dlugosc_ciagu;
	}

	NajdluzszyCiag(NajdluzszyCiag &c)
	{
		poczatek = c.poczatek;
		koniec = c.koniec;
		calkowita_dlugosc_ciagu = c.calkowita_dlugosc_ciagu;
		dlugosc_najdluzszego_ciagu = c.dlugosc_najdluzszego_ciagu;
		dlugosc_od_lewej = c.dlugosc_od_lewej;
		dlugosc_od_prawej = c.dlugosc_od_prawej;
	}

	NajdluzszyCiag& operator=(const NajdluzszyCiag &a)
	{
		poczatek = a.poczatek;
		koniec = a.koniec;
		calkowita_dlugosc_ciagu = a.calkowita_dlugosc_ciagu;
		dlugosc_od_lewej = a.dlugosc_od_lewej;
		dlugosc_od_prawej = a.dlugosc_od_prawej;
		dlugosc_najdluzszego_ciagu = a.dlugosc_najdluzszego_ciagu;
		return *this;
	}

	void wyswietl()
	{
		cout << endl << "	p " << poczatek << " k " << koniec << " czego " << endl;
		cout << "	" << calkowita_dlugosc_ciagu << ": " << dlugosc_najdluzszego_ciagu << " L " << dlugosc_od_lewej << " R " << dlugosc_od_prawej << endl;
	}
};

NajdluzszyCiag operator+(const NajdluzszyCiag &a1, const NajdluzszyCiag &a2)
{
	NajdluzszyCiag wynik(a1.poczatek, a2.koniec, a1.calkowita_dlugosc_ciagu + a2.calkowita_dlugosc_ciagu);
	wynik.dlugosc_najdluzszego_ciagu = max(a1.dlugosc_najdluzszego_ciagu, a2.dlugosc_najdluzszego_ciagu);
	wynik.dlugosc_od_lewej = a1.dlugosc_od_lewej;
	wynik.dlugosc_od_prawej = a2.dlugosc_od_prawej;
	if(a2.poczatek == '-')
		wynik.dlugosc_od_prawej = a1.dlugosc_od_prawej;
	if (a1.koniec == a2.poczatek && a1.koniec == 'A')
	{
		wynik.dlugosc_najdluzszego_ciagu = max(wynik.dlugosc_najdluzszego_ciagu, a1.dlugosc_od_prawej + a2.dlugosc_od_lewej);
		if (a1.dlugosc_od_lewej == a1.calkowita_dlugosc_ciagu)
			wynik.dlugosc_od_lewej = a1.calkowita_dlugosc_ciagu + a2.dlugosc_od_lewej;
		if (a2.dlugosc_od_prawej == a2.calkowita_dlugosc_ciagu)
			wynik.dlugosc_od_prawej = a2.calkowita_dlugosc_ciagu + a1.dlugosc_od_prawej;
	}
	return wynik;
}
