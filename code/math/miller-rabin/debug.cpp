#include "../../utils/main_test.cpp"
#include "main.cpp"

int main()
{
	LL n;
	cin >> n;
	cout << miller_rabin(n) << "\n";
}
