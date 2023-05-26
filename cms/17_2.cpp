#include <bits/extc++.h>
#define endl '\n'
#define int long long
using namespace std;
int len;
const int sz = 1e3;
vector<int> prime;
vector<bool> not_prime;
vector<int> aw, a, w;
int n, k, q;
const int mod = 1e9 + 7;
void set_up() {
	not_prime.resize(sz + 1, false);
	not_prime[0] = not_prime[1] = true;
	for (int s = 2; s <= sz; s++) {
		if (!not_prime[s]) prime.push_back(s);
		for (int p : prime) {
			if (s * p > sz) break;
			not_prime[s * p] = true;
			if (s % p == 0) break;
		}
	}
	len = prime.size();
	return;
}
int _plus(int x, int y) {
	return (x + y) % mod;
}
int _minus(int x, int y) {
	return (mod + x - y) % mod;
}
int _multiply(int x, int y) {
	return x * y % mod;
}
int _pow(int x, int y) {
	int ans = 1;
	for (int s = 1; s <= y; s <<= 1, x = _multiply(x, x)) {
		if (s & y) ans = _multiply(ans, x);
	}
	return ans;
}
pair<int, int> count(int v) {
	pair<int, int> ans = {0, 1};
	int sum, temp;
	for (const int &p : prime) {
		if (p * p > v) break;
		if (v % p) continue;
		sum = 1;
		temp = _pow(p, k);
		for (sum = 1; v % p == 0; v /= p)
			sum = _plus(_multiply(sum, temp), 1);
		ans.first = _plus(ans.first, 1);
		ans.second = _multiply(ans.second, sum);
	}
	if (v > 1) {
		ans.first = _plus(ans.first, 1);
		ans.second = _multiply(ans.second, _plus(_pow(v, k), 1));
	}
	return ans;
}
int query(int l, int r) {
	int ans = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1) ans = _plus(ans, aw[l++]);
		if (r & 1) ans = _plus(ans, aw[--r]);
	}
	return ans;
}
void modify(int p, int t) {
	pair<int, int> temp = count(t);
	w[p] = _plus(w[p], temp.first);
	a[p] = _multiply(a[p], temp.second);
	for (aw[p += n] = _multiply(w[p], a[p]); p > 1; p >>= 1) {
		aw[p >> 1] = _plus(aw[p], aw[p ^ 1]);
	}
	return;
}
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	set_up();
	cin >> n >> q >> k;
	pair<int, int> c;
	w.resize(n, 0), a.resize(n, 0), aw.resize(n << 1, 0);
	for (int s = 0, temp; s < n; s++) {
		cin >> temp;
		c = count(temp);
		w[s] = c.first;
		a[s] = c.second;
		aw[s + n] = _multiply(w[s], a[s]);
	}
	for (int s = n - 1; s >= 1; s--) aw[s] = _plus(aw[s << 1], aw[s << 1 | 1]);
	for (int type, l, r; q--;) {
		cin >> type >> l >> r;
		l--;
		if (type == 0) cout << query(l, r) << endl;
		if (type == 1) modify(l, r);
	}
}