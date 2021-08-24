// Code for finding lca of two nodes.
// Time Complexity - O(n * logn) for build and O(logn) for query where n is the number of nodes in tree.

int l, timer;
int tin[LIM], tout[LIM], up[LIM][22];

void dfs(int u, int p)
{
    tin[u] = ++timer;
    up[u][0] = p;

    for (int i = 1; i <= l; ++i)
        up[u][i] = up[up[u][i - 1]][i - 1];

    for (int x : adj[u])
    {
        if (x != p)
            dfs(x, u);
    }

    tout[u] = ++timer;
}

bool isAncestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (isAncestor(u, v))
        return u;

    if (isAncestor(v, u))
        return v;

    for (int i = l; i >= 0; --i)
    {
        if (!isAncestor(up[u][i], v))
            u = up[u][i];
    }

    return up[u][0];
}

void initLCA(int root)
{
    timer = 0;
    l = ceil(log2(n));

    dfs(root, root);
}
