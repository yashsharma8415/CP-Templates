// Code for sparse segment tree data structure.
// Time Complexity - O(log n) for query and update where n is the length of segment.
// LIM = 4 * q * log(n) where q is the number of queries and n is the length of segment.

struct node
{
    int l, r, val, lazy;

    node()
    {
        val = lazy = l = r = 0;
    }
};

int numNodes;
node segmentTree[LIM];

void lazyPropagate(int index, int l, int r)
{
    if (segmentTree[index].lazy == 0)
        return;

    segmentTree[index].val = r - l + 1;

    int mid = l + (r - l) / 2;

    if (segmentTree[index].l == 0)
        segmentTree[index].l = ++numNodes;

    if (segmentTree[index].r == 0)
        segmentTree[index].r = ++numNodes;

    segmentTree[segmentTree[index].l].lazy =
        segmentTree[segmentTree[index].r].lazy = 1;

    segmentTree[index].lazy = 0;
}

int update(int index, int curL, int curR, int queryL, int queryR)
{
    if (index == 0)
        index = ++numNodes;

    lazyPropagate(index, curL, curR);

    if (queryR < curL || queryL > curR)
        return index;

    if (queryL <= curL && queryR >= curR)
    {
        segmentTree[index].lazy = 1;
        lazyPropagate(index, curL, curR);
        return index;
    }

    int mid = (curL + curR) / 2;

    segmentTree[index].l = update(segmentTree[index].l, curL, mid, queryL, queryR);
    segmentTree[index].r = update(segmentTree[index].r, mid + 1, curR, queryL, queryR);

    segmentTree[index].val = segmentTree[segmentTree[index].l].val +
                             segmentTree[segmentTree[index].r].val;

    return index;
}

int query(int index, int curL, int curR, int queryL, int queryR)
{
    if (queryR < curL || queryL > curR || index == 0)
        return 0;

    lazyPropagate(index, curL, curR);

    if (queryL <= curL && queryR >= curR)
        return segmentTree[index].val;

    int mid = (curL + curR) / 2;

    return query(segmentTree[index].l, curL, mid, queryL, queryR) +
           query(segmentTree[index].r, mid + 1, curR, queryL, queryR);
}

void initSegmentTree()
{
    numNodes = 1;
}
