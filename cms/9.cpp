#include <bits/extc++.h>

using namespace std;
const int mod = 1e9 + 7;

inline int power(int x, int y) {
	long long ans = 1, base = x;
	for (int s = 1; s <= y; s <<= 1, base = base * base % mod)
		if (s & y) ans = base * ans % mod;
	return ans;
}
inline int times(int x, int y) {
	return (long long)x * y % mod;
}
inline int divide(int x, int y) {
	return times(x, power(y, mod - 2));
}
const int len = 1e6;
vector<int> o(len + 1);

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	o[0] = o[1] = 1;
	for (int s = 2; s <= len; s++) o[s] = times(o[s - 1], s);
	int q;
	cin >> q;
	for (int a, b; q--;) {
		cin >> b >> a;
		// cout << o[a + 1 - b] << " " << o[a - b + 1 - b] << endl;
		if (a + 1 - b - b < 0) cout << "0\n";
		else cout << divide(o[a + 1 - b], o[a - b + 1 - b]) << "\n";
	}
}