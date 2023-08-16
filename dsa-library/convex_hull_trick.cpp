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

/* Vrati priesecnik danych linearnych funkcii, ak pre kazde x plati a(x) < b(x) vrati
-INT_MAX, ak pre kazde x plati a(x) >= b(x) vrati INT_MAX. */
ld intersection(pair<ld, ld> &a, pair<ld, ld> &b) {
        ld d = a.ff - b.ff;
        if (d == 0 && a.ss >= b.ss) return INT_MAX;
        else if (d == 0) return -INT_MAX;
        return (b.ss - a.ss) / d;
}

/* Given a vector of linear functions sorted by slope, returns a vector v, in which holds,
that function with index v[i].second has maximum among all other functions in interval
(v[i].first, v[i + 1].first). It's guaranteed that v is sorted by v[i].first. O(N log N)*/
vector<pair<ld, int>> convex_hull_trick(vector<pair<ld, ld>> &lfs) {
        vector<pair<ld, int>> t({ { -INT_MAX, 0 } });
        for (int i = 1; i < sz(lfs); i++) {
                // new function
                pair<ld, ld> lf0 = lfs[i];
                // last function
                pair<ld, ld> lf1 = lfs[t.back().ss];
                // intersection of new and last function
                ld inters = intersection(lf0, lf1);
                
                // while intersection of new and last function is before intersection
                // of last two functions, last function won't have a maximum, so we can pop it
                while (sz(t) >= 2 && inters < t.back().ff) {
                        t.pop_back();
                        lf1 = lfs[t.back().ss];
                        inters = intersection(lf0, lf1);
                }
                // new function will have maximum on interval (inters, inf), where
                // inters is intersection of new and last function
                t.pb({ inters, i });
        }
        return t;
}
