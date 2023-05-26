#include <bits/extc++.h>
using namespace std;
int __lg10(int n) {
	int s = 0;
	for (; n; n /= 10, s++)
		;
	return s;
}
void print(int n, int len) {
	int l = __lg10(n);
	for (; l++ < len;) putchar('0');
	printf("%d", n);
}
signed main() {
	int date, m, y, d;
	scanf("%2d%2d%4d", &m, &d, &y);
	if (d > m) m++, d = m;
	if (d < m) d = m;
	if (m > 12) m = d = 1, y++;
	if (y % 100 > y / 100) y += 100, m = d = 1;
	if (y % 100 != y / 100) y = y / 100 * 101, m = d = 1;
	print(m, 2), print(d, 2), print(y, 4);
}
