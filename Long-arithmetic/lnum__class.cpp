#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define sp(n) fixed << setprecision(n)
#define _  << " " <<
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

class lnum {
private:
    const int Base = 1000 * 1000 * 10;
    const int Signs_in_base = 7;
    vector<int> a;
    bool negative = false;

    vector<int>& del_zeros(vector<int>& num) const {
        while (num.size() > 1 && num.back() == 0)
            num.pop_back();
        return num;
    }
    vector<int>& carry(vector<int>& num) const {
        int c = 0, n = (int)num.size();
        for (int i = 0; i < n; i++) {
            num[i] += c;
            c = num[i] / Base;
            num[i] %= Base;
        }
        while (c) {
            num.pb(c % Base);
            c /= Base;
        }
        return num;
    }
    vector<int> trans(ll num) const {
        vector<int> res;
        if (num == 0) {
            res.pb(0);
        }
        else {
            num = abs(num);
            while (num) {
                res.pb(num % Base);
                num /= Base;
            }
        }
        return res;
    }
    vector<int> trans(string s) const {
        vector<int> res;
        int m = (int)s.size();
        for (int i = m; i > 0; i -= Signs_in_base) {
            string t = (i < Signs_in_base ? s.substr(0, i) : s.substr(i - Signs_in_base, Signs_in_base));
            int val = 0;
            for (auto c : t) {
                val *= 10;
                val += c - '0';
            }
            res.pb(val);
        }
        return del_zeros(res);
    }
    void set_default() {
        a = trans(0);
        negative = false;
        return;
    }

    bool is_less(const vector<int>& a, const vector<int>& b) const {
        if (a.size() > b.size()) {
            return false;
        }
        else if (a.size() < b.size()) {
            return true;
        }
        else {
            for (int i = 0; i < (int)a.size(); i++) {
                if (a[i] < b[i]) return true;
                if (a[i] > b[i]) return false;
            }
            return false;
        }
    }

    vector<int> add(vector<int> a, vector<int> b) const {
        int n = max(a.size(), b.size());
        a.resize(n), b.resize(n);
        vector<int> res(n);
        for (int i = 0; i < n; i++)
            res[i] = a[i] + b[i];
        return carry(res);
    }
    vector<int> sub(vector<int> a, vector<int> b) const {
        int c = 0, n = (int)a.size();
        for (int i = 0; i < n; i++) {
            a[i] -= c + (i < (int)b.size() ? b[i] : 0);
            c = (a[i] < 0);
            if (c) a[i] += Base;
        }
        return del_zeros(a);
    }
    void fft(vector<complex<double> > & a, bool invert) const {
        int n = (int)a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;

            while (j >= bit) {
                j -= bit;
                bit >>= 1;
            }
            j += bit;

            if (i < j)
                swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * acos(-1) /len * (invert ? -1 : 1);
            complex<double> wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                complex<double> w(1);
                for (int j = 0; j < len / 2; j++) {
                    complex<double> u = a[i + j],  v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) {
            for (int i = 0; i < n; i++)
                a[i] /= n;
        }
        return;
    }

    vector<int> mul(const vector<int> & a, const vector<int> & b) const {
        vector<complex<double> > fa, fb;
        for (auto i : a) fa.pb(i);
        for (auto i : b) fb.pb(i);

        int n = 1;
        while (n < max(a.size(), b.size()))
            n <<= 1;
        n <<= 1;
        fa.resize(n),  fb.resize(n);

        fft(fa, false),  fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);

        vector<ll> num(n);
        for (int i = 0; i < n; i++)
            num[i] = (ll)(fa[i].real() + 0.5);

        ll c = 0;
        for (int i = 0; i < n; i++) {
            num[i] += c;
            c = num[i] / Base;
            num[i] %= Base;
        }
        while (c) {
            num.pb(c % Base);
            c /= Base;
        }

        vector<int> res(num.size());
        for (int i = 0; i < (int)num.size(); i++)
            res[i] = num[i];

        return del_zeros(res);
    }

