long long int floor_sum(long long int n, long long int m, long long int a, long long int b) {
	long long int add = 0;
	long long int ret = 0;
	add += a / m;
	add = add * n*(n - 1) / 2;
	if (b >= m) {
		add += b / m * n;
	}
	else if (b < 0) {
		add -= abs(b - m + 1) / m * n;
		b += abs(b - m + 1) / m * m;
	}
	long long int mx = (a%m) * (n - 1) + (b%m);
	mx /= m;
	add += n * mx;
	if (n <= 1) {
		ret = 0;
	}
	else if (a%m == 0) {
		ret = 0;
	}
	else {
		ret = floor_sum(mx, (a%m), m, (b%m) - m * mx);
	}
	return add + ret;
}