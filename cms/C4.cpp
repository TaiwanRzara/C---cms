#include <bits/extc++.h>
#define int long long
using namespace std;
struct edge {
	int a, b, w;
	void reverse(void) {
		swap(a, b);
	}
};
bool operator>(const edge &e, const edge &_e) {
	return e.w > _e.w;
}
bool cmp(const edge &e, const edge &_e) {
	return e.w < _e.w;
}
istream &operator>>(istream &s, edge &e) {
	s >> e.a >> e.b >> e.w;
	e.a--, e.b--;
	return s;
}
vector<set<int>> last;
vector<int> itf, dis;
vector<vector<edge>> graph, tr;
vector<bool> visited;
void press(int p) {
	if (visited[p]) return;
	itf[p] = dis.size();
	last[p].insert(dis.size());
	int v = -1;
	visited[p] = true;
	for (edge e : tr[p]) {
		if (visited[e.b]) {
			v = e.w;
			continue;
		}
		dis.push_back(e.w);
		press(e.b);
		last[p].insert(dis.size());
	}
	if (v >= 0) dis.push_back(v);
	return;
}
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n, m, q;
	cin >> n >> m;
	graph.resize(n), tr.resize(n), itf.resize(n), visited.resize(n, false), last.resize(n);
	//*
	for (edge temp; m--;) {
		cin >> temp;
		graph[temp.a].push_back(temp);
		temp.reverse();
		graph[temp.a].push_back(temp);
	}
	__gnu_pbds::priority_queue<edge, greater<edge>> pq;
	visited[0] = true;
	for (edge e : graph[0]) pq.push(e);
	edge temp;
	for (int cnt = 1; cnt < n && !pq.empty();) {
		temp = pq.top();
		pq.pop();
		if ((!visited[temp.a]) || visited[temp.b]) continue;
		visited[temp.b] = true, cnt++;
		tr[temp.a].push_back(temp), temp.reverse(), tr[temp.a].push_back(temp), temp.reverse();
		for (edge e : graph[temp.b]) {
			if (visited[e.b]) continue;
			pq.push(e);
		}
	}
	pq.clear();	 // pbds*/
	for (auto &i : tr) sort(i.begin(), i.end(), cmp);
	/*
	for (edge temp; m--;) {
		cin >> temp;
		tr[temp.a].push_back(temp);
		temp.reverse();
		tr[temp.a].push_back(temp);
	}
	//*/
	fill(visited.begin(), visited.end(), false);
	dis.reserve(n << 1);
	press(0);
	int sz = dis.size();
	vector<int> stree(sz << 1, 0);
	for (int s = 0; s < sz; s++) stree[s + sz] = dis[s];
	for (int s = sz; --s;) stree[s] = max(stree[s << 1], stree[s << 1 | 1]);
	cin >> q;
	set<int>::iterator it;
	for (int u, l, r, v, ans; q--;) {
		cin >> u >> v;
		l = itf[--u] + sz, r = itf[--v] + sz;
		if (l > r) swap(l, r), swap(u, v);
		it = last[u].lower_bound(itf[v]);
		it--;
		l = *it + sz;
		ans = 0;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, stree[l++]);
			if (r & 1) ans = max(ans, stree[--r]);
		}
		cout << ans << "\n";
	}
}
/*
6 5
1 2 3
2 3 2
3 5 5
3 4 1
1 6 4
1
1 6
*/
