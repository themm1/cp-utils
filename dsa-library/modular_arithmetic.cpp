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
const int MOD = 998244353;

/* Returns a^b % MOD. O(log(B)) */
int fast_pow(int a, int b) {
        int ans = 1;
        while (b > 0) {
                if (b % 2 == 1) ans = ((ll)a * (ll)ans) % MOD;
                a = ((ll)a * (ll)a) % MOD;
                b /= 2;
        }
        return ans;
}
 
/* Returns (a/b) % MOD. O(log(MOD)) */
int divide(int a, int b) {
        return ((ll)a * (ll)fast_pow(b, MOD - 2)) % MOD;
}

