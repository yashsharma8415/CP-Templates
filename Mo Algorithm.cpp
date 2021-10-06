int numsqrt;

bool comp(vector<int>& p1, vector<int>& p2)
{
    if (p1[0] / numsqrt < p2[0] / numsqrt)
        return true;
    else if (p1[0] / numsqrt == p2[0] / numsqrt && p1[1] < p2[1])
        return true;
    else
        return false;
}

void moAlgorithm(vector<vector<int>>& v)
{
    numsqrt = sqrt(n);

    vi a(n);
    Input(a);

    int aans[q];

    sort(v.begin(), v.end(), comp);

    int l = 0, r = -1, ans = 0;

    for (auto ele : v)
    {
        int reql = ele[0], reqr = ele[1], index = ele[2];

        while (r > reqr)
        {
            // remove(r)
            r--;
        }

        while (r < reqr)
        {
            r++;
            // add(r)
        }

        while (l > reql)
        {
            l--;
            // add(l)
        }

        while (l < reql)
        {
            // remove(l)
            l++;
        }

        aans[index] = ans;
    }

    return;
}
