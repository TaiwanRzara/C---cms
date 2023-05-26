const long long mod = 1e9 + 7;
long long power(long long a, long long n) {
	long long ans = 1;
	for (int s = 1; s <= n; s <<= 1, a = a * a % mod)
		if (s & n) ans = ans * a % mod;
	return ans;
}