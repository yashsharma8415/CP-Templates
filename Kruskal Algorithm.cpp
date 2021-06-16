// Code for Kruskal Algorithm for finding minimum spanning tree.
// Time Complexity - O(m * log n) where m is the number of edges and n is the number of nodes in graph.

int parent[LIM], size[LIM];

int findSet(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v]);
}

void makeSet(int v)
{
    parent[v] = v;
    size[v] = 1;
}

void unionSets(int a, int b)
{
    a = findSet(a);
    b = findSet(b);

    if (a != b)
    {
        if (size[a] < size[b])
            swap(a, b);

        parent[b] = a;
        size[a] += size[b];
    }
}

struct Edge
{
    int u, v, w;

    bool operator < (Edge& e)
    {
        return w < e.w;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<Edge> edges, mst;
    int cost = 0;

    for (int i = 0; i <= n; ++i)
        makeSet(i);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;

        edges.pb({u, v, w});
    }

    Sort(edges);

    for (auto e : edges)
    {
        if (findSet(e.u) != findSet(e.v))
        {
            cost += e.w;
            mst.push_back(e);
            unionSets(e.u, e.v);
        }

        if (mst.size() == n - 1)
            break;
    }

    if (mst.size() != n - 1)
        // no mst possible

        return;
}
