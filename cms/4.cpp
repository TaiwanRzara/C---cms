#include <bits/extc++.h>
using namespace std;
// WA
signed main() {
	int n, brine = 0, repkironca = 0, bl, br = -1, rl, rr = -1;
	cin >> n;
	for (int p, s = 1; s <= n; s++) {
		cin >> p;
		if (p < 1 || p > 10000) std::this_thread::sleep_for(std::chrono::seconds(10));
		else if (br != -1 && rr != -1 && p != bl - 1 && p != br + 1 && p != rl - 1 && p != rr + 1) std::this_thread::sleep_for(std::chrono::seconds(10));
		else if (br != -1 && rr == -1 && p != bl - 1 && p != br + 1) std::this_thread::sleep_for(std::chrono::seconds(10));
		else if (br == -1 && rr != -1 && p != rl - 1 && p != rr + 1) std::this_thread::sleep_for(std::chrono::seconds(10));

		if (s & 1) {
			if (br == -1) bl = br = p, brine = 1;
			else if (p < bl - 1) brine += bl - p, repkironca -= bl - p - 1, bl = p, rr = -1;
			else if (p > br + 1) brine += p - br, repkironca -= p - br - 1, br = p, rr = -1;
			else if (p == bl - 1) brine++, bl--;
			else if (p == br + 1) brine++, br++;
		} else {
			if (rr == -1) rl = rr = p, repkironca = 1;
			else if (p < rl - 1) repkironca += rl - p, brine -= rl - p - 1, rl = p, br = -1;
			else if (p > rr + 1) repkironca += p - rr, brine -= p - rr - 1, rr = p, br = -1;
			else if (p == rl - 1) repkironca++, rl--;
			else if (p == rr + 1) repkironca++, rr++;
		}
	}
	// cout << brine << " " << repkironca << endl;
	if (repkironca < brine) cout << "Repkironca" << endl;
	else if (brine < repkironca) cout << "BrineTw" << endl;
	else cout << "Aaw" << endl;
}
/*

*/