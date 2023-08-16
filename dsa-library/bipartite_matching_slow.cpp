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

int A, B, M;
vector<vector<int>> g;

bool dfs(int b, vector<bool> &visited, vector<int> &matching) {
        visited[b] = true;
        if (matching[b] == -1) return true;
        int a = matching[b];
        for (int next_b : g[a]) {
                if (!visited[next_b] && dfs(next_b, visited, matching)) {
                        matching[next_b] = a;
                        return true;
                }
        }
        return false;
}

/* Finds maximum bipartite matching. Returns vector with the matching, where
i-th element is paired with v[i] (v[i] == -1 if not paired). O(N * M) */
vector<int> max_bipartite_matching() {
        vector<int> matching(B, -1);
        // this cycle runs min(A, B) times at maximum, because in every
        // iteration we increment matching by 1 and maximum matching size
        // is min(A, B)
        while (true) {
                unordered_set<int> matched_as(all(matching));
                vector<bool> visited(B, false);
                bool found = false;
                // if alternating path which uses current a exists
                for (int a = 0; a < A && !found; a++) if (!contains(matched_as, a)) {
                        // try all possible alternating paths begginings
                        for (int b : g[a]) {
                                // improving path with a -> b beggining exists
                                if (dfs(b, visited, matching)) {
                                        matching[b] = a;
                                        found = true;
                                        break;
                                }
                        }
                }
                // no improving path exists so matching is the best possible
                if(!found) return matching;
        }
}