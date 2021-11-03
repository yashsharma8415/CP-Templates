// Code for lazy segment tree data structure.
// Time Complexity - O(n) for build and O(log n) for query and update where n is the length of array.

int idElement;
int st[4 * LIM], a[LIM];
int lazy[4 * LIM];

int combine(int a, int b)
{
    return a + b;
}

void build(int index, int l, int r)
{
    lazy[index] = 0;

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

void lazyPropagate(int index, int l, int r)
{
    if (lazy[index] == 0)
        return;

    st[index] += (lazy[index] * (r - l + 1));

    if (l == r)
    {
        lazy[index] = 0;
        return;
    }

    lazy[index * 2] += lazy[index];
    lazy[index * 2 + 1] += lazy[index];

    lazy[index] = 0;
}

int query(int index, int curL, int curR, int queryL, int queryR)
{
    lazyPropagate(index, curL, curR);

    if (queryR < curL || queryL > curR)
        return idElement;

    if (queryL <= curL && queryR >= curR)
        return st[index];

    int mid = (curL + curR) / 2;

    return combine(query(2 * index, curL, mid, queryL, queryR),
                   query(2 * index + 1, mid + 1, curR, queryL, queryR));
}

void update(int index, int curL, int curR, int queryL, int queryR, int addVal)
{
    lazyPropagate(index, curL, curR);

    if (queryR < curL || queryL > curR)
        return;

    if (queryL <= curL && queryR >= curR)
    {
        lazy[index] += addVal;
        lazyPropagate(index, curL, curR);
        return;
    }

    int mid = (curL + curR) / 2;

    update(2 * index, curL, mid, queryL, queryR, addVal);
    update(2 * index + 1, mid + 1, curR, queryL, queryR, addVal);

    st[index] = combine(st[index * 2],
                        st[index * 2 + 1]);
}

void initSegmentTree(int n)
{
    for (int i = 0; i < n + 5; ++i)
        a[i] = 0;

    idElement = 0;

    build(1, 0, n - 1);
}
