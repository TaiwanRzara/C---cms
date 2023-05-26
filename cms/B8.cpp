#include <bits/extc++.h>
using namespace std;
const int mod = 1e9 + 7;
int n, m, s, t, T;
int __lg10(int n) {
	int s = 0;
	for (; n; n /= 10, s++)
		;
	return s;
}
void print(int n, int len) {
	int l = __lg10(n);
	for (; l++ < len;) putchar('0');
	if (n) printf("%d", n);
}
signed main() {
	int sum = 0;
	pair<int, int> p;
	cin >> n >> m >> s >> t;
	vector<int> cost(n, mod);
	vector<vector<pair<int, int>>> edges(n);
	queue<int> update;
	vector<bool> updating(n, false);
	for (int s = 0, u, v, c; s < m; s++) cin >> u >> v >> c, edges[u].push_back({v, c});
	updating[0] = true;
	update.push(s);
	cost[s] = 0;
	for (; !update.empty(); updating[update.front()] = false, update.pop()) {
		for (pair<int, int> e : edges[update.front()]) {
			if (cost[e.first] > cost[update.front()] + e.second) {
				cost[e.first] = cost[update.front()] + e.second;
				if (updating[e.first] || e.first == t) continue;
				update.push(e.first);
				updating[e.first] = true;
			}
		}
	}
	sum = cost[t];
	fill(cost.begin(), cost.end(), mod);
	cost[t] = 0;
	update.push(t), updating[t] = true;
	for (; !update.empty(); updating[update.front()] = false, update.pop()) {
		for (pair<int, int> e : edges[update.front()]) {
			if (cost[e.first] > cost[update.front()] + e.second) {
				cost[e.first] = cost[update.front()] + e.second;
				if (updating[e.first] || e.first == s) continue;
				update.push(e.first);
				updating[e.first] = true;
			}
		}
	}
	sum += cost[s];
	sum /= 60;
	if (sum > 3600) cout << "So many sleepless nights where you were waiting up on me." << endl;
	else print(sum / 60, 2), putchar(':'), print(sum % 60, 2);
}
/*
5 9 0 4
0 1 1
0 2 4
1 2 2
2 3 8
3 0 16
3 4 32
4 1 18
4 2 13
4 0 64

*/
