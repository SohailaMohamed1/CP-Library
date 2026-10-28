// 2D Prefix Sum Template (1-based indexing)
// Ensure the base grid 'v' is read using 1-based indexing

vector<vector<ll>> pref(n + 1, vector<ll>(m + 1, 0));

// 1. Build the Prefix Sum array
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        pref[i][j] = v[i][j] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
}

// 2. Query function
auto sum = [&](int sx, int sy, int ex, int ey) {
    return pref[ex][ey] - pref[sx - 1][ey] - pref[ex][sy - 1] + pref[sx - 1][sy - 1];
};
