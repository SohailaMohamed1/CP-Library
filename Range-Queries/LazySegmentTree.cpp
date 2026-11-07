#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define lNode (2 * ni + 1)
#define rNode (2 * ni + 2)
#define md (lx + (rx - lx) / 2)

struct Node {
    ll val,lazy;
    bool islazy = false;

    Node() {
        val = lazy = 0;
    }

    Node(ll x) {
        val = x;
    }

    void update(ll x,int lx,int rx) {
        val += x * (rx - lx);
        lazy += x;
        islazy = true;
    }
};

struct LazySegTree {
    int tree_size;
    vector<Node> node;

    LazySegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;

        node.assign(2 * tree_size, Node());
    }

    Node merge(Node &lf, Node &ri) {
        Node ans = Node();
        ans.val = lf.val + ri.val;
        return ans;
    }

    void propagate(int ni,int lx,int rx) {
        if (rx - lx == 1 || !node[ni].islazy) return;

        node[lNode].update(node[ni].lazy,lx,md);
        node[rNode].update(node[ni].lazy,md,rx);

        node[ni].lazy = node[ni].islazy = 0;
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

    void update(int l,int r,ll val,int ni,int lx,int rx) {
        propagate(ni,lx,rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            node[ni].update(val,lx,rx);
            return;
        }

        update(l,r,val,lNode,lx,md);
        update(l,r,val,rNode,md,rx);

        node[ni] = merge(node[lNode],node[rNode]);
    }

    void update(int l,int r,ll val) {
        update(l,r,val,0,0,tree_size);
    }

    Node get(int l, int r, int ni, int lx, int rx) {
        propagate(ni,lx,rx);
        if (lx >= l && rx <= r) return node[ni];
        if (lx >= r || rx <= l) return Node();

        Node lf = get(l, r,lNode,lx,md);
        Node ri = get(l,r,rNode,md,rx);

        return merge(lf,ri);
    }

    ll get(int l, int r) {
        return get(l,r,0,0,tree_size).val;
    }
};

void solve() {
    int n,q;
    cin>>n>>q;
    LazySegTree st(n);

    while(q--) {
        int t,l,r;
        cin>>t>>l>>r;
        if(t==1) {
            ll val;
            cin>>val;
            st.update(l,r,val);
        }
        else {
            cout<<st.get(l,r)<<"\n";
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
