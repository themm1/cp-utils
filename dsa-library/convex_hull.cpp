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

bool _compare(pii a, pii b) {
        if (a.ff * b.ss > a.ss * b.ff) return true;
        return false;
}

/* Returns whether orientation of points (a -> b -> c) is clockwise, or anti-clockwise. */
bool orientation(pii a, pii b, pii c) {
        pii u = { b.ff - a.ff, b.ss - a.ss };
        pii v = { c.ff - a.ff, c.ss - a.ss };
        return u.ff * v.ss - u.ss * v.ff > 0;
}

/* Creates convex hull from given points using Graham scan. O(N log N)*/
vector<pii> convex_hull(vector<pii> &points) {
        pii mmin = *min_element(all(points));
        vector<pii> ps;
        // zo vsetkych bodov zoberieme relativnu poziciu k min. bodu
        for (pii p : points)
                if (p != mmin) ps.pb({ p.ff - mmin.ff, p.ss - mmin.ss });
        sort(all(ps), _compare);
        // pridame min. bod, aby sme na konci algortimu uzavreli konvex. obal (su od neho
        // odcitane jeho suradnice)
        ps.pb({ 0, 0 });

        // vytvorime konvex. obal Grahamovym scanom
        vector<pii> hull { mmin };
        for (pii p : ps) {
                p.ff += mmin.ff;
                p.ss += mmin.ss;
                while (hull.size() > 1 && !orientation(hull[sz(hull) - 2], hull[sz(hull) - 1], p))
                        hull.pop_back();
                hull.pb(p);
        }
        // odstranime min. bod, aby sa v konvex. obale nenachadzal dva-krat
        hull.pop_back();
        return hull;
}
