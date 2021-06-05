// Code for topological sort of a directed acyclic graph (DAG) using DFS.
// Time Complexity - O(n + m) where n is the number of vertices and m is the number of edges in the graph.

bool visited[LIM];
stack<int> st;

void dfs(int u)
{
    visited[u] = true;

    for (int x : adj[u])
    {
        if (!visited[x])
            dfs(x);
    }

    st.push(u);
}

vector<int> topoSort()
{
    for (int i = 0; i < LIM; i++)
        visited[i] = false;

    while (!st.empty())
        st.pop();

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            dfs(i);
    }

    vi order;

    while (!st.empty())
    {
        int ele = st.top();
        order.pb(ele);
        st.pop();
    }

    return order;
}
