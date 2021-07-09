// Code for segment tree data structure.
// Time Complexity - O(n) for build and O(log n) for query where n is the length of array.

int segmentTree[4 * LIM], a[LIM];

void build(int index, int l, int r)
{
    if (l == r)
        segmentTree[index] = a[l];
    else
    {
        int mid = (l + r) / 2;

        build(2 * index, l, mid);
        build(2 * index + 1, mid + 1, r);

        segmentTree[index] = segmentTree[index * 2] +
                             segmentTree[index * 2 + 1];
    }
}

int query(int index, int curL, int curR, int queryL, int queryR)
{
    if (queryR < curL || queryL > curR)
        return 0;

    if (queryL <= curL && queryR >= curR)
        return segmentTree[index];

    int mid = (curL + curR) / 2;

    return query(2 * index, curL, mid, queryL, queryR) +
           query(2 * index + 1, mid + 1, curR, queryL, queryR);
}

void update(int index, int l, int r, int pos, int newVal)
{
    if (l == r)
        segmentTree[index] = newVal;
    else
    {
        int mid = (l + r) / 2;

        if (pos <= mid)
            update(2 * index, l, mid, pos, newVal);
        else
            update(2 * index + 1, mid + 1, r, pos, newVal);

        segmentTree[index] = segmentTree[index * 2] +
                             segmentTree[index * 2 + 1];
    }
}
