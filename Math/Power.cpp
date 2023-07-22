long long int power(long long int x, long long int n, long long int M) {
	long long int ret = 1;
	long long int by = x % M;
	while (n) {
		if (n & 1) {
			ret *= by;
			ret %= M;
		}
		by *= by;
		by %= M;
		n >>= 1;
	}
	return ret;
}