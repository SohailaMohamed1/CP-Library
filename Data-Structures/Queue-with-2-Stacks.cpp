#include<bits/stdc++.h>
using namespace std;
#define ll long long

// ==========================================
// 1. Min/Max Queue
// Queue using two stacks to query min/max in O(1) amortized time
// ==========================================
struct element {
    ll val, mn, mx;
};

struct MinMaxQueue {
    stack<element> s1; // Stack for adding elements
    stack<element> s2; // Stack for removing elements

    void add(ll x) {
        ll new_mn = s1.empty() ? x : min(x, s1.top().mn);
        ll new_mx = s1.empty() ? x : max(x, s1.top().mx);
        s1.push({x, new_mn, new_mx});
    }

    void remove() {
        if (s2.empty()) {
            // Transfer all elements from s1 to s2 (this reverses their order)
            while (!s1.empty()) {
                ll x = s1.top().val;
                s1.pop();

                ll new_mn = s2.empty() ? x : min(x, s2.top().mn);
                ll new_mx = s2.empty() ? x : max(x, s2.top().mx);
                s2.push({x, new_mn, new_mx});
            }
        }

        if (!s2.empty()) {
            s2.pop(); // Remove the oldest element
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


// ==========================================
// 2. GCD Queue
// Queue using two stacks to query GCD in O(1) amortized time
// ==========================================
struct gcd_element {
    ll val, gcd_val;
};

struct GcdQueue {
    stack<gcd_element> s1; // Stack for adding elements
    stack<gcd_element> s2; // Stack for removing elements

    void add(ll x) {
        ll new_gcd = s1.empty() ? x : std::gcd(x, s1.top().gcd_val);
        s1.push({x, new_gcd});
    }

    void remove() {
        if (s2.empty()) {
            while (!s1.empty()) {
                ll x = s1.top().val;
                s1.pop();
                
                ll new_gcd = s2.empty() ? x : std::gcd(x, s2.top().gcd_val);
                s2.push({x, new_gcd});
            }
        }

        if (!s2.empty()) {
            s2.pop();
        }
    }

    // Returns the GCD of the entire current window
    ll get_gcd() {
        if (s1.empty() && s2.empty()) return 0; // If both are empty
        if (s1.empty()) return s2.top().gcd_val;
        if (s2.empty()) return s1.top().gcd_val;
        
        // If both stacks have elements, combine their GCDs
        return std::gcd(s1.top().gcd_val, s2.top().gcd_val);
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
    // cin >> t;

    while(t--) {
        solve();
    }
    return 0;
}
