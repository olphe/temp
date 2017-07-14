list<long long int> Prime(long long int num) {
	list<long long int>P;
	P.push_back(2);
	P.push_back(3);
	for (int i = 5; i <= num; i += 6) {
		bool flag = true;
		for (auto j : P) {
			if (i%j == 0) {
				flag = false;
				break;
			}
		}
		if (flag)P.push_back(i);
		flag = true;
		for (auto j : P) {
			if ((i + 2) % j == 0) {
				flag = false;
				break;
			}
		}
		if (flag)P.push_back(i + 2);
	}
	return P;
}