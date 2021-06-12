// Code for finding modular multiplicative inverse of n under modulo MOD (works when MOD is prime).
// Time Complexity - O(log MOD).

int modInverse(int n) {
    return fpow(n, MOD - 2) % MOD;
}
