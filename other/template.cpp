#include <bits/stdc++.h>
using namespace std;
// ordered set whith s.order_of_key(x) method, which returns rank of element x in set s
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

// pair printing
template <class T, class U>
ostream& operator<<(ostream& out, const pair<T, U> &par) {out << "(" << par.first << "; " << par.second << ")"; return out;}
// set printing
template <class T>
ostream& operator<<(ostream& out, const set<T> &cont) { out << "{"; for(const auto &x:cont) out << x << ", "; out << "}"; return out; }
// map printing
template <class T, class U>
ostream& operator<<(ostream& out, const map<T, U> &cont) {out << "{"; for(const auto &x:cont) out << x << ", "; out << "}"; return out; }
// unordered_set printing
template <class T>
ostream& operator<<(ostream& out, const unordered_set<T> &cont) {out << "{";for(const auto &x:cont) out << x << ", ";out << "}";return out;}
// unordered_map printing
template <class T, class U>
ostream& operator<<(ostream& out, const unordered_map<T, U> &cont) {out << "{";for(const auto &x:cont) out << x << ", ";out << "}";return out;}
// vector printing
template<class T>
ostream& operator<<(ostream& out, const vector<T> &cont){ out << "[";  for (const auto &x:cont) out << x << ", ";  out << "]"; return out;}

#define print(x) cout << (x) << endl;
#define dmp(x) cerr << #x << " = " << x << endl
#define dmpn(x) cerr << #x << " = " << x << "; "
#define dmpl(x) cerr << "Line " << __LINE__ << ": " << #x << " = " << x << endl

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
const int MOD = 998244353;

void solve() {
}

int32_t main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);

        int t = 1;
        cin >> t;
        while (t--) {
                solve();
        }
}
