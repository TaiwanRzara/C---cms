#include <bits/extc++.h>
using namespace std;
int mod = 1e9 + 7;
signed main() {
	int n, m, sum = 1;
	cin >> n >> m;
	vector<pair<int, int>> o(n);
	for (pair<int, int> &p : o) cin >> p.first >> p.second;
	sort(o.begin(), o.end());
	for (int s = 0, r = mod; s < n; s++) {
		if (o[s].first > r) sum++, r = mod;
		r = min(o[s].second, r);
	}
	if (sum > m) cout << ":(";
	else cout << ":)";
}