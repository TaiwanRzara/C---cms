#include <bits/extc++.h>
#define int long long
using namespace std;
const int inf = 1e17;
signed main() {
	string A, B;
	int a, b, c;
	cin >> A >> B >> a >> b >> c;
	int sza = A.size(), szb = B.size();
	vector<vector<vector<int>>> dp(2, vector<vector<int>>(sza + 1, vector<int>(szb + 1, inf)));
	dp[0][0][0] = sza * c;
	for (int s = 1; s < szb; s++) dp[1][0][s] = a + b * s + dp[0][0][0];
	// 0 alphabet 1:-
	for (int y = 1; y <= szb; y++) {
		for (int x = 1; x <= sza && x <= y; x++) {
			dp[0][x][y] = min(dp[0][x - 1][y - 1] - ((A[x - 1] == B[y - 1]) ? c : 0), dp[1][x - 1][y - 1] - ((A[x - 1] == B[y - 1]) ? c : 0));
			dp[1][x][y] = min(dp[0][x][y - 1] + a + b, (x && dp[1][x][y - 1] != inf) ? (dp[1][x][y - 1] + b) : inf);
		}
	}
	cout << min(dp[0][sza][szb], dp[1][sza][szb]) << endl;
}
