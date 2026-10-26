#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct element {
    ll val, mn, mx;
};

struct MinMaxQueue {
    stack<element> s1;
    stack<element> s2;

    void add(ll x) {
        ll new_mn = s1.empty() ? x : min(x, s1.top().mn);
        ll new_mx = s1.empty() ? x : max(x, s1.top().mx);
        s1.push({x, new_mn, new_mx});
    }

    void remove() {
        if (s2.empty()) {
            while (!s1.empty()) {
                ll x = s1.top().val;
                s1.pop();

                ll new_mn = s2.empty() ? x : min(x, s2.top().mn);
                ll new_mx = s2.empty() ? x : max(x, s2.top().mx);
                s2.push({x, new_mn, new_mx});
            }
        }

        if (!s2.empty()) {
            s2.pop();
        }
    }

    bool good(ll k) {
        ll curr_mn = 1e18;
        ll curr_mx = -1e18;

        if (!s1.empty()) {
            curr_mn = min(curr_mn, s1.top().mn);
            curr_mx = max(curr_mx, s1.top().mx);
        }

        if (!s2.empty()) {
            curr_mn = min(curr_mn, s2.top().mn);
            curr_mx = max(curr_mx, s2.top().mx);
        }

        return curr_mx - curr_mn <= k;
    }
};

void solve() {
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    MinMaxQueue window;
    int l = 1;
    ll cnt = 0;

    for (int r = 1; r <= n; r++) {
        window.add(v[r]);

        while (!window.good(k)) {
            window.remove();
            l++;
        }

        if (l <= r) {
            cnt += r - l + 1;
        }
    }

    cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    //cin >> t;

    while(t--) {
        solve();
    }
    return 0;
}
