#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Line {
        int a, b;

        int operator()(int x) {
                return a * x + b;
        }
};

ostream& operator<<(ostream& out, Line &f) {
        out << "f: y = " << f.a << "x + " << f.b << endl;
        return out;
}

int MINX = -1e9 + 10, MAXX = 1e9 + 10, MINV = -LLONG_MAX;

struct LiChaoTree {
        struct Node {
                Line opt = { 0, MINV };
                int left = -1, right = -1;
        };
        vector<Node> nodes = { {} };
        vector<Line> inserted;

        /* Inserts given linear function. O(log (MAXX - MINX)) */
        void insert(Line f, int v = 0, int l = MINX, int r = MAXX) {
                if (l == MINX && r == MAXX) inserted.push_back(f);

                if (l + 1 == r) {
                        if (nodes[v].opt(l) < f(l)) nodes[v].opt = f;
                        return;
                }
                int mid = (l + r) / 2;
                // set opt to the function with higher slope
                if (nodes[v].opt.a < f.a) swap(f, nodes[v].opt);
                // intersection is in [mid, ...)
                if (f(mid) >= nodes[v].opt(mid)) {
                        swap(f, nodes[v].opt);
                        if (nodes[v].right == -1) {
                                nodes[v].right = nodes.size();
                                nodes.push_back({});
                        }
                        insert(f, nodes[v].right, mid, r);
                // intersection is in (..., mid)
                } else {
                        if (nodes[v].left == -1) {
                                nodes[v].left = nodes.size();
                                nodes.push_back({});
                        }
                        insert(f, nodes[v].left, l, mid);
                }
        }

        /* Gives current maximum at x. O(log (MAXX - MINX)) */
        int query(int x, int v = 0, int l = MINX, int r = MAXX) {
                if (v == -1) return MINV;

                int mx = nodes[v].opt(x);
                int mid = (l + r) / 2;
                if (x < mid) {
                        return max(mx, query(x, nodes[v].left, l, mid));
                } else {
                        return max(mx, query(x, nodes[v].right, mid, r));
                }
        }
};