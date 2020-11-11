#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class segtree {
private:
    vector<int> t;
    int size;

    int init_value = INT_MIN;
    void init(int n) {
        size = 1;
        while (size < n)
            size <<= 1;
        t.assign(2 * size - 1, init_value);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            t[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
            set(i, v, x * 2 + 1, lx, m);
        else
            set(i, v, x * 2 + 2, m, rx);
        t[x] = std::max(t[x * 2 + 1], t[x * 2 + 2]);
    }

    int max(int l, int r, int x, int lx, int rx) {
        if (l <= lx && rx <= r)
            return t[x];
        if (rx <= l || r <= lx)
            return init_value;
        int m = (lx + rx) / 2;
        int s1 = max(l, r, 2 * x + 1, lx, m);
        int s2 = max(l, r, 2 * x + 2, m, rx);
        return std::max(s1, s2);
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

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int max(int l, int r) {
        return max(l, r, 0, 0, size);
    }
};
