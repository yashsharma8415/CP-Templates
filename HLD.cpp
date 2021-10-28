// Code for heavy-light decomposition of a tree.
// Time Complexity - O(n * logn) for build and O((logn) ^ 2) for each query where n is the number of nodes in tree.

int cnt, sz[LIM], parent[LIM], depth[LIM], pos[LIM], chainHead[LIM];

int dfsForSize(int u, int p)
{
    sz[u] = 1;
    parent[u] = p;
    depth[u] = depth[p] + 1;

    for (int x : adj[u])
    {
        if (x != p)
            sz[u] += dfsForSize(x, u);
    }

    return sz[u];
}

void hld(int u, int p, int curChainHead)
{
    pos[u] = cnt++;
    chainHead[u] = curChainHead;

    update(1, 0, n - 1, pos[u], val[u]);

    int heavySize = -1, heavyChild = -1;

    for (int x : adj[u])
    {
        if (x != p && sz[x] > heavySize)
        {
            heavySize = sz[x];
            heavyChild = x;
        }
    }

    if (heavyChild != -1)
        hld(heavyChild, u, curChainHead);

    for (int x : adj[u])
    {
        if (x != p && x != heavyChild)
            hld(x, u, x);
    }
}

int hldQuery(int u, int v)
{
    int ans = 0;

    while (chainHead[u] != chainHead[v])
    {
        if (depth[chainHead[u]] < depth[chainHead[v]])
            swap(u, v);

        ans = ans + query(1, 0, n - 1, pos[chainHead[u]], pos[u]);
        u = parent[chainHead[u]];
    }

    if (depth[u] < depth[v])
        swap(u, v);

    ans = ans + query(1, 0, n - 1, pos[v], pos[u]);

    return ans;
}

void initHLD()
{
    for (int i = 0; i < LIM; ++i)
        sz[i] = depth[i] = parent[i] = pos[i] = chainHead[i] = 0;

    cnt = 0;
}

void solve()
{
    initHLD();
    dfsForSize(1, 0);
    hld(1, 0, 1);
    
    for (int i = 0; i < q; ++i)
    {
        auto type;
        cin >> type;

        if (type == "update")
        {
            int node, newValue;
            cin >> node >> newValue;

            val[node] = newValue;
            update(1, 0, n - 1, pos[node], val[node]);
        }
        else
        {
            int u, v, ans = 0;
            cin >> u >> v;

            ans = hldQuery(u, v);

            cout << ans << endl;
        }
    }
}
