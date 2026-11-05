#include<bits/stdc++.h>
using namespace std;
using ll = long long;


struct Node {
    int sum;

    Node() {
        sum = 0;
    }

    Node(int x) {
        sum = x;
    }

    void change(int x) {
        sum += x;
    }
};

struct SegTree {
    int tree_size;
    vector<Node> SegData;

    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;

        SegData.assign(2 * tree_size, Node());
    }

    Node merge(Node &lf, Node &ri) {
        Node ans = Node();
        ans.sum = lf.sum + ri.sum;
        return ans;
    }

    void init(vector<int> &a, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size())
                SegData[ni] = Node(a[lx]);
            return;
        }

        int mid = (lx + rx) / 2;
        init(a, 2 * ni + 1, lx, mid);
        init(a, 2 * ni + 2, mid, rx);

        SegData[ni] = merge(SegData[2 * ni + 1], SegData[2 * ni + 2]);
    }

    void init(vector<int> &a) {
        init(a,0,0,tree_size);
    }

    void set(int idx, int val, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            SegData[ni].change(val);
            return;
        }

        int mid = (lx + rx) / 2;
        if (idx < mid) {
            set(idx,val,2 * ni + 1,lx,mid);
        }
        else {
            set(idx,val,2 * ni + 2,mid, rx);
        }

        SegData[ni] = merge(SegData[2 * ni + 1],SegData[2 * ni + 2]);
    }

    void set(int idx, int val) {
        set(idx,val,0,0,tree_size);
    }

    Node get(int l, int r, int ni, int lx, int rx) {
        if (lx >= l && rx <= r) {
            return SegData[ni];
        }

        if (lx >= r || rx <= l) {
            return Node();
        }

        int mid = (lx + rx) / 2;
        Node lf = get(l, r,2 * ni + 1,lx,mid);
        Node ri = get(r,l,2 * ni + 2,mid,rx);

        return merge(lf,ri);
    }

    int get(int l, int r) {
        return get(l,r,0,0,tree_size).sum;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegTree st = SegTree(n);
    st.init(a);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;

        cout << st.get(l, r) << "\n";
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
