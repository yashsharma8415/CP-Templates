// Code for finding prime factors of a number as a map with key as prime factor and value as its power.
// Time Complexity - O(logn * sqrt(n)).

map<int, int> primeFactors(int n) {
    map<int, int> mp;
    while (n % 2 == 0) {
        if (mp.count(2) == 1)
            mp[2]++;
        else
            mp.insert({2, 1});
        n = n / 2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            if (mp.count(i) == 1)
                mp[i]++;
            else
                mp.insert({i, 1});
            n = n / i;
        }
    }
    if (n > 2) {
        if (mp.count(n) == 1)
            mp[n]++;
        else
            mp.insert({n, 1});
    }
    return mp;
}
