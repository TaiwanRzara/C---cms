#include <bits/extc++.h>
#define int long long
using namespace std;
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n, k, sum = 0;
	cin >> n >> k;
	vector<int> a(n + 1, 0);
	for (int s = 1; s <= n; s++) cin >> a[s], a[s] += a[s - 1];
	for (int r = 1, l = 0; r <= n; r++) {
		for (; a[r] - a[l] > k; l++)
			;
		sum += r - l;
	}
	cout << sum << endl;
}
