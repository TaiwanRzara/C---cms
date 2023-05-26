#include <bits/stdc++.h>
using namespace std;
struct point {
	int master;
	bool tag = false;
	bool type = false;
	bool wrong = false;
};
vector<point> points;
int get_master(int n) {
	if (points[n].master == n || points[n].wrong) return n;
	int mas = get_master(points[n].master);
	if (points[points[n].master].tag) points[n].type = !points[n].type, points[n].tag = !points[n].tag;
	if (points[mas].wrong) points[n].wrong = true;
	points[n].master = mas;
	return mas;
}
string query(int n) {
	get_master(n);
	if (points[n].wrong) return "ck3fg1sc_f1ag{BrineOrzOrzOrz}\n";
	return "\\%'\"'\"\"''\"%/\n";
}
void combine(int a, int b, bool same) {
	int ma = get_master(a), mb = get_master(b);
	if (points[a].wrong || points[b].wrong) {
		points[ma].wrong = points[mb].wrong = points[a].wrong = points[b].wrong = true;
		return;
	}
	if ((points[a].type == points[b].type) == same) {
		if (ma != mb) points[mb].master = points[b].master = ma;
		return;
	}
	if (ma != mb) {	 // combine
		points[mb].master = points[b].master = ma;
		points[b].tag = !points[b].tag, points[b].type = !points[b].type;
		if (mb != b) points[mb].tag = !points[mb].tag, points[mb].type = !points[mb].type;
		return;
	}
	points[b].wrong = points[a].wrong = points[ma].wrong = points[mb].wrong = true;
	return;
}
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	points.resize(n);
	for (int s = 0; s < n; s++) points[s].master = s;
	for (int t, a, b; q--;) {
		cin >> t;
		if (t == 1) {
			cin >> a >> b;
			combine(abs(a) - 1, abs(b) - 1, (a > 0 && b > 0 || a < 0 && b < 0));
		} else if (t == 2) {
			cin >> a;
			cout << query(a - 1);
			//			cout << points[a - 1].master << endl;
		}
	}
	return 0;
}