#include <bits/extc++.h>
using namespace std;
vector<vector<int>> edge;
vector<int> depth, rate;
int r;
int dfs(int p) {
	if (edge[p].size() == 1 && p != 0) return p;
	int temp, d = 0;
	for (int e : edge[p]) {
		if (depth[e] != -1) continue;
		depth[e] = depth[p] + 1;
		temp = dfs(e);
		if (depth[temp] > depth[d]) d = temp;
	}
	return d;
}
int dfs2(int p, int d2) {
	if (edge[p].size() == 1) {
		rate[p] = r - d2;
		return rate[p];
	}
	for (int e : edge[p]) {
		if (depth[e] != depth[p] + 1) continue;
		rate[e] = r - d2 - 1;
		rate[p] += dfs2(e, d2 + 1);
	}
	return rate[p];
}
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n, np;
	cin >> n;
	edge.resize(n), depth.resize(n, -1), rate.resize(n, 0);
	for (int s = n, l, r; --s;) cin >> l >> r, edge[l].push_back(r), edge[r].push_back(l);
	int Max[2] = {0, 0}, temp;
	depth[0] = 0;
	for (auto &e : edge[0]) {
		depth[e] = 1;
		temp = dfs(e);
		if (depth[temp] > depth[Max[0]]) Max[1] = Max[0], Max[0] = temp;
		else if (depth[temp] > depth[Max[1]]) Max[1] = temp;
	}
	r = depth[Max[0]] + depth[Max[1]] + 1;
	// back;
	rate[0] = r;
	for (auto p : Max) {
		if (p) rate[p] = r;
		np = 0;
		for (; p;) {
			for (auto e : edge[p]) {
				if (e == 0) np = e;
				else if (rate[e]) continue;
				else if (depth[e] != depth[p] - 1) {
					rate[e] = r - 1;
					rate[p] += dfs2(e, 1);
				} else np = e;
			}
			if (np) rate[np] += rate[p] + r;
			else rate[np] += rate[p];
			p = np;
		}
	}
	for (auto e : edge[0]) {
		if (!rate[e]) {
			rate[e] = r - 1;
			rate[0] += dfs2(e, 1);
		}
	}
	for (auto i : rate) cout << i << "\n";
}