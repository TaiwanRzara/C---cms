#include <bits/extc++.h>
#define int long long
using namespace std;
const int mod = 2e5;
// AC
signed main() {
	int n;
	cin >> n;
	vector<int> val(n), dp(n);
	for (int &i : val) cin >> i, i = (i < 0) ? 0 : i;
	if (n == 1) {
		cout << val[0] << endl;
		return 0;
	}
	dp[0] = val[0], dp[1] = max(val[0], val[1]);
	for (int s = 2; s < n; s++) {
		dp[s] = max(dp[s - 2] + val[s], dp[s - 1]);
	}
	cout << max(dp[n - 1], dp[n - 2]);
}
