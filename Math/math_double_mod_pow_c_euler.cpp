#include <algorithm>

using namespace std;
using ll = long long;
using ld = long double;

const ld EPS = 1e-9;
bool is_less(ld a, ld b) {
    return a < b - EPS;
}
bool is_greater(ld a, ld b) {
    return a > b + EPS;
}
bool is_equal(ld a, ld b) {
    return b - EPS < a && a < b + EPS;
}

const ll MOD = 1000000007;
ll add(ll a, ll b, ll m = MOD) {
    return (a + b) % m;
}
ll sub(ll a, ll b, ll m = MOD) {
    return (a + m - b) % m;
}
ll mul(ll a, ll b, ll m = MOD) {
    return (a * b) % m;
}
ll qpow(ll a, ll n, ll m = MOD) {
    ll p = 1;
    while (n) {
        if (n & 1) p = (p * a) % m;
        a = (a * a) % m;
        n >>= 1;
    }
    return p;
}
ll rev(ll a, ll m = MOD) {
    return qpow(a, m - 2, m);
}
ll div(ll a, ll b, ll m = MOD) {
    return mul(a, rev(b, m), m);
}

ll C(ll n, ll k, ll m = MOD) {
    if (n < k) return 0;
    k = min(k, n - k);
    ll res = 1;
    for (ll i = 1; i <= k; i++)
        res = div(mul(res, add(n - k, i, m), m), i, m);
    return res % m;
}

//ll C(ll n, ll k, ll m = MOD) {
//    if (k > n) return 0;
//    return div(f[n], mul(f[k], f[n - k], m), m);
//}

//ll C(ll n, ll k) {
//    if (n < k) return 0;
//    k = min(k, n - k);
//    ll res = 1;
//    for (ll i = 1; i <= k; i++)
//        res = res * (n - k + i) / i;
//    return res;
//}

ll euler(ll n, ll m = MOD) {
    ll res = n % m;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            res = sub(res, div(res, i, m), m);
        }
    if (n > 1)
        res = sub(res, div(res, n, m), m);
    return res;
}

//ll euler(ll n) {
//    ll res = n;
//    for (ll i = 2; i * i <= n; i++)
//        if (n % i == 0) {
//            while (n % i == 0)
//                n /= i;
//            res -= res / i;
//        }
//    if (n > 1)
//        res -= res / n;
//    return res;
//}


