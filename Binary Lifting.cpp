// Code for finding binary lifting in a tree.
// Time Complexity - O(n * logn) for build and O(logn) for query where n is the number of nodes in tree.

int n, l, up[LIM][22];

void dfs(int u, int p)
{
    up[u][0] = p;

    for (int i = 1; i <= l; ++i)
        up[u][i] = up[up[u][i - 1]][i - 1];

    for (int x : adj[u])
    {
        if (x != p)
            dfs(x, u);
    }
}

void init(int root)
{
    l = ceil(log2(n));

    dfs(root, root);
}

int binaryLift(int x, int k)
{
    for (int i = l; i >= 0; --i)
    {
        if (k >= (1 << i))
        {
            x = up[x][i];
            k -= (1 << i);
        }
    }

    return x;
}
