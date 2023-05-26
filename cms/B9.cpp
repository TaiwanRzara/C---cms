#include <bits/extc++.h>
#define int long long
using namespace std;
int mod;
struct mat {
	vector<vector<int>> G;
	int n;
	mat(int _n, int cross = 1) {
		n = _n;
		G.resize(n, vector<int>(n, 0));
		for (; _n--;) {
			G[_n][_n] = cross;
		}
	}
};
mat operator*(const mat &m1, const mat &m2) {
	assert(m1.n == m2.n);
	mat ans(m1.n, 0);
	for (int i = 0; i < m1.n; i++) {
		for (int j = 0; j < m1.n; j++) {
			for (int k = 0; k < m1.n; k++) {
				if (m1.G[i][k] && m2.G[k][j]) {
					ans.G[i][j] += m1.G[i][k] * m2.G[k][j];
					if (ans.G[i][j] >= mod) ans.G[i][j] %= mod;
				}
			}
		}
	}
	return ans;
}
mat pow(mat x, int y) {
	mat ans(x.n);
	for (int s = 1; s <= y; s <<= 1, x = x * x)
		if (s & y) ans = ans * x;
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int x, y, n;
	cin >> x >> y >> n >> mod;
	mat A(x, 0), M(x, 0);
	for (int a, b, k; y--;) {
		cin >> a >> b >> k;
		A.G[b][a] += k;
	}
	for (int s = 0; s < x; s++) {
		cin >> M.G[s][0];
	}
	A = pow(A, n);
	A = A * M;
	for (int s = 0; s < x; s++) cout << A.G[s][0] << "\n";
}
