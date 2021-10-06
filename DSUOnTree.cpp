// Code for Sack or DSU on tree algorithm.
// Time Complexity - O(n.logn) where n is the number of vertices in the tree.

vector<int>* vec[LIM];

void DSUOnTree(int u, int p, bool keep)
{
    int maxi = -1, bigChild = -1;

    for (int x : adj[u])
    {
        if (x != p && sz[x] > maxi)
        {
            maxi = sz[x];
            bigChild = x;
        }
    }

    for (int x : adj[u])
    {
        if (x != p && x != bigChild)
            DSUOnTree(x, u, false);
    }

    if (bigChild == -1)
        vec[u] = new vector<int>();
    else
    {
        DSUOnTree(bigChild, u, true);
        vec[u] = vec[bigChild];
    }

    vec[u]->push_back(u);
    // operation on u

    for (int x : adj[u])
    {
        if (x != p && x != bigChild)
        {
            for (int ele : *vec[x])
            {
                // operation on ele
                vec[u]->push_back(ele);
            }
        }
    }

    // now *vec[u] contains all of the subtree of vertex u

    if (keep == false)
    {
        for (int x : *vec[u])
            // operation on x
        }
}
