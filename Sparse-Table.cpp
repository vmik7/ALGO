#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

template<class T> class sparse_table {
private:
    vector<vector<T>> t;
    int n, m;
    T init_value = INT_MAX;

public:
    sparse_table(int _n = 0) {
        resize(_n);
        for (int i = 0; i < _n; i++)
            t[i][0] = init_value;
        init();
    }
    template<class T2> sparse_table(vector<T2> a) {
        resize(a.size());
        for (int i = 0; i < (int)a.size(); i++)
            t[i][0] = a[i];
        init();
    }

    void resize(int _n) {
        n = _n; m = 0;
        while ((1 << m) <= n) m++;
        t.resize(n);
        for (auto& v : t)
            v.assign(m, init_value);
    }

    void init() {
        for (int j = 1; j < m; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                t[i][j] = std::min(t[i][j - 1], t[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int size() {
        return n;
    }

    T& operator [] (int i) {
        return t[i][0];
    }

    T min(int l, int r) {
        int len = r - l + 1;
        T ans = init_value;
        for (int j = 0; j < m; j++) {
            if (len & (1 << j)) {
                ans = std::min(ans, t[l][j]);
                l += (1 << j);
            }
        }
        return ans;
    }
};
