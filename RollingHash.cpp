struct RollingHash {
    unsigned long long int mod61 = (1LL << 61) - 1;
    unsigned long long int Mul61(unsigned long long int a, unsigned long long int b) {
        unsigned long long int au = a >> 31;
        unsigned long long int ad = a ^ (au << 31);
        unsigned long long int bu = b >> 31;
        unsigned long long int bd = b ^ (bu << 31);
        unsigned long long int ret = au * bu * 2;
        ret += ad * bd;
        unsigned long long int mid = ad * bu + au * bd;
        unsigned long long int midu = mid >> 30;
        unsigned long long int midd = mid & ((1 << 30) - 1);
        ret += midu + (midd << 31);
        return ret;
    }
    unsigned long long int CalcMod61(unsigned long long int num) {
        return num % mod61;
    }
    int num;
    vector<unsigned long long int>h;
    vector<unsigned long long int>by;
    RollingHash(string s, unsigned int base = 10007) {
        num = s.size();
        h.resize(s.size() + 1);
        by.resize(s.size() + 1, 1);
        for (int i = 1; i <= num; i++) {
            by[i] = CalcMod61(Mul61(by[i - 1], base));
            h[i] = CalcMod61(Mul61(h[i - 1], base) + s[i - 1]);
        }
    }
    unsigned long long int Get(int l, int r) {
        return CalcMod61(h[r] + mod61 * 4 - Mul61(h[l], by[r - l]));
    }
};