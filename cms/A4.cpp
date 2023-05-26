#include <bits/extc++.h>
using namespace std;
// WA
signed main() {
	vector<int> graph(10000 + 5, 0);
	int n, i;
	cin >> n;
	for (int s = 0, p; s < n; s++) {
		cin >> p;
		graph[p] = (s & 1) ? -1 : 1;
		if (graph[p + 1] == -graph[p])
			for (int i = p + 1; i <= 10000; i++) {
				if (graph[i] == -graph[p]) continue;
				else if (graph[i] == graph[p]) {
					for (; --i > p;) graph[i] = graph[p];
					break;
				} else break;
			}
		if (graph[p - 1] == -graph[p])
			for (int i = p - 1; i > 0; i--) {
				if (graph[i] == -graph[p]) continue;
				else if (graph[i] == graph[p]) {
					for (; ++i < p;) graph[i] = graph[p];
					break;
				} else break;
			}
	}
	i = 0;
	for (auto v : graph) i += v;
	if (i > 0) cout << "Repkironca";
	else if (i < 0) cout << "BrineTw";
	else cout << "Aaw";
}
/*

*/
