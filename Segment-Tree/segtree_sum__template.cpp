#include <vector>
using namespace std;

template<class T> class segtree {
private:
    vector<T> t;
    int size;

    void init(int n) {
        size = 1;
        while (size < n)
            size <<= 1;
        t.assign(2 * size - 1, 0);
    }

    void set(int i, T v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            t[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
            set(i, v, x * 2 + 1, lx, m);
        else
            set(i, v, x * 2 + 2, m, rx);
        t[x] = t[x * 2 + 1] + t[x * 2 + 2];
    }

    T sum(int l, int r, int x, int lx, int rx) {
        if (l <= lx && rx <= r)
            return t[x];
        if (rx <= l || r <= lx)
            return 0;
        int m = (lx + rx) / 2;
        T s1 = sum(l, r, 2 * x + 1, lx, m);
        T s2 = sum(l, r, 2 * x + 2, m, rx);
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

    void set(int i, T v) {
        set(i, v, 0, 0, size);
    }

    T sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};
