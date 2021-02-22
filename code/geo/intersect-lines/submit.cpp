#include "../../utils/headers/main.cpp"
#include "main.cpp"

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	cout << fixed << setprecision(2);
	while(t --> 0) {
		P p1, p2, p3, p4;
		cin >> p1 >> p2 >> p3 >> p4;
		auto v = intersect(p1, p2, p3, p4, true);
		auto print = [&](P p) {
			cout << p.x + eps << ' ' << p.y + eps << ' ';
		};
		if(size(v) == 0)
			cout << "none\n";
		else if(size(v) == 1) {
			print(v[0]);
			cout << '\n';
		}
		else if(size(v) == 2) {
			print(v[0]);
			print(v[1]);
			cout << '\n';
		}
	}
}

