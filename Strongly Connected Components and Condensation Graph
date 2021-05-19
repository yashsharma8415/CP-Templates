// Code for finding strongly connected components and building condensation graph.
// Time Complexity - O(n + m) where n is the number of vertices and m is the number of edges in the graph.

vi adj[LIM], adjReverse[LIM], adjSCC[LIM], order, component, rootNodes;
int root[LIM];
bool visited[LIM];

void dfs1(int u)
{
    visited[u] = true;

    for(int x : adj[u])
    {
        if(!visited[x])
            dfs1(x);
    }

    order.push_back(u);
}

void dfs2(int u)
{
    visited[u] = true;
    component.pb(u);

    for(int x : adjReverse[u])
    {
        if(!visited[x])
            dfs2(x);
    }
}

void findSCC()
{
    for(int i=0; i<LIM; i++)
    {
        visited[i] = false;
        adj[i].clear();
        adjReverse[i].clear();
        adjSCC[i].clear();
    }

    order.clear();
    component.clear();
    rootNodes.clear();

    int n, m;
    cin >> n >> m;

    for(int i=0; i<m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].pb(v);
        adjReverse[v].pb(u);
    }

    for(int i=1; i<=n; i++)
    {
        if(!visited[i])
            dfs1(i);
    }

    for(int i=0; i<LIM; i++)
        visited[i] = false;

    Rev(order);

    for(auto x : order)
    {
        if(!visited[x])
        {
            component.clear();

            dfs2(x);

            int r = component[0];
            rootNodes.pb(r);

            for(auto x : component)
            {
                root[x] = r;
            }
        }
    }

    for(int i=1; i<=n; i++)
    {
        for(auto x : adj[i])
        {
            int r1 = root[i], r2 = root[x];

            if(r1 != r2)
                adjSCC[r1].pb(r2);
        }
    }
}
