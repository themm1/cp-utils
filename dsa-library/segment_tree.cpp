#include <bits/stdc++.h>
using namespace std;

/* Segment tree with O(log N) complexities on query and point update operations. */
struct SegTree {
        int N;
        vector<int> segtree;
        
        const int neutral = -INT_MAX;
        int func(int a, int b) {
                return max(a, b);
        }
        SegTree(vector<int> &a) {
                N = (1 << (32 - __builtin_clz(a.size())));
                segtree.assign(2 * N, neutral);
                
                for (int i = 0; i < a.size(); i++) {
                        segtree[N + i] = a[i];
                }
                for (int i = N - 1; i > 0; i--) {
                        segtree[i] = func(segtree[i * 2], segtree[i * 2 + 1]);
                }
        }

        int _query(int l, int r, int i, int j, int idx = 1) {
                if (l <= i && j <= r) {
                        return segtree[idx];
                } else if ((i <= l && l < j) || (i < r && r <= j)) {
                        int mid = (i + j) / 2;
                        return func(_query(l, r, i, mid, idx * 2), _query(l, r, mid, j, idx * 2 + 1));
                } else {
                        return neutral;
                }
        }

        void _set(int idx, int val) {
                if (idx >= N) {
                        segtree[idx] = val;
                } else {
                        segtree[idx] = func(segtree[idx * 2], segtree[idx * 2 + 1]);
                }
                if (idx > 1) _set(idx / 2, val);
        }
        
        /* Queries interval [l, r) in O(log N). */
        int query(int l, int r) {
                return _query(l, r, 0, N, 1);
        }
        
        /* Changes element at idx to val and updates segment tree in O(log N). */
        void set(int idx, int val) {
                _set(N + idx, val);
        }
        
        /* Returns element at idx in O(1). */
        int at(int idx) {
                return segtree[N + idx];
        }
};
