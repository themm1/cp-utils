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
Segment tree with O(log n) complexity on query and point update operations.
Base row, neutral value and function have to be passed.  
*/
struct SegTree {
        int N;
        vector<int> segtree;
        int (*func)(int, int);
        int neutral;
        SegTree(vector<int> &v, int neutral_, int (*function)(int, int)) {
                N = pow(2, ceil(log2(v.size())));
                func = function;
                neutral = neutral_;

                // intialize base row
                segtree.assign(2 * N, neutral);
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
                int mid = (i + j) / 2;
                if (i >= l && j <= r)
                        return segtree[x];
                else if ((l >= i && l < j) || (r > i && r < j))
                        return func(_query(l, r, i, mid, x * 2), _query(l, r, mid, j, x * 2 + 1));
                else return neutral;
        }

        void _update(int x, int val) {
                if (x >= N) segtree[x] = val;
                else segtree[x] = func(segtree[x * 2], segtree[x * 2 + 1]);
                if (x > 1) _update(x / 2, val);
        }
        
        int query(int l, int r) {
                return _query(l, r, 0, N, 1);
        }
        
        void update(int x, int val) {
                _update(N + x, val);
        }
        
        int at(int x) {
                return segtree[N + x];
        }
};
