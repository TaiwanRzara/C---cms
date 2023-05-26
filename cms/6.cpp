#include <bits/extc++.h>
using namespace std;
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	int Max = 0;
	vector<int> p(n), c(m);
	for (int &i : p) cin >> i, Max = max(i, Max);
	for (int &i : c) cin >> i;
	vector<int> dp(Max + 1, 0);
	for (int coin : c) {
		for (int s = Max; s > coin; s--) {
			if (dp[s - coin]) dp[s] = max(dp[s], dp[s - coin] + 1);
		}
		dp[coin] = max(1, dp[coin]);
	}
	Max = 0;
	for (int s = 0; s < n; s++) {
		if (dp[p[s]] > dp[p[Max]]) Max = s;
	}
	if (!dp[p[Max]]) cout << -1;
	else cout << Max + 1 << " " << dp[p[Max]];
}