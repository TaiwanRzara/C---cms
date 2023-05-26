#include <bits/extc++.h>
using namespace std;
signed main() {
	string w[3], temp;
	int sum = 0;
	for (int s = 0; cin >> temp; s++, s %= 3) {
		w[s] = temp;
		if (temp != "cow" && temp != "5" && temp != "A") break;
		if (w[s] == "cow" && w[(s + 2) % 3] == "5" && w[(s + 1) % 3] == "A") sum++;
	}
	cout << sum << endl;
}
