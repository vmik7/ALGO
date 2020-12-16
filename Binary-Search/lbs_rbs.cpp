int lbs(vector<int>& a, int val) {
    int l = -1, r = (int)a.size();
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (a[mid] >= val)
            r = mid;
        else
            l = mid;
    }
    return (r == (int)a.size() ? -1 : r);
}
int rbs(vector<int>& a, int val) {
    int l = -1, r = (int)a.size();
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (a[mid] <= val)
            l = mid;
        else
            r = mid;
    }
    return l;
}
