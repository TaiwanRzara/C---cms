#include <bits/extc++.h>
using namespace std;
const int value[26] = {0, 0, 0, 4, 0, 2, 0, 0, 0, 0, 0, 0, 3, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const string str[6] = {"-1", "Ocean", "Forest", "Mountain", "Desert", "Plain"};
signed main() {
	int m, n, X, Y, h, ans = 0;
	char temp;
	cin >> n >> m;
	vector<vector<int>> graph(n, vector<int>(m)), height(n, vector<int>(m));
	vector<vector<vector<bool>>> ava(2, vector<vector<bool>>(n, vector<bool>(m)));
	for (int y = 0; y < m; y++)
		for (int x = 0; x < n; x++) cin >> temp, graph[x][y] = value[temp - 'A'];
	for (int y = 0; y < m; y++)
		for (int x = 0; x < n; x++) cin >> height[x][y];
	cin >> X >> Y >> h;
	bool b = true;
	ava[0][X - 1][Y - 1] = true;
	if (height[X - 1][Y - 1] == h) {
		cout << str[graph[X - 1][Y - 1]] << endl;
		return 0;
	}
	if (height[X - 1][Y - 1] > h) {
		cout << str[0] << endl;
		return 0;
	}
	for (int t = 1, a = h - 5 * t * t; b && a >= 0; t++, a = h - 5 * t * t) {
		b = false;
		for (auto &row : ava[t & 1]) fill(row.begin(), row.end(), false);
		for (int y = 0; y < m; y++)
			for (int x = 0; x < n; x++) {
				if (height[x][y] > a) continue;
				if (x)
					if (ava[t + 1 & 1][x - 1][y]) {
						ava[t & 1][x][y] = true;
						b = true;
						if (a == height[x][y]) ans = max(ans, graph[x][y]), ava[t & 1][x][y] = false;
						continue;
					}
				if (y)
					if (ava[t + 1 & 1][x][y - 1]) {
						ava[t & 1][x][y] = true;
						b = true;
						if (a == height[x][y]) ans = max(ans, graph[x][y]), ava[t & 1][x][y] = false;
						continue;
					}
				if (x < n - 1)
					if (ava[t + 1 & 1][x + 1][y]) {
						ava[t & 1][x][y] = true;
						b = true;
						if (a == height[x][y]) ans = max(ans, graph[x][y]), ava[t & 1][x][y] = false;
						continue;
					}
				if (y < m - 1)
					if (ava[t + 1 & 1][x][y + 1]) {
						ava[t & 1][x][y] = true;
						b = true;
						if (a == height[x][y]) ans = max(ans, graph[x][y]), ava[t & 1][x][y] = false;
						continue;
					}
			}
	}
	cout << str[ans] << endl;
}