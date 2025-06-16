#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 2e5 + 5;

int fact[MAXN * 2], inv_fact[MAXN * 2];

int power(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < 2 * MAXN; ++i) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }
    inv_fact[2 * MAXN - 1] = power(fact[2 * MAXN - 1], MOD - 2);
    for (int i = 2 * MAXN - 2; i >= 0; --i) {
        inv_fact[i] = 1LL * inv_fact[i + 1] * (i + 1) % MOD;
    }
}

int comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int compute_k_shifting(const vector<pair<int, int>>& insertions) {
    set<int> constraints;
    for (int i = insertions.size() - 1; i >= 0; --i) {
        int y = insertions[i].second;
        auto it = constraints.lower_bound(y);
        int y_pos = y;
        if (it != constraints.end() && *it == y) {
            y_pos++;
        }
        constraints.insert(y_pos);
    }
    return constraints.size();
}

int compute_k_unique_ys(const vector<pair<int, int>>& insertions) {
    set<int> constraints;
    for (const auto& p : insertions) {
        constraints.insert(p.second);
    }
    return constraints.size();
}

void solve(bool use_shifting_logic) {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> insertions(m);
    for (int i = 0; i < m; ++i) {
        cin >> insertions[i].first >> insertions[i].second;
    }
    int k = use_shifting_logic ? compute_k_shifting(insertions) : compute_k_unique_ys(insertions);
    int ans = comb(2 * n - 1 - k, n);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();

    int t;
    cin >> t;
    bool use_shifting_logic;
    // For this example, you can hardcode or prompt for which logic to use.
    // Here, we'll do both for demonstration.
    while (t--) {
        cout << "Shifting logic result: ";
        solve(true);
        cout << "Unique y's logic result: ";
        solve(false);
    }
    return 0;
}
