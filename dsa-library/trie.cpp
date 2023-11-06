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

struct Trie {
        struct Node {
                char value = ' ';
                int end_cnt = 0;
                vector<int> children;
        };
        vector<Node> nodes = { Node() };

        /* Inserts given string into the trie. (trie.insert(0, s, 0) */
        void insert(int v, string &s, int i) {
                if (i == sz(s)) {
                        nodes[v].end_cnt++;
                        return;
                }
                int next = -1;
                for (int u : nodes[v].children) if (nodes[u].value == s[i]) next = u;
                // new node has to be added
                if (next == -1) {
                        next = sz(nodes);
                        nodes[v].children.pb(next);
                        nodes.pb(Node { s[i] });
                }
                insert(next, s, i + 1);
        }

        /* Returns true iff given string is in the trie. (trie.search(0, s, 0) */
        bool search(int v, string &s, int i) {
                if (i == sz(s) && nodes[v].end_cnt > 0) return true;
                for (int u : nodes[v].children) if (nodes[u].value == s[i]) return search(u, s, i + 1);
                return false;
        }
};
