#include <bits/stdc++.h>

#define int long long
using namespace std;
const int mod = 1e9 + 7;
const int div2 = 500000004;
inline int lg_sz(int p, int n) {
	return __lg(n) - __lg(p) + ((p << __lg(n) - __lg(p)) < n);
}
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

struct s_tree {
	struct delta {
		int u, v;
		delta()
			: u(0), v(0){};
		delta(int u, int v)
			: u(u), v(v){};
		inline bool operator!() {
			return u == 0 && v == 0;
		}
		inline delta operator+=(delta d) {
			add(u, d.u), add(v, d.v);
			return *this;
		}
	};
	struct object {
		int u, v, u2, v2, uv;
		object(int u = 0, int v = 0)
			: u(u), v(v), u2(times(u, u)), v2(times(v, v)), uv(times(u, v)){};
		object operator+(object o) {
			add(o.u, u), add(o.v, v), add(o.u2, u2), add(o.v2, v2), add(o.uv, uv);
			return o;
		}
		inline void addu(int d, int sz) {
			add(uv, times(v, d));
			add(u2, times(u, d << 1)), add(u2, times(d << sz, d));
			add(u, times(d, 1 << sz));
		}
		inline void addv(int d, int sz) {
			add(uv, times(u, d));
			add(v2, times(v, d << 1)), add(v2, times(d << sz, d));
			add(v, times(d, 1 << sz));
		}
		inline object addd(delta d, int sz) {
			object o = *this;
			o.addu(d.u, sz);
			o.addv(d.v, sz);
			return o;
		}
	};
	vector<object> st;
	vector<delta> tag;
	int n;
	s_tree(int N) {
		n = N;
		st.resize(n << 1 | 7);
		tag.resize(n | 7);
	}
	inline void updu(int p, int d) {
		st[p].addu(d, lg_sz(p, n));
		if (p < n) tag[p].u += d;
	}
	inline void updv(int p, int d) {
		st[p].addv(d, lg_sz(p, n));
		if (p < n) tag[p].v += d;
	}
	inline void pushv(int p) {
		for (int h = __lg(n), i = p >> h; h >= 0; i = p >> --h) {
			if (!tag[i >> 1].v) continue;
			updv(i, tag[i >> 1].v);
			updv(i ^ 1, tag[i >> 1].v);
			tag[i >> 1].v = 0;
		}
	}
	inline void pushu(int p) {
		for (int h = __lg(n), i = p >> h; h >= 0; i = p >> --h) {
			if (!tag[i >> 1].u) continue;
			updu(i, tag[i >> 1].u);
			updu(i ^ 1, tag[i >> 1].u);
			tag[i >> 1].u = 0;
		}
	}
	void pull(int p) {
		int sz = lg_sz(p, n);
		for (p >>= 1; p > 0; p >>= 1, sz--) {
			st[p] = st[p << 1].addd(tag[p], sz) + st[p << 1 | 1].addd(tag[p], sz);
		}
	}
	inline void modifyv(int l, int r, int d) {
		pushu(l += n), pushu(r += n - 1);
		pushv(l), pushv(r);
		int l2 = l, r2 = r;
		for (r++; l < r; l >>= 1, r >>= 1) {
			if (l & 1) updv(l++, d);
			if (r & 1) updv(--r, d);
		}
		pull(l2), pull(r2);
	}
	inline void modifyu(int l, int r, int d) {
		pushv(l += n), pushv(r += n - 1);
		pushu(l), pushu(r);
		int l2 = l, r2 = r;
		for (r++; l < r; l >>= 1, r >>= 1) {
			if (l & 1) updu(l++, d);
			if (r & 1) updu(--r, d);
		}
		pull(l2), pull(r2);
	}
	inline int query(int l, int r) {
		pushv(l += n), pushv(r += n - 1);
		pushu(l), pushu(r);
		int uv = 0, u2 = 0, v2 = 0;
		for (r++; l < r; l >>= 1, r >>= 1) {
			if (l & 1) add(uv, st[l].uv), add(u2, st[l].u2), add(v2, st[l++].v2);
			if (r & 1) add(uv, st[--r].uv), add(u2, st[r].u2), add(v2, st[r].v2);
		}
		return times(times(uv, uv), times(u2, v2));
	}
};
signed main() {
	int n;
	cin >> n;
	s_tree vec(n);
	char t = 'Z';
	for (int l, r, d; cin >> t;) {
		if (t == '?') {
			cout << vec.query(0, n) << endl;
			continue;
		}
		if (t == 'e') break;
		cin >> l >> r >> d;
		add(d, mod);
		if (t == 'g') vec.modifyu(l - 1, r, d);
		if (t == 's') vec.modifyv(l - 1, r, d);
	}
}