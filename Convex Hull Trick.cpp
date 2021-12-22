// Code for solving dp problems using convex hull trick when slopes and queries are given in sorted order.
// Time Complexity - O(n + q) where n is the number of lines and q is the number of queries.

struct line
{
    int m, c;

    int getValue(int x)
    {
        return m * x + c;
    }

    double intersectionX(line l)
    {
        return (c - l.c + 0.0) / (l.m - m);
    }
};

deque<line> dq;

int getIndex(int x)
{
    int l = 0, r = dq.size() - 1;

    while (l < r)
    {
        int mid = (l + r) / 2;

        if (x > dq[mid].intersectionX(dq[mid + 1]))
            l = mid + 1;
        else
            r = mid;
    }

    return l;
}

void convexHullTrick()
{
    dq.push_front(some initial line);

    for (int i = 0; i < n; i++)
    {
        while (dq.size() >= 2 && dq.back().getValue(x[i]) >= dq[dq.size() - 2].getValue(x[i]))
            dq.pop_back();

        int index = getIndex(x[i]);
        int val = dq[index].getValue(x[i]) + constant;
        ans = val;

        line cur = {make line from this x[i]};

        while (dq.size() >= 2 && cur.intersectionX(dq[0]) <= dq[0].intersectionX(dq[1]))
            dq.pop_front();

        dq.pop_front(cur);
    }

    return;
}
