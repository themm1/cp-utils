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

bool dfs(int b, vector<int> &matching, vector<bool> &visited, vector<vector<int>> &g) {
        visited[b] = true;
        if (matching[b] == -1) return true;
        for (int next_b : g[matching[b]]) {
                if (!visited[next_b] && dfs(next_b, matching, visited, g)) {
                        matching[next_b] = matching[b];
                        return true;
                }
        }
        return false;
}

/* Given bipartite graph `g` and it's one part `left`, represented as array of vertices,
returns maximum bipartite matching in that graph as vector of paired verices,
where first vertex in every pair is from `left` part. Time complexity: O(N * M). */
vector<pii> max_bipartite_matching(vector<vector<int>> &g, vector<int> &left) {
        vector<bool> matched(sz(g), false);
        vector<int> matching(sz(g), -1);
        // this cycle runs min(A, B) times at maximum, because in every
        // iteration we increment matching by 1 and maximum matching size
        // is min(A, B)
        while (true) {
                bool found = false;
                vector<bool> visited(sz(g), false);
                // if alternating path which uses current a exists
                for (int a : left) if (!matched[a]) {
                        for (int b : g[a]) if (!visited[b]) {
                                found = dfs(b, matching, visited, g);
                                // improving path with a -> b beggining exists
                                if (found) {
                                        matching[b] = a;
                                        break;
                                }
                        }
                        if (found) break;
                }
                // no improving path exists so matching is the best possible
                if (!found) break;
                for (int a : matching) if (a != -1) matched[a] = true;
        }
        // construct matching as array of pairs of paired vertices
        vector<pii> answer;
        for (int i = 0; i < sz(matching); i++) if (matching[i] != -1) answer.pb({ matching[i], i });
        return answer;
}
