// Code for solving dp problems using li chao tree.
// Time Complexity - O(n * log maxx) where n is the number of lines and maxx is the largest possible query.

struct line
{
    int m, c;
 
    int getValue(int x)
    {
        return m*x + c;
    }
};
 
line liChaoTree[4 * LIM];
 
void insert(line ln, int l = 1, int r = LIM-1, int index = 1)
{
    int mid = (l + r)/2;
 
    bool leftComp = ln.getValue(l) < liChaoTree[index].getValue(l);
    bool midComp = ln.getValue(mid) < liChaoTree[index].getValue(mid);
 
    if(midComp)
        swap(ln, liChaoTree[index]);
 
    if(l == r)
        return;
 
    if(leftComp != midComp)
        insert(ln, l, mid, 2*index);
    else
        insert(ln, mid+1, r, 2*index + 1);
}
 
int query(int pos, int l = 1, int r = LIM-1, int index = 1)
{
    int mid = (l + r)/2;
 
    int curValue = liChaoTree[index].getValue(pos);
 
    if(l == r)
        return curValue;
 
    if(pos <= mid)
        return min(curValue, query(pos, l, mid, 2*index));
    else
        return min(curValue, query(pos, mid+1, r, 2*index + 1));
}
 
void solve()
{
    // fill liChaoTree[] with some initail value
 
    for(int i=0; i<n; i++)
    {
        line l;
        cin >> l;
 
        insert(l);
    }
  
    for(int i=0; i<q; i++)
    {
        int q;
        cin >> q;
 
        int ans = query(q);
    }
 
    return;
}
