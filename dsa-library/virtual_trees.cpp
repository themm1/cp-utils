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

int N, K;
vector<vector<int>> g, binlift;
vector<int> intimes, outtimes;

/* Sets DFS in-time and out-time for every vertex and precomputes binary jumps for every vertex. */
void preprocess(int v, int p, int &time) {
        intimes[v] = time++;
        binlift[v][0] = p;
        for (int i = 1; i < K; i++) binlift[v][i] = binlift[binlift[v][i - 1]][i - 1];
        for (int u : g[v]) {
                if (u == p) continue;
                preprocess(u, v, time);
        }
        outtimes[v] = time++;
}

/* Returns whether a is an ancestor of b. */
bool is_ancestor(int a, int b) {
        return intimes[a] <= intimes[b] && outtimes[a] >= outtimes[b];
}

int lca(int a, int b) {
        if (is_ancestor(b, a)) return b;
        if (is_ancestor(a, b)) return a;
        for (int i = K - 1; i >= 0; i--) {
                int u = binlift[b][i];
                if (!is_ancestor(u, a)) b = u;
        }
        return binlift[b][0];
}

bool dfs_cmp(int a, int b) {
        return intimes[a] < intimes[b];
}


/* Creates a virtual tree from given vertices. Returns root of created tree and the
tree adjecancy list, where vertices has indices from original tree. O(N log N)*/
pair<int, unordered_map<int, vector<int>>> make_virtual_tree(vector<int> vertices) {
        sort(all(vertices), dfs_cmp);
        int k = sz(vertices);
        set<int> s(all(vertices));
        for (int i = 0; i < k - 1; i++) s.insert(lca(vertices[i], vertices[i + 1]));
        // creates new vertices vector, so there are all needed vertices and no duplicates
        vertices.clear();
        for (int v : s) vertices.pb(v);
        sort(all(vertices), dfs_cmp);
        // creates virutal tree
        unordered_map<int, vector<int>> tree;
        vector<int> stck;
        for (int u : vertices) {
                while (!stck.empty() && !is_ancestor(stck.back(), u))
                        stck.pop_back();
                if (!stck.empty()) {
                        tree[u].pb(stck.back());
                        tree[stck.back()].pb(u);
                        stck.pb(u);
                } else stck.pb(u);
        }
        return { stck[0], tree };
}

