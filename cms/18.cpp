#include <iostream>

#include "libBus.h"

int main() {
	int n = init();
	int l, r, mid;
	if (n == -1) {
		l = 1, r = 1001;
		for (mid = l + r >> 1; l < r - 1; mid = l + r >> 1) {
			if (query(mid) == -1) r = mid;
			else l = mid;
		}
		n = mid + 1;
	}
	int k, _k;
	l = 1, r = n >> 1, mid;
	for (mid = l + r >> 1; l < r - 1; mid = l + r >> 1) {
		if (query(mid) != query(-mid)) r = mid;
		else l = mid;
	}
	mid++;
	report(mid, n - 2 * mid);
	return 0;
}
/*
7 8
0
1 2 3 4 5 6 7
16 17 18 37 43 25 69 42
*/