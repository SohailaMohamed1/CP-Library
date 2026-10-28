#include <bits/stdc++.h>
using namespace std;

// adj: adjacency list for unweighted graph
// dist: stores the shortest distance from 'start' to all nodes
void bfs(int start, int n, const vector<vector<int>>& adj, vector<int>& dist) {
    // 1. Initialize distances to -1 (meaning unvisited)
    dist.assign(n + 1, -1);
    queue<int> q;

    // 2. Set distance for the starting node and push to queue
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // 3. Iterate over all neighbors
        for (int v : adj[u]) {
            // If the node hasn't been visited yet
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1; // Distance increases by 1
                q.push(v);
            }
        }
    }
}
