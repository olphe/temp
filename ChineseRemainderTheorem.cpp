
long long int mul(long long int a, long long int b, long long int m) {
	long long int ret = 0;
	long long int add = a;
	for (int i = 0; i < 63; i++) {
		if (b >> i & 1)ret += add;
		ret %= m;
		add *= 2;
		add %= m;
	}
	return ret;
}

pair<long long int, long long int>crt(long long int m1, long long int a1, long long int m2, long long int a2) {
	if (m1 <= 0 || m2 <= 0)return { -1,-1 };
	long long int g = gcd(m1, m2);
	if (a1%g != a2 % g)return { -1,-1 };
	long long int by = (a2 - a1) / g;
	if (by < 0) {
		by *= -1;
		by %= m1 / g * m2;
		by *= -1;
		by += m1 / g * m2;
	}
	by %= m1 / g * m2;
	long long int a = extended_gcd(m1 / g, m2 / g);
	a %= m1 / g * m2;
	a = mul(a, by, m1 / g * m2);
	a = mul(a, m1, m1 / g * m2);
	a += a1;
	a %= m1 / g * m2;
	return { m1 / g * m2,a };
}

long long int crt(vector<long long int>m, vector<long long int>a) {
	long long int reta = 0;
	long long int retm = 1;
	for (int i = 0; i < m.size(); i++) {
		tie(retm, reta) = crt(retm, reta, m[i], a[i]);
	}
	return reta;
}