vector<int> Prime(int num) {
	vector<int>ret;
	ret.push_back(2);
	ret.push_back(3);
	for (int i = 5; i <= num; i += 6) {
		bool flag = true;
		for (int j = 2; j < ret.size(); j++) {
			if (ret[j] * ret[j] > i)break;
			if (i%j == 0) {
				flag = false;
				break;
			}
		}
		if (flag)ret.push_back(i);
		flag = true;
		for (int j = 2; j < ret.size(); j++) {
			if (ret[j] * ret[j] > i + 2)break;
			if ((i + 2) % j == 0) {
				flag = false;
				break;
			}
		}
		if (flag)ret.push_back(i + 2);
	}
	return ret;
}