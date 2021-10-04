typedef std :: pair<int,int> PII;
typedef std :: vector<PII> VPII;

int Prims_MST (int source_node, std :: vector<VPII> & graph)
{

    // The priority_queue stores the pair<weight, node>
    std :: priority_queue<PII, std :: vector<PII>, std :: greater<PII>> q;

    // The cost of the source node to itself is 0
    q.push(std :: make_pair(0, source_node));

    bool added[graph.size()];
    memset(added, false, sizeof(bool)*graph.size());

    int mst_cost = 0;

    while (!q.empty())
    {

        // Select the item <cost, node> with minimum cost
        PII item;
        item = q.top();
        q.pop();

        int node = item.second;
        int cost = item.first;

        // If the node is node not yet added to the minimum spanning tree add it, and increment the cost.
        if (!added[node]) 
        {
            mst_cost += cost;
            added[node] = true;

            // Iterate through all the nodes adjacent to the node taken out of priority queue.
            // Push only those nodes (weight,node) that are not yet present in the minumum spanning tree.
            for (auto & pair_cost_node : graph[node]) 
            {
                int adj_node = pair_cost_node.second;
                if (added[adj_node] == false)
                    q.push(pair_cost_node);
            }
        }
    }
    return mst_cost;
}
