#include <vector>
using namespace std;

class segtree {
private:
    vector<long long> t, t_inc;
    int size;

    void init(int n) {
        size = 1;
        while (size < n)
            size <<= 1;
        t.assign(2 * size - 1, 0);
        t_inc.assign(2 * size - 1, 0);
    }

    void increase(long long val, int x, int lx, int rx) {
        t_inc[x] += val;
        t[x] += (rx - lx) * val;
    }

    void push(int x, int lx, int rx) {
        int m = (lx + rx) / 2;
        increase(t_inc[x], x * 2 + 1, lx, m);
        increase(t_inc[x], x * 2 + 2, m, rx);
        t_inc[x] = 0;
    }

    void set(int i, long long val, int x, int lx, int rx) {
        if (rx - lx == 1) {
            t[x] = val;
            return;
        }
        push(x, lx, rx);
        int m = (lx + rx) / 2;
        if (i < m)
            set(i, val, x * 2 + 1, lx, m);
        else
            set(i, val, x * 2 + 2, m, rx);
        t[x] = t[x * 2 + 1] + t[x * 2 + 2];
    }

    void inc(int l, int r, long long val, int x, int lx, int rx) {
        if (rx <= l || r <= lx)
            return;
        if (l <= lx && rx <= r) {
            increase(val, x, lx, rx);
            return;
        }
        push(x, lx, rx);
        int m = (lx + rx) / 2;
        inc(l, r, val, x * 2 + 1, lx, m);
        inc(l, r, val, x * 2 + 2, m, rx);
        t[x] = t[x * 2 + 1] + t[x * 2 + 2];
    }

    long long sum(int l, int r, int x, int lx, int rx) {
        if (rx <= l || r <= lx)
            return 0;
        if (l <= lx && rx <= r)
            return t[x];
        push(x, lx, rx);
        int m = (lx + rx) / 2;
        long long s1 = sum(l, r, 2 * x + 1, lx, m);
        long long s2 = sum(l, r, 2 * x + 2, m, rx);
        return s1 + s2;
    }

public:
    segtree(int n = 0) {
        init(n);
    }
    template<class T2> segtree(vector<T2> a) {
        init(a.size());
        for (int i = 0; i < a.size(); i++)
            set(i, a[i]);
    }

    void set(int i, long long val) {
        set(i, val, 0, 0, size);
    }

    void inc(int l, int r, long long val) {
        inc(l, r, val, 0, 0, size);
    }

    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};
