#include <bits/extc++.h>
#define endl "\n"
using namespace std;
struct edge {
	int a, b, w;
	bool operator<(const edge &t) {
		return w > t.w;
	}
	void reverse(void) {
		swap(a, b);
	}
};
bool operator<(const edge &e, const edge &_e) {
	return e.w > _e.w;
}

istream &operator>>(istream &s, edge &e) {
	s >> e.a >> e.b >> e.w;
	e.a--, e.b--;
	return s;
}
vector<vector<edge>> graph, tr;
vector<bool> visited;
vector<int> depth, max_depth;
// HLD
struct point {
	int parent, self, con;
	point(edge e)
		: parent(e.a), self(e.b), con(e.w){};
	point(int parent, int self, int con)
		: parent(parent), self(self), con(con){};
};
struct chain {
	int master = -1, top;
	vector<point> points;
	vector<int> stree;
	int query(int l, int r) {
		int sz = points.size();
		int ans = 0;
		for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, stree[l++]);
			if (r & 1) ans = max(ans, stree[--r]);
		}
		return ans;
	}
};
vector<chain> chains;
vector<pair<int, int>> pos;
void build(edge anc) {
	int sz = max_depth[anc.b] - depth[anc.b] + 1;
	chains[anc.b].master = anc.a;
	chains[anc.b].points.reserve(sz), chains[anc.b].stree.resize(sz << 1, 0);
	edge son;
	chains[anc.b].points.push_back(anc);
	pos[anc.b] = {anc.b, 0};
	chains[anc.b].top = anc.b;
	for (int depth = 1, p = anc.b, last = anc.a; depth < sz; depth++, p = son.b, last = son.a) {
		son.b = -1558;
		for (edge e : tr[p]) {
			if (e.b == last) continue;
			if (son.b == -1558 && max_depth[p] == max_depth[e.b]) {
				son = e;
				continue;
			}
			build(e);
		}
		chains[anc.b].points.push_back(son);
		pos[son.b] = {anc.b, depth};
	}
	for (int s = 0; s < sz; s++) chains[anc.b].stree[s + sz] = chains[anc.b].points[s].con;
	for (int s = sz - 1; s > 0; s--) chains[anc.b].stree[s] = max(chains[anc.b].stree[s << 1], chains[anc.b].stree[s << 1 | 1]);
	return;
}
int query(int a, int b) {
	int m;
	pair<int, int> pa = pos[a], pb = pos[b], pma, pmb;
	if (pa.first == pb.first) {
		if (pa.second > pb.second) swap(pa, pb);
		return chains[pa.first].query(pa.second + 1, pb.second + 1);
	}
	if (depth[pa.first] == depth[pb.first]) return max(query(chains[pa.first].master, chains[pb.first].master), max(chains[pa.first].query(0, pa.second + 1), chains[pb.first].query(0, pb.second + 1)));
	if (depth[pa.first] > depth[pb.first]) swap(pa, pb), swap(a, b);
	return max(query(a, chains[pb.first].master), chains[pb.first].query(0, pb.second + 1));
}
int dfs(int p) {
	visited[p] = true;
	if (tr[p].size() == 1 && p != 0) return max_depth[p] = depth[p];
	for (edge e : tr[p]) {
		if (visited[e.b]) continue;
		depth[e.b] = depth[p] + 1;
		max_depth[p] = max(dfs(e.b), max_depth[p]);
	}
	return max_depth[p];
}
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n, m, q;
	cin >> n >> m;
	chains.resize(n), pos.resize(n), graph.resize(n), tr.resize(n), visited.resize(n, false), depth.resize(n), max_depth.resize(n, 0);
	//*
	if (m != n - 1) {
		for (edge temp; m--;) {
			cin >> temp;
			graph[temp.a].push_back(temp);
			temp.reverse();
			graph[temp.a].push_back(temp);
		}
		__gnu_pbds::priority_queue<edge> pq;
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
		graph.clear();
	} else {
		for (edge temp; m--;) {
			cin >> temp;
			tr[temp.a].push_back(temp);
			temp.reverse();
			tr[temp.a].push_back(temp);
		}
	}
	fill(visited.begin(), visited.end(), false);
	depth[0] = 0;
	dfs(0);
	build({0, 0, 0});

	cin >> q;
	for (int a, b; q--;) {
		cin >> a >> b;
		cout << query(a - 1, b - 1) << endl;
	}
}
/*
6 5
1 2 3
1 6 4
2 3 2
3 4 1
3 5 5

*/
/*
7 12
1 2 2
1 3 4
1 4 1
2 4 3
2 5 10
3 4 2
3 6 5
4 5 7
4 6 8
4 7 4
5 7 6
6 7 1

*/
/*
6 9
1 2 6
1 3 5
1 4 11
1 5 16
2 3 3
3 4 7
3 6 10
4 5 9
4 6 2
*/
