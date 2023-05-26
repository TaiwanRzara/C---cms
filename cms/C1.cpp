#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> uv, u, v, u2, v2;
vector<int> tag_u, tag_v;
int n;
const int mod = 1e9 + 7;
inline int add(int &a, int b) {
	a += b;
	if (a >= mod) a %= mod;
	return a;
}
inline int times(int a, int b) {
	a *= b;
	if (a >= mod) a %= mod;
	return a;
}
inline int pow(int x, int y) {
	int ans = 1;
	for (int s = 1; s <= y; s <<= 1, x = times(x, x))
		if (s & y) ans = times(ans, x);
	return ans;
}
inline int divide(int x, int y) {
	return times(x, pow(y, mod - 2));
}
void modify_u(int l, int r, int du, int it = 1, int L = 0, int R = n) {
	if (l == L && r == R) {
		add(uv[it], times(v[it], du));
		add(u2[it], times(u[it], times(du, 2))), add(u2[it], times(r - l, times(du, du)));
		add(u[it], times(du, r - l));
		if (r - l > 1) add(tag_u[it], du);
		return;
	}
	int M = L + R >> 1, itl = it << 1, itr = it << 1 | 1;
	if (tag_u[it]) {
		add(uv[itl], times(v[itl], tag_u[it]));
		add(u2[itl], times(u[itl], times(tag_u[it], 2))), add(u2[itl], times(M - L, times(tag_u[it], tag_u[it])));
		add(u[itl], times(tag_u[it], M - L));
		if (M - L > 1) add(tag_u[itl], tag_u[it]);
		add(uv[itr], times(v[itr], tag_u[it]));
		add(u2[itr], times(u[itr], times(tag_u[it], 2))), add(u2[itr], times(R - M, times(tag_u[it], tag_u[it])));
		add(u[itr], times(tag_u[it], R - M));
		if (R - M > 1) add(tag_u[itr], tag_u[it]);
		tag_u[it] = 0;
	}
	if (tag_v[it]) {
		add(uv[itl], times(u[itl], tag_v[it]));
		add(v2[itl], times(v[itl], times(tag_v[it], 2))), add(v2[itl], times(M - L, times(tag_v[it], tag_v[it])));
		add(v[itl], times(tag_v[it], M - L));
		if (M - L > 1) add(tag_v[itl], tag_v[it]);
		add(uv[itr], times(u[itr], tag_v[it]));
		add(v2[itr], times(v[itr], times(tag_v[it], 2))), add(v2[itr], times(R - M, times(tag_v[it], tag_v[it])));
		add(v[itr], times(tag_v[it], R - M));
		if (R - M > 1) add(tag_v[itr], tag_v[it]);
		tag_v[it] = 0;
	}
	if (r <= M) modify_u(l, r, du, itl, L, M);
	else if (l >= M) modify_u(l, r, du, itr, M, R);
	else modify_u(l, M, du, itl, L, M), modify_u(M, r, du, itr, M, R);
	if (R - L == 1) return;
	u[it] = v[it] = uv[it] = u2[it] = v2[it] = 0;
	add(u[it], u[itl]), add(u[it], u[itr]);
	add(v[it], v[itl]), add(v[it], v[itr]);
	add(u2[it], u2[itl]), add(u2[it], u2[itr]);
	add(v2[it], v2[itl]), add(v2[it], v2[itr]);
	add(uv[it], uv[itl]), add(uv[it], uv[itr]);
	return;
}

void modify_v(int l, int r, int dv, int it = 1, int L = 0, int R = n) {
	if (l == L && r == R) {
		add(uv[it], times(u[it], dv));
		add(v2[it], times(v[it], times(dv, 2))), add(v2[it], times(r - l, times(dv, dv)));
		add(v[it], times(dv, r - l));
		if (r - l > 1) add(tag_v[it], dv);
		return;
	}
	int M = L + R >> 1, itl = it << 1, itr = it << 1 | 1;
	if (tag_u[it]) {
		add(uv[itl], times(v[itl], tag_u[it]));
		add(u2[itl], times(u[itl], times(tag_u[it], 2))), add(u2[itl], times(M - L, times(tag_u[it], tag_u[it])));
		add(u[itl], times(tag_u[it], M - L));
		if (M - L > 1) add(tag_u[itl], tag_u[it]);
		add(uv[itr], times(v[itr], tag_u[it]));
		add(u2[itr], times(u[itr], times(tag_u[it], 2))), add(u2[itr], times(R - M, times(tag_u[it], tag_u[it])));
		add(u[itr], times(tag_u[it], R - M));
		if (R - M > 1) add(tag_u[itr], tag_u[it]);
		tag_u[it] = 0;
	}
	if (tag_v[it]) {
		add(uv[itl], times(u[itl], tag_v[it]));
		add(v2[itl], times(v[itl], times(tag_v[it], 2))), add(v2[itl], times(M - L, times(tag_v[it], tag_v[it])));
		add(v[itl], times(tag_v[it], M - L));
		if (M - L > 1) add(tag_v[itl], tag_v[it]);
		add(uv[itr], times(u[itr], tag_v[it]));
		add(v2[itr], times(v[itr], times(tag_v[it], 2))), add(v2[itr], times(R - M, times(tag_v[it], tag_v[it])));
		add(v[itr], times(tag_v[it], R - M));
		if (R - M > 1) add(tag_v[itr], tag_v[it]);
		tag_v[it] = 0;
	}
	if (r <= M) modify_v(l, r, dv, itl, L, M);
	else if (l >= M) modify_v(l, r, dv, itr, M, R);
	else modify_v(l, M, dv, itl, L, M), modify_v(M, r, dv, itr, M, R);
	if (R - L == 1) return;
	u[it] = v[it] = uv[it] = u2[it] = v2[it] = 0;
	add(u[it], u[itl]), add(u[it], u[itr]);
	add(v[it], v[itl]), add(v[it], v[itr]);
	add(u2[it], u2[itl]), add(u2[it], u2[itr]);
	add(v2[it], v2[itl]), add(v2[it], v2[itr]);
	add(uv[it], uv[itl]), add(uv[it], uv[itr]);
	return;
}
int query() {
	return times(times(uv[1], uv[1]), times(v2[1], u2[1]));
}
signed main() {
	cin >> n;
	uv.resize(n << 2, 0), u.resize(n << 2, 0), v.resize(n << 2, 0), u2.resize(n << 2, 0), v2.resize(n << 2, 0), tag_u.resize(n << 2, 0), tag_v.resize(n << 2, 0);
	char t = 'z';
	for (int l, r, d; cin >> t;) {
		if (t == '?') {
			cout << query() << endl;
			continue;
		}
		cin >> l >> r >> d;
		l--;
		add(d, mod);
		if (t == 'g') modify_u(l, r, d);
		if (t == 's') modify_v(l, r, d);
	}
}
