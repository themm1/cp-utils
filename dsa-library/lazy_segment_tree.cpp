#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define ff first
#define ss second
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define contains(s,x) ((s).find(x) != (s).end())

/*
Lazy segment tree with O(log n) complexity on query and range update operations.
Base row for segment tree and neutral values and functions for lazy and segments
fields have to be passed.  
*/
struct LazySegTree {
        int N;
        vector<int> segtree, lazy;
        int (*func)(int, int), (*update_func)(int, int);
        int seg_neutral, lazy_neutral;
        LazySegTree(vector<int> &v, int seg_neutral_, int lazy_neutral_,
                        int (*func_)(int, int), int (*update_func_)(int, int))
        {
                N = pow(2, ceil(log2(v.size())));
                func = func_;
                update_func = update_func_;
                seg_neutral = seg_neutral_;
                lazy_neutral = lazy_neutral_;

                // intialize base row
                segtree.assign(2 * N, seg_neutral);
                lazy.assign(2 * N, lazy_neutral);
                for (int i = 0; i < v.size(); i++)
                        segtree[N + i] = v[i];

                // initialize tree
                int s = N;
                while (s > 1) {
                        for (int i = s; i < 2 * s; i += 2)
                                segtree[i / 2] = func(segtree[i], segtree[i + 1]);
                        s /= 2;
                }
        }

        int _query(int l, int r, int i, int j, int x) {
                if (i >= r || j <= l) return seg_neutral;
                if (i >= l && j <= r) return update_func(segtree[x], lazy[x]);

                lazy[2 * x] = update_func(lazy[2 * x], lazy[x]);
                lazy[2 * x + 1] = update_func(lazy[2 * x + 1], lazy[x]);
                segtree[x] = update_func(segtree[x], lazy[x]);
                lazy[x] = lazy_neutral;

                return func(
                        _query(l, r, i, (i + j) / 2, x * 2),
                        _query(l, r, (i + j) / 2, j, x * 2 + 1)
                );
        }

        void _update(int l, int r, int i, int j, int x, int val) {
                if (i >= r || j <= l) return;
                if (i >= l && j <= r) {
                        lazy[x] = update_func(lazy[x], val);
                        return;
                }

                _update(l, r, i, (i + j) / 2, x * 2, val);
                _update(l, r, (i + j) / 2, j, x * 2 + 1, val);

                segtree[x] = func(
                        update_func(lazy[2 * x], segtree[2 * x]),
                        update_func(lazy[2 * x + 1], segtree[2 * x + 1])
                );
        }

        int query(int l, int r) {
                return _query(l, r, 0, N, 1);
        }
        
        void update(int l, int r, int val) {
                _update(l, r, 0, N, 1, val);
        }
};