public:
    lnum() { set_default(); }
    lnum(ll num) {
        a = trans(num);
        negative = (num < 0);
    }
    lnum(string s) {
        if (s == "") {
            set_default();
            return;
        }
        int m = (int)s.size();
        bool ok = true;
        for (int i = 0; i < m; i++)
            ok &= (s[i] >= '0' && s[i] <= '9' || i == 0 && s[i] == '-');

        if (!ok) {
            cerr << "String \"" << s << "\" can not be converted to lnum! It will be set to default.\n";
            set_default();
            return;
        }

        if (s[0] == '-') {
            a = trans(s.substr(1));
            negative = true;
        }
        else {
            a = trans(s);
            negative = false;
        }
    }
    lnum(vector<int> _a, bool _negative = false) {
        a = del_zeros(carry(_a));
        negative = _negative;
    }

    void print(ostream& os = cout) const {
        if (a.empty() || (int)a.size() == 1 && a[0] == 0) {
            os << 0;
            return;
        }
        if (negative) {
            os << "-";
        }
        os << a.back();
        for (int i = (int)a.size() - 2; i >= 0; i--)
            cout << setw(Signs_in_base) << setfill('0') << a[i];
        return;
    }

    lnum& operator = (const lnum& t) {
        this->a = t.a;
        this->negative = t.negative;
        return *this;
    }

    friend ostream& operator << (ostream& os, const lnum& a);
    friend istream& operator >> (istream& is, lnum& num);

    bool operator == (const lnum& t) const {
        return (this->a == t.a && this->negative == t.negative);
    }
    bool operator != (const lnum& t) const {
        return !(*this == t);
    }
    lnum operator - () const {
        lnum res = *this;
        if (res != lnum(0))
            res.negative = !res.negative;
        return res;
    }
    bool operator < (const lnum& t) const {
        if (!this->negative && t.negative) return false;
        if (this->negative && !t.negative) return true;
        if (this->negative) return is_less(t.a, this->a);
        return is_less(this->a, t.a);
    }
    bool operator <= (const lnum& t) const {
        return (*this < t || *this == t);
    }
    bool operator >= (const lnum& t) const {
        return !(*this < t);
    }
    bool operator > (const lnum& t) const {
        return !(*this <= t);
    }
    lnum operator + (const lnum& t) const {
        if (this->negative == t.negative) {
            return lnum(add(this->a, t.a), this->negative);
        }
        else {
            if (t.negative) {
                if (is_less(this->a, t.a))
                    return lnum(sub(t.a, this->a), true);
                return lnum(sub(this->a, t.a), false);
            }
            else {
                if (is_less(t.a, this->a))
                    return lnum(sub(this->a, t.a), true);
                return lnum(sub(t.a, this->a), false);
            }
        }
    }
    lnum operator - (const lnum& t) const {
        return (*this + (-t));
    }
    lnum operator * (const lnum& t) const {
        lnum res(mul(this->a, t.a), ((this->negative) ^ (t.negative)));
        if (res == lnum(0))
            res.negative = false;
        return res;
    }
};
istream& operator >> (istream& is, lnum& num) {
    string s;
    if (is >> s)
        num = lnum(s);
    return is;
}
ostream& operator << (ostream& os, const lnum& a) {
    a.print(os);
    return os;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << sp(10);

#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
#endif

    lnum a, b;
    cin >> a >> b;

    if (a == b) cout << a << " == " << b << endl;
    if (a != b) cout << a << " != " << b << endl;
    if (a < b) cout << a << " < " << b << endl;
    if (a <= b) cout << a << " <= " << b << endl;
    if (a > b) cout << a << " > " << b << endl;
    if (a >= b) cout << a << " >= " << b << endl;

    cout << "-(" << a << ") = " << -a << endl;
    cout << "-(" << a << ") = " << -b << endl;

    cout << "(" << b << ") + (" << a << ") = "<< b + a << endl;
    cout << "(" << a << ") + (" << b << ") = "<< a + b << endl;
    cout << "(" << a << ") - (" << b << ") = "<< a - b << endl;
    cout << "(" << b << ") - (" << a << ") = "<< b - a << endl;

    cout << "(" << b << ") * (" << a << ") = "<< b * a << endl;

#ifdef LOCAL_DEBUG
    cerr << "Execution time: " << 1.0 * clock() / CLOCKS_PER_SEC << "s.\n";
#endif

    return 0;
}
