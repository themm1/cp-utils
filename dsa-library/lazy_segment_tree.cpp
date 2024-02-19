#include <bits/stdc++.h>
using namespace std;

/* Lazy segment tree with O(log N) complexities on query and range update operations. */
struct LazySegTree {
        int N;
        vector<int> segtree, lazy;

        int seg_neutral = INT_MAX, lazy_neutral = 0;
        int func(int a, int b) {
                return min(a, b);
        }
        int update_func(int a, int b) {
                return a + b;
        }
        LazySegTree(vector<int> &a) {
                N = (1 << (32 - __builtin_clz(a.size())));
                segtree.assign(2 * N, seg_neutral);
                lazy.assign(2 * N, lazy_neutral);
                
                for (int i = 0; i < a.size(); i++) {
                        segtree[N + i] = a[i];
                }
                for (int i = N - 1; i > 0; i--) {
                        segtree[i] = func(segtree[i * 2], segtree[i * 2 + 1]);
                }
        }

        int _query(int l, int r, int i, int j, int idx) {
                if (l <= i && j <= r) {
                        return update_func(segtree[idx], lazy[idx]);
                } else if ((i <= l && l < j) || (i < r && r <= j)) {
                        // propagate lazy value
                        segtree[idx] = update_func(segtree[idx], lazy[idx]);
                        lazy[2 * idx] = update_func(lazy[2 * idx], lazy[idx]);
                        lazy[2 * idx + 1] = update_func(lazy[2 * idx + 1], lazy[idx]);
                        lazy[idx] = lazy_neutral;

                        int mid = (i + j) / 2;
                        return func(_query(l, r, i, mid, idx * 2), _query(l, r, mid, j, idx * 2 + 1));
                } else {
                        return seg_neutral;
                }
        }

        void _update(int l, int r, int i, int j, int idx, int val) {
                if (l <= i && j <= r) {
                        lazy[idx] = update_func(lazy[idx], val);
                } else if ((i <= l && l < j) || (i < r && r <= j)) {
                        int mid = (i + j) / 2;
                        _update(l, r, i, mid, idx * 2, val);
                        _update(l, r, mid, j, idx * 2 + 1, val);
                        segtree[idx] = func(update_func(segtree[2 * idx], lazy[2 * idx]),
                                            update_func(segtree[2 * idx + 1], lazy[2 * idx + 1]));
                }
        }

        /* Queries interval [l, r) in O(log N). */
        int query(int l, int r) {
                return _query(l, r, 0, N, 1);
        }
        
        /* Updates interval [l, r) in O(log N) with val. */
        void update(int l, int r, int val) {
                _update(l, r, 0, N, 1, val);
        }
};
