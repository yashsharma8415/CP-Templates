#include <bits/stdc++.h>
#define nl cout<<"\n";
#define ll long long int
#define ld double
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define F(i,a,b) for(i=a;i<b;i++)
using namespace std;
const ll M=1e18;
const ll MAXN=100200;
ll i,j,mask;
#define root 0
#define N 100200
#define LN 20

vector <ll> adj[N], costs[N], indexx[N];
ll baseArray[N], ptr;
ll chainNo, chainInd[N], chainHead[N], posInBase[N];
ll depth[N], pa[LN][N], otherEnd[N], subsize[N];
vector<ll> tree(4*N);

/*
 * make_tree:
 * Used to construct the segment tree. It uses the baseArray for construction
 */
void make_tree(ll node, ll start, ll ends)
{
    if(start == ends) 
    {
        // Leaf node will have a single element
        tree[node] = baseArray[start];
    } 
    else 
    {
        ll mid = (start + ends) / 2;
        // Recurse on the left child
        make_tree(2*node, start, mid);
        // Recurse on the right child
        make_tree(2*node+1, mid+1, ends);
        // Internal node will have the sum of both of its children
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

/*
 * update_tree:
 * Poll update. Update a single element of the segment tree.
 */
void update_tree(ll node, ll start, ll ends, ll idx, ll val)
{
    if(start == ends) 
    {
        // Leaf node
        tree[node] = val;
    } 
    else 
    {
        ll mid = (start + ends) / 2;
        if(start <= idx && idx <= mid) 
        {
            // If idx is in the left child, recurse on the left child
            update_tree(2*node, start, mid, idx, val);
        } 
        else 
        {
            // if idx is in the right child, recurse on the right child
            update_tree(2*node+1, mid+1, ends, idx, val);
        }
        // Internal node will have the sum of both of its children
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

/*
 * query_tree:
 * Given S and E, it will return the maximum value in the range [S,E)
 */
ll query_tree(ll node, ll start, ll ends, ll l, ll r)
{
    if(r < start || ends < l)
    {
        // range represented by a node is completely outside the given range
        return 0;
    }
    if(l <= start && ends <= r) 
    {
        // range represented by a node is completely inside the given range
        return tree[node];
    }
    // range represented by a node is partially inside and partially outside the given range
    ll mid = (start + ends) / 2;
    ll p1 = query_tree(2*node, start, mid, l, r);
    ll p2 = query_tree(2*node+1, mid+1, ends, l, r);
    return (p1 + p2);
}

/*
 * query_up:
 * It takes two nodes u and v, condition is that v is an ancestor of u
 * We query the chain in which u is present till chain head, then move to next chain up
 * We do that way till u and v are in the same chain, we query for that part of chain and break
 */

ll query_up(ll u, ll v)
{
    if(u == v)
        return 0; // Trivial
    ll uchain, vchain = chainInd[v], ans = 0;
    // uchain and vchain are chain numbers of u and v
    while(1) 
    {
        uchain = chainInd[u];
        if(uchain == vchain) 
        {
            // Both u and v are in the same chain, so we need to query from u to v, update answer and break.
            // We break because we came from u up till v, we are done
            if(u==v)
                break;
            ans+=query_tree(1, 0, ptr, posInBase[v]+1, posInBase[u]);
            // Above is call to segment tree query function
            break;
        }
        ans+=query_tree(1, 0, ptr, posInBase[chainHead[uchain]], posInBase[u]);
        // Above is call to segment tree query function. We do from chainHead of u till u. That is the whole chain from
        // start till head. We then update the answer
        u = chainHead[uchain]; // move u to u's chainHead
        u = pa[0][u]; //Then move to its parent, that means we changed chains
    }
    return ans;
}

/*
 * LCA:
 * Takes two nodes u, v and returns Lowest Common Ancestor of u, v
 */
ll LCA(ll u, ll v)
{
    if(depth[u] < depth[v])
        swap(u,v);
    ll diff = depth[u] - depth[v];
    for(ll g =0; g<LN; g++)
        if( (diff>>g)&1 )
            u = pa[g][u];
    if(u == v)
        return u;
    for(ll g=LN-1; g>=0; g--)
    {
        if(pa[g][u] != pa[g][v]) 
        {
            u = pa[g][u];
            v = pa[g][v];
        }
    }
    return pa[0][u];
}

void query(ll u, ll v)
{
    /*
     * We have a query from u to v, we break it llo two queries, u to LCA(u,v) and LCA(u,v) to v
     */
    ll lca = LCA(u, v);
    ll ans = query_up(u, lca); // One part of path
    ll temp = query_up(v, lca); // another part of path
    ans+=temp;
    cout<<ans;
    nl
}

/*
 * change:
 * We just need to find its position in segment tree and update it
 */
void change(ll g, ll val)
{
    ll u = otherEnd[g];
    update_tree(1, 0, ptr, posInBase[u], val);
}

/*
 * Actual HL-Decomposition part
 * Initially all entries of chainHead[] are set to -1.
 * So when ever a new chain is started, chain head is correctly assigned.
 * As we add a new node to chain, we will note its position in the baseArray.
 * In the first for loop we find the child node which has maximum sub-tree size.
 * The following if condition is failed for leaf nodes.
 * When the if condition passes, we expand the chain to special child.
 * In the second for loop we recursively call the function on all normal nodes.
 * chainNo++ ensures that we are creating a new chain for each normal child.
 */
void HLD(ll curNode, ll cost, ll prev)
{
    if(chainHead[chainNo] == -1) 
    {
        chainHead[chainNo] = curNode; // Assign chain head
    }
    chainInd[curNode] = chainNo;
    posInBase[curNode] = ptr; // Position of this node in baseArray which we will use in Segtree
    baseArray[ptr++] = cost;

    ll sc = -1, ncost;
    // Loop to find special child
    for(ll g=0; g<adj[curNode].size(); g++)
    {
        if(adj[curNode][g] != prev) 
        {
            if(sc == -1 || subsize[sc] < subsize[adj[curNode][g]]) 
            {
                sc = adj[curNode][g];
                ncost = costs[curNode][g];
            }
        }
    }

    if(sc != -1)
    {
        // Expand the chain
        HLD(sc, ncost, curNode);
    }

    for(ll g=0; g<adj[curNode].size(); g++)
    {
        if(adj[curNode][g] != prev) 
        {
            if(sc != adj[curNode][g]) 
            {
                // New chains at each normal node
                chainNo++;
                HLD(adj[curNode][g], costs[curNode][g], curNode);
            }
        }
    }
}

/*
 * dfs used to set parent of a node, depth of a node, subtree size of a node
 */
void dfs(ll cur, ll prev, ll _depth=0)
{
    pa[0][cur] = prev;
    depth[cur] = _depth;
    subsize[cur] = 1;
    for(ll g=0; g<adj[cur].size(); g++)
    {
        if(adj[cur][g] != prev) 
        {
            otherEnd[indexx[cur][g]] = adj[cur][g];
            dfs(adj[cur][g], cur, _depth+1);
            subsize[cur] += subsize[adj[cur][g]];
        }
    }
}
void solve()
{
    ptr = 0;
    ll n, q;
    cin>>n>>q;
    // Cleaning step, new test case
    for(i=0; i<n; i++) 
    {
        adj[i].clear();
        costs[i].clear();
        indexx[i].clear();
        chainHead[i] = -1;
        for(j=0; j<LN; j++)
            pa[j][i] = -1;
    }
    vector<ll> ag(n);
    F(i,0,n)
    {
        cin>>ag[i];
    }
    vector<pair<ll, ll> > po(n+1);
    for(i=1; i<n; i++) 
    {
        ll u, v;
        cin>>u>>v;
        u--;
        v--;
        po[i-1]= {u, v};
        ll cost_edge=max(abs(ag[u]+ag[v]), abs(ag[u]-ag[v]));
        adj[u].push_back(v);
        costs[u].push_back(cost_edge);
        indexx[u].push_back(i-1);
        adj[v].push_back(u);
        costs[v].push_back(cost_edge);
        indexx[v].push_back(i-1);
    }

    chainNo = 0;
    dfs(root, -1); // We set up subsize, depth and parent for each node
    HLD(root, -1, -1); // We decomposed the tree and created baseArray
    make_tree(1, 0, ptr); // We use baseArray and construct the needed segment tree

    // Below Dynamic programming code is for LCA.
    for(i=1; i<LN; i++)
    {
        for(j=0; j<n; j++)
        {
            if(pa[i-1][j] != -1)
                pa[i][j] = pa[i-1][pa[i-1][j]];
        }
    }

    while(q--) 
    {
        ll val;
        cin>>val;
        ll a, b;
        cin>>a>>b;
        if(val==2) 
        {
            query(a-1, b-1);
        } 
        else 
        {
            for(auto t:indexx[a-1]) 
            {
                ll x=po[t].fi, y=po[t].se;
                ag[a-1]=b;
                ll cost_edge=0;
                if(x!=a-1) 
                {
                    cost_edge=max(abs(ag[x]+ag[a-1]), abs(ag[x]-ag[a-1]));
                }
                if(y!=a-1) 
                {
                    cost_edge=max(abs(ag[y]+ag[a-1]), abs(ag[y]-ag[a-1]));
                }
                change(t, cost_edge);
            }
        }
    }
}
