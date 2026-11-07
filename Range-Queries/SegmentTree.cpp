#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define lNode (2 * ni + 1)
#define rNode (2 * ni + 2)
#define md (lx + (rx - lx) / 2)

struct Node {
    ll sum;

    Node() {
        sum = 0;
    }

    Node(ll x) {
        sum = x;
    }

    void change(ll x) {
        sum = x;
    }
};

struct SegTree {
    int tree_size;
    vector<Node> node;

    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;

        node.assign(2 * tree_size, Node());
    }

    Node merge(Node &lf, Node &ri) {
        Node ans = Node();
        ans.sum = lf.sum + ri.sum;
        return ans;
    }

    void init(vector<ll> &a, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size())
                node[ni] = Node(a[lx]);
            return;
        }
        
        init(a, lNode, lx, md);
        init(a, rNode, md, rx);

        node[ni] = merge(node[lNode], node[rNode]);
    }

    void init(vector<ll> &a) {
        init(a,0,0,tree_size);
    }

    void set(int idx, ll val, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            node[ni].change(val);
            return;
        }
        
        if (idx < md) {
            set(idx,val,lNode,lx,md);
        }
        else {
            set(idx,val,rNode,md, rx);
        }

        node[ni] = merge(node[lNode],node[rNode]);
    }

    void set(int idx, ll val) {
        set(idx,val,0,0,tree_size);
    }

    Node get(int l, int r, int ni, int lx, int rx) {
        if (lx >= l && rx <= r) {
            return node[ni];
        }

        if (lx >= r || rx <= l) {
            return Node();
        }
        
        Node lf = get(l, r,lNode,lx,md);
        Node ri = get(l,r,rNode,md,rx);

        return merge(lf,ri);
    }

    ll get(int l, int r) {
        return get(l,r,0,0,tree_size).sum;
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegTree st = SegTree(n);
    st.init(a);

    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int idx;
            ll val;
            cin >> idx>>val;
            st.set(idx,val);
        }
        else {
            int l,r;
            cin >> l >> r;
            cout<<st.get(l,r)<<endl;
        }
    }
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
