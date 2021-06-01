// Code for Disjoint Set Union data structure.
// Amortized Time Complexity - O(1).
// Note: Amortized complexity is the total time per operation, evaluated over a sequence of multiple operations. A single call might take O(logn) in the worst case,
// but if we do m such calls back to back we will end up with an average time of O(α(n)). 

int parent[LIM], size[LIM];

int findSet(int v) 
{
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v]);
}

void makeSet(int v) 
{
    parent[v] = v;
    size[v] = 1;
}

void unionSets(int a, int b) 
{
    a = findSet(a);
    b = findSet(b);

    if (a != b) 
    {
        if (size[a] < size[b])
            swap(a, b);

        parent[b] = a;
        size[a] += size[b];
    }
}
