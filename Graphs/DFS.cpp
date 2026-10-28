#include <bits/stdc++.h>
using namespace std;


void dfs(int u, const vector<vector<int>>& adj, vector<bool>& vis) {
    vis[u] = true;

    // (Optional) Process node 'u' before visiting its children (Pre-order)

    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v, adj, vis);
        }
    }

    // (Optional) Process node 'u' after visiting its children (Post-order)
}

/* 
Usage Example in main():
vector<bool> vis(n + 1, false);
for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
        dfs(i, adj, vis);
        // This means we found a new connected component
    }
}
*/
