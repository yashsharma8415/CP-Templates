// Code for topological sort of a directed acyclic graph (DAG) using Kuhn algorithm.
// Time Complexity - O(n + m) where n is the number of vertices and m is the number of edges in the graph.

int inDegree[LIM];

vector<int> topoSort()
{
    queue<int> q;
    vector<int> order;

    for (int i = 0; i < LIM; i++)
        inDegree[i] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int x : adj[i])
            inDegree[x]++;
    }

    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
            q.push(i);
    }

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        order.push_back(x);

        for (int u : adj[x])
        {
            inDegree[u]--;

            if (inDegree[u] == 0)
                q.push(u);
        }
    }

    if (order.size() == n)
        return order;
    else
        return { -1};
}
