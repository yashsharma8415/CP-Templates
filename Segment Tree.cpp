// Code for segment tree data structure.
// Time Complexity - O(n) for build and O(log n) for query and update where n is the length of array.

int idElement;
int st[4 * LIM], a[LIM];

int combine(int a, int b)
{
    return a + b;
}

void build(int index, int l, int r)
{
    if (l == r)
        st[index] = a[l];
    else
    {
        int mid = (l + r) / 2;

        build(2 * index, l, mid);
        build(2 * index + 1, mid + 1, r);

        st[index] = combine(st[index * 2],
                            st[index * 2 + 1]);
    }
}

int query(int index, int curL, int curR, int queryL, int queryR)
{
    if (queryR < curL || queryL > curR)
        return idElement;

    if (queryL <= curL && queryR >= curR)
        return st[index];

    int mid = (curL + curR) / 2;

    return combine(query(2 * index, curL, mid, queryL, queryR),
                   query(2 * index + 1, mid + 1, curR, queryL, queryR));
}

void update(int index, int l, int r, int pos, int newVal)
{
    if (l == r)
        st[index] = newVal;
    else
    {
        int mid = (l + r) / 2;

        if (pos <= mid)
            update(2 * index, l, mid, pos, newVal);
        else
            update(2 * index + 1, mid + 1, r, pos, newVal);

        st[index] = combine(st[index * 2],
                            st[index * 2 + 1]);
    }
}

void initSegmentTree(int n)
{
    idElement = 0;

    build(1, 0, n - 1);
}
