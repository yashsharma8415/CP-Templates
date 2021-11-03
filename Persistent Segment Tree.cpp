// Code for persistent segment tree data structure.
// Time Complexity - O(log n) for query and update where n is the length of array.

int numNodes, idElement;
int a[LIM], root[LIM];

struct node
{
    int l, r, val;

    node()
    {
        val = idElement;
        l = r = 0;
    }
};

node st[32 * LIM];

int combine(int a, int b)
{
    return a + b;
}

int query(int index, int curL, int curR, int queryL, int queryR)
{
    if (queryR < curL || queryL > curR)
        return idElement;

    if (queryL <= curL && queryR >= curR)
        return st[index].val;

    int mid = (curL + curR) / 2;

    return combine(query(st[index].l, curL, mid, queryL, queryR),
                   query(st[index].r, mid + 1, curR, queryL, queryR));
}

int update(int index, int l, int r, int pos, int addVal)
{
    st[++numNodes] = st[index];
    index = numNodes;

    if (l == r)
        st[index].val += addVal;
    else
    {
        int mid = (l + r) / 2;

        if (pos <= mid)
            st[index].l = update(st[index].l, l, mid, pos, addVal);
        else
            st[index].r = update(st[index].r, mid + 1, r, pos, addVal);

        st[index].val = combine(st[st[index].l].val,
                                st[st[index].r].val);
    }

    return index;
}

void initSegmentTree(int n)
{
    for (int i = 0; i < n + 5; ++i)
        a[i] = root[i] = 0;

    idElement = 0;
    numNodes = 0;
}
