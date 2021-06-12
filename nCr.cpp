// Code for finding nCr % MOD.
// Time Complexity - O(log MOD).

int nCr(int n, int r) {
    if(r == 0)
        return 1;
    return (fact[n] * modInverse(fact[r]) % MOD * modInverse(fact[n - r]) % MOD) % MOD;
}
