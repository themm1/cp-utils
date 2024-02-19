#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, M;
vector<vector<int>> adj;
vector<vector<pair<int, int>>> weighted_adj;

/* Finds distances to all vertices from u. In the graph weighted_adj, first value in a pair
should be edge weight and second vertex. Time complexity: O(N + M log M). */
vector<ll> dijkstra(int u) {
        vector<ll> dists(N, -1);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> min_heap;
        min_heap.push({ 0, u });

        while (!min_heap.empty()) {
                pair<ll, int> pr = min_heap.top();
                min_heap.pop();
                int u = pr.second;
                if (dists[u] == -1) {
                        dists[u] = pr.first;
                        for (pair<int, int> edge : weighted_adj[u]) {
                                min_heap.push({ dists[u] + (ll)edge.first, edge.second });
                        }
                }
        }
        return dists;
}

/* Finds bridges in an undirected graph component. Time complexity: O(N + M) */
int bridges_dfs(int u, int depth, vector<int> &depths, vector<pair<int, int>> &bridges) {
        depths[u] = depth;
        int over_u = 0;
        for (int v : adj[u]) {
                // edge to unvisited vertex v
                if (depths[v] == -1) {
                        int over_v = bridges_dfs(v, depth + 1, depths, bridges);
                        // if no edge is going over v, edge (u, v) is a bridge
                        if (over_v == 0) bridges.push_back({ u, v });
                        over_u += over_v;
                // back edge to ancestor v
                } else if (depths[v] < depths[u]) {
                        over_u++;
                // back edge, where u is the ancestor
                } else {
                        over_u--;
                }
        }
        return over_u - (depths[u] != 0);
}

/* Finds articulations in an undirected graph component. Time complexity: O(N + M) */
int articulations_dfs(int u, int depth, vector<int> &depths, vector<int> &back_edges, vector<int> &articulations) {
        depths[u] = depth;
        bool is_articulation = false;
        int over_u = 0, children_cnt = 0;
        for (int v : adj[u]) {
                // edge to unvisited vertex v
                if (depths[v] == -1) {
                        int over_v = articulations_dfs(v, depth + 1, depths, back_edges, articulations);
                        // if all edges over v are ending at u and u is not the root, u is articulation
                        if (depths[u] != 0 && over_v == back_edges[u]) is_articulation = true;
                        over_u += over_v;
                        back_edges[u] = 0;
                        children_cnt++;
                // back edge, where v is ancestor and v isn't a parent
                } else if (depths[v] < depths[u] && depths[v] != depths[u] - 1) {
                        over_u++;
                        back_edges[v]++;
                // back edge, where u is ancestor
                } else if (depths[v] > depths[u]) {
                        over_u--;
                }
        }
        // if is root and has multiple tree children, or is regular articulation
        if ((depths[u] == 0 && children_cnt > 1) || is_articulation) articulations.push_back(u);
        return over_u;
}
