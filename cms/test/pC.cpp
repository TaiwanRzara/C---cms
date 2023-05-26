#include <bits/extc++.h>
using namespace std;
int main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> st(n << 1);
	for (int s = n, n2 = n << 1; s < n2; s++) cin >> st[s];
	for (int s = n; --s;) st[s] = max(st[s << 1], st[s << 1 | 1]);
	for (int l, r, ans = 0; q--; ans = 0) {
		cin >> l >> r;
		for (l += n - 1, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, st[l++]);
			if (r & 1) ans = max(ans, st[--r]);
		}
		cout << ans << "\n";
	}
}