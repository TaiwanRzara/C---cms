#include <bits/extc++.h>
#define int long long
using namespace std;
int pow10(int n) {
	int ans = 1;
	for (int base = 10, s = 1; s <= n; s <<= 1, base *= base) {
		if (s & n) ans *= base;
	}
	return ans;
}
signed main() {
	int a, b;
	string w;
	char u;
	cin >> a >> u >> w;
	// if (u != '.') _sleep(10000);
	int _10 = pow10(w.size()) - 1;
	b = stoi(w);
	if (!b) {
		cout << a << "/1";
		return 0;
	}
	// cout << a << " " << b << " " << _10 << endl;
	a = a * _10 + b;
	b = _10;
	int gcd = __gcd(a, b);
	a /= gcd, b /= gcd;
	cout << a << "/" << b;
	return 0;
}
