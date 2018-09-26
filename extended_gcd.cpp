long long int extended_gcd(long long int a, long long int b, long long int c, long long int d, long long int m) {
	long long int ret = 0;
	if (c == 1)return d;
	ret = extended_gcd(c, d, a%c, (b + (MOD *MOD / m)*m - ((a / c) % m)*(d%m)) % m, m);
	return ret;
}

long long int extended_gcd(long long int a, long long int b) {
	int g = gcd(a, b);
	a /= g;
	b /= g;
	long long int box = a % b;
	long long int bag = b - (a % b);
	long long int bbox = 1;
	long long int bbag = b - 1;
	return extended_gcd(box, bbox, bag, bbag, b)*g;
}