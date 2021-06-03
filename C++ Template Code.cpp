/*

    Author      : YASH SHARMA
    Institution : IIT PATNA
    Country     : INDIA

*/


#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("O3")
#pragma GCC target ("avx")

typedef long long ll;
typedef long double ld;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define fio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define minheap priority_queue<int,vector<int>,greater<int>>
#define print2d(dp,n,m) for(int i=0;i<n;i++){for(int j=0;j<m;j++)cout<<dp[i][j]<<" ";cout<<"\n";}
#define ftt int t;cin>>t;for(int tt=1;tt<=t;++tt)
#define Sum(v) accumulate(v.begin(),v.end(),(ll)0)
#define Rev(v) reverse(v.begin(),v.end());
#define Sort(v) sort(v.begin(),v.end());
#define Input(v) for(auto &x:v) cin>>x;
#define Output(v) for(auto x:v) cout<<x<<" ";
#define mem(a, b) memset(a, b, sizeof(a))
#define dbgx(x) cout<<"\nhi "<<x<<"\n"
#define double long double
#define int long long
#define maxheap priority_queue<int>
#define dbg cout<<"\nhi\n"
#define sayy cout<<"YES\n"
#define sayn cout<<"NO\n"
#define pii pair<int,int>
#define mii map<int,int>
#define umii unordered_map<int,int>
#define vii vector<pair<int,int>>
#define vvi vector<vector<int>>
#define vb vector<bool>
#define vi vector<int>
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define snd second
#define fst first
#define endl "\n"

const int INF   = numeric_limits<int>::max() / 2;
const double PI = 3.1415926535898;
const int MOD   = 1e9 + 7;
const int LIM   = 2e6 + 5;

// O(log y)
int fpow(int x, int y) {
    int temp;
    if (y == 0)
        return 1;
    temp = fpow(x, y / 2);
    if (y % 2 == 0)
        return (temp * temp) % MOD;
    else
        return (x * ((temp * temp) % MOD)) % MOD;
}

// O(log max(a, b))
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// O(n)
/*bool prime[5*LIM];
void sieve(int n) {
    memset(prime, true, sizeof(prime));
    for (int p=2; p*p<=n; p++)
        if (prime[p] == true)
            for (int i=p*p; i<=n; i += p)
                prime[i] = false;
    prime[1]=0;}*/

// O(sqrt(n))
bool isPrime(int n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

int modInverse(int n, int p) {
    return fpow(n, p - 2) % p;
}

/*int nCr(int n, int r, int p) {
    if(r == 0)
        return 1;
    return (fact[n] * modInverse(fact[r], p) % p * modInverse(fact[n - r], p) % p) % p;
}*/

// O(logn * sqrt(n))
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

void solve()
{

    return;
}


//*************************************************************************************************************************


int32_t main()
{   fio;

    ftt
    {
        solve();
    }

    return 0;
}
