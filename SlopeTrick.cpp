struct SlopeTrick {
	long long mn, add_lft, add_rht;
	priority_queue<long long>lft;
	priority_queue<long long, vector<long long>, greater<long long>>rht;
	SlopeTrick() {
		mn = 0;
		add_lft = 0;
		add_rht = 0;
	}
	void Add(long long num) {
		mn += num;
	}
	void AddBoth(long long num) {
		add_lft += num;
		add_rht += num;
	}
	void AddLeft(long long num) {
		add_lft += num;
	}
	void AddRight(long long num) {
		add_rht += num;
	}
	void AddIncreasing(long long num) {
		if (lft.size() && lft.top() + add_lft > num) {
			mn += lft.top() + add_lft - num;
			rht.push(lft.top() + add_lft - add_rht);
			lft.pop();
			lft.push(num - add_lft);
		}
		else {
			rht.push(num - add_rht);
		}
	}
	void AddDecreasing(long long num) {
		if (rht.size() && rht.top() + add_rht < num) {
			mn += num - (rht.top() + add_rht);
			lft.push(rht.top() + add_rht - add_lft);
			rht.pop();
			rht.push(num - add_rht);
		}
		else {
			lft.push(num - add_lft);
		}
	}
	void DeleteLeft() {
		while (!lft.empty()) {
			lft.pop();
		}
	}
	void DeleteRight() {
		while (!rht.empty()) {
			rht.pop();
		}
	}
};