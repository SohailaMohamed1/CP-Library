#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

// adj[u] = {v, weight} -> {Target Node, Edge Weight}
void dijkstra(int start, int n, const vector<vector<pair<int, int>>>& adj, vector<ll>& dist) {
    // 1. Initialize all distances to infinity
    dist.assign(n + 1, INF);
    
    // 2. Min-Heap to process smallest distances first
    // We store {distance, node} so the queue sorts by distance automatically
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        ll d = pq.top().first;   // Current distance
        int u = pq.top().second; // Current node
        pq.pop();

        // Lazy Deletion: skip outdated pairs if a shorter path was already found
        if (d > dist[u]) continue;

        // 3. Iterate over neighbors
        for (auto edge : adj[u]) {
            int v = edge.first;  // Target node (always 'first' in adjacency list)
            int w = edge.second; // Edge weight (always 'second' in adjacency list)

            // 4. Relaxation condition (Change to max() for Bottleneck Path problems)
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v}); // Push new state: {new_distance, target_node}
            }
        }
    }
}
