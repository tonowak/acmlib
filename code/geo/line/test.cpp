#include "../../utils/headers/main.cpp"
#include "main.cpp"

int main() { 
	P a, b;
	cin >> a >> b;
	Line l(a, b);
	debug(l.A * a.x + l.B * a.y + l.C);
	debug(l.A * b.x + l.B * b.y + l.C);
	debug(l.get_pts());
	debug(l.get_dir());
}
