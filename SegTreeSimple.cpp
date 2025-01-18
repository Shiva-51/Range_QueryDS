struct Tree {
    int n;
    vector<int> a;
    vector<int> seg;
    Tree(vector<int>&x) {
        a = x;
        n = ssize(a);
        int sz = 1;
        while(sz < 2 * n) {
            sz <<= 1; 
        }
        seg.resize(sz);
        build(1, 0, n - 1);
    }
    auto merge(auto &l, auto &r) {
        return min(l, r);
    }
    void build(int index, int start, int end) {
        if(start == end) {
            seg[index] = a[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * index, start, mid);
        build(2 * index + 1, mid + 1, end);
        seg[index] = merge(seg[2 * index], seg[2 * index + 1]);
    }
    void update(int index, int start, int end, int pt, int val) {
        if(start == end) {
            seg[index] = val;
            return;
        }
        int mid = (start + end) / 2;
        if(pt <= mid) {
            update(2 * index, start, mid, pt, val);
        }
        else {
            update(2 * index + 1, mid + 1, end, pt, val);
        }
        seg[index] = merge(seg[2 * index], seg[2 * index + 1]);
    }
    int query(int index, int start, int end, int qL, int qR) {
        if(start >= qL and end <= qR) {
            return seg[index];
        }
        if(start > qR or end < qL) {
            return INT_MAX;
        }
        int mid = (start + end) / 2;
        auto ansL = query(2 * index, start, mid, qL, qR);
        auto ansR = query(2 * index + 1, mid + 1, end, qL, qR);
        return merge(ansL, ansR);
    }
    void make_update(int pt, int val) {
        update(1, 0, n-1, pt, val);
    }
    int make_query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};
